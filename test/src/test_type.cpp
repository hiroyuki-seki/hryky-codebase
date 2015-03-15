/**
  @file         test_type.cpp
  @brief        tests for identification of type.
  @author       HRYKY
  @version      $Id: test_type.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/type.h"
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
		
		/// tests to identify type.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * g_testname = "type";
	
} // namespace "anonymous"

	/// user defined type.
	struct Tmp
	{
		Tmp() {}
	};
	LiteralString<> const g_tmp_name("tmp");

} // namespace test
} // namespace hryky
//------------------------------------------------------------------------------
// class specialization
//------------------------------------------------------------------------------
namespace hryky
{
namespace type
{
/// specializes the name of Tmp
template<>
class Name<hryky::test::Tmp>
{
public :
	static name_type const value;
};
name_type const
Name<hryky::test::Tmp>::value = test::g_tmp_name;
} // namespace type
} // namespace hryky
//------------------------------------------------------------------------------
// static variable
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// public member functions
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
  @brief tests to identify type.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	String<> str;
	Vector<int> ints;
	Vector<char> chars;
	Vector<char> chars2;

	if (type::info(str) != type::info(str)) {
		hryky_log_err("same instances must be equal.");
		return false;
	}

	if (type::info(str) == type::info(ints)) {
		hryky_log_err("different instances must not be equal.");
		return false;
	}

	if (type::info(chars) != type::info(chars2)) {
		hryky_log_err("different instances of same type must be equal.");
		return false;
	}

	Tmp tmp1, tmp2;

	if (type::info(tmp1) != type::info(tmp2)) {
		hryky_log_err("same instances of user defined type must be equal.");
		return false;
	}

	if (type::info(tmp1).name() != g_tmp_name) {
		hryky_log_err("The name of user defined type is invalid.");
		return false;
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
//------------------------------------------------------------------------------
// protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// private member functions
//------------------------------------------------------------------------------
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
} // namespace "anonymous"
} // namespace test
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
