/*
  @file         test_mempool_lock.cpp
  @brief        tests hryky::mempool::Lock.
  @author       HRYKY
  @version      $Id: test_mempool_lock.cpp 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/memory.h"
#include "hryky/random.h"
#include "hryky/scoped_array.h"
#include "hryky/batch.h"
#include "hryky/task.h"
#include "hryky/thread.h"
#include "hryky/common.h"
#include "hryky/foreach.h"
#include "hryky/raii.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace
{
	// enregisters a test
	class Test : public testing::unit::Base
	{
	public :
		typedef testing::unit::Base base_type;
		typedef Test this_type;
		
		Test()
			: testing::unit::Base("mempool_lock")
		{
		}
		
	private :
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		// creates the instances of mempool::Lock and tests them.
		virtual bool run_impl();

	};
	Test const g_test;

	// task to allocates memory
	struct Allocate :
		public WithStreamOut<Allocate>
	{
		typedef batch::Worker<Allocate> worker_type;
		typedef void * address_type;

		Allocate()
			: mempool_()
			  , address_()
			  , size_(0)
		{}

		Allocate(
			mempool::Base & mempool,
			address_type & address,
			size_t size)
			: mempool_(&mempool)
			  , address_(&address)
			  , size_(size)
		{}

		void operator()(worker_type &)
		{
			*this->address_ = this->mempool_->allocate(this->size_);
		}

		/// outputs the information of Allocate.
		template <typename StreamT>
		StreamT & write_to(StreamT & out) const;

	private :
		mempool::Base *    mempool_;
		address_type *          address_;
		size_t                  size_;
	};
	
	// task to allocates memory
	struct Deallocate :
		public WithStreamOut<Deallocate>
	{
		typedef batch::Worker<Deallocate> worker_type;
		typedef void * address_type;

		Deallocate()
			: mempool_()
			  , address_()
		{}

		Deallocate(
			mempool::Base & mempool,
			address_type & address)
			: mempool_(&mempool)
			  , address_(&address)
		{}

		void operator()(worker_type &)
		{
			if (!hryky_is_null(*this->address_)) {
				this->mempool_->deallocate(*this->address_);
				*this->address_ = hryky_nullptr;
			}
		}

		/// outputs the information of Deallocate.
		template <typename StreamT>
		StreamT & write_to(StreamT & out) const;

	private :
		mempool::Base *    mempool_;
		address_type *          address_;
	};

} // namespace *anonymous*
} // namespace hryky
//------------------------------------------------------------------------------
// global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace
{
/**
  @brief creates the instances of hryky::mempool::Lock and tests them.
 */
