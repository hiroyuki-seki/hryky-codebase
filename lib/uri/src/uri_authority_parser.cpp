/**
  @file     uri_authority_parser.cpp
  @brief    parses characters representing the authority part of URI.
  @author   HRYKY
  @version  $Id: uri_authority_parser.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/uri/uri_authority_parser.h"
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
namespace authority
{
namespace
{
} // namespace "anonymous"
} // namespace authority
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
hryky::uri::authority::Parser::Parser()
	: base_type()
{
}
/**
  @brief copy constructor.
 */
hryky::uri::authority::Parser::Parser(this_type const &)
	: base_type()
{
}
/**
  @brief move constructor.
 */
hryky::uri::authority::Parser::Parser(this_type &&)
	: base_type()
{
}
/**
  @brief destructor.
 */
hryky::uri::authority::Parser::~Parser()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::uri::authority::Parser::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::uri::authority::Parser::swap(this_type & src)
{
	this->base_type::swap(src);
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
namespace authority
{
namespace
{
} // namespace "anonymous"
} // namespace authority
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
