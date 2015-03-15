/**
  @file     symbolic_computation_subtract.h
  @brief    operates a subtraction.
  @author   HRYKY
  @version  $Id: symbolic_computation_subtract.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_SUBTRACT_H_20131010122142181
#define SYMBOLIC_COMPUTATION_SUBTRACT_H_20131010122142181
#include "hryky/symbolic_computation/symbolic_computation_differentiate.h"
#include "hryky/symbolic_computation/symbolic_computation_evalable.h"
#include "hryky/symbolic_computation/symbolic_computation_integer.h"
#include "hryky/symbolic_computation/symbolic_computation_scatter.h"
#include "hryky/symbolic_computation/symbolic_computation_some.h"
#include "hryky/symbolic_computation/symbolic_computation_with_stream_out.h"
#include "hryky/symbolic_computation/symbolic_computation_substitute.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename LhsT, typename RhsT
#define hryky_template_arg \
	LhsT, RhsT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// The alias of Subtract.
	template <hryky_template_param>
	class Sub;

	/// operates a subtraction.
	template <hryky_template_param>
	class Subtract;

	/// specializes a subtraction in regard to the LHS.
	template <hryky_template_param>
	class SubLhs;

	/// specializes a subtraction in regard to the RHS.
	template <hryky_template_param>
	class SubRhs;

	/// operates a subtraction internally.
	template <hryky_template_param>
	class SubtractImpl;

	template <typename LhsT, typename RhsT>
	class AddImpl;

	template <typename TermT>
	class Complement;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The alias of Subtract.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Sub :
	public WithStreamOut<Sub<hryky_template_arg> >,
	public Evalable<
		Sub<hryky_template_arg>, typename LhsT::type::eval_type>
{
private :
	typedef Subtract<typename LhsT::type, typename RhsT::type> impl;
public :
	typedef typename impl::type         type;
};
/**
  @brief operates a subtraction.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Subtract :
	public WithStreamOut<Subtract<hryky_template_arg> >,
	public Evalable<
		Subtract<hryky_template_arg>,
		typename LhsT::type::eval_type>
{
private :
	typedef SubLhs<typename LhsT::type, typename RhsT::type> impl;
public :
	typedef typename impl::type         type;
};
/**
  @brief specializes a subtraction in regard to the LHS.
 */
template <hryky_template_param>
class hryky::symbolic_computation::SubLhs
{
public :
	typedef typename SubRhs<hryky_template_arg>::type type;
};
/**
  @brief specializes a subtraction in regard to the RHS.
 */
template <hryky_template_param>
class hryky::symbolic_computation::SubRhs
{
public :
	typedef typename SubtractImpl<hryky_template_arg>::type type;
};
/**
  @brief operates a subtraction internally.
 */
template <hryky_template_param>
class hryky::symbolic_computation::SubtractImpl :
	public hryky::WithStreamOut<SubtractImpl<hryky_template_arg> >
{
public :
	typedef typename LhsT::type                 lhs_type;
	typedef typename RhsT::type                 rhs_type;
	typedef SubtractImpl<hryky_template_arg>    type;
	
	typedef decltype(
		typename lhs_type::eval_type() - typename rhs_type::eval_type())
		eval_type;

	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters)
	{
		return lhs_type::eval(parameters) -
			rhs_type::eval(parameters);
	}

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
  @brief ignores zero at LHS.
 */
template <typename RhsT>
class SubLhs<Integer<typename RhsT::eval_type, 0>, RhsT>
{
public :
	typedef typename Complement<RhsT>::type type;
};
/**
  @brief ignores zero at RHS.
 */
template <typename LhsT>
class SubRhs<LhsT, Integer<typename LhsT::eval_type, 0> >
{
public :
	typedef typename LhsT::type type;
};
/**
  @brief calculates the subtraction between integral values.
 */
