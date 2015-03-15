/**
  @file         unsigned_enough.h
  @brief        retrieves the type of integer which has the capacity of the
                specified size.
  @author       HRYKY
  @version      $Id: unsigned_enough.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef UNSIGNED_ENOUGH_H_20130119113535149
#define UNSIGNED_ENOUGH_H_20130119113535149
#include "hryky/stdint.h"
#include "hryky/integer/bits_enough_unsigned.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/**
	  retrieves the type of unsigned integer which has the capacity of the
	  specified byte size.
	 */
	template <size_t Bytes>
	class UnsignedEnoughBytes;

	/**
	  retrieves the type of unsigned integer which has the capacity of the
	  specified exponent.
	 */
	template <size_t BytesExponent>
	class UnsignedEnoughBytesExponent;

	/**
	  retrieves the type of unsigned integer which has the capacity of the
	  specified bits size.
	 */
	template <size_t Bits>
	class UnsignedEnoughBits;

	/**
	  retrieves the type of unsigned integer which can store the specified
	  unsigned integer value.
	 */
	template <uint64_t Uint>
	class UnsignedEnoughUint;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the type of unsigned integer which has the capacity of
  the specified byte size.
 */
template <size_t Bytes>
class hryky::UnsignedEnoughBytes
{
public :
	/**
	  obtains the base-2 logarithm of the Bytes by UnsignedEnoughBytes.
	  0 bytes => 0 (in pow(2, 0))
	  1 bytes => 0 (in pow(2, 0))
	  2 bytes => 1 (in pow(2, 1))
	  3 bytes => 2 (in pow(2, 2))
	  4 bytes => 2 (in pow(2, 2))
	  5 bytes => 3 (in pow(2, 3))
	  ...
	 */
	typedef typename UnsignedEnoughBytesExponent<
		BitsEnoughUnsigned<((Bytes - 1) << 1)>::value - 1>::type type;
};
/**
  @brief retrieves the type of unsigned integer which has the capacity of
  the specified exponent.
 */
template <size_t BytesExponent>
class hryky::UnsignedEnoughBytesExponent
{
public :

};
/**
  @brief retrieves the type of unsigned integer which has the capacity of
  the specified bits.
 */
template <size_t Bits>
class hryky::UnsignedEnoughBits
{
public :
	typedef typename UnsignedEnoughBytes<((Bits + 7) >> 3)>::type type;
};
/**
  @brief retrieves the type of unsigned integer which can store the specified
  unsigned integer.
 */
template <uint64_t Uint>
class hryky::UnsignedEnoughUint
{
public :
	typedef typename UnsignedEnoughBits<
		BitsEnoughUnsigned<Uint>::value>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief The type of unsigned integer which can store 0 bytes value.
 */
template <>
class UnsignedEnoughBytes<0u>
{
public :
	typedef uint8_t type;
};
/**
  @brief The type of unsigned integer which can store 2^0 bytes value.
 */
template <>
class UnsignedEnoughBytesExponent<0>
{
public :
	typedef uint8_t type;
};
/**
  @brief The type of unsigned integer which can store 2^1 bytes value.
 */
template <>
class UnsignedEnoughBytesExponent<1>
{
public :
	typedef uint16_t type;

};
/**
  @brief The type of unsigned integer which can store 2^2 bytes value.
 */
template <>
class UnsignedEnoughBytesExponent<2>
{
public :
	typedef uint32_t type;
};
/**
  @brief The type of unsigned integer which can store 2^3 bytes value.
 */
template <>
class UnsignedEnoughBytesExponent<3>
{
public :
	typedef uint64_t type;
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
#endif // UNSIGNED_ENOUGH_H_20130119113535149
// end of file
