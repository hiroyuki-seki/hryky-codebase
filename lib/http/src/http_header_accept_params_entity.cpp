/**
  @file         http_header_accept_params_entity.cpp
  @brief        retains the information for 'accept-params' of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_accept_params_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_accept_params_entity.h"
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
namespace accept
{
namespace params
{
namespace
{
} // namespace "anonymous"
} // namespace params
} // namespace accept
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
hryky::http::header::accept::params::Entity::Entity()
	: qvalue_(header::default_qvalue_)
	  , extensions_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::accept::params::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(qvalue)
	  , hryky_copy_member(extensions)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::accept::params::Entity::Entity(
	this_type && rhs)
	: hryky_move_member(qvalue)
	  , hryky_move_member(extensions)
{
}
/**
  @brief constructor with mempool.
 */
hryky::http::header::accept::params::Entity::Entity(mempool_type const mempool)
	: qvalue_(header::default_qvalue_)
	  , extensions_(mempool)
{
}
/**
  @brief destructor.
 */
hryky::http::header::accept::params::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::accept::params::Entity::clear()
{
	hryky::clear(this->extensions_);
	this->qvalue_ = header::default_qvalue_;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::accept::params::Entity::swap(this_type & src)
{
	hryky_swap_member(qvalue);
	hryky_swap_member(extensions);
}
/**
  @brief appends an 'accept-extension'.
 */
bool hryky::http::header::accept::params::Entity::append(
	extension_type const & extension)
{
	return this->extensions_.push_back(extension);
}
/**
  @brief assigns a new 'qvalue'.
 */
void hryky::http::header::accept::params::Entity::qvalue(
	qvalue_type const src)
{
	this->qvalue_ = src;
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
namespace accept
{
namespace params
{
namespace
{
} // namespace "anonymous"
} // namespace params
} // namespace accept
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
