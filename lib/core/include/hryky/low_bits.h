/**
  @file     low_bits.h
  @brief    retrieves the lower part of bits.
  @author   HRYKY
  @version  $Id: low_bits.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef LOW_BITS_H_20130922180652421
#define LOW_BITS_H_20130922180652421
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
	/// retrieves the lower part of bits.
	template <typename ValueT>
	typename LowerOf<ValueT>::type low_bits(ValueT src);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the lower part of bits.
 */
template <typename ValueT>
typename hryky::LowerOf<ValueT>::type hryky::low_bits(ValueT src)
{
	return static_cast<LowerOf<ValueT>::type>(src);
}
#endif // LOW_BITS_H_20130922180652421
// end of file
