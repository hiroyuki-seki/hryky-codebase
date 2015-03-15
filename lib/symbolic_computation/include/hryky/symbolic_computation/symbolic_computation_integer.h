/**
  @file     symbolic_computation_integer.h
  @brief    represents a constant integral value.
  @author   HRYKY
  @version  $Id: symbolic_computation_integer.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_INTEGER_H_20131010134524239
#define SYMBOLIC_COMPUTATION_INTEGER_H_20131010134524239
#include "hryky/symbolic_computation/symbolic_computation_differentiate.h"
#include "hryky/symbolic_computation/symbolic_computation_dividable.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename EvalT, int Value
#define hryky_template_arg \
	EvalT, Value
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// represents a constant integral value.
	template <hryky_template_param>
	class Integer;

	template <typename EvalT, int Dividend, int Divisor>
	class Fraction;

	template <typename EvalT, int Dividend, int Divisor>
	class FractionImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief represents a constant integral value.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Integer :
	public hryky::WithStreamOut<Integer<hryky_template_arg> >
{
public :
	typedef EvalT eval_type;
	typedef Integer<hryky_template_arg> type;

	/// evaluates an integer.
	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters);

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief divides by integer.
 */
template <hryky_template_param, int Wrt>
class DividableImpl<Integer<hryky_template_arg>, Integer<EvalT, Wrt> >
{
public :
	static bool const value = true;
	typedef typename Fraction<EvalT, Value, Wrt>::type type;
};
/**
  @brief divides by fraction.
 */
template <hryky_template_param, int WrtDividend, int WrtDivisor>
class DividableImpl<
	Integer<hryky_template_arg>,
	FractionImpl<EvalT, WrtDividend, WrtDivisor>
>
{
public :
	static bool const value = true;
	typedef typename Fraction<
		EvalT, Value * WrtDivisor, WrtDividend>::type type;
};
/**
  @brief differentiates a constant integral value.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<Integer<hryky_template_arg>, WrtT>
{
private :
	typedef Integer<hryky_template_arg> derived_type;
public :
	typedef typename Integer<EvalT, 0>::type type;
};
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief evaluates an integer.
 */
template <hryky_template_param>
template <typename ParametersT>
EvalT hryky::symbolic_computation::Integer<hryky_template_arg>::eval(
	ParametersT const &)
{
	return eval_type(Value);
}
/**
  @brief prints an integer.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::Integer<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out << eval_type(Value);
}
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
#endif // SYMBOLIC_COMPUTATION_INTEGER_H_20131010134524239
// end of file
