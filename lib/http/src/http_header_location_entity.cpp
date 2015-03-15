/**
  @file         http_header_location_entity.cpp
  @brief        retains the information for 'Location' field of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_location_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_location_entity.h"
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
namespace location
{
namespace
{
} // namespace "anonymous"
} // namespace location
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
hryky::http::header::location::Entity::Entity()
	: uri_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::location::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(uri)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::location::Entity::Entity(this_type && rhs)
	: hryky_move_member(uri)
{
}
/**
  @brief constructor.
 */
hryky::http::header::location::Entity::Entity(mempool_type const mempool)
	: uri_(mempool)
{
}
/**
  @brief destructor.
 */
hryky::http::header::location::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::location::Entity::clear()
{
	hryky::clear(this->uri_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::location::Entity::swap(this_type & src)
{
	hryky_swap_member(uri);
}
/**
  @brief assigns a new URI.
 */
void hryky::http::header::location::Entity::uri(uri_type const & src)
{
	this->uri_ = src;
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
namespace location
{
namespace
{
} // namespace "anonymous"
} // namespace location
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
