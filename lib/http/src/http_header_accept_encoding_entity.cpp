/**
  @file         http_header_accept_encoding_entity.cpp
  @brief        retains the information for 'Accept-Encoding' field of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_accept_encoding_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_accept_encoding_entity.h"
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
namespace accept
{
namespace encoding
{
namespace
{
} // namespace "anonymous"
} // namespace encoding
} // namespace accept
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
hryky::http::header::accept::encoding::Entity::Entity()
	: contents_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::accept::encoding::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(contents)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::accept::encoding::Entity::Entity(this_type && rhs)
	: hryky_move_member(contents)
{
}
/**
  @brief constructor.
 */
hryky::http::header::accept::encoding::Entity::Entity(mempool_type const mempool)
	: contents_(mempool)
{
}
/**
  @brief destructor.
 */
hryky::http::header::accept::encoding::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::accept::encoding::Entity::clear()
{
	hryky::clear(this->contents_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::accept::encoding::Entity::swap(this_type & src)
{
	hryky_swap_member(contents);
}
/**
  @brief appends a new 'Accept-Encoding' field-content.
 */
bool hryky::http::header::accept::encoding::Entity::append(
	content_type const & src)
{
	return this->contents_.push_back(src);
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
namespace accept
{
namespace encoding
{
namespace
{
} // namespace "anonymous"
} // namespace encoding
} // namespace accept
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
