/**
  @file         uri_parser.cpp
  @brief        parses URI syntax.
  @author       HRYKY
  @version      $Id: uri_parser.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/uri/uri_parser.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
namespace
{
} // namespace "anonymous"
} // namespace uri
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
hryky::uri::Parser::Parser()
	: base_type()
	  , entity_()
{
}
/**
  @brief constructor.
 */
hryky::uri::Parser::Parser(mempool_type const mempool)
	: base_type(mempool)
	  , entity_()
{
}
/**
  @brief copy constructor.
 */
hryky::uri::Parser::Parser(this_type const & rhs)
	: base_type(rhs)
	  , hryky_copy_member(entity)
{
}
/**
  @brief move constructor.
 */
hryky::uri::Parser::Parser(this_type && rhs)
	: base_type(::std::move(rhs))
	  , hryky_move_member(entity)
{
}
/**
  @brief destructor.
 */
hryky::uri::Parser::~Parser()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::uri::Parser::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::uri::Parser::swap(this_type & src)
{
	this->base_type::swap(src);
	hryky_swap_member(entity);
}
/**
  @brief assigns the destination to which the result is written.
 */
void hryky::uri::Parser::entity(entity_type * src)
{
	this->entity_ = src;
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
namespace uri
{
namespace
{
} // namespace "anonymous"
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
