/**
  @file         http_header_accept_encoding_content_entity.cpp
  @brief        retains the information for 'Accept-Encoding' field-content of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_accept_encoding_content_entity.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_accept_encoding_content_entity.h"
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
namespace content
{
namespace
{
} // namespace "anonymous"
} // namespace content
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
hryky::http::header::accept::encoding::content::Entity::Entity()
	: coding_()
	  , qvalue_(header::default_qvalue_)
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::accept::encoding::content::Entity::Entity(
	this_type const & rhs)
	: hryky_copy_member(coding)
	  , hryky_copy_member(qvalue)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::accept::encoding::content::Entity::Entity(
	this_type && rhs)
	: hryky_move_member(coding)
	  , hryky_move_member(qvalue)
{
	
}
/**
  @brief constructor.
 */
hryky::http::header::accept::encoding::content::Entity::Entity(
	mempool_type const mempool)
	: coding_(mempool)
	  , qvalue_(header::default_qvalue_)
{
}
/**
  @brief destructor.
 */
hryky::http::header::accept::encoding::content::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::accept::encoding::content::Entity::clear()
{
	this->qvalue_ = header::default_qvalue_;
	hryky::clear(this->coding_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::accept::encoding::content::Entity::swap(
	this_type & src)
{
	hryky_swap_member(coding);
	hryky_swap_member(qvalue);
}
/**
  @brief assigns a new 'content-coding'.
 */
void hryky::http::header::accept::encoding::content::Entity::coding(
	coding_type const & src)
{
	this->coding_ = src;
}
/**
  @brief assigns a new 'qvalue'.
 */
void hryky::http::header::accept::encoding::content::Entity::qvalue(
	qvalue_type const src)
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
namespace encoding
{
namespace content
{
namespace
{
} // namespace "anonymous"
} // namespace content
} // namespace encoding
} // namespace accept
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
