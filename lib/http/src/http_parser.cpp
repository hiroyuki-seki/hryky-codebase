/**
  @file         http_parser.cpp
  @brief        writes out a HTTP Message.
  @author       HRYKY
  @version      $Id: http_parser.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_parser.h"
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
namespace
{
} // namespace "anonymous"
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
hryky::http::Parser::Parser()
	: header_parser_()
	  , entity_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::Parser::Parser(this_type const & rhs)
	: hryky_copy_member(header_parser)
	  , hryky_copy_member(entity)
{
}
/**
  @brief move constructor.
 */
hryky::http::Parser::Parser(this_type && rhs)
	: hryky_move_member(header_parser)
	  , hryky_move_member(entity)
{
}
/**
  @brief constructor.
 */
hryky::http::Parser::Parser(mempool_type const mempool)
	: header_parser_(mempool)
	  , entity_()
{
}
/**
  @brief destructor.
 */
hryky::http::Parser::~Parser()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::Parser::clear()
{
	hryky::clear(this->header_parser_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::Parser::swap(this_type & src)
{
	hryky_swap_member(header_parser);
	hryky_swap_member(entity);
}
/**
  @brief assignes the destination to be written the HTTP Message.
 */
void hryky::http::Parser::entity(entity_type * src)
{
	this->entity_ = src;
}
/**
  @brief confirms the HTTP Message is parsed completely.
 */
bool hryky::http::Parser::accepted() const
{
	return this->header_parser_.accepted();
}
/**
  @brief finishes the parsing.
 */
bool hryky::http::Parser::complete()
{
	header::parser_type::result_type const result =
		this->header_parser_.parse('\0');
	
	return header::parser_type::Result::accept == result;
}
/**
  @brief confirms whether the parsing is failed.
 */
bool hryky::http::Parser::fail() const
{
	return header::parser_type::Result::abort ==
		this->header_parser_.last_result();
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
namespace
{
} // namespace "anonymous"
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
