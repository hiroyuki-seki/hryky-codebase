/**
  @file     test_event.cpp
  @brief    tests hryky::event module.
  @author   HRYKY
  @version  $Id: test_event.cpp 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/event.h"
#include "hryky/exclusion.h"
#include "hryky/window.h"
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

		/// tests hryky::event module.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "event";

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
  @brief tests hryky::event module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	// creates window
	window::Context const window_context;
	if (hryky_is_null(window_context)) {
		hryky_log_alert("failed to create window");
		return false;
	}

	event::Facility event;
	event.on_draw([&window_context]() {
		window_context.update();
		return true;
	});
	if (!event.run(chrono::seconds(5u))) {
		hryky_log_alert("failed to handle events.");
		return false;
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
