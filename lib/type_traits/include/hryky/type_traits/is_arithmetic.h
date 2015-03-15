/**
  @file         is_arithmetic.h
  @brief        confirmes whether the type is numeric.
  @author       HRYKY
  @version      $Id: is_arithmetic.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef IS_ARITHMETIC_H_20121230174233404
#define IS_ARITHMETIC_H_20121230174233404
#include "hryky/type_traits/is_integral.h"
#include "hryky/type_traits/is_floating_point.h"
#include "hryky/type_traits/integral_constant.h"
#include "hryky/tmp/tmp_or.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// confirmes whether the type is numeric.
	template <typename ValueT>
	class IsArithmetic;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirmes whether the type is numeric.
 */
template <typename ValueT>
class hryky::IsArithmetic
{
public :
	typedef typename IntegralConstantOf<tmp::Or<
		IsIntegral<ValueT>,
		IsFloatingPoint<ValueT>
	> >::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
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
#endif // IS_ARITHMETIC_H_20121230174233404
// end of file
