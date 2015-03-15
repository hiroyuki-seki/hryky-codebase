/**
  @file         ascii_common.h
  @brief        common definitions for hryky::ascii.
  @author       HRYKY
  @version      $Id: ascii_common.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef ASCII_COMMON_H_20120922170458378
#define ASCII_COMMON_H_20120922170458378
#include "hryky/stdint.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
/// pseudo label of 'case' statement for upper case characters of ASCII.
#define hryky_case_ascii_upalpha \
	'A': \
	case 'B': \
	case 'C': \
	case 'D': \
	case 'E': \
	case 'F': \
	case 'G': \
	case 'H': \
	case 'I': \
	case 'J': \
	case 'K': \
	case 'L': \
	case 'M': \
	case 'N': \
	case 'O': \
	case 'P': \
	case 'Q': \
	case 'R': \
	case 'S': \
	case 'T': \
	case 'U': \
	case 'V': \
	case 'W': \
	case 'X': \
	case 'Y': \
	case 'Z'

/// pseudo label of 'case' statement for lower case characters of ASCII.
#define hryky_case_ascii_loalpha \
	'a': \
	case 'b': \
	case 'c': \
	case 'd': \
	case 'e': \
	case 'f': \
	case 'g': \
	case 'h': \
	case 'i': \
	case 'j': \
	case 'k': \
	case 'l': \
	case 'm': \
	case 'n': \
	case 'o': \
	case 'p': \
	case 'q': \
	case 'r': \
	case 's': \
	case 't': \
	case 'u': \
	case 'v': \
	case 'w': \
	case 'x': \
	case 'y': \
	case 'z'

/// pseudo label of 'case' statement for alphabets of ASCII.
#define hryky_case_ascii_alpha \
	hryky_case_ascii_upalpha: \
	case hryky_case_ascii_loalpha

/// pseudo label of 'case' statement for printable characters of ASCII.
#define hryky_case_ascii_printable \
	hryky_case_ascii_alpha: \
	case hryky_case_ascii_digit: \
	case '!': \
	case '"': \
	case '#': \
	case '$': \
	case '%': \
	case '&': \
	case '\'': \
	case '(': \
	case ')': \
	case '*': \
	case '+': \
	case ',': \
	case '-': \
	case '.': \
	case '/': \
	case ':': \
	case ';': \
	case '<': \
	case '=': \
	case '>': \
	case '?': \
	case '@': \
	case '[': \
	case '\\': \
	case ']': \
	case '^': \
	case '_': \
	case '`': \
	case '{': \
	case '|': \
	case '}': \
	case '~'

/// pseudo label of 'case' statement for control characters of ASCII.
#define hryky_case_ascii_control \
	0x00: /*NUL*/ \
	case 0x01: /*SOH*/ \
	case 0x02: /*STX*/ \
	case 0x03: /*ETX*/ \
	case 0x04: /*EOT*/ \
	case 0x05: /*ENQ*/ \
	case 0x06: /*ACK*/ \
	case 0x07: /*BEL*/ \
	case 0x08: /*BS*/ \
	case 0x09: /*HT*/ \
	case 0x0A: /*LF*/ \
	case 0x0B: /*VT*/ \
	case 0x0C: /*FF*/ \
	case 0x0D: /*CR*/ \
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

/// pseudo label of 'case' statement for decimal numbers of ASCII.
#define hryky_case_ascii_digit \
	'0': \
	case '1': \
	case '2': \
	case '3': \
	case '4': \
	case '5': \
	case '6': \
	case '7': \
	case '8': \
	case '9'

/**
   pseudo lable of 'case' statement for upper case characters in hexadecimal
  of ASCII.
 */
#define hryky_case_ascii_uphexdig \
	'A': \
	case 'B': \
	case 'C': \
	case 'D': \
	case 'E': \
	case 'F'

/**
   pseudo lable of 'case' statement for lower case characters in hexadecimal
  of ASCII.
 */
#define hryky_case_ascii_lohexdig \
	'a': \
	case 'b': \
	case 'c': \
	case 'd': \
	case 'e': \
	case 'f'

/// pseudo lable of 'case' statement for hexadecimal numbers of ASCII.
#define hryky_case_ascii_hexdig \
	hryky_case_ascii_digit: \
	case hryky_case_ascii_uphexdig: \
	case hryky_case_ascii_lohexdig

//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace ascii
{
	octet_type const cr = 0x0Du;
	octet_type const lf = 0x0Au;
	octet_type const sp = 0x20u;
	octet_type const ht = 0x09u;
	octet_type const double_quote = 0x22u;
	
	/// confirms whether the octet is in the range of ASCII Codes.
	bool verify(octet_type const octet);

	/// confirms whether the octet is a non-printable control character.
	bool is_control(octet_type const octet);

	/// confirms that an octet is a DIGIT of URI.
	bool is_digit(octet_type const octet);

	/// confirms that an octet is a HEXDIG of URI.
	bool is_hexdig(octet_type const octet);

	/// converts an octet to the corresponding number in decimal.
	bool to_digit(uint8_t & dest, octet_type const octet);

	/// converts an octet to the corresponding number in decimal without checking an error.
	uint8_t to_digit(octet_type const octet);

	/// converts an octet to the corresponding number in hexadecimal.
	bool to_hexdig(uint8_t & dest, octet_type const octet);

	/// converts an octet to the corresponding number in hexadecimal without checking an error.
	uint8_t to_hexdig(octet_type const octet);

	/// confirms that an octet is a alphabet.
	bool is_alpha(octet_type const octet);

	/// confirms that an octet is an uppercase character of alphabet.
	bool is_upalpha(octet_type const octet);

	/// confirms that an octet is a lowercase character of alphabet.
	bool is_loalpha(octet_type const octet);

	/// converts the upper-case character to the lower-case character.
	octet_type to_lower(octet_type const octet);

	/// convert the lower-case character to the upper-case character.
	octet_type to_uppper(octet_type const octet);

} // namespace ascii
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
namespace ascii
{
	/// converts a number to the corresponding hexadecimal character.
	template <typename ValueT>
	char to_hexchar(ValueT const value);

} // namespace ascii
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief converts a number to the corresponding hexadecimal character.
 */
template <typename ValueT>
char hryky::ascii::to_hexchar(ValueT const value)
{
	char const octet = static_cast<char>(value);

	return (
		0 <= octet
		? (10 > octet
		   ? ('0' + octet)
		   : (16 > octet
			  ? 'A' + (octet - 10)
			  : '0'))
		: '0');
}
#endif // ASCII_COMMON_H_20120922170458378
// end of file
