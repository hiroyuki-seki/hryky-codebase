/**
  @file     test_filesystem.cpp
  @brief    tests hryky::filesystem module.
  @author   HRYKY
  @version  $Id: test_filesystem.cpp 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
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

		/// tests hryky::filesystem module.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "filesystem";

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
  @brief tests hryky::filesystem module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
