/**
  @file         error_holder.cpp
  @brief        retains the pointer to an instance of error::Base.
  @author       HRYKY
  @version      $Id: error_holder.cpp 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/error/error_holder.h"
#include "hryky/error/error_base.h"
#include "hryky/is_null.h"
#include "hryky/log.h"
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
  @brief constructor.
 */
hryky::error::Holder::Holder()
	: entity_()
{
}
/**
  @brief copy constructor.
 */
hryky::error::Holder::Holder(this_type const & rhs)
	: hryky_copy_member(entity)
{
}
/**
  @brief move constructor.
 */
hryky::error::Holder::Holder(this_type && rhs)
	: hryky_move_member(entity)
{
}
/**
  @brief constructor with a pointer to error::Base.
 */
hryky::error::Holder::Holder(entity_type const & entity)
	: entity_(entity)
{
	return;
}
/**
  @brief destructor.
 */
hryky::error::Holder::~Holder()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::error::Holder::swap(this_type & src)
{
	hryky_swap_member(entity)
}
/**
  @brief retrieves the description of the held error.
 */
char const * hryky::error::Holder::what() const
{
	if (hryky_is_null(this->entity_)) {
		return "ok";
	}
	
	return this->entity_->what();
}
/**
  @brief confirms whether no error occurred.
 */
bool hryky::error::Holder::is_null() const
{
	return hryky_is_null(this->entity_);
}
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
