/**
  @file         is_unsigned.h
  @brief        confirms whether a type is unsigned.
  @author       HRYKY
  @version      $Id: is_unsigned.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef TYPE_IS_UNSIGNED_H_20120923195217494
#define TYPE_IS_UNSIGNED_H_20120923195217494
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
	/// confirms whether a type is unsigned.
	template < typename ValueT >
	class IsUnsigned;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether a type is unsigned.
 */
template < typename ValueT >
class hryky::IsUnsigned
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
  @brief specializes uint8_t.
 */
template <>
class IsUnsigned<uint8_t>
{
public :
	typedef true_type type;
};
/**
  @brief specializes uint16_t.
 */
template <>
class IsUnsigned<uint16_t>
{
public :
	typedef true_type type;
};
/**
  @brief specializes uint32_t.
 */
template <>
class IsUnsigned<uint32_t>
{
public :
	typedef true_type type;
};
/**
  @brief specializes uint64_t.
 */
template <>
class IsUnsigned<uint64_t>
{
public :
	typedef true_type type;
};
/**
  @brief specializes uint64_t.
 */
template <>
class IsUnsigned<uint_t>
{
public :
	typedef true_type type;
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
#endif // TYPE_IS_UNSIGNED_H_20120923195217494
// end of file
