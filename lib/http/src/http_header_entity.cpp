/**
  @file         http_header_entity.cpp
  @brief        retains message-headers of HTTP Message.
  @author       HRYKY
  @version      $Id: http_header_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_entity.h"
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
  @brief default constructor.
 */
hryky::http::header::Entity::Entity()
	: host_()
{
}
/**
  @brief constructor.
 */
hryky::http::header::Entity::Entity(mempool_type const mempool)
	: host_(mempool)
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(host)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::Entity::Entity(this_type && rhs)
	: hryky_move_member(host)
{
}
/**
  @brief destructor.
 */
hryky::http::header::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::Entity::clear()
{
	hryky::clear(this->host_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::Entity::swap(this_type & src)
{
	hryky_swap_member(host);
}
/**
  @brief retrieves the mutable reference to Host field.
 */
hryky::uri::authority::Entity & hryky::http::header::Entity::host()
{
	return this->host_;
}
/**
  @brief retrieves the immutable reference to Host field.
 */
hryky::uri::authority::Entity const & hryky::http::header::Entity::host() const
{
	return this->host_;
}
/**
  @brief assigns the kind of 'Connection' field.
 */
void hryky::http::header::Entity::connection(connection::kind_type const & src)
{
	this->connection_ = src;
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
