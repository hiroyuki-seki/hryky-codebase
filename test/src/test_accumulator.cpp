/**
  @file         test_accumulator.cpp
  @brief        tests the hryky::accumulator module.
  @author       HRYKY
  @version      $Id: test_accumulator.cpp 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/accumulator.h"
#include "hryky/thread.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace test
{
namespace
{
	// enretisters a test.
	class Test : testing::unit::Base
	{
	public:
		typedef testing::unit::Base base_type;
		typedef Test this_type;

		/// constructor.
		Test();

	private:
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		/// tests the hryky::accumulator module.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "accumulator";

} // namespace "anonymous"
} // namespace test
} // namespace hryky
namespace hryky
{
namespace test
{
namespace
{
//------------------------------------------------------------------------------
// public member functions of Test
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
Test::Test()
	: base_type(g_testname)
{
}
//------------------------------------------------------------------------------
// private member functions of Test
//------------------------------------------------------------------------------
/**
  @brief tests the hryky::accumulator module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	// random.seed(1364559326);
	log.writer() << "random" << random;

	typedef size_t value_type;

	// randomizes the number of accumulated values.
	random::Uniform<value_type> values_size_dist(
		random.generator(), 0x1, 0x1000000);

	size_t const values_size = values_size_dist();
	log.writer() << "values_size" << values_size;

	/**
	  randomizes the maximum number of accumulated values by one
	  concurrent task.
	 */
	random::Uniform<value_type> accumulations_size_dist(
		random.generator(), 0x100, 0x100 + values_size);

	size_t const accumulations_size = accumulations_size_dist();
	log.writer() << "accumulations_size" << accumulations_size;

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

	typedef Vector<size_t> values_type;

	Vector<size_t> values;
	if (!values.resize(values_size)) {
		hryky_log_alert(
			"failed to allocate the buffer for accumulated values.");
		return false;
	}

	// initializes accumulated values.
	{
		values.foreach_at([](
			values_type::reference element, size_t const index) {
			element = index + 1;
		});
	}

	accumulator::Facility<values_type::iterator> accumulator;

	if (!accumulator.accumulate(
		values.begin(), values.end(), accumulations_size)) {
		hryky_log_alert(
			"failed to start accumulating values.");
		return false;
	}

	accumulator.join();

	size_t const result = accumulator.result();
	size_t const answer = ((values_size + 1) * values_size) >> 1;

	if (answer != result) {
		hryky_log_alert(
			"The result is wrong. "
			<< (json::writer()
			<< stream::denote("result") << result
			<< stream::denote("answer") << answer));
		return false;
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky

