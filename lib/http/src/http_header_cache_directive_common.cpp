/**
  @file         http_header_cache_directive_common.cpp
  @brief        common definitions for hryky::http::header::cache::directive.
  @author       HRYKY
  @version      $Id: http_header_cache_directive_common.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_cache_directive_common.h"
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
namespace cache
{
namespace directive
{
	LiteralString<> const g_tokens[Kind::num] = {
		LiteralString<>("extention"),
		LiteralString<>("no-cache"),
		LiteralString<>("no-store"),
		LiteralString<>("max-age"),
		LiteralString<>("max-stale"),
		LiteralString<>("min-fresh"),
		LiteralString<>("no-transform"),
		LiteralString<>("only-if-cached"),
		LiteralString<>("public"),
		LiteralString<>("private"),
		LiteralString<>("must-revalidate"),
		LiteralString<>("proxy-revalidate"),
		LiteralString<>("s-maxage"),
	};

namespace
{
} // namespace "anonymous"
} // namespace directive
} // namespace cache
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
namespace cache
{
namespace directive
{
namespace
{
} // namespace "anonymous"
} // namespace directive
} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
