/**
  @file         http_request_line_entity.cpp
  @brief        retains the information of the first line of HTTP Request Message.
  @author       HRYKY
  @version      $Id: http_request_line_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_request_line_entity.h"
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
namespace request
{
namespace line
{
namespace
{
} // namespace "anonymous"
} // namespace line
} // namespace request
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
hryky::http::request::line::Entity::Entity()
	: method_()
	  , uri_()
	  , version_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::request::line::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(method)
	  , hryky_copy_member(uri)
	  , hryky_copy_member(version)
{
}
/**
  @brief move constructor.
 */
hryky::http::request::line::Entity::Entity(this_type && rhs)
	: hryky_move_member(method)
	  , hryky_move_member(uri)
	  , hryky_move_member(version)
{
}
/**
  @brief constructor.
 */
hryky::http::request::line::Entity::Entity(mempool_type const mempool)
	: method_()
	  , uri_(mempool)
	  , version_()
{
}
/**
  @brief constructor with components.
 */
hryky::http::request::line::Entity::Entity(
	method_type const & method,
	uri_type const & uri,
	version_type const & version)
	: method_(method)
	  , uri_(uri)
	  , version_(version)
{
}
/**
  @brief destructor.
 */
hryky::http::request::line::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::request::line::Entity::clear()
{
	hryky::clear(this->method_);
	hryky::clear(this->uri_);
	hryky::clear(this->version_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::request::line::Entity::swap(this_type & src)
{
	hryky_swap_member(method);
	hryky_swap_member(uri);
	hryky_swap_member(version);
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
namespace request
{
namespace line
{
namespace
{
} // namespace "anonymous"
} // namespace line
} // namespace request
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
