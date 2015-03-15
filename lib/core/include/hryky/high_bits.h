/**
  @file     high_bits.h
  @brief    retrieves the higher part of bits.
  @author   HRYKY
  @version  $Id: high_bits.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef HIGH_BITS_H_20130922175917416
#define HIGH_BITS_H_20130922175917416
#include "hryky/integer/lower_of.h"
#include "hryky/bitsize_of.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
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
	/// retrieves the higher part of bits.
	template <typename ValueT>
	typename LowerOf<ValueT>::type high_bits(ValueT src);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the higher part of bits.
 */
template <typename ValueT>
typename hryky::LowerOf<ValueT>::type hryky::high_bits(ValueT src)
{
	return static_cast<LowerOf<ValueT>::type>(
		src >> (BitsizeOf<ValueT>::value >> 1));;
}
#endif // HIGH_BITS_H_20130922175917416
// end of file
