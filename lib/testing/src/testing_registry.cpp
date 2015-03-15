/**
  @file         testing_registry.cpp
  @brief        the collection of all tests.
  @author       HRYKY
  @version      $Id: testing_registry.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing/testing_registry.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_disable_warning_unthreadsafe_instance
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace
{
}
//------------------------------------------------------------------------------
// static variable
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the singleton instance.
 */
hryky::testing::Registry &
hryky::testing::Registry::instance()
{
	static Registry instance;
	
	return instance;
}
/**
  @brief retrieves the functor of the test.
 */
hryky::testing::Registry::unit_type
hryky::testing::Registry::operator[](char const * const name) const
{
	table_type::const_iterator const found = this->table_.find(name);

	if (this->table_.end() == found) {
		return unit_type();
	}

	return (*found).second;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
hryky::testing::Registry::Registry()
	: table_()
{
}
/**
  @brief destructor.
 */
hryky::testing::Registry::~Registry()
{
}
/**
  @brief maps the name of the test and the function to invoke the test.
 */
void hryky::testing::Registry::enregister(char const * const name, unit_type unit)
{
	this->table_[table_type::key_type(name)] = unit_type(unit);
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace
{
}
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
