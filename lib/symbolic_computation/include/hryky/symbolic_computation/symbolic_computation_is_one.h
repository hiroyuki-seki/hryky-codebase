/**
  @file     symbolic_computation_is_one.h
  @brief    confirms whether a type represents one.
  @author   HRYKY
  @version  $Id: symbolic_computation_is_one.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_IS_ONE_H_20131111231131632
#define SYMBOLIC_COMPUTATION_IS_ONE_H_20131111231131632
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
	/// confirms whether a type represents one.
	template <
		typename ValueT, typename EvalT = typename ValueT::type::eval_type
	>
	class IsOne;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether a type represents one.
 */
template <hryky_template_param>
class hryky::symbolic_computation::IsOne
{
public :
	static bool const value = IsSame<
		typename Integer<EvalT, 1>::type,
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
#endif // SYMBOLIC_COMPUTATION_IS_ONE_H_20131111231131632
// end of file
