/**
  @file     symbolic_computation_reduce_int_power.h
  @brief    confirms the possibility to reduce an integral exponent.
  @author   HRYKY
  @version  $Id: symbolic_computation_reduce_int_power.h 355 2014-06-22 08:47:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_SYMPLIFY_INT_POWER_H_20131013160319335
#define SYMBOLIC_COMPUTATION_SYMPLIFY_INT_POWER_H_20131013160319335
#include "hryky/symbolic_computation/symbolic_computation_simplify.h"
#include "hryky/symbolic_computation/symbolic_computation_int_power.h"
#include "hryky/tmp/tmp_pow.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename BaseopT, int Exponent
#define hryky_template_arg \
	BaseopT, Exponent
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	template <typename EvalT, int Value>
	class Integer;

	template <typename EvalT, int Dividend, int Divisor>
	class Fraction;

	template <typename EvalT, int Dividend, int Divisor>
	class FractionImpl;

	template <
		hryky_template_param,
		bool Positive = (0 < Exponent)
	>
	class ReduceIntPower;
	
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief reduces IntPowerImpl with the sign of exponent.
 */
template <typename BaseopT, int Exponent, bool Positive>
class hryky::symbolic_computation::ReduceIntPower
{
private :
	typedef Reduce<BaseopT> baseop;
	typedef IntPower<baseop, Exponent> int_power;
public :
	static bool const value = baseop::value || IsAtom<int_power>::value;
	typedef typename ReduceIfC<value, int_power>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief reduces the power whose exponent is integral value.
 */
template <hryky_template_param>
class ReduceImpl<IntPowerImpl<hryky_template_arg> >
{
private :
	typedef ReduceIntPower<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
//------------------------------------------------------------------------------
// specializes power whose exponent is integral.
//------------------------------------------------------------------------------
/**
  @brief calculates the power of integral value with a positive exponent.
 */
template <typename EvalT, int Value, int Exponent>
class ReduceIntPower<Integer<EvalT, Value>, Exponent, true>
{
public :
	typedef typename Integer<
		EvalT, tmp::PowC<Value, Exponent>::value>::type type;
	static bool const value = true;
};
/**
  @brief calculates the power of integral value with a negative exponent.
 */
template <typename EvalT, int Value, int Exponent>
class ReduceIntPower<Integer<EvalT, Value>, Exponent, false>
{
public :
	typedef typename Reduce<Fraction<
		EvalT,
		1,
		tmp::PowC<Value, -Exponent>::value
	> >::type type;
	static bool const value = true;
};
/**
  @brief calculates the power of fraction with a positive exponent.
 */
template <typename EvalT, int Dividend, int Divisor, int Exponent>
class ReduceIntPower<
	FractionImpl<EvalT, Dividend, Divisor>, Exponent, true>
{
public :
	typedef typename Reduce<
		Fraction<
			EvalT,
			tmp::PowC<Dividend, Exponent>::value,
			tmp::PowC<Divisor, Exponent>::value
		>
	>::type type;
	static bool const value = true;
};
/**
  @brief calculates the power of fraction with a negative exponent.
 */
template <typename EvalT, int Dividend, int Divisor, int Exponent>
class ReduceIntPower<
	FractionImpl<EvalT, Dividend, Divisor>, Exponent, false>
{
public :
	typedef typename Reduce<
		Fraction<
			EvalT,
			tmp::PowC<Divisor, -Exponent>::value,
			tmp::PowC<Dividend, -Exponent>::value
		>
	>::type type;
	static bool const value = true;
};
/**
  @brief multiplies exponents.
 */
template <
	typename BaseopT, int InnerExponent, int OuterExponent, bool Positive>
class ReduceIntPower<
	IntPowerImpl<BaseopT, InnerExponent>, OuterExponent, Positive>
{
public :
	typedef typename Reduce<
		IntPower<BaseopT, InnerExponent * OuterExponent> >::type type;
	static bool const value = true;
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
#endif // SYMBOLIC_COMPUTATION_SYMPLIFY_INT_POWER_H_20131013160319335
// end of file
