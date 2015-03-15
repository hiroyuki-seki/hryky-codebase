/**
  @file         http_header_field_common.h
  @brief        common definitions for hryky::http::field.
  @author       HRYKY
  @version      $Id: http_header_field_common.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_FIELD_COMMON_H_20120908165811373
#define HTTP_HEADER_FIELD_COMMON_H_20120908165811373
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
namespace field
{
	struct Kind {
		enum Raw {
			// general-header
			begin,
			general_header_begin    = begin,
			cache_control           = general_header_begin,
			connection,
			date,
			pragma,
			trailer,
			transfer_encoding,
			upgrade,
			via,
			warning,
			general_header_end,

			// request-header
			request_header_begin    = general_header_end,
			accept                  = request_header_begin,
			accept_charset,
			accept_encoding,
			accept_language,
			authorization,
			expect,
			from,
			host,
			if_match,
			if_modified_since,
			if_none_match,
			if_range,
			if_unmodified_since,
			max_forwards,
			proxy_authorization,
			range,
			referer,
			te,
			user_agent,
			request_header_end,

			// response-header
			response_header_begin   = request_header_end,
			accept_ranges           = response_header_begin,
			age,
			etag,
			location,
			proxy_authenticate,
			retry_after,
			server,
			vary,
			www_authenticate,
			response_header_end,

			// entity-header
			entity_header_begin     = response_header_end,
			allow                   = entity_header_begin,
			content_encoding,
			content_language,
			content_length,
			content_location,
			content_md5,
			content_range,
			content_type,
			expires,
			last_modified,
			entity_header_end,
			end                     = entity_header_end,

			num                     = end,

			extension_header,
			invalid,
		};
	};

	extern LiteralString<> const g_tokens[Kind::num];

	typedef hryky::Kind<
		Kind, Kind::invalid, Kind::num, LiteralString<>, g_tokens>
			kind_type;

} // namespace field
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
namespace field
{
} // namespace field
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_FIELD_COMMON_H_20120908165811373
// end of file
