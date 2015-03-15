/**
  @file     symbolic_computation_is_zero.h
  @brief    confirms whether a type represents zero.
  @author   HRYKY
  @version  $Id: symbolic_computation_is_zero.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_IS_ZERO_H_20131111231554636
#define SYMBOLIC_COMPUTATION_IS_ZERO_H_20131111231554636
#include "hryky/type_traits/is_same.h"
#include "hryky/symbolic_computation/symbolic_computation_integer.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, typename EvalT
#define hryky_template_arg \
	ValueT, EvalT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// confirms whether a type represents zero.
	template <
		typename ValueT, typename EvalT = typename ValueT::type::eval_type
	>
	class IsZero;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether a type represents zero.
 */
template <hryky_template_param>
class hryky::symbolic_computation::IsZero
{
public :
	static bool const value = IsSame<
		typename Integer<EvalT, 0>::type,
		typename ValueT::type
	>::type::value;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
} // namespace symbolic_computation
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
namespace symbolic_computation
{
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SYMBOLIC_COMPUTATION_IS_ZERO_H_20131111231554636
// end of file
