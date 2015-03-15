/**
  @file         http_header_parameter_entity.cpp
  @brief        retains the information for 'parameter' of HTTP Syntax.
  @author       HRYKY
  @version      $Id: http_header_parameter_entity.cpp 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_parameter_entity.h"
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
namespace header
{
namespace parameter
{
namespace
{
} // namespace "anonymous"
} // namespace parameter
} // namespace header
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
hryky::http::header::parameter::Entity::Entity()
	: attribute_()
	  , value_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::parameter::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(attribute)
	  , hryky_copy_member(value)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::parameter::Entity::Entity(this_type && rhs)
	: hryky_move_member(attribute)
	  , hryky_move_member(value)
{
}
/**
  @brief constructor.
 */
hryky::http::header::parameter::Entity::Entity(
	attribute_type const & attribute, value_type const & value)
	: attribute_(attribute)
	  , value_(value)
{
}
/**
  @brief destructor.
 */
hryky::http::header::parameter::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::parameter::Entity::clear()
{
	hryky::clear(this->value_);
	hryky::clear(this->attribute_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::parameter::Entity::swap(this_type & src)
{
	hryky_swap_member(attribute);
	hryky_swap_member(value);
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
namespace header
{
namespace parameter
{
namespace
{
} // namespace "anonymous"
} // namespace parameter
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
