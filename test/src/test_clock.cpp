/**
  @file     test_clock.cpp
  @brief    tests hryky::clock.
  @author   HRYKY
  @version  $Id: test_clock.cpp 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/clock.h"
#include "hryky/chrono.h"
#include "hryky/stream.h"
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

		/// tests hryky::clock.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "clock";

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
  @brief tests hryky::clock.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	{
		log.writer() << "test1";
		auto elapse = clock::auto_elapse(log.writer());
	}

	{
		chrono::fmilliseconds duration;
		{
			auto stream = ostream::assign(duration);
			auto elapse = clock::auto_elapse(stream);
		}
		log.writer() << "test2" << duration.count();
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
