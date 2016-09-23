/**
  @file         is_signed.h
  @brief        confirms whether a type is signed type.
  @author       HRYKY
  @version      $Id: is_signed.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef TYPE_IS_SIGNED_H_20120923200750505
#define TYPE_IS_SIGNED_H_20120923200750505
#include "hryky/definition.h"
#include "hryky/stdint.h"
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// confirms whether a type is signed type.
	template < typename ValueT >
	class IsSigned;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether a type is signed type.
 */
template < typename ValueT >
class hryky::IsSigned
{
public :
	typedef false_type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief specializes int8_t.
 */
template <>
class IsSigned<int8_t>
{
public :
	typedef true_type type;
};
/**
  @brief specializes int16_t.
 */
template <>
class IsSigned<int16_t>
{
public :
	typedef true_type type;
};
/**
  @brief specializes int32_t.
 */
template <>
class IsSigned<int32_t>
{
public :
	typedef true_type type;
};
/**
  @brief specializes int64_t.
 */
template <>
class IsSigned<int64_t>
{
public :
	typedef true_type type;
};
#if hryky_distinct_int_and_int32
/**
  @brief specializes int_t.
 */
template <>
class IsSigned<int_t>
{
public :
	typedef true_type type;
};
#endif // hryky_distinct_int_and_int32
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
#endif // TYPE_IS_SIGNED_H_20120923200750505
// end of file
