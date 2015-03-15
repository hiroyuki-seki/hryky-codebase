/**
  @file         http_header_cache_directive_common.h
  @brief        common definitions for hryky::http::header::cache::directive.
  @author       HRYKY
  @version      $Id: http_header_cache_directive_common.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_CACHE_DIRECTIVE_COMMON_H_20121123115311161
#define HTTP_HEADER_CACHE_DIRECTIVE_COMMON_H_20121123115311161
#include "hryky/kind.h"
#include "hryky/literal_string.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
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
	struct Kind {
		enum Raw {
			extention,
			no_cache,
			no_store,
			max_age,
			max_stale,
			min_fresh,
			no_transform,
			only_if_cached,
			as_public,
			as_private,
			must_revalidate,
			proxy_revalidate,
			s_maxage,
			num,
		};
	};

	extern LiteralString<> const g_tokens[Kind::num];

	typedef hryky::Kind<
		Kind, Kind::extention, Kind::num, LiteralString<>, g_tokens> kind_type;
	
} // namespace directive
} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
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
} // namespace directive
} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_CACHE_DIRECTIVE_COMMON_H_20121123115311161
// end of file
