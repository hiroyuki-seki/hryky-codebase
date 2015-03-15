/**
  @file     symbolic_computation_reduce_fraction.h
  @brief    reduces a fraction.
  @author   HRYKY
  @version  $Id: symbolic_computation_reduce_fraction.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_REDUCE_FRACTION_H_20131116181057424
#define SYMBOLIC_COMPUTATION_REDUCE_FRACTION_H_20131116181057424
#include "hryky/symbolic_computation/symbolic_computation_simplify.h"
#include "hryky/is_divisible.h"
#include "hryky/gcd.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename EvalT, int Dividend, int Divisor
#define hryky_template_arg \
	EvalT, Dividend, Divisor
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	template <hryky_template_param>
	class Fraction;
	
	template <hryky_template_param>
	class FractionImpl;
	
	template <typename EvalT, int Value>
	class Integer;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief simplified a fraction.
 */
template <hryky_template_param>
class ReduceImpl<FractionImpl<EvalT, Dividend, Divisor> >
{
private :
	typedef hryky::IsDivisible<Dividend, Divisor> divisible;
	typedef hryky::Gcd<Dividend, Divisor> gcd;
public :
	typedef typename Conditional<
		divisible,
		// reduces to the integer.
		typename Integer<EvalT, Dividend / Divisor>::type,
		typename ConditionalC<
			1 != gcd::value,
			// divides by the Greatest Common Divisor.
			typename Fraction<
				EvalT,
				Dividend / gcd::value,
				Divisor / gcd::value
			>::type,
			typename Fraction<EvalT, Dividend, Divisor>::type
		>::type
	>::type type;
	
	static bool const value = divisible::type::value || 1 != gcd::value;
};
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
#endif // SYMBOLIC_COMPUTATION_REDUCE_FRACTION_H_20131116181057424
// end of file
