/**
  @file         http_header_accept_content_entity.cpp
  @brief        retains the information for 'Accept' field-content of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_accept_content_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_accept_content_entity.h"
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
namespace content
{
namespace
{
} // namespace "anonymous"
} // namespace content
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
hryky::http::header::accept::content::Entity::Entity()
	: media_range_()
	  , params_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::accept::content::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(media_range)
	  , hryky_copy_member(params)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::accept::content::Entity::Entity(this_type && rhs)
	: hryky_move_member(media_range)
	  , hryky_move_member(params)
{
}
/**
  @brief constructor.
 */
hryky::http::header::accept::content::Entity::Entity(mempool_type const mempool)
	: media_range_(mempool)
	  , params_(mempool)
{
}
/**
  @brief destructor.
 */
hryky::http::header::accept::content::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::accept::content::Entity::clear()
{
	hryky::clear(this->media_range_);
	hryky::clear(this->params_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::accept::content::Entity::swap(this_type & src)
{
	hryky_swap_member(media_range);
	hryky_swap_member(params);
}
/**
  @brief assigns a new 'media-range'.
 */
void hryky::http::header::accept::content::Entity::media_range(
	media_type_type const & src)
{
	this->media_range_ = src;
}
/**
  @brief assigns a new 'accept-params'.
 */
void hryky::http::header::accept::content::Entity::params(
	params_type const & src)
{
	this->params_ = src;
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
namespace content
{
namespace
{
} // namespace "anonymous"
} // namespace content
} // namespace accept
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
