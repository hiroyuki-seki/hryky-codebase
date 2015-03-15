/**
  @file     symbolic_computation_add.h
  @brief    operates an addition.
  @author   HRYKY
  @version  $Id: symbolic_computation_add.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_ADD_H_20130930232203640
#define SYMBOLIC_COMPUTATION_ADD_H_20130930232203640
#include "hryky/symbolic_computation/symbolic_computation_differentiate.h"
#include "hryky/symbolic_computation/symbolic_computation_dividable.h"
#include "hryky/symbolic_computation/symbolic_computation_evalable.h"
#include "hryky/symbolic_computation/symbolic_computation_scatter.h"
#include "hryky/symbolic_computation/symbolic_computation_search.h"
#include "hryky/symbolic_computation/symbolic_computation_with_stream_out.h"
#include "hryky/symbolic_computation/symbolic_computation_substitute.h"
#include "hryky/tmp/tmp_not.h"
#include "hryky/type_traits/conditional.h"
#include "hryky/type_traits/is_same.h"
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
	template <typename EvalT, int Value>
	class Integer;

	template <typename EvalT, int Dividend, int Divisor>
	class Fraction;

	template <typename EvalT, int Dividend, int Divisor>
	class FractionImpl;

	/// operates an addition.
	template <hryky_template_param>
	class Add;

	/// specializes an addition in regard to the LHS.
	template <hryky_template_param>
	class AddLhs;

	/// specializes an addition in regard to the RHS.
	template <hryky_template_param>
	class AddRhs;

	/// internal operates an addition.
	template <hryky_template_param>
	class AddImpl;

	/// achieves the type of either term of ADD operation.
	template <
		typename LhsEvalT,
		typename RhsEvalT,
		bool EitherNull =
			IsSame<LhsEvalT, hryky::Null>::type::value ||
				IsSame<RhsEvalT, hryky::Null>::type::value
	>
	struct AddEvalType;
	

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief operates an addition.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Add :
	public WithStreamOut<Add<hryky_template_arg> >,
	public Evalable<Add<LhsT, RhsT>, typename LhsT::type::eval_type >
{
private :
	typedef typename AddLhs<
		typename LhsT::type, typename RhsT::type> impl;

public :
	typedef typename impl::type type;
};
/**
  @brief specializes an addition in regard to the LHS.
 */
template <hryky_template_param>
class hryky::symbolic_computation::AddLhs
{
public :
	typedef typename AddRhs<hryky_template_arg>::type type;
};
/**
  @brief specializes an addition in regard to the RHS.
 */
template <hryky_template_param>
class hryky::symbolic_computation::AddRhs
{
public :
	typedef typename AddImpl<hryky_template_arg>::type type;
};
/**
  @brief The internal operates an addition.
 */
template <hryky_template_param>
class hryky::symbolic_computation::AddImpl :
	public hryky::WithStreamOut<AddImpl<hryky_template_arg> >
{
public :
	typedef typename LhsT::type             lhs_type;
	typedef typename RhsT::type             rhs_type;
	typedef AddImpl<LhsT, RhsT>             type;
	
	typedef typename AddEvalType<
		typename lhs_type::eval_type,
		typename rhs_type::eval_type
	>::type eval_type;

	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters)
	{
		return lhs_type::eval(parameters) +
			rhs_type::eval(parameters);
	}

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;
};
/**
  @brief achieves the type of either term of ADD operation.
 */
template <typename LhsEvalT, typename RhsEvalT, bool EitherNull>
struct hryky::symbolic_computation::AddEvalType
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
  @brief ignores zero at LHS.
 */
template <typename EvalT, typename RhsT>
class AddLhs<Integer<EvalT, 0>, RhsT>
{
public :
	typedef typename RhsT::type type;
};
/**
  @brief ignores zero at RHS.
 */
template <typename EvalT, typename LhsT>
class AddRhs<LhsT, Integer<EvalT, 0> >
{
public :
	typedef typename LhsT::type type;
};
/**
  @brief calculates literal integer.
 */
