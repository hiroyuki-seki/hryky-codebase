/**
  @file     symbolic_computation_reduce_multiply.h
  @brief    confirms the possibility to reduce a multiplication.
  @author   HRYKY
  @version  $Id: symbolic_computation_reduce_multiply.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_SYMPLIFY_MULTIPLY_H_20131012175515413
#define SYMBOLIC_COMPUTATION_SYMPLIFY_MULTIPLY_H_20131012175515413
#include "hryky/symbolic_computation/symbolic_computation_simplify.h"
#include "hryky/symbolic_computation/symbolic_computation_is_integer.h"
#include "hryky/symbolic_computation/symbolic_computation_is_zero.h"
#include "hryky/symbolic_computation/symbolic_computation_is_one.h"
#include "hryky/symbolic_computation/symbolic_computation_int_power.h"
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

	template <hryky_template_param>
	class Mul;

	template <hryky_template_param>
	class MultiplyImpl;

	template <hryky_template_param>
	class Divide;

	template <hryky_template_param>
	class DivideImpl;

	template <hryky_template_param>
	class Add;

	template <hryky_template_param>
	class AddImpl;

	template <hryky_template_param>
	class Sub;

	template <hryky_template_param>
	class SubtractImpl;

	template <typename TermT>
	class Complement;

	template <typename TermT>
	class ComplementImpl;

	template <typename EvalT, int Value>
	class Integer;
	
	template <
		typename LhsT,
		typename RhsT,
		bool IsSame = hryky::IsSame<hryky_template_arg>::type::value
	>
	class ReduceMulSame;

	template <hryky_template_param>
	class ReduceMulPermutate;
	
	template <hryky_template_param>
	class ReduceMulLhs;
	
	template <hryky_template_param>
	class ReduceMulRhs;
	
	template <hryky_template_param>
	class ReduceMul;
	
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief reduces multiplication between same type.

  Specializaing same types is prior to the other specialization.
 */
template <
	typename LhsT,
	typename RhsT,
	bool IsSame
