/**
  @file     utf8_common.h
  @brief    The common definition of utf8 module.
  @author   HRYKY
  @version  $Id: utf8_common.h 362 2014-07-07 09:43:31Z hryky.private@gmail.com $
 */
#ifndef UTF8_COMMON_H_20140325192302474
#define UTF8_COMMON_H_20140325192302474
#include "hryky/stdint.h"
#include "hryky/bitmask.h"
#include "hryky/stream/stream_hex.h"
#include "hryky/log.h"
#include "hryky/json.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace utf8
{
	uint8_t const g_utf8_tail_bits = 6u;
	uint8_t const g_utf8_tail_mask = Bitmask<
		g_utf8_tail_bits, 0u, uint8_t>::value;

} // namespace utf8
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace utf8
{
	/// converts a UTF-32 character to octets of UTF-8.
	template <typename OutputStreamT>
	bool encode(OutputStreamT & dest, char32_t const src);

	/// converts a UTF8 string to the corresponding UTF32 character.
	template <typename InputStreamT>
	bool decode(char32_t & dest, InputStreamT & src);

} // namespace utf8
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief converts a UTF-32 character to octets of UTF-8.
 */
template <typename OutputStreamT>
bool
hryky::utf8::encode(OutputStreamT & dest, char32_t const src)
{
	uint8_t const utf8_1_bits = 7u;
	uint8_t const utf8_2_bits = 11u;
	uint8_t const utf8_3_bits = 16u;
	char32_t const utf8_1_mask = Bitmask<utf8_1_bits, 0u, char32_t>::value;
	char32_t const utf8_2_mask = Bitmask<utf8_2_bits, 0u, char32_t>::value;
	char32_t const utf8_3_mask = Bitmask<utf8_3_bits, 0u, char32_t>::value;
	char32_t const utf8_4_end = 0x00110000;

	if (0 == (src & ~utf8_1_mask)) {
		dest << static_cast<char>(src & utf8_1_mask);
	}
	else if (0 == (src & ~utf8_2_mask)) {
		(dest << static_cast<char>(
			0xC0 | static_cast<char>(
				src >> g_utf8_tail_bits))
		 << static_cast<char>(
			 0x80 | static_cast<char>(
				 src & g_utf8_tail_mask)));
	}
	else if (0 == (src & ~utf8_3_mask)) {
		(dest << static_cast<char>(
			0xE0 | static_cast<char>(
				src >> (g_utf8_tail_bits << 1)))
		 << static_cast<char>(
			 0x80 | static_cast<char>(
				 (src >> g_utf8_tail_bits) & g_utf8_tail_mask))
		 << static_cast<char>(
			 0x80 | static_cast<char>(
				 src & g_utf8_tail_mask)));
	}
	else if (utf8_4_end > src) {
		(dest << static_cast<char>(
			0xF0 | static_cast<char>(
				src >> (g_utf8_tail_bits * 3)))
		 << static_cast<char>(
			 0x80 | static_cast<char>(
				 (src >> (g_utf8_tail_bits << 1)) & g_utf8_tail_mask))
		 << static_cast<char>(
			0x80 | static_cast<char>(
				(src >> g_utf8_tail_bits) & g_utf8_tail_mask))
		 << static_cast<char>(
			 0x80 | static_cast<char>(
				 src & g_utf8_tail_mask)));
	}
	else {
		hryky_log_warning(
			"This character is not encoed by UTF8: " << src);
		return false;
	}

	return true;
}
/**
  @brief converts a UTF8 string to the corresponding UTF32 character.
 */
