/**
  @file         http_header_media_type_entity.cpp
  @brief        retains the information for 'media-range' of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_media_type_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_media_type_entity.h"
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
namespace media_type
{
namespace
{
} // namespace "anonymous"
} // namespace media_type
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
hryky::http::header::media_type::Entity::Entity()
	: type_name_()
	  , subtype_name_()
	  , parameters_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::media_type::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(type_name)
	  , hryky_copy_member(subtype_name)
	  , hryky_copy_member(parameters)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::media_type::Entity::Entity(this_type && rhs)
	: hryky_move_member(type_name)
	  , hryky_move_member(subtype_name)
	  , hryky_move_member(parameters)
{
}
/**
  @brief constructor with mempool.
 */
hryky::http::header::media_type::Entity::Entity(mempool_type const mempool)
	: type_name_(mempool)
	  , subtype_name_(mempool)
	  , parameters_(mempool)
{
}
/**
  @brief destructor.
 */
hryky::http::header::media_type::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::media_type::Entity::clear()
{
	hryky::clear(this->parameters_);
	hryky::clear(this->subtype_name_);
	hryky::clear(this->type_name_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::media_type::Entity::swap(this_type & src)
{
	hryky_swap_member(type_name);
	hryky_swap_member(subtype_name);
	hryky_swap_member(parameters);
}
/**
  @brief assigns a new 'type-name'.
 */
void hryky::http::header::media_type::Entity::type_name(
	type_name_type const & src)
{
	this->type_name_ = src;
}
/**
  @brief assigns a new 'subtype-name'.
 */
void hryky::http::header::media_type::Entity::subtype_name(
	subtype_name_type const & src)
{
	this->subtype_name_ = src;
}
/**
  @brief appends a new 'parameter'.
 */
bool hryky::http::header::media_type::Entity::append(
	parameter_type const & src)
{
	return this->parameters_.push_back(src);
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
namespace media_type
{
namespace
{
} // namespace "anonymous"
} // namespace media_type
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
