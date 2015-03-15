/**
  @file     test_chrono.cpp
  @brief    tests hryky::chrono.
  @author   HRYKY
  @version  $Id: test_chrono.cpp 369 2014-07-20 21:33:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/chrono.h"
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

		/// tests hryky::chrono.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "chrono";

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
  @brief tests hryky::chrono.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	chrono::seconds one_sec(1);

	static_assert(
		1 == chrono::nanoseconds::period::num,
		"numerator of nanoseconds is 1");
	static_assert(
		1000000000 == chrono::nanoseconds::period::den,
		"denominator of nanoseconds is 1000000000");

	{
		(log.writer()
		 << "sec" << one_sec
		 << "msec" << chrono::milliseconds(one_sec)
		 << "usec" << chrono::microseconds(one_sec)
		 << "nsec" << chrono::nanoseconds(one_sec)
		 << "minutes" << chrono::fminutes(one_sec)
		 << "hours" << chrono::fhours(one_sec)
		 << "days" << chrono::fdays(one_sec)
		 << "weeks" << chrono::fweeks(one_sec));
	}

	{
		chrono::seconds thirty(30);
		
		(log.writer()
		 << "nsec" << chrono::nanoseconds(thirty)
		 );
	}

	{
		log.writer() << "sec1.0" << chrono::Duration<float>(1);
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
