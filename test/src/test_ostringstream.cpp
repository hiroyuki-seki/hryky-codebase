/**
  @file     test_ostringstream.cpp
  @brief    tests hryky::ostream::String.
  @author   HRYKY
  @version  $Id: test_ostringstream.cpp 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
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
		
		/// tests hryky::ostream::String.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "ostringstream";

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
  @brief tests hryky::ostream::String.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	ostream::String<String<> > stream;

	(stream << endl <<
	 "foobar" << endl <<
	 0 << endl <<
	 1 << endl <<
	 -1 << endl <<
	 0.0f << endl <<
	 1.0f << endl <<
	 1.0 << endl <<
	 2.0f << endl <<
	 2.0 << endl <<
	 3.0f << endl <<
	 3.0 << endl <<
	 -1.0f << endl <<
	 -0.1f << endl <<
	 0.1f << endl <<
	 100.1f << endl <<
	 1000000.1f << endl <<
	 100000000.1f << endl <<
	 0.01f << endl <<
	 0.0001f << endl <<
	 1.0000001f << endl);

	log.writer() << "result" << stream.str();

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
