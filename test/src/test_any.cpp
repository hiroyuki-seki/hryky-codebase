/**
  @file         test_any.cpp
  @brief        tests for retantion of arbitrary types.
  @author       HRYKY
  @version      $Id: test_any.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/any.h"
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
		
		/// tests for retantion of arbitrary types.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "any";

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
  @brief tests for retantion of arbitrary types.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	typedef Any<> any_type;

	any_type any;

	any = any_type(0);
	if (0 != any.cast<int32_t>()) {
		hryky_log_err("signed integer is not assigned.");
		return false;
	}
	
	any = any_type(0u);
	if (0u != any.cast<uint32_t>()) {
		hryky_log_err("unsigned integer is not assigned.");
		return false;
	}
	
	any = any_type(1);
	if (1 != any.cast<int32_t>()) {
		hryky_log_err("positive integer is not assigned.");
		return false;
	}
	
	any = any_type(-1);
	if (-1 != any.cast<int32_t>()) {
		hryky_log_err("negative integer is not assigned.");
		return false;
	}
	
	any = any_type(1.0f);
	if (1.0f != any.cast<float>()) {
		hryky_log_err(
			"single precision floating-point number is not assigned.");
		return false;
	}
	
	any = any_type(1.0);
	if (1.0 != any.cast<double>()) {
		hryky_log_err(
			"double precision floating-point number is not assigned.");
		return false;
	}

	any = 0;
	any = 0u;
	any = 1;
	any = -1;
	any = 1.0f;
	any = 1.0;

	if (hryky_nullptr != any.cast<Vector<int> >()) {
		hryky_log_err("builtin type can't be converted to an arbitrary type.");
		return false;
	}

	hryky_log_info("passed to cast a float value to a vector.");
	

	typedef String<> string_type;

	char const * const str_value = "str";

	any = any_type(string_type(str_value), mempool::global::Registry::instance());

	if (hryky_nullptr != any.cast<Vector<int> >()) {
		hryky_log_err("String<> can't be converted to Vector<int>.");
		return false;
	}

	hryky_log_info("passed to cast a string with a vector.");
	
	if (hryky_nullptr == any.cast<string_type>()) {
		hryky_log_err("String<> must be casted to the same type.");
		return false;
	}

	hryky_log_info("passed to cast a string with a same string.");
	
	if (str_value != *any.cast<string_type>()) {
		hryky_log_err("The casted value must have the same value.");
		return false;
	}

	hryky_log_info("passed to compare casted values.");
	
	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
