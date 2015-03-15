/**
  @file     is_divisible.h
  @brief    confirms an integer can be divisible by an other integer.
  @author   HRYKY
  @version  $Id: is_divisible.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef IS_DIVISIBLE_H_20131022223258606
#define IS_DIVISIBLE_H_20131022223258606
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	int Lhs, int Rhs
#define hryky_template_arg \
	Lhs, Rhs
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// confirms an integer can be divisible by an other integer.
	template <hryky_template_param>
	class IsDivisible;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms an integer can be divisible by an other integer.
 */
template <int Lhs, int Rhs>
class hryky::IsDivisible
{
public :
	typedef IntegralConstant<
		bool, Lhs == (Lhs / Rhs * Rhs)> type;
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
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // IS_DIVISIBLE_H_20131022223258606
// end of file
