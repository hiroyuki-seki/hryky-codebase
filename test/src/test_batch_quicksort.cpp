/*
  @file         test_batch_quicksort.cpp
  @brief        tests hryky::batch module by quick-sort.
  @author       HRYKY
  @version      $Id: test_batch_quicksort.cpp 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
 */
#include <precompiled.h>
#include "hryky/batch.h"
#include "hryky/testing.h"
#include "hryky/clock.h"
#include "hryky/random.h"
#include "hryky/thread.h"
#include "hryky/integer.h"
#include "hryky/qsort.h"
#include "hryky/task.h"
#include "hryky/scoped_array.h"
#include "hryky/memory.h"
#include "hryky/mempool.h"
#include "hryky/stream.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
#define PRINT_VERBOSELY     (0)
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace batch
{
namespace
{
	// enregister a test
	class Test : testing::unit::Base
	{
	public :
		typedef testing::unit::Base base_type;
		typedef Test this_type;
		
		Test()
			: testing::unit::Base("batch_quicksort")
		{
		}

	private :
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		// tests hryky::batch module by using quicksort concurrently.
		virtual bool run_impl();

	};
	Test const g_test;
	
	typedef uint32_t sample_type;

	// a task to print "hello ${this->id_}".
	struct Sort :
		public WithStreamOut<Sort>
	{
		typedef batch::Worker<Sort> worker_type;

		enum
		{
			// the lower number to create a new task recursively.
			distributable_distance_ = 0x2,
		};
		
		Sort() : begin_(hryky_nullptr), end_(hryky_nullptr) {}
		
		Sort(sample_type * begin, sample_type * end)
			: begin_(begin), end_(end) {}

		// sorts fixed array concurrently
		void operator()(worker_type & worker);

		/// outputs the information of Sort.
		template <typename StreamT>
		StreamT & write_to(StreamT & out) const;

		sample_type *   begin_;
		sample_type *   end_;
	};

	// typedef function_pointer task_type;
	typedef Sort                        task_type;
	typedef task_type::worker_type      worker_type;

} // namespace *anonymous*
} // namespace batch
} // namespace hryky
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace batch
{
namespace
{
/**
  @brief tests hryky::batch module by quicksort.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes a random number generator
	testing::Random random;

	log.writer() << "random" << random;

	// randomizes the number of tasks which one worker can dispose at once.
	random::Normal<size_t> grab_size_dist(
		random.generator(),
		0x10 >> 1,  // deviation
		0x10,       // mean
		1,          // min
		0x10 << 4); // max
	size_t const grab_size = grab_size_dist();

	(log.writer()
	<< stream::denote("grab_size") << grab_size
	<< stream::denote("grab_size_dist") << grab_size_dist);

	// randomizes the number of the sorted values.
	random::Normal<size_t> samples_size_dist(
		random.generator(),
		0x1000,     // deviation
		0x10000,    // mean
		1,          // min
		0x100000);  // max
	size_t const samples_size = samples_size_dist();

	(log.writer()
	<< stream::denote("samples_size") << samples_size
	<< stream::denote("samples_size_dist") << samples_size_dist);

	typedef sample_type                     value_type;
	typedef mempool::Array<sample_type>::type  samples_type;
	typedef samples_type::const_reference   const_reference;
	typedef samples_type::reference         reference;
	typedef samples_type::size_type         size_type;

	samples_type sorted =
		mempool::global::array<sample_type>(samples_size);

	if (sorted.is_null()) {
		hryky_log_alert(
			"failed to allocate the buffer of samples.");
		return false;
	}

	samples_type answer =
		mempool::global::array<sample_type>(samples_size);

	if (answer.is_null()) {
		hryky_log_alert(
			"failed to allocate the buffer of samples.");
		return false;
	}

	// prepares sample values
	{
		// pseudo random number uniformly distributed
		random::Uniform<uint32_t>
			sample_dist(random.generator(), 0, MaxOf<uint32_t>::value);

		sorted.foreach([&sample_dist](reference element) {
			element = sample_dist();
		});
	}

#if PRINT_VERBOSELY
	{
		log.writer() << stream::denote("sorted");
		testing::Log::array_type const array(log.writer());

		sorted.foreach([&log](const_reference element) {
			log.writer() << element;
		});
	}
#endif // PRINT_VERBOSELY

	memcpy(
		&*answer.begin(),
		&*sorted.begin(),
		sizeof(sample_type) * samples_size);

	// sorts the samples in this individual context.
	clock::duration_type qsort_duration;
	{
		auto stream = ostream::assign(qsort_duration);
		auto const elapse = clock::auto_elapse(stream);

		hryky::qsort(
			answer.begin(),
			answer.begin()
			+ static_cast<samples_type::difference_type>(samples_size));
	}

#if PRINT_VERBOSELY
	{
		log.writer() << stream::denote("answer");
		testing::Log::array_type const array(log.writer());

		answer.foreach([&log](const_reference element) {
			log.writer() << element;
		});
	}
#endif // PRINT_VERBOSELY

	// checks the result of sorting.
	{
		sample_type left = 0;

		if (!answer.every_at([&left](
			const_reference element, size_type const index) {
			if (left > element) {
				hryky_log_err(
					"quick sort failed "
					<< (json::writer()
					<< stream::denote("index") << index));
				return false;
			}
			left = element;
			return true;
		})) {
			hryky_log_err("The result is invalid" << answer);
			return false;
		}
	}

	samples_type parallel =
		mempool::global::array<sample_type>(samples_size);

	if (parallel.is_null()) {
		hryky_log_alert(
			"failed to allocate the buffer of samples.");
		return false;
	}
	memcpy(
		&*parallel.begin(),
		&*sorted.begin(),
		sizeof(sample_type) * samples_size);

	/**
	  creates the default pool of thread resources.
	 */
	thread::pool_type thread_pool;
	thread::pool::registry_type const enregister_thread_pool(&thread_pool);

	/**
	  creates the default factory for concurrent units.
	 */
	task::factory_type task_factory;
	task::factory_registry_type const enregister_task_factory(&task_factory);

	/**
	  creates the default facility to control the flow of tasks.
	 */
	flow::facility_type flow_facility;
	flow::facility_registry_type const
		enregister_flow_facility(&flow_facility);

	// initializes a facility to dispose plenty of same tasks.
	batch::Facility<Sort> batch;
	
	batch.grab_size(grab_size);
	
	// sorts the samples by concurrent units
	clock::duration_type concurrent_qsort_duration;
	{
		auto stream = ostream::assign(concurrent_qsort_duration);
		auto const elapse = clock::auto_elapse(stream);

		// distributes tasks to workers.
		if (!batch.distribute(
			task_type(&*parallel.begin(), &*parallel.end())))
		{
			hryky_log_alert(
				"failed to distribute a task");
			return false;
		}

		// attaches tasks to concurrent units(threads).
		if (!batch.attach()) {
			hryky_log_alert(
				"failed to attach workers to concurrent units");
			return false;
		}

		// waits to complete the execution of the tasks.
		if (!batch.join(exclusion::duration_type(
			exclusion::g_default_duration))) {
			hryky_log_alert(
				"failed to wait that the workers complete tasks");
			return false;
		}
	}

#if PRINT_VERBOSELY
	{
		log.writer() << stream::denote("parallel");
		testing::Log::array_type const array(log.writer());

		parallel.foreach([&log](const_reference element) {
			log.writer() << element;
		});
	}
#endif // PRINT_VERBOSELY

	// checks the sorted result
	{
		sample_type left = 0;

		if (!parallel.every_at([&left](
			const_reference element, size_type const index) {
			if (left > element) {
				hryky_log_err(
					"concurrent quick-sort failed "
					<< (json::writer()
					<< stream::denote("index") << index
					<< stream::denote("lhs") << left
					<< stream::denote("rhs") << element));
				return false;
			}
			left = element;
			return true;
		})) {
			hryky_log_err("The sorted result is invalid " << parallel);
			return false;
		}
	}

	(log.writer()
	 << stream::denote("batch") << batch
	 << stream::denote("qsort_duration")
	 << qsort_duration.count()
	 << stream::denote("concurrent_qsort_duration")
	 << concurrent_qsort_duration.count()
	 << stream::denote("concurrent ratio")
	 << (static_cast<double>(qsort_duration.count())
		 / concurrent_qsort_duration.count())
	 );

	return true;
}
/**
  @brief sorts fixed array concurrently.
 */
void Sort::operator()(worker_type & worker)
{
	sample_type * const boundary =
		hryky::qsort_internal::partition(this->begin_, this->end_);

	if (boundary == this->end_) {
		return;
	}

	batch::Facility<Sort> & batch = worker.facility();

	size_t const first_distance = static_cast<size_t>(
		boundary - this->begin_);
	size_t const second_distance = static_cast<size_t>(
		this->end_ - boundary);

	if (Sort::distributable_distance_ > first_distance) {
		if (Sort::distributable_distance_ > second_distance) {
			// sorts the last half of the region in this thread.
			hryky::qsort(boundary, this->end_);
		}
		else {
			// sorts the last half of the region concurrently.
			if (!batch.attach_with(Sort(boundary, this->end_))) {
				hryky_log_alert(
					"failed to execute a task to sort the last half of the region "
					<< (json::writer()
					<< stream::denote("boundary") << boundary));
				worker.error();
				return;
			}
		}
		// sorts the first half of the region in this thread.
		hryky::qsort(this->begin_, boundary);
	}
	else if (Sort::distributable_distance_ > second_distance) {
		// sorts the first half of the region concurrently.
		if (!batch.attach_with(Sort(this->begin_, boundary))) {
			hryky_log_alert(
				"failed to execute a task to sort the first half of the region "
				<< (json::writer()
				<< stream::denote("boundary") << boundary));
			worker.error();
			return;
		}

		// sorts the last half of the region in this thread.
		hryky::qsort(boundary, this->end_);
	}
	else if (first_distance > second_distance) {
		// sorts the first half of the region concurrently.
		if (!batch.attach_with(Sort(this->begin_, boundary))) {
			hryky_log_alert(
				"failed to execute a task to sort the first half of the region "
				<< (json::writer()
				<< stream::denote("boundary") << boundary));
			worker.error();
			return;
		}

		// sorts the last half of the region in this thread.
		hryky::qsort(boundary, this->end_);
	}
	else {
		// sorts the last half of the region concurrently.
		if (!batch.attach_with(Sort(boundary, this->end_))) {
			hryky_log_alert(
				"failed to execute a task to sort the last half of the region "
				<< (json::writer()
				<< stream::denote("boundary") << boundary));
			worker.error();
			return;
		}

		// sorts the first half of the region in this thread.
		hryky::qsort(this->begin_, boundary);
	}

	return;
}
/**
  @brief outputs the information of Sort.
 */
template <typename StreamT>
StreamT &
Sort::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(begin);
	hryky_write_member(end);
	
	return out;
}
} // namespace *anonymous*
} // namespace batch
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