>
class hryky::symbolic_computation::ReduceMulSame
{
private :
	typedef ReduceMulPermutate<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief permutates the order of terms in multiplication.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceMulPermutate
{
private :
	typedef ReduceMulLhs<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief reduces multiplication whose LHS term is the specific operation.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceMulLhs
{
private :
	typedef ReduceMulRhs<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief reduces multiplication whose RHS term is the specific operation.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceMulRhs
{
private :
	typedef ReduceMul<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief reduces multiplication.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceMul
{
public :
	typedef Reduce<LhsT>    lhs;
	typedef Reduce<RhsT>    rhs;
	typedef Mul<lhs, rhs>   mul;
public :
	static bool const value =
		lhs::value || rhs::value || IsAtom<mul>::value;
	typedef typename ReduceIfC<value, mul>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief reduces multiplication.
 */
template <hryky_template_param>
class ReduceImpl<MultiplyImpl<hryky_template_arg> >
{
private :
	typedef ReduceMulSame<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static const bool value = impl::value;
};
//------------------------------------------------------------------------------
// reduces multiplication between values of same type.
//------------------------------------------------------------------------------
/**
  @brief reduces to the power of 2.
 */
template <typename TermT>
class ReduceMulSame<TermT, TermT, true>
{
public :
	typedef typename Reduce<IntPower<TermT, 2> >::type type;
	static bool const value = true;
};
//------------------------------------------------------------------------------
// reduces multiplication between numerical values.
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// permutates the order of terms in multiplication.
//------------------------------------------------------------------------------
/**
  @brief precedes an integral value.
 */
template <typename LhsT, typename EvalT, int Value>
class ReduceMulPermutate<LhsT, Integer<EvalT, Value> >
{
public :
	typedef typename Reduce<Mul<Integer<EvalT, Value>, LhsT> >::type type;
	static bool const value = true;
};
//------------------------------------------------------------------------------
// reduces multiplication having other operation at LHS.
//------------------------------------------------------------------------------
/**
  @brief reduces multiplication to other multiplication from RHS.
 */
template <typename LLhsT, typename LRhsT,typename RhsT>
class ReduceMulLhs<MultiplyImpl<LLhsT, LRhsT>, RhsT>
{
private :
	typedef Reduce<RhsT>                    rhs;
	typedef Reduce<LLhsT>                   llhs;
	typedef Reduce<LRhsT>                   lrhs;
	typedef ReduceBinary<llhs, lrhs, Mul>   lhs;
	typedef ReduceBinary<llhs, rhs, Mul>    llhs_rhs;
	typedef ReduceBinary<lrhs, rhs, Mul>    lrhs_rhs;
public :
	/**
	  prefers to preserve the order of operations.
	 */
	typedef typename ReduceIf<
		lhs,
		Mul<lhs, rhs>,
		ReduceIf<
			lrhs_rhs,
			Mul<llhs, lrhs_rhs>,
			ReduceIf<
				llhs_rhs,
				Mul<llhs_rhs, lrhs>,
				ReduceIf<
					rhs,
					Mul<lhs, rhs>
				>
			>
		>
	>::type type;

	static bool const value = (
		llhs_rhs::value || lrhs_rhs::value || rhs::value || lhs::value);
};
/**
  @brief reduces multiplication having a division at LHS.
 */
template <typename LLhsT, typename LRhsT,typename RhsT>
class ReduceMulLhs<DivideImpl<LLhsT, LRhsT>, RhsT>
{
private :
	typedef Reduce<RhsT>                        rhs;
	typedef Reduce<LLhsT>                       llhs;
	typedef Reduce<LRhsT>                       lrhs;
	typedef ReduceBinary<llhs, lrhs, Divide>    lhs;
	typedef ReduceBinary<llhs, rhs, Mul>        llhs_rhs;
	typedef ReduceBinary<rhs, lrhs, Divide>     rhs_lrhs;
public :
	/**
	  prefers to preserve the order of operations.
	 */
	typedef typename ReduceIf<
		lhs,
		Mul<lhs, rhs>,
		ReduceIf<
			llhs_rhs,
			Divide<llhs_rhs, lrhs>,
			ReduceIf<
				rhs_lrhs,
				Mul<llhs, rhs_lrhs>,
				ReduceIf<
					rhs,
					Mul<lhs, rhs>
				>
			>
		>
	>::type type;

	static bool const value = (
		llhs_rhs::value || rhs_lrhs::value || rhs::value || lhs::value);
};
//------------------------------------------------------------------------------
// reduces multiplication having other operation at RHS.
//------------------------------------------------------------------------------
/**
  @brief reduces multiplication to other multiplication from LHS.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class ReduceMulRhs<LhsT, MultiplyImpl<RLhsT, RRhsT> >
{
private :
	typedef Reduce<LhsT>                    lhs;
	typedef Reduce<RLhsT>                   rlhs;
	typedef Reduce<RRhsT>                   rrhs;
	typedef ReduceBinary<rlhs, rrhs, Mul>   rhs;
	typedef ReduceBinary<lhs, rlhs, Mul>    lhs_rlhs;
	typedef ReduceBinary<lhs, rrhs, Mul>    lhs_rrhs;
public :
	/**
	  prefers to preserve the order of operations.
	 */
	typedef typename ReduceIf<
		lhs_rlhs,
		Mul<lhs_rlhs, rrhs>,
		ReduceIf<
			rhs,
			Mul<lhs, rhs>,
			ReduceIf<
				lhs_rrhs,
				Mul<rlhs, lhs_rrhs>,
				ReduceIf<
					lhs,
					Mul<lhs, rhs>
				>
			>
		>
	>::type type;

	static bool const value = (
		lhs_rlhs::value || lhs_rrhs::value || lhs::value || rhs::value);
};
/**
  @brief reduces multiplication having a division at RHS.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class ReduceMulRhs<LhsT, DivideImpl<RLhsT, RRhsT> >
{
private :
	typedef Reduce<LhsT>                        lhs;
	typedef Reduce<RLhsT>                       rlhs;
	typedef Reduce<RRhsT>                       rrhs;
	typedef ReduceBinary<rlhs, rrhs, Divide>    rhs;
	typedef ReduceBinary<lhs, rlhs, Mul>        lhs_rlhs;
	typedef ReduceBinary<lhs, rrhs, Divide>     lhs_rrhs;
public :
	/**
	  prefers to preserve the order of operations.
	 */
	typedef typename ReduceIf<
		lhs_rlhs,
		Divide<lhs_rlhs, rrhs>,
		ReduceIf<
			rhs,
			Mul<lhs, rhs>,
			ReduceIf<
				lhs_rrhs,
				Mul<lhs_rrhs, rlhs>,
				ReduceIf<
					lhs,
					Mul<lhs, rhs>
				>
			>
		>
	>::type type;

	static bool const value = (
		lhs_rlhs::value || lhs_rrhs::value || lhs::value || rhs::value);
};
//------------------------------------------------------------------------------
// reduces multiplication.
//------------------------------------------------------------------------------
/**
  @brief multiplies the complement term at RHS.
 */
template <hryky_template_param>
class ReduceMul<LhsT, ComplementImpl<RhsT> >
{
public :
	typedef typename Reduce<Complement<Mul<hryky_template_arg> > >::type type;
	static bool const value = true;
};
/**
  @brief multiplies the complement term at LHS.
 */
template <hryky_template_param>
class ReduceMul<ComplementImpl<LhsT>, RhsT>
{
public :
	typedef typename Reduce<Complement<Mul<hryky_template_arg> > >::type type;
	static bool const value = true;
};
/**
  @brief multiplies the term at LHS to the exponent at RHS.
 */
template <typename LhsT, int Exponent>
class ReduceMul<LhsT, IntPowerImpl<LhsT, Exponent> >
{
public :
	typedef typename Reduce<IntPower<LhsT, Exponent + 1> >::type type;
	static bool const value = true;
};
/**
  @brief multiplies the term at RHS to the exponent at LHS.
 */
template <typename RhsT, int Exponent>
class ReduceMul<IntPowerImpl<RhsT, Exponent>, RhsT>
{
public :
	typedef typename Reduce<IntPower<RhsT, Exponent + 1> >::type type;
	static bool const value = true;
};
/**
  @brief multiplies two exponents.
 */
template <typename TermT, int LhsExponent, int RhsExponent>
class ReduceMul<
	IntPowerImpl<TermT, LhsExponent>,
	IntPowerImpl<TermT, RhsExponent>
>
{
public :
	typedef typename Reduce<
		IntPower<TermT, LhsExponent + RhsExponent> >::type type;
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
#endif // SYMBOLIC_COMPUTATION_SYMPLIFY_MULTIPLY_H_20131012175515413
// end of file
