/**
  @file         type_info.cpp
  @brief        interface for each type::Info.
  @author       HRYKY
  @version      $Id: type_info.cpp 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/type/type_info.h"
#include "hryky/swap.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace type
{
namespace
{
} // namespace "anonymous"
} // namespace type
} // namespace hryky
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
  @brief default constructor.
 */
hryky::type::Info::Info()
	: id_(g_invalid_id)
	  , name_("")
{
}
/**
  @brief copy constructor.
 */
hryky::type::Info::Info(this_type const & rhs)
	: hryky_copy_member(id)
	  , hryky_copy_member(name)
{
}
/**
  @brief move constructor.
 */
hryky::type::Info::Info(this_type && rhs)
	: hryky_move_member(id)
	  , hryky_move_member(name)
{
}
/**
  @brief constructor with parameters.
 */
hryky::type::Info::Info(
	id_type const id, name_type const & name)
	: id_(id)
	  , name_(name)
{
}
/**
  @brief destructor.
 */
hryky::type::Info::~Info()
{
}
/**
  @brief compares each type.
 */
bool hryky::type::Info::operator==(this_type const & rhs) const
{
	return this->id_ == rhs.id_;
}
/**
  @brief compares whether both types are not equal.
 */
bool hryky::type::Info::operator!=(this_type const & rhs) const
{
	return !this->operator==(rhs);
}
/**
  @brief releases the internal resources.
 */
void hryky::type::Info::clear()
{
	this->id_ = g_invalid_id;
	this->name_ = "";
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::type::Info::swap(this_type & src)
{
	hryky_swap_member(id);
	hryky_swap_member(name);
}
/**
  @brief retrieves the name of type.
 */
hryky::type::name_type const & hryky::type::Info::name() const
{
	return this->name_;
}
/**
  @brief retrieves the ID of type.
 */
hryky::type::id_type hryky::type::Info::id() const
{
	return this->id_;
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
namespace hryky
{
namespace type
{
namespace
{
} // namespace "anonymous"
} // namespace type
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
