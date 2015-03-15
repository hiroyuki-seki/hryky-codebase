/**
  @file     symbolic_computation_divide.h
  @brief    operates a division.
  @author   HRYKY
  @version  $Id: symbolic_computation_divide.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_DIVIDE_H_20131010114739158
#define SYMBOLIC_COMPUTATION_DIVIDE_H_20131010114739158
#include "hryky/stream/ostream_string.h"
#include "hryky/symbolic_computation/symbolic_computation_align.h"
#include "hryky/symbolic_computation/symbolic_computation_differentiate.h"
#include "hryky/symbolic_computation/symbolic_computation_dividable.h"
#include "hryky/symbolic_computation/symbolic_computation_evalable.h"
#include "hryky/symbolic_computation/symbolic_computation_gather.h"
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
	template <typename BaseopT, int Exponent>
	class IntPower;

	/// operates a division.
	template <hryky_template_param>
	class Divide;

	/// specializes division in regard to LHS.
	template <hryky_template_param>
	class DivideLhs;

	/// specializes division in regard to RHS.
	template <hryky_template_param>
	class DivideRhs;

	/// operates a division internally.
	template <hryky_template_param>
	class DivideImpl;

	template <typename LhsT, typename RhsT>
	class Subtract;

	template <typename LhsT, typename RhsT>
	class Multiply;

	template <typename EvalT, int Value>
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
  @brief operates a division.

  The name 'Div' can't be used as the alias of Divide.
  In Vector Analysis, the symbol 'div' means 'divergence' conventionally.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Divide :
	public WithStreamOut<Divide<hryky_template_arg> >,
	public Evalable<
		Divide<hryky_template_arg>,
		typename LhsT::type::eval_type>
{
private :
	typedef DivideLhs<typename LhsT::type, typename RhsT::type> impl;
public :
	typedef typename impl::type         type;
};
/**
  @brief specializes division in regard to LHS.
 */
template <hryky_template_param>
class hryky::symbolic_computation::DivideLhs
{
public :
	typedef typename DivideRhs<hryky_template_arg>::type type;
};
/**
  @brief specializes division in regard to RHS.
 */
template <hryky_template_param>
class hryky::symbolic_computation::DivideRhs
{
public :
	typedef typename DivideImpl<hryky_template_arg>::type type;
};
/**
  @brief operates a division.
 */
