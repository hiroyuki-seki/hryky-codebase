/**
  @file         http_header_field_base.cpp
  @brief        base class for each field of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_field_base.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_field_base.h"
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
  @brief destructor.
 */
hryky::http::header::field::Base::~Base()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::field::Base::swap(this_type &)
{
}
/**
  @brief dispatches the implementation.
 */
bool hryky::http::header::field::Base::dispatch(dispatcher_type & dispatcher)
{
	return this->dispatch_impl(dispatcher);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
hryky::http::header::field::Base::Base()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::field::Base::Base(this_type const &)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::field::Base::Base(this_type &&)
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::field::Base::clear()
{
}
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
