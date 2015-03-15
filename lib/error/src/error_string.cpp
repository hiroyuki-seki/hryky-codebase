/**
  @file         error_string.cpp
  @brief        holds the string about the error as string.
  @author       HRYKY
  @version      $Id: hryky-template.l 63 2012-05-01 03:42:24Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/error/error_string.h"
#include "hryky/error/error_common.h"
#include "hryky/mempool.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace error
{
namespace
{
} // namespace "anonymous"
} // namespace error
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
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
hryky::error::String::String()
	: base_type()
	  , raw_(error::mempool())
{
	return;
}
/**
  @brief copy constructor.
 */
hryky::error::String::String(this_type const & rhs)
	: base_type(rhs)
	  , hryky_copy_member(raw)
{
}
/**
  @brief constructor with the initial string as an array of characters.
 */
hryky::error::String::String(
	char const * const src, size_t const src_size)
	: base_type()
	  , raw_(src, src_size, error::mempool())
{
	return;
}
/**
  @brief constructor with the initial string as a null-terminated string.
 */
hryky::error::String::String(
	char const * const src)
	: base_type()
	  , raw_(src, error::mempool())
{
	return;
}
/**
  @brief destructor.
 */
hryky::error::String::~String()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::error::String::swap(this_type & src)
{
	this->base_type::swap(src);
	hryky_swap_member(raw);
}
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the description about this error.
 */
char const *
hryky::error::String::what_impl() const
{
	return this->raw_.c_str();
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates an error represented by string.
 */
hryky::error_type
hryky::error::string(char const * const c_str)
{
	return error_type::entity_type(
		mempool::instantiate<String>(error::mempool(), c_str).release());
}
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace error
{
namespace
{
} // namespace "anonymous"
} // namespace error
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
