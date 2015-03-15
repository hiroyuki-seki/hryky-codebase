/**
  @file         error_base.cpp
  @brief        retains arbitary data polymorphically.
  @author       HRYKY
  @version      $Id: error_base.cpp 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/error/error_base.h"
#include "hryky/error/error_common.h"
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
  @brief retrieves the description about this error.
 */
char const *
hryky::error::Base::what() const
{
	return this->what_impl();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::error::Base::swap(this_type &)
{
}
/**
  @brief destructor.
 */
hryky::error::Base::~Base()
{
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
hryky::error::Base::Base()
	: intrusive_ptr_trait(error::mempool())
{
}
/**
  @brief copy constructor.
 */
hryky::error::Base::Base(this_type const & rhs)
	: intrusive_ptr_trait(rhs)
{
}
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
