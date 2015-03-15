/**
  @file     bits_length.h
  @brief    retrieves the highest position of enable bit.
  @author   HRYKY
  @version  $Id: bits_length.h 360 2014-07-05 06:59:57Z hryky.private@gmail.com $
 */
#ifndef BITS_LENGTH_H_20130922161405343
#define BITS_LENGTH_H_20130922161405343
#include "hryky/integer/lower_of.h"
#include "hryky/bitsize_of.h"
#include "hryky/high_bits.h"
#include "hryky/low_bits.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the highest position of 1 bit in arbitrary bit string.
	template <typename ValueT>
	size_t bits_length(ValueT const bits);

	/// retrieves the highest position of 1 bit in 8 bit string.
	size_t bits_length(uint8_t const bits);

	/// retrieves the highest position of 1 bit in 8 bit string.
	size_t bits_length(int8_t const bits);

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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the highest position of 1 bit in arbitrary bit string.
 */
template <typename ValueT>
hryky::size_t hryky::bits_length(ValueT const bits)
{
	typedef typename LowerOf<ValueT>::type lower_type;
	size_t const high = bits_length(high_bits(bits));
	
	return (
		0 < high ? high + BitsizeOf<lower_type>::value :
		bits_length(low_bits(bits)));
}
/**
  @brief retrieves the highest position of 1 bit in 8 bit string.
 */
inline
hryky::size_t hryky::bits_length(uint8_t const bits)
{
	return static_cast<size_t>(
		0 < ((1 << 7) & bits) ? 8 :
		0 < ((1 << 6) & bits) ? 7 :
		0 < ((1 << 5) & bits) ? 6 :
		0 < ((1 << 4) & bits) ? 5 :
		0 < ((1 << 3) & bits) ? 4 :
		0 < ((1 << 2) & bits) ? 3 :
		0 < ((1 << 1) & bits) ? 2 :
		0 < (1 & bits) ? 1 : 0);
}
/**
  @brief retrieves the highest position of 1 bit in 8 bit string.
 */
inline
hryky::size_t hryky::bits_length(int8_t const bits)
{
	return bits_length(static_cast<uint8_t>(bits));
}
#endif // BITS_LENGTH_H_20130922161405343
// end of file
