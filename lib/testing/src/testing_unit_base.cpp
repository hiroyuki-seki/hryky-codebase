/**
  @file         testing_unit_base.cpp
  @brief        base class to test one module.
  @author       HRYKY
  @version      $Id: testing_unit_base.cpp 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing/testing_unit_base.h"
#include "hryky/testing/testing_registry.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace
{
} // namespace "anonymous"
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
  @brief enregister self to the singleton hryky::testing::Registry.
 */
hryky::testing::unit::Base::Base(char const * const name)
	: name_(name)
{
	Registry::Enregister(
		Registry::instance(), name, this);
}
/**
  @brief enregisters self to the specified hryky::testing::Registry.
 */
hryky::testing::unit::Base::Base(
	registry_type registry, char const * const name)
	: name_(name)
{
	Registry::Enregister(
		registry, name, this);
}
/**
  @brief destructor.
 */
hryky::testing::unit::Base::~Base()
{
}
/**
  @brief executes this test.
 */
bool hryky::testing::unit::Base::run()
{
	return this->run_impl();
}
/**
  @brief retrieves the name of this test.
 */
hryky::testing::unit::Base::name_type const &
hryky::testing::unit::Base::name() const
{
	return this->name_;
}
//------------------------------------------------------------------------------
// defines public member functions of Registry::Test
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace
{
} // namespace "anonymous"
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
