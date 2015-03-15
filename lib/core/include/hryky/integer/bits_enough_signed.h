/**
  @file         bits_enough_signed.h
  @brief        retrieves the bit width in which a signed value can be stored.
  @author       HRYKY
  @version      $Id: bits_enough_signed.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef BITS_ENOUGH_SIGNED_H_20130928112820144
#define BITS_ENOUGH_SIGNED_H_20130928112820144
#include "hryky/integer/bits_enough_unsigned.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the bit width in which a signed value can be stored.
	template <int64_t SintValue, typename BitsT>
	class BitsEnoughSigned;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the bit width in which a signed value can be stored.
 */
template <int64_t SintValue, typename BitsT = uint32_t>
class hryky::BitsEnoughSigned
{
public :

	static BitsT const value = (
		0 > SintValue ?
		BitsEnoughUnsigned<~SintValue>::value :
		BitsEnoughUnsigned<SintValue>::value) + 1u;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief SintValue is 0.
 */
template <typename BitsT>
class BitsEnoughSigned<0, BitsT>
{
public :

	static BitsT const value = 1u;

};
/**
  @brief SintValue is -1.
 */
template <typename BitsT>
class BitsEnoughSigned<-1, BitsT>
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
#endif // BITS_ENOUGH_SIGNED_H_20130928112820144
// end of file
