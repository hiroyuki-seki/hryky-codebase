/**
  @file         http_header_comment_string.cpp
  @brief        retains the octets as constituent of comment hierarchy.
  @author       HRYKY
  @version      $Id: http_header_comment_string.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_comment_string.h"
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
namespace comment
{
namespace
{
} // namespace "anonymous"
} // namespace comment
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
hryky::http::header::comment::String::String()
	: octets_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::comment::String::String(this_type const & rhs)
	: hryky_copy_member(octets)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::comment::String::String(this_type && rhs)
	: hryky_move_member(octets)
{
}
/**
  @brief constructor.
 */
hryky::http::header::comment::String::String(mempool_type const mempool)
	: octets_(mempool)
{
}
/**
  @brief destructor.
 */
hryky::http::header::comment::String::~String()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::comment::String::clear()
{
	hryky::clear(this->octets_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::comment::String::swap(this_type & src)
{
	hryky_swap_member(octets);
}
/**
  @brief appends an octet to the end of string.
 */
bool hryky::http::header::comment::String::push_back(octet_type const octet)
{
	return this->octets_.push_back(octet);
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
namespace comment
{
namespace
{
} // namespace "anonymous"
} // namespace comment
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
