/**
  @file         http_header_field_extension_entity.cpp
  @brief        retains the information for 'extension-header' field of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_field_extension_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_field_extension_entity.h"
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
namespace field
{
namespace extension
{
namespace
{
} // namespace "anonymous"
} // namespace extension
} // namespace field
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
hryky::http::header::field::extension::Entity::Entity()
	: name_()
	  , contents_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::field::extension::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(name)
	  , hryky_copy_member(contents)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::field::extension::Entity::Entity(this_type && rhs)
	: hryky_move_member(name)
	  , hryky_move_member(contents)
{
}
/**
  @brief constructor.
 */
hryky::http::header::field::extension::Entity::Entity(
	mempool_type const mempool)
	: name_(mempool)
	  , contents_(mempool)
{
}
/**
  @brief destructor.
 */
hryky::http::header::field::extension::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::field::extension::Entity::clear()
{
	hryky::clear(this->contents_);
	hryky::clear(this->name_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::field::extension::Entity::swap(this_type & src)
{
	hryky_swap_member(name);
	hryky_swap_member(contents);
}
/**
  @brief assigns a new name of this field.
 */
void hryky::http::header::field::extension::Entity::name(name_type const & src)
{
	this->name_ = src;
}
/**
  @brief appends a new content of this field.
 */
bool hryky::http::header::field::extension::Entity::append(
	content_type const & src)
{
	return this->contents_.push_back(src);
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
namespace field
{
namespace extension
{
namespace
{
} // namespace "anonymous"
} // namespace extension
} // namespace field
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
