/**
  @file     symbolic_computation_multiply.h
  @brief    operates a multiplication.
  @author   HRYKY
  @version  $Id: symbolic_computation_multiply.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_MULTIPLY_H_20131009225020618
#define SYMBOLIC_COMPUTATION_MULTIPLY_H_20131009225020618
#include "hryky/stream/ostream_string.h"
#include "hryky/symbolic_computation/symbolic_computation_differentiate.h"
#include "hryky/symbolic_computation/symbolic_computation_dividable.h"
#include "hryky/symbolic_computation/symbolic_computation_evalable.h"
#include "hryky/symbolic_computation/symbolic_computation_gather.h"
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
	template <typename LhsT, typename RhsT>
	class Add;

	template <typename EvalT, int Dividend, int Divisor>
	class Fraction;

	template <typename EvalT, int Dividend, int Divisor>
	class FractionImpl;

	/// The alias of Multiply.
	template <hryky_template_param>
	class Mul;

	/// operates a multiplication.
	template <hryky_template_param>
	class Multiply;

	/// specializes multiplication in regard to LHS.
	template <hryky_template_param>
	class MulLhs;

	/// specializes multiplication in regard to RHS.
	template <hryky_template_param>
	class MulRhs;

	/// operates a multiplication internally.
	template <hryky_template_param>
	class MultiplyImpl;

	/**
	  @brief achieves the type of either term of MUL operation.
	 */
	template <
		typename LhsEvalT,
		typename RhsEvalT,
		bool EitherNull =
			IsSame<LhsEvalT, hryky::Null>::type::value ||
				IsSame<RhsEvalT, hryky::Null>::type::value
	>
	struct MulEvalType;
	
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The alias of Multiply.
 */
template <typename LhsT, typename RhsT>
class hryky::symbolic_computation::Mul :
	public WithStreamOut<Mul<hryky_template_arg> >,
	public Evalable<Mul<hryky_template_arg>, typename LhsT::type::eval_type>
{
private :
	typedef Multiply<typename LhsT::type, typename RhsT::type> impl;
public :
	typedef typename impl::type         type;
};
/**
  @brief operates a multiplication.
 */
template <typename LhsT, typename RhsT>
class hryky::symbolic_computation::Multiply :
	public WithStreamOut<Multiply<hryky_template_arg> >,
	public Evalable<
		Multiply<hryky_template_arg>,
		typename LhsT::type::eval_type>
{
private :
	typedef MulLhs<typename LhsT::type, typename RhsT::type> impl;
public :
	typedef typename impl::type         type;
};
/**
  @brief specializes multiplication in regard to LHS.
 */
template <hryky_template_param>
class hryky::symbolic_computation::MulLhs
{
public :
	typedef typename MulRhs<hryky_template_arg>::type type;
};
/**
  @brief specializes multiplication in regard to RHS.
 */
template <hryky_template_param>
class hryky::symbolic_computation::MulRhs
{
public :
	typedef typename MultiplyImpl<hryky_template_arg>::type type;
};
/**
  @brief operates a multiplication.
 */
template <hryky_template_param>
class hryky::symbolic_computation::MultiplyImpl :
	public hryky::WithStreamOut<MultiplyImpl<hryky_template_arg> >
{
public :
	typedef typename LhsT::type                 lhs_type;
	typedef typename RhsT::type                 rhs_type;
	typedef MultiplyImpl<hryky_template_arg>    type;
	
	typedef typename MulEvalType<
		typename lhs_type::eval_type,
		typename rhs_type::eval_type
	>::type eval_type;

	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters)
	{
		return lhs_type::eval(parameters) *
			rhs_type::eval(parameters);
	}

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;
};
/**
  @brief achieves the type of either term of MUL operation.
 */
