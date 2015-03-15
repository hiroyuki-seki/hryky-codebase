/*
  @file         test_batch_hello.cpp
  @brief        tests hryky::batch module by printing a string.
  @author       HRYKY
  @version      $Id: test_batch_hello.cpp 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#include <precompiled.h>
#include "hryky/batch.h"
#include "hryky/task.h"
#include "hryky/testing.h"
#include "hryky/thread.h"
#include "hryky/random.h"
#include "hryky/memory.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace batch
{
namespace
{
	// enregisters a test.
	class Test : testing::unit::Base
	{
	public :
		typedef testing::unit::Base base_type;
		typedef Test this_type;
		
		Test()
			: testing::unit::Base("batch_hello")
		{
		}

	private :
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		// tests hryky::batch module by printing strings concurrently.
		virtual bool run_impl();
	};
	Test const g_test;

	// a task to print "hello ${this->id_}".
	struct Hello :
		public WithStreamOut<Hello>
	{
		typedef batch::Worker<Hello> worker_type;
		
		Hello() : id_() {}
		
		Hello(size_t id) : id_(id) {}

		void operator()(worker_type &);

		/// outputs the information of Hello.
		template <typename StreamT>
		StreamT & write_to(StreamT & out) const;

		size_t id_;
	};

} // namespace anonymous
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
  @brief tests hryky::batch module by printing strings concurrently.
 */
bool Test::run_impl()
{
	// initializes logging
	testing::Log log(*this);

	// initializes a random number generator
	testing::Random random;

	log.writer() << "random" << random;

	// randomizes the number of tasks
	random::Normal<size_t>
		tasks_size_dist(random.generator(), 0x1000);
	(tasks_size_dist
	 .mean(0x100)
	 .min(1)
	 .max(0x100000));
	
	size_t const tasks_size = tasks_size_dist();

	(log.writer()
	 << "tasks_size" << tasks_size
	 << "tasks_size_dist" << tasks_size_dist
	 );

	// randomizes the number of tasks which one worker can dispose at once.
	random::Normal<size_t>
		grab_size_dist(
			random.generator(), ::std::max<size_t>(1, tasks_size >> 2));
	(grab_size_dist
	 .mean(tasks_size >> 1)
	 .min(1)
	 .max(tasks_size));

	size_t const grab_size = grab_size_dist();

	(log.writer()
	 << "grab_size" << grab_size
	 << "grab_size_dist" << grab_size_dist
	 );

	/**
	  creates the default pool of thread resources.
	 */
	thread::pool_type thread_pool;
	thread::pool::registry_type const enregister_thread_pool(&thread_pool);

	/**
	  creates the default factory to provide concurrent units.
	 */
	task::factory_type task_factory;
	task::factory_registry_type const enregister_task_factory(&task_factory);

	/**
	  creates the default facility to control the flow of tasks.
	 */
	flow::facility_type flow_facility;
	flow::facility_registry_type const
		enregister_flow_facility(&flow_facility);

	// initializes the facility to dispose plenty of same tasks.
	batch::Facility<Hello> batch;
	
	batch.grab_size(grab_size);

	// distributes tasks to workers.
	size_t task_id = 0;
	for (; tasks_size != task_id; ++task_id) {
		if (!batch.distribute(Hello(task_id))) {
			hryky_log_crit(
				"failed to append a task "
				<< (json::writer()
					<< "task_id" << task_id));
			return false;
		}
	}

	// attaches the workers to concurrent units.
	if (!batch.attach()) {
		hryky_log_crit("failed to attach workers to concurrent units");
		return false;
	}

	// waits until the completion of tasks.
	if (!batch.join(chrono::minutes(1u))) {
		hryky_log_crit(
			"failed to wait that the workers complete tasks");
		return false;
	}

	return true;
}
/**
  @brief prints "hello this->id_".
 */
void Hello::operator()(worker_type &)
{
	hryky_log_debug(
		(json::writer() << "hello" << *this));
}
/**
  @brief outputs the information of Hello.
 */
template <typename StreamT>
StreamT &
Hello::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(id);
	return out;
}
} // namespace *anonymous*
} // namespace batch
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
