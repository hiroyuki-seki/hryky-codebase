/**
  @file         uri_scheme_common.h
  @brief        common definitions of URI Schemes.
  @author       HRYKY
  @version      $Id: uri_scheme_common.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef URI_SCHEME_COMMON_H_20120807232523642
#define URI_SCHEME_COMMON_H_20120807232523642
#include "hryky/kind.h"
#include "hryky/literal_string.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
/// pseudo label of switch-case statement for 'scheme' of URI syntax
#define hryky_case_uri_scheme \
	hryky_case_ascii_alpha: \
	case hryky_case_ascii_digit: \
	case '-': \
	case '+': \
	case '.'

//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
namespace scheme
{
	struct Kind
	{
		enum Raw
		{
			unknown,
			http,
			https,
			ftp,
			ldap,
			mailto,
			urn,
			ws,
			relative,
			
			num,
		};
	};

	extern LiteralString<> const g_tokens[Kind::num];

	typedef hryky::Kind<
		Kind, Kind::unknown, Kind::num, LiteralString<>, g_tokens> kind_type;

} // namespace scheme
} // namespace uri
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
namespace uri
{
namespace scheme
{
	/// confirms whether this octet is one of the characters of URI Scheme.
	bool is_char(octet_type const octet);

} // namespace scheme
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // URI_SCHEME_COMMON_H_20120807232523642
// end of file
