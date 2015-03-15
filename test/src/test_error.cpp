/**
  @file         test_error.cpp
  @brief        tests to invoke errors and retrieve them.
  @author       HRYKY
  @version      $Id: test_error.cpp 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/error.h"
#include "hryky/testing.h"
#include "hryky/memory.h"
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
	// enregisters a test
	class Test : testing::unit::Base
	{
	public :
		typedef testing::unit::Base base_type;
		typedef Test this_type;
		
		/// constructor.
		Test();

	private :
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		/// tests to access atomic values.
		virtual bool run_impl();

		/// tests all operators.
		template < typename AtomicT >
		bool test_integer(typename AtomicT::value_type const & value);

	};
	Test const g_test;

	char const * g_testname = "error";
	
} // namespace "anonymous"
} // namespace test
} // namespace hryky
//------------------------------------------------------------------------------
// global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace test
{
namespace
{
/**
  @brief constructor.
 */
Test::Test()
	: base_type(g_testname)
{
	return;
}
/**
  @brief tests to invoke errors and retrieve them.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	{
		error_type const error;
		log.writer() << "errorNone" << error;
	}

	{
		error_type const error = error::string("test");
		log.writer() << "errorString" << error;
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
