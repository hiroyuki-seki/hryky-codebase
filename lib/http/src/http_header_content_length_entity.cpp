/**
  @file         http_header_content_length_entity.cpp
  @brief        retains the information for 'Content-Length' field of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_content_length_entity.cpp 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_content_length_entity.h"
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
namespace content
{
namespace length
{
namespace
{
} // namespace "anonymous"
} // namespace length
} // namespace content
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
hryky::http::header::content::length::Entity::Entity()
	: value_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::content::length::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(value)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::content::length::Entity::Entity(this_type && rhs)
	: hryky_move_member(value)
{
}
/**
  @brief constructor.
 */
hryky::http::header::content::length::Entity::Entity(value_type const value)
	: value_(value)
{
}
/**
  @brief destructor.
 */
hryky::http::header::content::length::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::content::length::Entity::clear()
{
	hryky::clear(this->value_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::content::length::Entity::swap(this_type & src)
{
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
namespace content
{
namespace length
{
namespace
{
} // namespace "anonymous"
} // namespace length
} // namespace content
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
