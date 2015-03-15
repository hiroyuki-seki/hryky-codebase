/**
  @file     ip_vf_parser.cpp
  @brief    parses characters representing a future IP Address.
  @author   HRYKY
  @version  $Id: ip_vf_parser.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/ip/ip_vf_parser.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace ip
{
namespace vf
{
namespace
{
} // namespace "anonymous"
} // namespace vf
} // namespace ip
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
hryky::ip::vf::Parser::Parser()
	: base_type()
{
}
/**
  @brief copy constructor.
 */
hryky::ip::vf::Parser::Parser(this_type const &)
	: base_type()
{
}
/**
  @brief move constructor.
 */
hryky::ip::vf::Parser::Parser(this_type &&)
	: base_type()
{
}
/**
  @brief destructor.
 */
hryky::ip::vf::Parser::~Parser()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::ip::vf::Parser::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::ip::vf::Parser::swap(this_type & src)
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
namespace ip
{
namespace vf
{
namespace
{
} // namespace "anonymous"
} // namespace vf
} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
