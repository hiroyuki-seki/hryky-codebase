/**
  @file         http_request_entity.cpp
  @brief        retains the information of HTTP Request.
  @author       HRYKY
  @version      $Id: http_request_entity.cpp 331 2014-03-09 06:44:48Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_request_entity.h"
#include "hryky/mempool/mempool_global_registry.h"
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
hryky::http::request::Entity::Entity()
	: method_()
	  , uri_()
	  , version_()
	  , header_()
	  , body_()
{
	return;
}
/**
  @brief constructor with mempool.
 */
hryky::http::request::Entity::Entity(mempool_type const mempool)
	: method_()
	  , uri_(mempool)
	  , version_()
	  , header_(mempool)
	  , body_(mempool)
{
}
/**
  @brief copy constructor.
 */
hryky::http::request::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(method)
	  , hryky_copy_member(uri)
	  , hryky_copy_member(version)
	  , hryky_copy_member(header)
	  , hryky_copy_member(body)
{
}
/**
  @brief move constructor.
 */
hryky::http::request::Entity::Entity(this_type && rhs)
	: hryky_move_member(method)
	  , hryky_move_member(uri)
	  , hryky_move_member(version)
	  , hryky_move_member(header)
	  , hryky_move_member(body)
{
}
/**
  @brief destructor.
 */
hryky::http::request::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::request::Entity::clear()
{
	hryky::clear(this->body_);
	hryky::clear(this->header_);
	hryky::clear(this->version_);
	hryky::clear(this->uri_);
	hryky::clear(this->method_);
}
/**
  @brief retrieves the mutable entity of URI.
 */
hryky::uri::Entity & hryky::http::request::Entity::uri()
{
	return this->uri_;
}
/**
  @brief retrieves the immutable entity of URI.
 */
hryky::uri::Entity const & hryky::http::request::Entity::uri() const
{
	return this->uri_;
}
/**
  @brief assigns a new URI.
 */
void hryky::http::request::Entity::uri(uri_type const & src)
{
	this->uri_ = src;
}
/**
  @brief assigns a HTTP Method.
 */
void hryky::http::request::Entity::method(method::kind_type const & src)
{
	this->method_ = src;
}
/**
  @brief assigns a HTTP-Version.
 */
void hryky::http::request::Entity::version(version::Entity const & src)
{
	this->version_ = src;
}
/**
  @brief retrieves the mutable message-header.
 */
hryky::http::header::Entity & hryky::http::request::Entity::header()
{
	return this->header_;
}
/**
  @brief retrieves the immutable message-header.
 */
hryky::http::header::Entity const & hryky::http::request::Entity::header() const
{
	return this->header_;
}
/**
  @brief assigns a new list of headers.
 */
void hryky::http::request::Entity::header(header_type const & src)
{
	this->header_ = src;
}
/**
  @brief retrieves the immutable message-body of HTTP Message.
 */
hryky::http::body::Entity const & hryky::http::request::Entity::body() const
{
	return this->body_;
}
/**
  @brief retrieves the mutable message-body of HTTP Message.
 */
hryky::http::body::Entity & hryky::http::request::Entity::body()
{
	return this->body_;
}
/**
  @brief assigns a new block for body of HTTP Message.
 */
void hryky::http::request::Entity::body(body_type const & src)
{
	this->body_ = src;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::request::Entity::swap(this_type & src)
{
	hryky_swap_member(method);
	hryky_swap_member(uri);
	hryky_swap_member(version);
	hryky_swap_member(header);
	hryky_swap_member(body);
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