template <typename InputStreamT>
bool hryky::utf8::decode(
	char32_t & dest, InputStreamT & src)
{
	if (src.eof()) {
		hryky_log_warning(
			"The stream reached the end before the first octet.");
		return false;
	}
	uint8_t first;
	src >> *reinterpret_cast<char *>(&first);

	if (0 == (0x80 & first)) {
		dest = static_cast<char32_t>(first);
		return true;
	}

	uint8_t const utf8_tail_prefix = 2u;

	if (src.eof()) {
		hryky_log_warning(
			"The stream reached the end before the second octet.");
		return false;
	}
	uint8_t second;
	src >> *reinterpret_cast<char *>(&second);
	if (utf8_tail_prefix != (second >> g_utf8_tail_bits)) {
		hryky_log_warning(
			"The UTF8 second octet is invalid:"
			<< (json::writer()
				<< "first" << stream::Hex() << first
				<< "second" << stream::Hex() << second
				));
		return false;
	}

	uint8_t const utf8_2_first_prefix = 0x6u;
	uint8_t const utf8_2_first_bits = 5u;
	uint8_t const utf8_2_first_mask = (1 << utf8_2_first_bits) - 1;

	if (utf8_2_first_prefix == (first >> utf8_2_first_bits)) {
		dest = static_cast<char32_t>(
			(static_cast<uint32_t>(first & utf8_2_first_mask)
			 << g_utf8_tail_bits)
			| (second & g_utf8_tail_mask)
			);
		return true;
	}

	if (src.eof()) {
		hryky_log_warning(
			"The stream reached the end before the third octet.");
		return false;
	}
	uint8_t third;
	src >> *reinterpret_cast<char *>(&third);
	if (utf8_tail_prefix != (third >> g_utf8_tail_bits)) {
		hryky_log_warning(
			"The UTF8 third octet is invalid:"
			<< (json::writer()
				<< "first" << stream::Hex() << first
				<< "second" << stream::Hex() << second
				<< "third" << stream::Hex() << third
				));
		return false;
	}

	uint8_t const utf8_3_first_prefix = 0xEu;
	uint8_t const utf8_3_first_bits = 4u;
	uint8_t const utf8_3_first_mask = (1 << utf8_3_first_bits) - 1;

	if (utf8_3_first_prefix == (first >> utf8_3_first_bits)) {
		dest = static_cast<char32_t>(
			(static_cast<uint32_t>(first & utf8_3_first_mask)
			 << (g_utf8_tail_bits * 2u))
			| (static_cast<uint32_t>(second & g_utf8_tail_mask)
			   << g_utf8_tail_bits)
			| (third & g_utf8_tail_mask)
			);
		return true;
	}

	if (src.eof()) {
		hryky_log_warning(
			"The stream reached the end before the fourth octet.");
		return false;
	}
	uint8_t fourth;
	src >> *reinterpret_cast<char *>(&fourth);
	if (utf8_tail_prefix != (fourth >> g_utf8_tail_bits)) {
		hryky_log_warning(
			"The UTF8 fourth octet is invalid:"
			<< (json::writer()
				<< "first" << stream::Hex() << first
				<< "second" << stream::Hex() << second
				<< "third" << stream::Hex() << third
				<< "fourth" << stream::Hex() << fourth
				));
		return false;
	}

	uint8_t const utf8_4_first_prefix = 0x1Eu;
	uint8_t const utf8_4_first_bits = 3u;
	uint8_t const utf8_4_first_mask = (1 << utf8_4_first_bits) - 1;

	if (utf8_4_first_prefix == (first >> utf8_4_first_bits)) {
		dest = static_cast<char32_t>(
			(static_cast<uint32_t>(first & utf8_4_first_mask)
			 << (g_utf8_tail_bits * 3u))
			| (static_cast<uint32_t>(second & g_utf8_tail_mask)
			   << (g_utf8_tail_bits * 2u))
			| (static_cast<uint32_t>(third & g_utf8_tail_mask)
			   << g_utf8_tail_bits)
			| (fourth & g_utf8_tail_mask)
			);
		return true;
	}

	hryky_log_warning(
		"Five octets of UTF8 is not decoded to char32_t");

	return false;
}
#endif // UTF8_COMMON_H_20140325192302474
// end of file
