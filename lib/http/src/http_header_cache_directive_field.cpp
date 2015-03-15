/**
  @file         http_header_cache_directive_field.cpp
  @brief        retains 'field-name's of cache-directive.
  @author       HRYKY
  @version      $Id: http_header_cache_directive_field.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_cache_directive_field.h"
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
namespace cache
{
namespace directive
{
namespace
{
} // namespace "anonymous"
} // namespace directive
} // namespace cache
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
hryky::http::header::cache::directive::Field::Field()
	: kind_()
	  , fields_()
{
}
/**
  @brief constructs with kind and mempool.
 */
hryky::http::header::cache::directive::Field::Field(
	Kind::Raw const kind, mempool_type const mempool)
	: kind_(kind)
	  , fields_(mempool)
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::cache::directive::Field::Field(this_type const & rhs)
	: hryky_copy_member(kind)
	  , hryky_copy_member(fields)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::cache::directive::Field::Field(this_type && rhs)
	: hryky_move_member(kind)
	  , hryky_move_member(fields)
{
}
/**
  @brief constructor.
 */
hryky::http::header::cache::directive::Field::Field(mempool_type const mempool)
	: kind_()
	  , fields_(mempool)
{
}
/**
  @brief constructor with a kind of directive and an array of field-names.
 */
hryky::http::header::cache::directive::Field::Field(
	Kind::Raw const kind, fields_type const & fields)
	: kind_(kind)
	  , fields_(fields)
{
}
/**
  @brief destructor.
 */
hryky::http::header::cache::directive::Field::~Field()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::cache::directive::Field::clear()
{
	this->fields_.clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::cache::directive::Field::swap(this_type & src)
{
	hryky_swap_member(kind);
	hryky_swap_member(fields);
}
/**
  @brief retrieves the kind of directive.
 */
hryky::http::header::cache::directive::kind_type const & 
hryky::http::header::cache::directive::Field::kind() const
{
	return this->kind_;
}
/**
  @brief retrieves the beginning of the array of field-names.
 */
hryky::http::header::cache::directive::Field::fields_type::const_iterator
hryky::http::header::cache::directive::Field::begin() const
{
	return this->fields_.begin();
}
/**
  @brief retrieves the end of the array of field-names.
 */
hryky::http::header::cache::directive::Field::fields_type::const_iterator
hryky::http::header::cache::directive::Field::end() const
{
	return this->fields_.end();
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
namespace cache
{
namespace directive
{
namespace
{
} // namespace "anonymous"
} // namespace directive
} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