bool Test::run_impl()
{
	// initializes log
	testing::Log log(*this);

	// initializes a random number generator
	testing::Random random;
	// random.seed(1364713083);
	log.writer() << "random" << random;

	// randomizes the number of allocations.
	size_t const allocations_size = random::Uniform<size_t>(
		random.generator(),
		0x400u,     // min
		0x8000u    // max
		)();
	log.writer() << "allocations_size" << allocations_size;

	// randomizes the size of the allocated memory.
	size_t const buffer_size = random::Normal<size_t>(
		random.generator(),
		0x1000,         // deviation
		0x400000,       // mean
		0x20000000,      // min
		0x20000000       // max
		)();
	log.writer() << "buffer_size" << buffer_size;

	// randomizes the size of batch disposal for allocations.
	size_t const allocation_grab_size = random::Normal<size_t>(
		random.generator(),
		0x10 >> 1,  // deviation
		0x10,       // mean
		1,          // min
		0x10 << 4   // max
		)();
	log.writer() << "allocation_grab_size" << allocation_grab_size;

	// randomizes the size of batch disposal for deallocations.
	size_t const deallocation_grab_size = random::Normal<size_t>(
		random.generator(),
		0x10 >> 1,  // deviation
		0x10,       // mean
		1,          // min
		0x10 << 4   // max
		)();
	log.writer() << "deallocation_grab_size" << deallocation_grab_size;

	void * buffer = ::std::malloc(buffer_size);
	if (hryky_nullptr == buffer) {
		hryky_log_alert(
			"failed to allocate buffer for the test of memory::Pool::Arbitrary "
			<< (json::writer()
			<< stream::denote("buffer_size") << buffer_size));
		return false;
	}
	AutoFree const free_buffer(buffer);

	// initializes memory pool.
	mempool::Adapter<
		mempool::Lock<mempool::Arbitrary<> > > mempool;
	if (!mempool.get()->get()->reset(buffer, buffer_size)) {
		hryky_log_alert(
			"failed to reset mempool::Arbitrary "
			<< (json::writer()
			<< stream::denote("buffer_size") << buffer_size));
		return false;
	}

	if (!mempool.get()->get()->verify()) {
		hryky_log_alert(
			"Verification failed "
			<< (json::writer()
			<< stream::denote("mempool") << mempool));
		return false;
	}

	/**
	  initialies the default thread mempool.
	 */
	thread::pool_type thread_pool;
	thread::pool::registry_type const enregister_thread_pool(&thread_pool);

	/**
	  initializes the default factory to provide concurrens units.
	 */
	task::factory_type task_factory(&mempool);
	task::factory_registry_type const enregister_task_factory(&task_factory);

	/**
	  initializes the default facility to control the flow of tasks.
	 */
	flow::facility_type flow_facility(&mempool);
	flow::facility_registry_type const
		enregister_flow_facility(&flow_facility);

	typedef mempool::Array<void *>::type   allocations_type;
	typedef allocations_type::size_type size_type;
	typedef allocations_type::reference reference;
	
	allocations_type allocations =
		mempool::global::array<void *>(allocations_size);
	if (allocations.is_null()) {
		hryky_log_alert(
			"failed to allocate buffer for allocation "
			<< (json::writer()
			<< stream::denote("allocations_size") << allocations_size));
		return false;
	}
	hryky::memset(&*allocations.begin(), 0x00u, allocations.size() * sizeof(void*));

	// executes task for memory allocation.
	{
		typedef Allocate                task_type;

		// initializes a facility to dispose plenty of same tasks.
		batch::Facility<Allocate> batch(&mempool);
		
		batch.grab_size(allocation_grab_size);
		
		random::Normal<size_t> allocation_size(
			random.generator(),
			0x100,  // deviation
			0x400,  // mean
			0x1,    // min
			0x4000  // max
			);

		if (!allocations.every_at([&batch, &mempool, &allocation_size](
			reference allocation, size_type const index) {
			if (!batch.distribute(
				task_type(mempool, allocation, allocation_size()))) {
				hryky_log_alert(
					"failed to distribute a task "
					<< (json::writer()
					<< stream::denote("index") << index));
				return false;
			}
			return true;
		})) {
			return false;
		}

		// attaches tasks to concurrent units(threads).
		if (!batch.attach()) {
			hryky_log_alert("failed to attach workers to concurrent units");
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

	if (!mempool.get()->get()->verify()) {
		hryky_log_alert(
			"Verification failed "
			<< (json::writer()
			<< stream::denote("mempool") << mempool));
		return false;
	}

	// executes task for memory deallocation.
	{
		typedef Deallocate task_type;

		// initializes a facility to dispose plenty of tasks.
		batch::Facility<Deallocate> batch(&mempool);
		
		batch.grab_size(deallocation_grab_size);

		if (!allocations.every_at([&batch, &mempool](
			reference allocation, size_type const index) {
			if (!batch.distribute(
				task_type(mempool, allocation))) {
				hryky_log_alert(
					"failed to distribute a task of deallocation "
					<< (json::writer()
					<< stream::denote("index") << index
					));
				return false;
			}
			return true;
		})) {
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

	log.writer() << "mempool" << mempool;

	if (!mempool.get()->get()->verify()) {
		hryky_log_alert(
			"Verification failed "
			<< (json::writer()
			<< stream::denote("mempool") << mempool));
		return false;
	}

	return true;
}
/**
  @brief outputs the information of Allocate.
 */
template <typename StreamT>
StreamT &
Allocate::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(address);
	hryky_write_member(size);
	return out;
}
/**
  @brief outputs the information of Deallocate.
 */
template <typename StreamT>
StreamT &
Deallocate::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(address);
	return out;
}
} // namespace *anonymous*
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
