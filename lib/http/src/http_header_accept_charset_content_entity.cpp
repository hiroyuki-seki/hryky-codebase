/**
  @file         http_header_accept_charset_content_entity.cpp
  @brief        retains the information for 'Accept-Charset' field-content of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_accept_charset_content_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_accept_charset_content_entity.h"
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
namespace charset
{
namespace content
{
namespace
{
} // namespace "anonymous"
} // namespace content
} // namespace charset
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
hryky::http::header::accept::charset::content::Entity::Entity()
	: charset_()
	  , qvalue_(header::default_qvalue_)
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::accept::charset::content::Entity::Entity(
	this_type const & rhs)
	: hryky_copy_member(charset)
	  , hryky_copy_member(qvalue)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::accept::charset::content::Entity::Entity(
	this_type && rhs)
	: hryky_move_member(charset)
	  , hryky_move_member(qvalue)
{
}
/**
  @brief constructor.
 */
hryky::http::header::accept::charset::content::Entity::Entity(
	mempool_type const mempool)
	: charset_(mempool)
	  , qvalue_(header::default_qvalue_)
{
}
/**
  @brief destructor.
 */
hryky::http::header::accept::charset::content::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::accept::charset::content::Entity::clear()
{
	this->qvalue_ = header::default_qvalue_;
	hryky::clear(this->charset_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::accept::charset::content::Entity::swap(
	this_type & src)
{
	hryky_swap_member(charset);
	hryky_swap_member(qvalue);
}
/**
  @brief assigns a new 'charset'.
 */
void hryky::http::header::accept::charset::content::Entity::charset(
	header::charset_type const & src)
{
	this->charset_ = src;
}
/**
  @brief assigns a new 'qvalue'.
 */
void hryky::http::header::accept::charset::content::Entity::qvalue(
	header::qvalue_type const src)
{
	this->qvalue_ = src;
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
namespace charset
{
namespace content
{
namespace
{
} // namespace "anonymous"
} // namespace content
} // namespace charset
} // namespace accept
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
