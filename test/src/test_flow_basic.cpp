/**
  @file         test_flow_basic.cpp
  @brief        tests the basic function of hryky::flow.
  @author       HRYKY
  @version      $Id: test_flow_basic.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/flow.h"
#include "hryky/task.h"
#include "hryky/testing.h"
#include "hryky/thread.h"
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
		
		/// tests the basic function of hryky::flow.
		virtual bool run_impl();

		/// tests a unit of flows.
		bool test_flow(testing::Log & log, testing::Random & random);

	};
	Test const g_test;

	char const * const g_testname = "flow_basic";

} // namespace "anonymous"
} // namespace hryky
namespace hryky
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
  @brief tests the basic function of hryky::flow.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	size_t repeat = 100;
	do {
		if (!this->test_flow(log, random)) {
			return false;
		}
	} while (0 < --repeat);

	return true;
}
/**
  @brief tests a unit of flows.
 */
bool Test::test_flow(testing::Log &, testing::Random &)
{
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

	typedef flow::node_type node_type;

	/**
	  creates the default facility to dispose the flow of tasks.
	 */
	flow::facility_type flow_facility;
	flow::facility_registry_type const
		enregister_flow_facility(&flow_facility);

	node_type func_a = flow::function([] (node_type const &) {
		hryky_log_debug("func_a");
		return flow::next;
	});
	func_a->attach();

	node_type func_b = flow::function([] (node_type const &) {
		hryky_log_debug("func_b");
		return flow::next;
	});

	node_type func_c = flow::function([] (node_type const &) {
		hryky_log_debug("func_c");
		return flow::next;
	});

	node_type func_d = flow::function([] (node_type const &) {
		hryky_log_debug("func_d");
		return flow::next;
	});
	func_d->call([] (node_type const &){
		hryky_log_debug("func_e");
		return flow::next;
	})->call([] (node_type const &){
		hryky_log_debug("func_f");
		return flow::next;
	});

	size_t counter = 0;
	node_type func_g = flow::function([&counter] (node_type const &) {
		hryky_log_debug("func_g");
		if (10 < ++counter) {
			return flow::next;
		}
		return flow::again;
	});

	node_type func_h = flow::function([] (node_type const &) {
		hryky_log_debug("func_h");
		return flow::next;
	});
	func_h->append(flow::function([](node_type const&) {
		hryky_log_debug("func_i");
		return flow::next;
	}))->append(flow::function([](node_type const&) {
		hryky_log_debug("func_j");
		return flow::next;
	}));

	func_a->append(func_b);
	func_c->attach();
	func_d->attach();
	func_g->attach();
	func_h->attach();

	flow::join()->join(func_g, func_h)->call([] (node_type const &) {
		hryky_log_debug("func_k");
		return flow::next;
	});

	return true;
}
} // namespace "anonymous"
} // namespace hryky
