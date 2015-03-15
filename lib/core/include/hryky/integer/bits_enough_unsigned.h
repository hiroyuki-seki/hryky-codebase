/**
  @file         bits_enough_unsigned.h
  @brief        retrieves the bit width in which an unsigned value can be stored.
  @author       HRYKY
  @version      $Id: bits_enough_unsigned.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef BITS_ENOUGH_UNSIGNED_H_20130928112739144
#define BITS_ENOUGH_UNSIGNED_H_20130928112739144
#include "hryky/stdint.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the bit width in which an unsigned value can be stored.
	template <uint64_t UintValue, typename BitsT>
	class BitsEnoughUnsigned;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the bit width in which an unsigned value can be stored.
 */
template <uint64_t UintValue, typename BitsT = uint32_t>
class hryky::BitsEnoughUnsigned
{
public :

	static BitsT const value =
		BitsEnoughUnsigned<(UintValue >> 1), BitsT>::value + 1u;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief terminates the recursion when UintValue is 0u.
 */
template <typename BitsT>
class BitsEnoughUnsigned<0u, BitsT>
{
public :

	static BitsT const value = 1u;

};
/**
  @brief terminates the recursion when UintValue is 1u.
 */
template <typename BitsT>
class BitsEnoughUnsigned<1u, BitsT>
{
public :

	static BitsT const value = 1u;

};
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
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
#endif // BITS_ENOUGH_UNSIGNED_H_20130928112739144
// end of file
