/**
  @file         http_header_expires_entity.cpp
  @brief        retains the information for 'Expires' field of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_expires_entity.cpp 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_expires_entity.h"
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
namespace expires
{
namespace
{
} // namespace "anonymous"
} // namespace expires
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
hryky::http::header::expires::Entity::Entity()
	: date_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::expires::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(date)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::expires::Entity::Entity(this_type && rhs)
	: hryky_move_member(date)
{
}
/**
  @brief constructor.
 */
hryky::http::header::expires::Entity::Entity(header::date_type const & date)
	: date_(date)
{
}
/**
  @brief destructor.
 */
hryky::http::header::expires::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::expires::Entity::clear()
{
	hryky::clear(this->date_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::expires::Entity::swap(this_type & src)
{
	hryky_swap_member(date);
}
/**
  @brief assigns a new date.
 */
void hryky::http::header::expires::Entity::date(header::date_type const & src)
{
	this->date_ = src;
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
namespace expires
{
namespace
{
} // namespace "anonymous"
} // namespace expires
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
