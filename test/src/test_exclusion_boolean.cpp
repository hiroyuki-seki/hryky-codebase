/**
  @file     test_exclusion_boolean.cpp
  @brief    tests exclusion::Boolean.
  @author   HRYKY
  @version  $Id: test_exclusion_boolean.cpp 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/exclusion.h"
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
		
		/// tests exclusion::Boolean.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "exclusion_boolean";

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
  @brief tests exclusion::Boolean.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	/**
	  creates the default pool of thread resources.
	 */
	thread::pool_type thread_pool;
	thread::pool::registry_type const enregister_thread_pool(&thread_pool);

	typedef exclusion::Boolean<> boolean_type;

	{
		exclusion::Variable<bool> failure;
	
		boolean_type first, second;
		if (!thread_pool.run([&first, &second, &failure]() {
			auto fail = auto_call([&failure]() {
				failure = true;
			});
			if (!first.wait_true(chrono::seconds(5))) {
				hryky_log_err(
					"failed to wait the update of the first boolean");
				return;
			}
			second.enable();
			
			fail.disable();
		})) {
			hryky_log_alert("failed to execute a function asynchronously.");
			return false;
		}

		first.enable();
		if (!second.wait_true(chrono::seconds(5))) {
			hryky_log_err(
				"failed to wait the update of the second boolean");
			return false;
		}

		if (failure) {
			hryky_log_alert("Some sequence failed.");
			return false;
		}
	}

	{
		exclusion::Variable<bool> failure;
		
		boolean_type first(true), second(true);
		if (!thread_pool.run([&first, &second, &failure]() {
			auto fail = auto_call([&failure]() {
				failure = true;
			});
			if (!first.wait_false(chrono::seconds(5))) {
				hryky_log_err(
					"failed to wait the update of the first boolean");
				return;
			}
			second = false;
			
			fail.disable();
		})) {
			hryky_log_alert("failed to execute a function asynchronously.");
			return false;
		}

		first = false;
		if (!second.wait_false(chrono::seconds(5))) {
			hryky_log_err(
				"failed to wait the update of the second boolean");
			return false;
		}

		if (failure) {
			hryky_log_alert("Some sequence failed.");
			return false;
		}
	}


	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
