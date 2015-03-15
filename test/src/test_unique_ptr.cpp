/**
  @file     test_unique_ptr.cpp
  @brief    tests unique_ptr.
  @author   HRYKY
  @version  $Id: test_unique_ptr.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/unique_ptr.h"
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
namespace unique
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
		
		/// tests unique_ptr.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "unique_ptr";

} // namespace "anonymous"
} // namespace unique
} // namespace test
} // namespace hryky
namespace hryky
{
namespace test
{
namespace unique
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
  @brief tests unique_ptr.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	{
		auto int_ptr = mempool::global::instantiate<int>();
	}

	{
		auto int_ptr = mempool::global::array<int>(3);
	}

	return true;
}
} // namespace "anonymous"
} // namespace unique
} // namespace test
} // namespace hryky
