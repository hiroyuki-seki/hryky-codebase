/**
  @file         signed_enough.h
  @brief        retrieves the type of signed integer which has the capacity of
                the specified size.
  @author       HRYKY
  @version      $Id: signed_enough.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SIGNED_ENOUGH_H_20130119160307335
#define SIGNED_ENOUGH_H_20130119160307335
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
	  retrieves the type of signed integer which has the capacity of the
	  specified size.
	 */
	template <size_t Bytes>
	class SignedEnoughBytes;

	/**
	  retrieves the type of signed integer which has the capacity of the
      specified exponent.
	 */
	template <size_t BytesExponent>
	class SignedEnoughBytesExponent;
	
	/**
	  retrieves the type of signed integer which has the capacity of the
	  specified bits.
	 */
	template <size_t Bits>
	class SignedEnoughBits;
	
	/**
	  retrieves the type of signed integer which can store the the
	  signed integer.
	 */
	template <int64_t Int>
	class SignedEnoughInt;
	

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the type of signed integer which has the capacity of
  the specified size.
 */
template <size_t Bytes>
class hryky::SignedEnoughBytes
{
public :
	typedef typename SignedEnoughBytesExponent<
		BitsEnoughUnsigned<((Bytes - 1) << 1)>::value - 1>::type type;

};
/**
  @brief retrieves the type of signed integer which has the capacity of
  the specified exponent.
 */
template <size_t BytesExponent>
class hryky::SignedEnoughBytesExponent
{
public :

};
/**
  @brief retrieves the type of signed integer which has the capacity of
  the specified exponent.
 */
template <size_t Bits>
class hryky::SignedEnoughBits
{
public :
	typedef typename SignedEnoughBytes<((Bits + 7) >> 3)>::type type;

};
/**
  @brief retrieves the type of signed integer which can store the specified
  signed integer.
 */
template <int64_t Int>
class hryky::SignedEnoughInt
{
public :
	typedef typename SignedEnoughBits<
		BitsEnoughSigned<Int>::value>::type type;
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
class SignedEnoughBytes<0u>
{
public :
	typedef int8_t type;
};
/**
  @brief The type of unsigned integer which can store 2^0 bytes value.
 */
template <>
class SignedEnoughBytesExponent<0>
{
public :
	typedef int8_t type;
};
/**
  @brief The type of unsigned integer which can store 2^1 bytes value.
 */
template <>
class SignedEnoughBytesExponent<1>
{
public :
	typedef int16_t type;

};
/**
  @brief The type of unsigned integer which can store 2^2 bytes value.
 */
template <>
class SignedEnoughBytesExponent<2>
{
public :
	typedef int32_t type;
};
/**
  @brief The type of unsigned integer which can store 2^3 bytes value.
 */
template <>
class SignedEnoughBytesExponent<3>
{
public :
	typedef int64_t type;
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
#endif // SIGNED_ENOUGH_H_20130119160307335
// end of file
