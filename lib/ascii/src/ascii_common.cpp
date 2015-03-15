/**
  @file         ascii_common.cpp
  @brief        utility for US-ASCII.
  @author       HRYKY
  @version      $Id: ascii_common.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/ascii/ascii_common.h"
#include "hryky/intrusive_ptr.h"
#include "hryky/debug/debug_source.h"
#include "hryky/log/log_definition.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace
{
} // namespace "anonymous"
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief confirms whether the octet is in the range of ASCII Codes.
 */
bool hryky::ascii::verify(octet_type const octet)
{
	return 0 == (0x80 & octet);
}
/**
  @brief confirms whether the octet is a non-printable control character.
 */
bool hryky::ascii::is_control(octet_type const octet)
{
	return 0 == (0xE0 & octet) || 0x7F == octet;
}
/**
  @brief confirms that an octet is a DIGIT of URI.
 */
bool hryky::ascii::is_digit(octet_type const octet)
{
	switch (octet) {
	case hryky_case_ascii_digit:
		return true;
	default:
		return false;
	}
}
/**
  @brief confirms that an octet is a HEXDIG of URI.
 */
bool hryky::ascii::is_hexdig(octet_type const octet)
{
	switch (octet) {
	case hryky_case_ascii_hexdig:
		return true;
	default:
		return false;
	}
}
/**
  @brief converts an octet to the corresponding number in decimal.
 */
bool hryky::ascii::to_digit(uint8_t & dest, octet_type const octet)
{
	switch (octet) {
	case '0': dest = 0x0u; break;
	case '1': dest = 0x1u; break;
	case '2': dest = 0x2u; break;
	case '3': dest = 0x3u; break;
	case '4': dest = 0x4u; break;
	case '5': dest = 0x5u; break;
	case '6': dest = 0x6u; break;
	case '7': dest = 0x7u; break;
	case '8': dest = 0x8u; break;
	case '9': dest = 0x9u; break;
	default:
		hryky_log_debug(
			"the octet "
			<< static_cast<uint16_t>(octet)
			<< " is not converted to a decimal number");
		return false;
	}
	return true;
}
/**
  @brief converts an octet to the corresponding number in decimal without checking an error.
 */
hryky::uint8_t hryky::ascii::to_digit(octet_type const octet)
{
	switch (octet) {
	case '0': return 0x0u;
	case '1': return 0x1u;
	case '2': return 0x2u;
	case '3': return 0x3u;
	case '4': return 0x4u;
	case '5': return 0x5u;
	case '6': return 0x6u;
	case '7': return 0x7u;
	case '8': return 0x8u;
	case '9': return 0x9u;
	default:
		hryky_log_debug(
			"The octet "
			<< static_cast<uint16_t>(octet)
			<< " is not converted to a decimal number");
		return 0x0u;
	}
}
/**
  @brief converts an octet to the corresponding number in hexadecimal.
 */
bool hryky::ascii::to_hexdig(uint8_t & dest, octet_type const octet)
{
	switch (octet) {
	case '0': dest = 0x0u; break;
	case '1': dest = 0x1u; break;
	case '2': dest = 0x2u; break;
	case '3': dest = 0x3u; break;
	case '4': dest = 0x4u; break;
	case '5': dest = 0x5u; break;
	case '6': dest = 0x6u; break;
	case '7': dest = 0x7u; break;
	case '8': dest = 0x8u; break;
	case '9': dest = 0x9u; break;
	case 'A': dest = 0xAu; break;
	case 'B': dest = 0xBu; break;
	case 'C': dest = 0xCu; break;
	case 'D': dest = 0xDu; break;
	case 'E': dest = 0xEu; break;
	case 'F': dest = 0xFu; break;
	case 'a': dest = 0xAu; break;
	case 'b': dest = 0xBu; break;
	case 'c': dest = 0xCu; break;
	case 'd': dest = 0xDu; break;
	case 'e': dest = 0xEu; break;
	case 'f': dest = 0xFu; break;
	default:
		hryky_log_debug(
			"The octet "
			<< static_cast<uint16_t>(octet)
			<< " is not converted to a hexadecimal number");
		return false;
	}
	return true;
}
/**
  @brief converts an octet to the corresponding number in hexadecimal without checking an error.
 */
hryky::uint8_t hryky::ascii::to_hexdig(octet_type const octet)
{
	switch (octet) {
	case '0': return 0x0u;
	case '1': return 0x1u;
	case '2': return 0x2u;
	case '3': return 0x3u;
	case '4': return 0x4u;
	case '5': return 0x5u;
	case '6': return 0x6u;
	case '7': return 0x7u;
	case '8': return 0x8u;
	case '9': return 0x9u;
	case 'A': return 0xAu;
	case 'B': return 0xBu;
	case 'C': return 0xCu;
	case 'D': return 0xDu;
	case 'E': return 0xEu;
	case 'F': return 0xFu;
	case 'a': return 0xAu;
	case 'b': return 0xBu;
	case 'c': return 0xCu;
	case 'd': return 0xDu;
	case 'e': return 0xEu;
	case 'f': return 0xFu;
	default:
		hryky_log_debug(
			"The octet "
			<< static_cast<uint16_t>(octet)
			<< " is not converted to a hexadecimal number");
		return 0x0u;
	}
}
/**
  @brief confirms that an octet is a alphabet.
 */
bool hryky::ascii::is_alpha(octet_type const octet)
{
	switch (octet) {
	case hryky_case_ascii_alpha:
		return true;
	default:
		return false;
	}
}
/**
  @brief confirms that an octet is a uppercase character of alphabet.
 */
bool hryky::ascii::is_upalpha(octet_type const octet)
{
	switch (octet) {
	case hryky_case_ascii_upalpha:
		return true;
	default:
		return false;
	}
}
/**
  @brief confirms that an octet is a lowercase character of alphabet.
 */
bool hryky::ascii::is_loalpha(octet_type const octet)
{
	switch (octet) {
	case hryky_case_ascii_loalpha:
		return true;
	default:
		return false;
	}
}
/**
  @brief converts the upper-case character to the lower-case character.
 */
hryky::octet_type hryky::ascii::to_lower(octet_type const octet)
{
	switch (octet) {
	case hryky_case_ascii_upalpha:
		return octet | 0x20u;
	default:
		return octet;
	}
}
/**
  @brief convert the lower-case character to the upper-case character.
 */
hryky::octet_type hryky::ascii::to_uppper(octet_type const octet)
{
	switch (octet) {
	case hryky_case_ascii_loalpha:
		return octet & 0xDFu;
	default:
		return octet;
	}
}
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace
{
} // namespace "anonymous"
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
