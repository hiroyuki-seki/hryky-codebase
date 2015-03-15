/**
  @file         uri_common.h
  @brief        common definitions for hryky::uri.
  @author       HRYKY
  @version      $Id: uri_common.h 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#ifndef URI_COMMON_H_20120716164045361
#define URI_COMMON_H_20120716164045361
#include "hryky/vector.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
/// pseudo label of switch-case statement for 'gen-delim' of URI syntax.
#define hryky_case_uri_gen_delim \
	':': \
	case '/': \
	case '?': \
	case '#': \
	case '[': \
	case ']': \
	case '@'

/// pseudo label of switch-case statement for 'sub-delim' of URI syntax.
#define hryky_case_uri_sub_delim \
	hryky_case_uri_sub_delim_except_plus: \
	case '+'

/// pseudo label of switch-case statement for 'sub-delim' of URI syntax.
#define hryky_case_uri_sub_delim_except_plus \
	'!': \
	case '$': \
	case '&': \
	case '\'': \
	case '(': \
	case ')': \
	case '*': \
	case ',': \
	case ';': \
	case '='

/// pseudo label of switch-case statement for 'unreserved' of URI syntax.
#define hryky_case_uri_unreserved \
hryky_case_uri_unreserved_symbol: \
	case hryky_case_ascii_alpha: \
	case hryky_case_ascii_digit

/**
  pseudo label of switch-case statement for 'unreserved' symbols of URI syntax.
 */
#define hryky_case_uri_unreserved_symbol \
	uri::hyphen: \
	case uri::period: \
	case uri::underscore: \
	case uri::tilde


/// pseudo label of switch-case statement for 'segment' of URI syntax.
#define hryky_case_uri_segment \
	':': \
	case '@': \
	case hryky_case_uri_sub_delim: \
	case hryky_case_uri_unreserved
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
	octet_type const hyphen =      0x2Du;
	octet_type const period =      0x2Eu;
	octet_type const underscore =  0x5Fu;
	octet_type const tilde =       0x7Eu;

	typedef Vector<octet_type> segment_type;
	
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
	/// confirms that an octet is a gen-delim of URI.
	bool is_gen_delim(octet_type const octet);

	/// confirms that an octet is a sub-delim of URI.
	bool is_sub_delim(octet_type const octet);

	/// confirms that an octet is reserved in URI.
	bool is_reserved(octet_type const octet);

	/// confirms that an octet is unreserved in URI.
	bool is_unreserved(octet_type const octet);

	/**
	  confirms whether this octet is one of the characters of segment in URI.
	  @note
	  - The first character of 'percent encoding'(%) isn't included.
	 */
	bool is_segment(octet_type const octet);

	

} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // URI_COMMON_H_20120716164045361
// end of file
