/**
  @file         http_header_parser.cpp
  @brief        parses a text string of HTTP Message.
  @author       HRYKY
  @version      $Id: http_header_parser.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/any.h"
#include "hryky/http/http_header_comment_adapter.h"
#include "hryky/http/http_header_field_dispatcher_base.h"
#include "hryky/http/http_header_parser.h"
#include "hryky/log.h"
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
namespace
{
	uint32_t const g_terminal = 
		('\r' << 24) | ('\n' << 16) | ('\r' << 8) | '\n';
	
} // namespace "anonymous"
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
hryky::http::header::Parser::Parser()
	: base_type()
	  , entity_()
	  , last_four_octets_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::Parser::Parser(this_type const & rhs)
	: base_type(rhs)
	  , hryky_copy_member(entity)
	  , hryky_copy_member(last_four_octets)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::Parser::Parser(this_type && rhs)
	: base_type(::std::move(rhs))
	  , hryky_move_member(entity)
	  , hryky_move_member(last_four_octets)
{
}
/**
  @brief constructor with mempool.
 */
hryky::http::header::Parser::Parser(mempool_type const mempool)
	: base_type(mempool)
	  , entity_()
	  , last_four_octets_()
{
}
/**
  @brief destructor.
 */
hryky::http::header::Parser::~Parser()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::Parser::clear()
{
	hryky::clear(this->last_four_octets_);
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::Parser::swap(this_type & src)
{
	this->base_type::swap(src);
	hryky_swap_member(entity);
	hryky_swap_member(last_four_octets);
}
/**
  @brief assigns a destination to which the parsed result is stored.
 */
void hryky::http::header::Parser::entity(header_type * const src)
{
	this->entity_ = src;
}
/**
  @brief retrieves the destination to which the parsed result is stored.
 */
hryky::http::header_type * hryky::http::header::Parser::entity()
{
	return this->entity_;
}
/**
  @brief parses a token with checking the termination.
 */
hryky::http::header::Parser::result_type
hryky::http::header::Parser::parse_token(
	token_type const & token, token_id_type const token_id)
{
	result_type const result = this->base_type::parse_token(token, token_id);

	if (Result::pause != result) {
		return result;
	}

	/**
	  If the last four octets are "CR LF CR LF", the HTTP Header will be
	  completed so that HTTP body follows the HTTP Header.
	 */
	this->last_four_octets_ <<= 8;
	this->last_four_octets_ |= token.cast<uint8_t>();
	if (g_terminal == this->last_four_octets_) {
		return this->complete();
	}
	
	return result;
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
namespace
{
} // namespace "anonymous"
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
