/**
  @file         http_method_common.h
  @brief        common definitions for hryky::http::method.
  @author       HRYKY
  @version      $Id: http_method_common.h 350 2014-04-24 10:10:31Z hryky.private@gmail.com $
 */
#ifndef HTTP_METHOD_COMMON_H_20120718004910700
#define HTTP_METHOD_COMMON_H_20120718004910700
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
namespace method
{
	struct Kind {
		enum Raw {
			options,
			get,
			head,
			post,
			put,
			as_delete,
			trace,
			connect,

			num,

			extension  = num,
			invalid,
		};
	};

	extern LiteralString<> const g_tokens[Kind::num];

	typedef hryky::Kind<
		Kind, Kind::invalid, Kind::num, LiteralString<>, g_tokens>
			kind_type;

	auto const g_equal_character = [](char const lhs, char const rhs) {
		return lhs == rhs;
	};

} // namespace method
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
namespace method
{
} // namespace method
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_METHOD_COMMON_H_20120718004910700
// end of file