template <typename LhsEvalT, typename RhsEvalT, bool EitherNull>
struct hryky::symbolic_computation::MulEvalType
{
	typedef typename Conditional<
		tmp::Not<IsSame<LhsEvalT, hryky::Null> >,
		LhsEvalT,
		typename Conditional<
			tmp::Not<IsSame<RhsEvalT, hryky::Null> >,
			RhsEvalT,
			int
		>::type
	>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief ignores the value one at LHS.
 */
template <typename EvalT, typename RhsT>
class MulLhs<Integer<EvalT, 1>, RhsT>
{
public :
	typedef typename RhsT::type type;
};
/**
  @brief cancels by the value zero at LHS.
 */
template <typename EvalT, typename RhsT>
class MulLhs<Integer<EvalT, 0>, RhsT>
{
public :
	typedef typename Integer<EvalT, 0>::type type;
};
/**
  @brief ignores the value one at RHS.
 */
template <typename EvalT, typename LhsT>
class MulRhs<LhsT, Integer<EvalT, 1> >
{
public :
	typedef typename LhsT::type type;
};
/**
  @brief cancels by the value zero at RHS.
 */
template <typename EvalT, typename LhsT>
class MulRhs<LhsT, Integer<EvalT, 0> >
{
public :
	typedef typename Integer<EvalT, 0>::type type;
};
/**
  @brief calculates the multiplication between integral values.
 */
template <typename EvalT, int Lhs, int Rhs>
class MultiplyImpl<Integer<EvalT, Lhs>, Integer<EvalT, Rhs> >
{
public :
	typedef typename Integer<EvalT, Lhs * Rhs>::type type;
};
/**
  @brief calculates the multiplication between integral value and fraction.
 */
template <typename EvalT, int Lhs, int Dividend, int Divisor>
class MultiplyImpl<
	Integer<EvalT, Lhs>, FractionImpl<EvalT, Dividend, Divisor> >
{
public :
	typedef typename Fraction<
		EvalT, Lhs * Dividend, Divisor>::type type;
};
/**
  @brief calculates the multiplication between fraction and integral value.
 */
template <typename EvalT, int Rhs, int Dividend, int Divisor>
class MultiplyImpl<
	FractionImpl<EvalT, Dividend, Divisor>, Integer<EvalT, Rhs> >
{
public :
	typedef typename Fraction<
		EvalT, Rhs * Dividend, Divisor>::type type;
};
/**
  @brief calculates the multiplication between two fractions.
 */
template <
	typename EvalT,
	int LhsDividend,
	int LhsDivisor,
	int RhsDividend,
	int RhsDivisor
>
class MultiplyImpl<
	FractionImpl<EvalT, LhsDividend, LhsDivisor>,
	FractionImpl<EvalT, RhsDividend, RhsDivisor>
>
{
public :
	typedef typename Fraction<
		EvalT,
		LhsDividend * RhsDividend,
		LhsDivisor * RhsDivisor
	>::type type;
};
/**
  @brief differentiates by a differential operator.
 */
template <typename TargetT, typename WrtT, typename RhsT>
class MultiplyImpl<DifferentiateImpl<TargetT, WrtT>, RhsT>
{
public :
	typedef typename ApplyDifferentiate<
		RhsT,
		DifferentiateImpl<TargetT, WrtT>
	>::type type;
};
/**
  @brief achieves the type resulted by Multiply operation.
 */
template <typename LhsEvalT, typename RhsEvalT>
struct MulEvalType<LhsEvalT, RhsEvalT, false>
{
	typedef decltype(LhsEvalT() * RhsEvalT()) type;
};
//------------------------------------------------------------------------------
// specializes other classes in respect to this class.
//------------------------------------------------------------------------------
/**
  @brief evaluates function through multiplication.
 */
template <hryky_template_param, template <typename> class FunctionT>
class SomeImpl<MultiplyImpl<hryky_template_arg>, FunctionT>
{
public :
	typedef typename Some2<LhsT, RhsT, FunctionT>::type type;
};
/**
  @brief Multiplication can be divided if either term can be divided.
 */
template <hryky_template_param, typename WrtT>
class DividableImpl<MultiplyImpl<hryky_template_arg>, WrtT>
{
private :
	typedef Dividable<LhsT, WrtT> lhs;
	typedef Dividable<RhsT, WrtT> rhs;
public :
	typedef typename ConditionalC<
		lhs::value,
		typename Mul<lhs, RhsT>::type,
		typename ConditionalC<
			rhs::value,
			typename Mul<LhsT, rhs>::type,
			typename Mul<LhsT, RhsT>::type
		>::type
	>::type type;
	static bool const value = lhs::value || rhs::value;
};
/**
  @brief substites operations in both terms.
 */
template <hryky_template_param, typename ForT, typename AlternativeT>
class SubstituteImpl<MultiplyImpl<hryky_template_arg>, ForT, AlternativeT>
{
private :
	typedef MultiplyImpl<hryky_template_arg> target;
public :
	typedef typename Mul<
		Substitute<typename target::lhs_type, ForT, AlternativeT>,
		Substitute<typename target::rhs_type, ForT, AlternativeT>
	>::type type;
};
/**
  @brief extracts multiplier in both term.
 */
template <hryky_template_param>
class GatherImpl<MultiplyImpl<hryky_template_arg> >
{
public :
	typedef typename Mul<Gather<LhsT>, Gather<RhsT> >::type type;
};
/**
  @brief differentiates an operation of binary multiplication.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<MultiplyImpl<hryky_template_arg>, WrtT>
{
private :
	typedef MultiplyImpl<hryky_template_arg> target;
public :
	typedef typename Add<
		Mul<
			D<typename target::lhs_type, WrtT>,
			typename target::rhs_type>,
		Mul<
			typename target::lhs_type,
			D<typename target::rhs_type, WrtT> >
	>::type type;
};
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief prints a multiplication operation.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::MultiplyImpl<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out << '(' << lhs_type() << '*' << rhs_type() << ')';
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
#endif // SYMBOLIC_COMPUTATION_MULTIPLY_H_20131009225020618
// end of file