template <typename EvalT, int Lhs, int Rhs>
class AddImpl<Integer<EvalT, Lhs>, Integer<EvalT, Rhs> >
{
public :
	typedef typename Integer<EvalT, Lhs + Rhs>::type type;
	static bool const value = true;
};
/**
  @brief calculates an addition between fractions.
 */
template <
	typename EvalT,
	int LhsDividend,
	int LhsDivisor,
	int RhsDividend,
	int RhsDivisor
>
class AddImpl<
	FractionImpl<EvalT, LhsDividend, LhsDivisor>,
	FractionImpl<EvalT, RhsDividend, RhsDivisor>
>
{
public :
	typedef typename Fraction<
		EvalT,
		LhsDividend * RhsDivisor + RhsDividend * LhsDivisor,
		LhsDivisor * RhsDivisor
	>::type type;
};
/**
  @brief calculates an addition between integer and fraction.
 */
template <
	typename EvalT,
	int Value,
	int Dividend,
	int Divisor
>
class AddImpl<
	Integer<EvalT, Value>, FractionImpl<EvalT, Dividend, Divisor> >
{
public :
	typedef typename Fraction<
		EvalT, Divisor * Value + Dividend, Divisor>::type type;
};
/**
  @brief calculates the addition between fraction and integer.
 */
template <
	typename EvalT,
	int Dividend,
	int Divisor,
	int Value
>
class AddImpl<
	FractionImpl<EvalT, Dividend, Divisor>, Integer<EvalT, Value> >
{
public :
	typedef typename Fraction<
		EvalT, Dividend + Divisor * Value, Divisor>::type type;
};
/**
  @brief achieves the type of ADD operation.
 */
template <typename LhsEvalT, typename RhsEvalT>
struct AddEvalType<LhsEvalT, RhsEvalT, false>
{
	typedef decltype(LhsEvalT() + RhsEvalT()) type;
};
//------------------------------------------------------------------------------
// specializes other classes in respect to this class.
//------------------------------------------------------------------------------
/**
  @brief search term through addition.
 */
template <hryky_template_param, template <typename> class FunctionT>
class SomeImpl<AddImpl<hryky_template_arg>, FunctionT>
{
public :
	typedef typename Some2<LhsT, RhsT, FunctionT>::type type;
};
/**
  @brief Addition can be divided if both term can be divided.
 */
template <hryky_template_param, typename WrtT>
class DividableImpl<AddImpl<hryky_template_arg>, WrtT>
{
private :
	typedef Dividable<LhsT, WrtT> lhs;
	typedef Dividable<RhsT, WrtT> rhs;
public :
	typedef typename ConditionalC<
		lhs::value && rhs::value,
		typename Add<lhs, rhs>::type,
		typename Add<LhsT, RhsT>::type
	>::type type;
	static bool const value = lhs::value && rhs::value;
};
/**
  @brief substites operations in both terms.
 */
template <hryky_template_param, typename ForT, typename AlternativeT>
class SubstituteImpl<AddImpl<hryky_template_arg>, ForT, AlternativeT>
{
private :
	typedef AddImpl<hryky_template_arg> target;
public :
	typedef typename Add<
		Substitute<typename target::lhs_type, ForT, AlternativeT>,
		Substitute<typename target::rhs_type, ForT, AlternativeT>
	>::type type;
};
/**
  @brief differentiates an internal operation of binary add.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<AddImpl<hryky_template_arg>, WrtT>
{
private :
	typedef AddImpl<hryky_template_arg> target;
public :
	typedef typename Add<
		D<typename target::lhs_type, WrtT>,
		D<typename target::rhs_type, WrtT> >::type type;
};
/**
  @brief distributes multiplications in the both terms.
 */
template <hryky_template_param>
class ScatterImpl<AddImpl<hryky_template_arg> >
{
public :
	typedef typename Add<Scatter<LhsT>, Scatter<RhsT> >::type type;
};
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief prints an add operation to an outout string-stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::AddImpl<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out << '(' << lhs_type() << '+' << rhs_type() << ')';
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
#endif // SYMBOLIC_COMPUTATION_ADD_H_20130930232203640
// end of file
