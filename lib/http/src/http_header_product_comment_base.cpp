/**
  @file         http_header_product_comment_base.cpp
  @brief        base class for holding 'comment' and 'product' representation polymorphically.
  @author       HRYKY
  @version      $Id: http_header_product_comment_base.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_product_comment_base.h"
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
namespace product_comment
{
namespace
{
} // namespace "anonymous"
} // namespace product_comment
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
hryky::http::header::product_comment::Base::Base()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::product_comment::Base::Base(this_type const &)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::product_comment::Base::Base(this_type &&)
{
}
/**
  @brief destructor.
 */
hryky::http::header::product_comment::Base::~Base()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::product_comment::Base::clear()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::product_comment::Base::swap(this_type &)
{
}
/**
  @brief dispatches the implementation.
 */
bool hryky::http::header::product_comment::Base::dispatch(
	dispatcher_type & dispatcher)
{
	return this->dispatch_impl(dispatcher);
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
namespace product_comment
{
namespace
{
} // namespace "anonymous"
} // namespace product_comment
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
