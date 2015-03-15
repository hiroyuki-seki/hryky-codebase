/**
  @file         http_header_connection_common.cpp
  @brief        common definitions for hryky::http::header::connection.
  @author       HRYKY
  @version      $Id: http_header_connection_common.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_connection_common.h"
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
namespace connection
{
	LiteralString<> const g_tokens[Kind::num] = {
		LiteralString<>("keep-alive"),
		LiteralString<>("close"),
	};

namespace
{
} // namespace "anonymous"
} // namespace connection
} // namespace header
} // namespace http
} // namespace hryky
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
namespace connection
{
namespace
{
} // namespace "anonymous"
} // namespace connection
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