template <hryky_template_param>
class hryky::symbolic_computation::DivideImpl :
	public hryky::WithStreamOut<DivideImpl<hryky_template_arg> >
{
public :
	typedef typename LhsT::type                 lhs_type;
	typedef typename RhsT::type                 rhs_type;
	typedef DivideImpl<hryky_template_arg>      type;
	
	typedef decltype(
		typename lhs_type::eval_type() / typename rhs_type::eval_type())
		eval_type;

	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters)
	{
		return lhs_type::eval(parameters) /
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
  @brief The dividend is zero.
 */
template <typename RhsT, typename EvalT>
class DivideLhs<Integer<EvalT, 0>, RhsT>
{
public :
	typedef typename Integer<EvalT, 0>::type type;
};
/**
  @brief divides by one.
 */
template <typename LhsT, typename EvalT>
class DivideRhs<LhsT, Integer<EvalT, 1> >
{
public :
	typedef typename LhsT::type type;
};
/**
  @brief calculates division of integeral values.
 */
template <typename EvalT, int Lhs, int Rhs>
class DivideImpl<Integer<EvalT, Lhs>, Integer<EvalT, Rhs> >
{
public :
	typedef typename Fraction<EvalT, Lhs, Rhs>::type type;
};
/**
  @brief divides an integeral value by a fractional value.
 */
template <typename EvalT, int Lhs, int RLhs, int RRhs>
class DivideImpl<Integer<EvalT, Lhs>, FractionImpl<EvalT, RLhs, RRhs> >
{
public :
	typedef typename Fraction<
		EvalT, Lhs * RRhs, RLhs>::type type;
};
/**
  @brief divides a fractional value by an integral value.
 */
template <typename EvalT, int LLhs, int LRhs, int Rhs>
class DivideImpl<FractionImpl<EvalT, LLhs, LRhs>, Integer<EvalT, Rhs> >
{
public :
	typedef typename Fraction<
		EvalT, LLhs, LRhs * Rhs>::type type;
};
/**
  @brief divides a fractional value by a fractional value.
 */
template <typename EvalT, int LLhs, int LRhs, int RLhs, int RRhs>
class DivideImpl<
	FractionImpl<EvalT, LLhs, LRhs>, FractionImpl<EvalT, RLhs, RRhs> >
{
public :
	typedef typename Fraction<
		EvalT, LLhs * RRhs, LRhs * RLhs>::type type;
};
/**
  @brief specializes if the RHS can is zero. This is DivideImpl by Zero.
 */
template <typename EvalT, typename LhsT>
class DivideImpl<LhsT, Integer<EvalT, 0> >
{
public :
	typedef typename LhsT::type                 lhs_type;
	typedef typename Integer<EvalT, 0>::type    rhs_type;
	typedef typename Integer<EvalT, 0>::type    type;
	typedef EvalT                               eval_type;

	template <typename ParametersT>
	static eval_type eval(
		ParametersT const & parameters)
	{
		static_assert(false, "zero division is detected.");
		return eval_type();
	}
};
//------------------------------------------------------------------------------
// specializes other classes in respect to this class.
//------------------------------------------------------------------------------
/**
  @brief evaluates function through division.
 */
template <hryky_template_param, template <typename> class FunctionT>
class SomeImpl<DivideImpl<hryky_template_arg>, FunctionT>
{
public :
	typedef typename Some2<LhsT, RhsT, FunctionT>::type type;
};
/**
  @brief Division can be divided if either term can be divided.
 */
template <hryky_template_param, typename WrtT>
class DividableImpl<DivideImpl<hryky_template_arg>, WrtT>
{
private :
	typedef Dividable<LhsT, WrtT> lhs;
	typedef Dividable<RhsT, IntPower<WrtT, -1> > rhs;
public :
	typedef typename ConditionalC<
		lhs::value,
		typename Divide<lhs, RhsT>::type,
		typename ConditionalC<
			rhs::value,
			typename Divide<LhsT, rhs>::type,
			typename Divide<LhsT, RhsT>::type
		>::type
	>::type type;
	static bool const value = lhs::value || rhs::value;
};
/**
  @brief substites operations in both terms.
 */
template <hryky_template_param, typename ForT, typename AlternativeT>
class SubstituteImpl<DivideImpl<hryky_template_arg>, ForT, AlternativeT>
{
private :
	typedef DivideImpl<hryky_template_arg> target;
public :
	typedef typename Divide<
		Substitute<typename target::lhs_type, ForT, AlternativeT>,
		Substitute<typename target::rhs_type, ForT, AlternativeT>
	>::type type;
};
/**
  @brief differentiates an operation of binary division.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<DivideImpl<hryky_template_arg>, WrtT>
{
private :
	typedef DivideImpl<hryky_template_arg> target;
public :
	typedef typename Subtract<
		Divide<
			D<typename target::lhs_type, WrtT>,
			typename target::rhs_type
		>,
		Divide<
			Multiply<
				typename target::lhs_type,
				D<typename target::rhs_type, WrtT> >,
			Multiply<
				typename target::rhs_type,
				typename target::rhs_type>
		>
	>::type type;
};
/**
  @brief extracts multiplier in dividend and divisor.
 */
template <hryky_template_param>
class GatherImpl<DivideImpl<hryky_template_arg> >
{
public :
	typedef typename Divide<Gather<LhsT>, Gather<RhsT> >::type type;
};
/**
  @brief aligns operations in the both terms.
 */
template <hryky_template_param>
class AlignImpl<DivideImpl<hryky_template_arg> >
{
public :
	typedef typename Divide<Align<LhsT>, Align<RhsT> >::type type;
};
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief prints a division operation.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::DivideImpl<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out << '(' << lhs_type() << '/' << rhs_type() << ')';
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
#endif // SYMBOLIC_COMPUTATION_DIVIDE_H_20131010114739158
// end of file
