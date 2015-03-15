/**
  @file         http_header_cache_directive_second.cpp
  @brief        retains delta-seconds of cache-directive in HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_cache_directive_second.cpp 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_cache_directive_second.h"
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
hryky::http::header::cache::directive::Second::Second()
	: kind_()
	  , seconds_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::cache::directive::Second::Second(this_type const & rhs)
	: hryky_copy_member(kind)
	  , hryky_copy_member(seconds)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::cache::directive::Second::Second(this_type && rhs)
	: hryky_move_member(kind)
	  , hryky_move_member(seconds)
{
}
/**
  @brief constructor.
 */
hryky::http::header::cache::directive::Second::Second(
	Kind::Raw const kind, cache::seconds_type const & second)
	: kind_(kind)
	  , seconds_(second)
{
}
/**
  @brief destructor.
 */
hryky::http::header::cache::directive::Second::~Second()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::cache::directive::Second::clear()
{
	hryky::clear(this->kind_);
	hryky::clear(this->seconds_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::cache::directive::Second::swap(this_type & src)
{
	hryky_swap_member(kind);
	hryky_swap_member(seconds);
}
/**
  @brief retrieves the kind of cache-directive.
 */
hryky::http::header::cache::directive::kind_type const & 
hryky::http::header::cache::directive::Second::kind() const
{
	return this->kind_;
}
/**
  @brief retrieves the delta seconds.
 */
hryky::http::header::cache::seconds_type const & 
hryky::http::header::cache::directive::Second::second() const
{
	return this->seconds_;
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
