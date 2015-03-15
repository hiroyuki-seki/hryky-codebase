/**
  @file         is_floating_point.h
  @brief        confirms whether a type is builtin floating point.
  @author       HRYKY
  @version      $Id: is_floating_point.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef TYPE_IS_FLOATING_POINT_H_20120923203457524
#define TYPE_IS_FLOATING_POINT_H_20120923203457524
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// confirms whether a type is builtin floating point.
	template < typename ValueT >
	class IsFloatingPoint;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether a type is builtin floating point.
 */
template < typename ValueT >
class hryky::IsFloatingPoint
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
  @brief specializes float.
 */
template <>
class IsFloatingPoint<float>
{
public :
	typedef true_type type;
};
/**
  @brief specializes double.
 */
template <>
class IsFloatingPoint<double>
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
#endif // TYPE_IS_FLOATING_POINT_H_20120923203457524
// end of file
