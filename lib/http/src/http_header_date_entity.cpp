/**
  @file         http_header_date_entity.cpp
  @brief        retains the information for 'HTTP-date' of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_date_entity.cpp 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_date_entity.h"
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
namespace date
{
namespace
{
} // namespace "anonymous"
} // namespace date
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
hryky::http::header::date::Entity::Entity()
	: date_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::date::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(date)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::date::Entity::Entity(this_type && rhs)
	: hryky_move_member(date)
{
}
/**
  @brief destructor.
 */
hryky::http::header::date::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::date::Entity::clear()
{
	hryky::clear(this->date_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::date::Entity::swap(this_type & src)
{
	hryky_swap_member(date);
}
/**
  @brief assigns a new date.
 */
void hryky::http::header::date::Entity::date(hryky::date_type const & src)
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
namespace date
{
namespace
{
} // namespace "anonymous"
} // namespace date
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
