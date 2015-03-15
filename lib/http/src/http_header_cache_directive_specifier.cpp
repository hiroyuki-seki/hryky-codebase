/**
  @file         http_header_cache_directive_specifier.cpp
  @brief        specifies the kind of cache directive of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_cache_directive_specifier.cpp 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_cache_directive_specifier.h"
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
hryky::http::header::cache::directive::Specifier::Specifier()
	: kind_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::cache::directive::Specifier::Specifier(
	this_type const & rhs)
	: hryky_copy_member(kind)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::cache::directive::Specifier::Specifier(
	this_type && rhs)
	: hryky_move_member(kind)
{
}
/**
  @brief constructor.
 */
hryky::http::header::cache::directive::Specifier::Specifier(
	kind_type const & kind)
	: kind_(kind)
{
}
/**
  @brief destructor.
 */
hryky::http::header::cache::directive::Specifier::~Specifier()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::cache::directive::Specifier::clear()
{
	hryky::clear(this->kind_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::cache::directive::Specifier::swap(this_type & src)
{
	hryky_swap_member(kind);
}
/**
  @brief retrieves the kind of directive.
 */
hryky::http::header::cache::directive::kind_type const & 
hryky::http::header::cache::directive::Specifier::kind() const
{
	return this->kind_;
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
