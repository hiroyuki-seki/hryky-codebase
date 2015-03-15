/**
  @file     date_parser.cpp
  @brief    parses the representation of date.
  @author   HRYKY
  @version  $Id: date_parser.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/date/date_parser.h"
#include "hryky/date/date_entity.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace date
{
namespace
{
} // namespace "anonymous"
} // namespace date
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
hryky::date::Parser::Parser()
	: base_type()
	  , entity_()
{
}
/**
  @brief constructor with memory pool.
 */
hryky::date::Parser::Parser(mempool_type const mempool)
	: base_type(mempool)
	  , entity_()
{
}
/**
  @brief copy constructor.
 */
hryky::date::Parser::Parser(this_type const & rhs)
	: base_type()
	  , hryky_copy_member(entity)
{
}
/**
  @brief move constructor.
 */
hryky::date::Parser::Parser(this_type && rhs)
	: base_type()
	  , hryky_move_member(entity)
{
}
/**
  @brief destructor.
 */
hryky::date::Parser::~Parser()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::date::Parser::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::date::Parser::swap(this_type & src)
{
	this->base_type::swap(src);
	hryky_swap_member(entity);
}
/**
  @brief assigns the destination to which the result is written.
 */
void hryky::date::Parser::entity(entity_type * const src)
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
namespace date
{
namespace
{
} // namespace "anonymous"
} // namespace date
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
