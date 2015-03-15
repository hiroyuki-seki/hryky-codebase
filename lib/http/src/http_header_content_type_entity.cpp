/**
  @file         http_header_content_type_entity.cpp
  @brief        retains the information for 'Content-Type' field of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_content_type_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_content_type_entity.h"
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
namespace type
{
namespace
{
} // namespace "anonymous"
} // namespace type
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
hryky::http::header::content::type::Entity::Entity()
	: media_type_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::content::type::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(media_type)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::content::type::Entity::Entity(this_type && rhs)
	: hryky_move_member(media_type)
{
}
/**
  @brief constructor.
 */
hryky::http::header::content::type::Entity::Entity(mempool_type const mempool)
	: media_type_(mempool)
{
}
/**
  @brief destructor.
 */
hryky::http::header::content::type::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::content::type::Entity::clear()
{
	hryky::clear(this->media_type_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::content::type::Entity::swap(this_type & src)
{
	hryky_swap_member(media_type);
}
/**
  @brief assigns a new 'media-type'.
 */
void hryky::http::header::content::type::Entity::media_type(
	media_type_type const & src)
{
	this->media_type_ = src;
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
namespace type
{
namespace
{
} // namespace "anonymous"
} // namespace type
} // namespace content
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
