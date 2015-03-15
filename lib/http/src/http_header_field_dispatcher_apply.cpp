/**
  @file         http_header_field_dispatcher_apply.cpp
  @brief        applies the implementation of field to HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_field_dispatcher_apply.cpp 350 2014-04-24 10:10:31Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_field_dispatcher_apply.h"
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
namespace dispatcher
{
namespace
{
} // namespace "anonymous"
} // namespace dispatcher
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
  @brief constructor.
 */
hryky::http::header::field::dispatcher::Apply::Apply(header_type & header)
	: base_type()
	  , header_(header)
{
}
/**
  @brief destructor.
 */
hryky::http::header::field::dispatcher::Apply::~Apply()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::field::dispatcher::Apply::swap(this_type & src)
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
  @brief dispatches http::header::accept_type.
 */
bool hryky::http::header::field::dispatcher::Apply::on_accept(
	accept_type &)
{
	return true;
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
namespace field
{
namespace dispatcher
{
namespace
{
} // namespace "anonymous"
} // namespace dispatcher
} // namespace field
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
