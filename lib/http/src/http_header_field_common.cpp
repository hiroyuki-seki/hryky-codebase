/**
  @file         http_header_field_common.cpp
  @brief        common definitions for hryky::http::field.
  @author       HRYKY
  @version      $Id: http_header_field_common.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_field_common.h"
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
namespace field
{
	LiteralString<> const g_tokens[Kind::num] = {
		// general-header
		LiteralString<>("cache-control"),
		LiteralString<>("connection"),
		LiteralString<>("date"),
		LiteralString<>("pragma"),
		LiteralString<>("trailer"),
		LiteralString<>("transfer-encoding"),
		LiteralString<>("upgrade"),
		LiteralString<>("via"),
		LiteralString<>("warning"),

		// request-header
		LiteralString<>("accept"),
		LiteralString<>("accept-charset"),
		LiteralString<>("accept-encoding"),
		LiteralString<>("accept-language"),
		LiteralString<>("authorization"),
		LiteralString<>("expect"),
		LiteralString<>("from"),
		LiteralString<>("host"),
		LiteralString<>("if-match"),
		LiteralString<>("if-modified-since"),
		LiteralString<>("if-none-match"),
		LiteralString<>("if-range"),
		LiteralString<>("if-unmodified-since"),
		LiteralString<>("max-forwards"),
		LiteralString<>("proxy-authorization"),
		LiteralString<>("range"),
		LiteralString<>("referer"),
		LiteralString<>("te"),
		LiteralString<>("user-agent"),

		// response-header
		LiteralString<>("accept-ranges"),
		LiteralString<>("age"),
		LiteralString<>("etag"),
		LiteralString<>("location"),
		LiteralString<>("proxy-authenticate"),
		LiteralString<>("retry-after"),
		LiteralString<>("server"),
		LiteralString<>("vary"),
		LiteralString<>("www-authenticate"),

		// entity-header
		LiteralString<>("allow"),
		LiteralString<>("content-encoding"),
		LiteralString<>("content-language"),
		LiteralString<>("content-length"),
		LiteralString<>("content-location"),
		LiteralString<>("content-md5"),
		LiteralString<>("content-range"),
		LiteralString<>("content-type"),
		LiteralString<>("expires"),
		LiteralString<>("last-modified"),
	};
	
namespace
{
} // namespace "anonymous"
} // namespace field
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
namespace field
{
namespace
{
} // namespace "anonymous"
} // namespace field
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
