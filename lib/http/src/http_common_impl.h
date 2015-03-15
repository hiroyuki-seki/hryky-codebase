/**
  @file         http_common_impl.h
  @brief        internal common definitions of http.
  @author       HRYKY
  @version      $Id: http_common_impl.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef HTTP_COMMON_IMPL_H_20120716050223876
#define HTTP_COMMON_IMPL_H_20120716050223876
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
/// pseudo label of 'case' statement for 'separator' of HTTP syntax.
#define hryky_case_http_separator \
	'(': \
	case ')': \
	case '<': \
	case '>': \
	case '@': \
	case ',': \
	case ';': \
	case ':': \
	case '\\': \
	case '"': \
	case '/': \
	case '[': \
	case ']': \
	case '?': \
	case '=': \
	case '{': \
	case '}': \
	case ascii::sp: \
	case ascii::ht

/// pseudo label of 'case' statement for 'token' of HTTP syntax.
#define hryky_case_http_token \
	hryky_case_ascii_alpha: \
	case hryky_case_ascii_digit: \
	case '!': \
	case '#': \
	case '$': \
	case '%': \
	case '&': \
	case '\'': \
	case '*': \
	case '+': \
	case '-': \
	case '.': \
	case '^': \
	case '_': \
	case '`': \
	case '|': \
	case '~'

/// pseudo label of 'case' statement for NOT 'TEXT' of HTTP syntax.
#define hryky_case_http_not_text \
	0x00: /*NUL*/ \
	case 0x01: /*SOH*/ \
	case 0x02: /*STX*/ \
	case 0x03: /*ETX*/ \
	case 0x04: /*EOT*/ \
	case 0x05: /*ENQ*/ \
	case 0x06: /*ACK*/ \
	case 0x07: /*BEL*/ \
	case 0x08: /*BS*/ \
	/*case 0x09: HT*/ \
	/*case 0x0A: LF*/ \
	case 0x0B: /*VT*/ \
	case 0x0C: /*FF*/ \
	/*case 0x0D: CR*/ \
	case 0x0E: /*SO*/ \
	case 0x0F: /*SI*/ \
	case 0x10: /*DLE*/ \
	case 0x11: /*DC1*/ \
	case 0x12: /*DC2*/ \
	case 0x13: /*DC3*/ \
	case 0x14: /*DC4*/ \
	case 0x15: /*NAK*/ \
	case 0x16: /*SYN*/ \
	case 0x17: /*ETB*/ \
	case 0x18: /*CAN*/ \
	case 0x19: /*EM*/ \
	case 0x1A: /*SUB*/ \
	case 0x1B: /*ESC*/ \
	case 0x1C: /*FS*/ \
	case 0x1D: /*GS*/ \
	case 0x1E: /*RS*/ \
	case 0x1F: /*US*/ \
	case 0x7F /*DEL*/

//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
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
	/// confirms that an octet is a separator of HTTP.
	bool is_separator(octet_type const octet);

	/// confirms that an octet belongs to the character of token.
	bool is_token_char(octet_type const octet);

	/// confirms that an octet belongs to the characters of TEXT.
	bool is_text_char(octet_type const octet);

} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_COMMON_IMPL_H_20120716050223876
// end of file