template <typename EvalT, int Lhs, int Rhs>
class SubtractImpl<Integer<EvalT, Lhs>, Integer<EvalT, Rhs> >
{
public :
	typedef typename Integer<EvalT, Lhs - Rhs>::type type;
};
/**
  @brief calculates the subtraction between fractions.
 */
template <
	typename EvalT,
	int LhsDividend,
	int LhsDivisor,
	int RhsDividend,
	int RhsDivisor
>
class SubtractImpl<
	FractionImpl<EvalT, LhsDividend, LhsDivisor>,
	FractionImpl<EvalT, RhsDividend, RhsDivisor>
>
{
public :
	typedef typename Fraction<
		EvalT,
		LhsDividend * RhsDivisor - RhsDividend * LhsDivisor,
		LhsDivisor * RhsDivisor
	>::type type;
};
/**
  @brief calculates the subtraction between integer and fraction.
 */
template <
	typename EvalT,
	int Value,
	int Dividend,
	int Divisor
>
class SubtractImpl<
	Integer<EvalT, Value>, FractionImpl<EvalT, Dividend, Divisor> >
{
public :
	typedef typename Fraction<
		EvalT, Divisor * Value - Dividend, Divisor>::type type;
};
/**
  @brief calculates the subtraction between fraction and integer.
 */
template <
	typename EvalT,
	int Dividend,
	int Divisor,
	int Value
>
class SubtractImpl<
	FractionImpl<EvalT, Dividend, Divisor>, Integer<EvalT, Value> >
{
public :
	typedef typename Fraction<
		EvalT, Dividend - Divisor * Value, Divisor>::type type;
};
//------------------------------------------------------------------------------
// specializes other classes in respect to this class.
//------------------------------------------------------------------------------
/**
  @brief evaluates function through subtraction.
 */
template <hryky_template_param, template <typename> class FunctionT>
class SomeImpl<SubtractImpl<hryky_template_arg>, FunctionT>
{
public :
	typedef typename Some2<LhsT, RhsT, FunctionT>::type type;
};
/**
  @brief Subtraction can be divided if both term can be divided.
 */
template <hryky_template_param, typename WrtT>
class DividableImpl<SubtractImpl<hryky_template_arg>, WrtT>
{
private :
	typedef Dividable<LhsT, WrtT> lhs;
	typedef Dividable<RhsT, WrtT> rhs;
public :
	typedef typename ConditionalC<
		lhs::value && rhs::value,
		typename Sub<lhs, rhs>::type,
		typename Sub<LhsT, RhsT>::type
	>::type type;
	static bool const value = lhs::value && rhs::value;
};
/**
  @brief substites operations in both terms.
 */
template <hryky_template_param, typename ForT, typename AlternativeT>
class SubstituteImpl<SubtractImpl<hryky_template_arg>, ForT, AlternativeT>
{
private :
	typedef SubtractImpl<hryky_template_arg> target;
public :
	typedef typename Sub<
		Substitute<typename target::lhs_type, ForT, AlternativeT>,
		Substitute<typename target::rhs_type, ForT, AlternativeT>
	>::type type;
};
/**
  @brief differentiates an operation of binary add.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<SubtractImpl<hryky_template_arg>, WrtT>
{
private :
	typedef SubtractImpl<hryky_template_arg> target;
public :
	typedef typename Sub<
		D<typename target::lhs_type, WrtT>,
		D<typename target::rhs_type, WrtT>
	>::type type;
};
/**
  @brief distributes multiplications in the both terms.
 */
template <hryky_template_param>
class ScatterImpl<SubtractImpl<hryky_template_arg> >
{
public :
	typedef typename Sub<Scatter<LhsT>, Scatter<RhsT> >::type type;
};
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief prints a subtraction operation to an outout string-stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::SubtractImpl<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out << '(' << lhs_type() << '-' << rhs_type() << ')';
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
#endif // SYMBOLIC_COMPUTATION_SUBTRACT_H_20131010122142181
// end of file
