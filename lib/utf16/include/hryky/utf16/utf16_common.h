/**
  @file     utf16_common.h
  @brief    The common definition of utf16 module.
  @author   HRYKY
  @version  $Id: utf16_common.h 361 2014-07-06 10:03:06Z hryky.private@gmail.com $
 */
#ifndef UTF16_COMMON_H_20140325170559379
#define UTF16_COMMON_H_20140325170559379
#include "hryky/bitmask.h"
#include "hryky/stdint.h"
#include "hryky/type_traits/value_type_of.h"
#include "hryky/type_traits/enable_if.h"
#include "hryky/utf16/utf16_compatible.h"
#include "hryky/log.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace utf16
{
	char16_t const g_high_surrogate_begin = 0xD800;
	char16_t const g_high_surrogate_end = 0xDC00;
	char16_t const g_low_surrogate_begin = 0xDC00;
	char16_t const g_low_surrogate_end = 0xE000;
	char32_t const g_surrogate_pair_begin = 0x100000;
	uint8_t const g_half_surrogate_bits = 10u;
	char16_t const g_half_surrogate_mask = Bitmask<
		g_half_surrogate_bits, 0u, char16_t>::value;
	
} // namespace utf16
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace utf16
{
	/// confirms whether the char16_t is the first half of surrogate pair.
	bool in_high_surrogate(char16_t const src);

	/// extracts the high surrogate from the first half of surrogate pair.
	char16_t to_high_surrogate(char16_t const src);

	/// confirms whether the char16_t is the last half of surrogate pair.
	bool in_low_surrogate(char16_t const src);

	/// extracts the low surrogate from the last half of surrogate pair.
	char16_t to_low_surrogate(char16_t const src);

	/// creates a surrogate pair without checking errors.
	char32_t surrogate_pair(char16_t const high, char16_t const low);

	/// converts utf16 to utf32.
	template <typename InputStreamT>
	bool decode(
		char32_t & dest,
		InputStreamT & src);

	/// converts utf32 to utf16.
	template <typename OutputStreamT>
	bool encode(
		OutputStreamT & dest,
		char32_t const src);

	/// measures the length of a null-terminated string.
	size_t length(char16_t const * const c_str);

} // namespace utf16
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief confirms whether the char16_t is the first half of surrogate pair.
 */
inline
bool hryky::utf16::in_high_surrogate(char16_t const src)
{
	return g_high_surrogate_begin <= src && g_high_surrogate_end > src;
}
/**
  @brief extracts the high surrogate from the first half of surrogate pair.
 */
inline
char16_t hryky::utf16::to_high_surrogate(char16_t const src)
{
	return static_cast<char16_t>(src - g_high_surrogate_begin);
}
/**
  @brief confirms whether the char16_t is the last half of surrogate pair.
 */
inline
bool hryky::utf16::in_low_surrogate(char16_t const src)
{
	return g_low_surrogate_begin <= src && g_low_surrogate_end > src;
}
/**
  @brief extracts the low surrogate from the last half of surrogate pair.
 */
inline
char16_t hryky::utf16::to_low_surrogate(char16_t const src)
{
	return static_cast<char16_t>(src - g_low_surrogate_begin);
}
/**
  @brief creates a surrogate pair without checking errors.
 */
inline
char32_t hryky::utf16::surrogate_pair(
	char16_t const high, char16_t const low)
{
	return (
		g_surrogate_pair_begin
		| (static_cast<char32_t>(high & g_half_surrogate_mask)
		   << g_half_surrogate_bits)
		| static_cast<char32_t>(low & g_half_surrogate_mask)
		);
}
/**
  @brief converts utf16 to utf32.
 */
template <typename InputStreamT>
bool hryky::utf16::decode(
	char32_t & dest, InputStreamT & src)
{
	if (src.eof()) {
		return false;
	}
	char16_t first;
	src >> first;
	
	if (in_high_surrogate(first)) {
		char16_t const half_high = to_high_surrogate(first);

		if (src.eof()) {
			hryky_log_warning(
				"There is no low surrogate area");
			return false;
		}

		char16_t second;
		src >> second;
		if (!in_low_surrogate(second)) {
			hryky_log_warning(
				"The last half of surrogate pair is not in "
				"the low surrogate area.");
			return false;
		}
		char16_t const half_low = to_low_surrogate(second);

		dest = surrogate_pair(half_high, half_low);
	}
	else {
		dest = first;
	}
	
	return true;
}
/**
  @brief converts utf32 to utf16.
 */
template <typename OutputStreamT>
bool hryky::utf16::encode(
	OutputStreamT & dest, char32_t const src)
{
	if (g_surrogate_pair_begin > src) {
		dest << static_cast<char16_t>(src);
		return true;
	}

	if (0x10FFFF < src) {
		hryky_log_warning(
			"This character is not encoded by UTF16: "
			<< src);
		return false;
	}

	(dest
	 << static_cast<char16_t>(
		 g_high_surrogate_begin
		 | ((src >> g_half_surrogate_bits)
			& g_half_surrogate_mask))
	 << static_cast<char16_t>(
		 g_low_surrogate_begin
		 | (src & g_half_surrogate_mask)));
	
	return true;
}
/**
  @brief measures the length of a null-terminated string.
 */
inline
hryky::size_t
hryky::utf16::length(char16_t const * const c_str)
{
	size_t ret = 0u;
	char16_t const * ptr = c_str;
	while (0 != *ptr) {
		++ret;
		++ptr;
	}
	return ret;
}
#endif // UTF16_COMMON_H_20140325170559379
// end of file
