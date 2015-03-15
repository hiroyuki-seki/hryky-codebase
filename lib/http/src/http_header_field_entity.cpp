/**
  @file     http_header_field_entity.cpp
  @brief    retains the kind and the name of HTTP Header field.
  @author   HRYKY
  @version  $Id: http_header_field_entity.cpp 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_field_entity.h"
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
namespace
{
} // namespace "anonymous"
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
hryky::http::header::field::Entity::Entity()
	: kind_()
	  , name_()
	  , contents_()
{
}
/**
  @brief constructor with a kind and name.
 */
hryky::http::header::field::Entity::Entity(
	Kind::Raw const kind, name_type const & name)
	: kind_(kind)
	  , name_(name)
	  , contents_(name.get_allocator())
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::field::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(kind)
	  , hryky_copy_member(name)
	  , hryky_copy_member(contents)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::field::Entity::Entity(this_type && rhs)
	: hryky_move_member(kind)
	, hryky_move_member(name)
	, hryky_move_member(contents)
{
}
/**
  @brief destructor.
 */
hryky::http::header::field::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::field::Entity::clear()
{
	hryky::clear(this->kind_);
	hryky::clear(this->name_);
	hryky::clear(this->contents_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::field::Entity::swap(this_type & src)
{
	hryky_swap_member(kind);
	hryky_swap_member(name);
	hryky_swap_member(contents);
}
/**
  @brief retrieves the kind of HTTP Header field.
 */
hryky::http::header::field::kind_type const & 
hryky::http::header::field::Entity::kind() const
{
	return this->kind_;
}
/**
  @brief assigns a new name of this field.
 */
void hryky::http::header::field::Entity::name(name_type const & src)
{
	this->name_ = src;
}
/**
  @brief appends a new content of this field.
 */
bool hryky::http::header::field::Entity::append(
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
namespace
{
} // namespace "anonymous"
} // namespace field
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
