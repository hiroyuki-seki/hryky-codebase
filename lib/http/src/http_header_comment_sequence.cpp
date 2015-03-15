/**
  @file         http_header_comment_sequence.cpp
  @brief        retains the array of http::header::comment::Base components.
  @author       HRYKY
  @version      $Id: http_header_comment_sequence.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_comment_sequence.h"
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
hryky::http::header::comment::Sequence::Sequence()
	: components_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::comment::Sequence::Sequence(this_type const & rhs)
	: hryky_copy_member(components)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::comment::Sequence::Sequence(this_type && rhs)
	: hryky_move_member(components)
{
}
/**
  @brief constructor.
 */
hryky::http::header::comment::Sequence::Sequence(mempool_type const mempool)
	: components_(mempool)
{
}
/**
  @brief destructor.
 */
hryky::http::header::comment::Sequence::~Sequence()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::comment::Sequence::clear()
{
	hryky::clear(this->components_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::comment::Sequence::swap(this_type & src)
{
	hryky_swap_member(components);
}
/**
  @brief appends a constituent of the array of http::header::comment_type.
 */
bool hryky::http::header::comment::Sequence::append(component_type const & src)
{
	return this->components_.push_back(src);
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
