/**
  @file         http_header_host_entity.cpp
  @brief        retains the information of 'host' field of HTTP header.
  @author       HRYKY
  @version      $Id: http_header_host_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_host_entity.h"
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
namespace host
{
namespace
{
} // namespace "anonymous"
} // namespace host
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
hryky::http::header::host::Entity::Entity()
	: host_()
	  , port_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::host::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(host)
	  , hryky_copy_member(port)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::host::Entity::Entity(this_type && rhs)
	: hryky_move_member(host)
	  , hryky_move_member(port)
{
}
/**
  @brief constructor with mempool.
 */
hryky::http::header::host::Entity::Entity(mempool_type const mempool)
	: host_(mempool)
	  , port_()
{
}
/**
  @brief destructor.
 */
hryky::http::header::host::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::host::Entity::clear()
{
	hryky::clear(this->port_);
	hryky::clear(this->host_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::host::Entity::swap(this_type & src)
{
	hryky_swap_member(host);
	hryky_swap_member(port);
}
/**
  @brief assigns a new URI host.
 */
void hryky::http::header::host::Entity::host(host_type const & src)
{
	this->host_ = src;
}
/**
  @brief assigns a new URI port.
 */
void hryky::http::header::host::Entity::port(port_type const & src)
{
	this->port_ = src;
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
namespace host
{
namespace
{
} // namespace "anonymous"
} // namespace host
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
