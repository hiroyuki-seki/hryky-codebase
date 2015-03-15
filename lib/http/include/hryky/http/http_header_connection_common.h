/**
  @file         http_header_connection_common.h
  @brief        common definitions for hryky::http::header::connection.
  @author       HRYKY
  @version      $Id: http_header_connection_common.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_CONNECTION_COMMON_H_20120923122346183
#define HTTP_HEADER_CONNECTION_COMMON_H_20120923122346183
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
namespace connection
{
	struct Kind {
		enum Raw {
			keep_alive,
			close,
			num,
			unknown_ = num,
		};
	};

	extern LiteralString<> const g_tokens[Kind::num];

	typedef hryky::Kind<
		Kind, Kind::num, Kind::num, LiteralString<>, g_tokens> kind_type;

} // namespace connection
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
namespace connection
{
} // namespace connection
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_CONNECTION_COMMON_H_20120923122346183
// end of file
