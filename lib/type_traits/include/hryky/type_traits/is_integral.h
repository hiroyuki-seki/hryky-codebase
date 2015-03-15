/**
  @file         is_integral.h
  @brief        confirms wheter the type is integer.
  @author       HRYKY
  @version      $Id: is_integral.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef IS_INTEGRAL_H_20121230175026410
#define IS_INTEGRAL_H_20121230175026410
#include "hryky/type_traits/is_signed.h"
#include "hryky/type_traits/is_unsigned.h"
#include "hryky/type_traits/is_boolean.h"
#include "hryky/type_traits/is_char.h"
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
	/// confirms wheter the type is integer.
	template <typename ValueT>
	class IsIntegral;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms wheter the type is integer.
 */
template <typename ValueT>
class hryky::IsIntegral
{
public :
	typedef typename IntegralConstantOf<tmp::Or<
		IsChar<ValueT>,
		tmp::Or<
			IsBoolean<ValueT>,
			tmp::Or<
				IsSigned<ValueT>,
				IsUnsigned<ValueT>
			>
		>
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
#endif // IS_INTEGRAL_H_20121230175026410
// end of file
