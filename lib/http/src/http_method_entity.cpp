/**
  @file         http_method_entity.cpp
  @brief        retains the HTTP Method.
  @author       HRYKY
  @version      $Id: http_method_entity.cpp 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_method_entity.h"
#include "hryky/clear.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace method
{
namespace
{
} // namespace "anonymous"
} // namespace method
} // namespace http
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
hryky::http::method::Entity::Entity()
	: kind_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::method::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(kind)
{
}
/**
  @brief move constructor.
 */
hryky::http::method::Entity::Entity(this_type && rhs)
	: hryky_move_member(kind)
{
}
/**
  @brief constructor.
 */
hryky::http::method::Entity::Entity(kind_type const kind)
	: kind_(kind)
{
}
/**
  @brief destructor.
 */
hryky::http::method::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::method::Entity::clear()
{
	hryky::clear(this->kind_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::method::Entity::swap(this_type & src)
{
	hryky_swap_member(kind);
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
namespace http
{
namespace method
{
namespace
{
} // namespace "anonymous"
} // namespace method
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
