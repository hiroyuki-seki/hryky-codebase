/**
  @file         http_header_cache_directive_dispatcher_apply.cpp
  @brief        applies the implementation of cache-directive to cache-control.
  @author       HRYKY
  @version      $Id: http_header_cache_directive_dispatcher_apply.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_cache_directive_dispatcher_apply.h"
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
namespace dispatcher
{
namespace
{
} // namespace "anonymous"
} // namespace dispatcher
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
  @brief constructor.
 */
hryky::http::header::cache::directive::dispatcher::Apply::Apply(
	control_type & control)
	: base_type()
	  , control_(control)
{
}
/**
  @brief destructor.
 */
hryky::http::header::cache::directive::dispatcher::Apply::~Apply()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::cache::directive::dispatcher::Apply::swap(
	this_type & src)
{
	this->base_type::swap(src);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief copy constructor.
 */
hryky::http::header::cache::directive::dispatcher::Apply::Apply(
	this_type const & rhs)
	: base_type(rhs)
	  , hryky_copy_member(control)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::cache::directive::dispatcher::Apply::Apply(
	this_type && rhs)
	: base_type(::std::move(rhs))
	  , hryky_copy_member(control)
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::cache::directive::dispatcher::Apply::clear()
{
	this->base_type::clear();
}
/**
  @brief applies http::header::cache::specifier_type to cache-control.
 */
bool hryky::http::header::cache::directive::dispatcher::Apply::on_specifier(
	specifier_type & specifier)
{
	return this->control_.append(specifier.kind());
}
/**
  @brief applies http::header::cache::directive::seconds_type to cache-control.
 */
bool hryky::http::header::cache::directive::dispatcher::Apply::on_seconds(
	seconds_type & second)
{
	return this->control_.append(second.kind(), second.second());
}
/**
  @brief applies http::header::cache::directive::field_type to control.
 */
bool hryky::http::header::cache::directive::dispatcher::Apply::on_field(
	field_type & field)
{
	return this->control_.append(
		field.kind(), field.begin(), field.end());
}
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
namespace dispatcher
{
namespace
{
} // namespace "anonymous"
} // namespace dispatcher
} // namespace directive
} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
