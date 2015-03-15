/**
  @file     symbolic_computation_reduce_divide.h
  @brief    reduces dividing.
  @author   HRYKY
  @version  $Id: symbolic_computation_reduce_divide.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_REDUCE_DIVIDE_H_20131116011652720
#define SYMBOLIC_COMPUTATION_REDUCE_DIVIDE_H_20131116011652720
#include "hryky/symbolic_computation/symbolic_computation_simplify.h"
#include "hryky/symbolic_computation/symbolic_computation_is_one.h"
#include "hryky/symbolic_computation/symbolic_computation_reduce.h"
#include "hryky/symbolic_computation/symbolic_computation_dividable.h"
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

	template <typename EvalT, int Value>
	class Integer;
	
	template <typename TermT>
	class Complement;
	
	template <typename TermT>
	class ComplementImpl;
	
	template <hryky_template_param>
	class ReduceDivideSame;
	
	template <
		hryky_template_param,
		bool LhsDividable = Dividable<LhsT, RhsT>::value,
		bool RhsDividable = Dividable<RhsT, LhsT>::value
	>
	class ReduceDivideDividable;
	
	template <hryky_template_param>
	class ReduceDivideLhs;
	
	template <hryky_template_param>
	class ReduceDivideRhs;
	
	template <hryky_template_param>
	class ReduceDivide;
	
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief simplifieds an operation divided by the type same to dividend.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceDivideSame
{
private :
	typedef ReduceDivideDividable<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief simplifieds an dividable operation.
 */
template <hryky_template_param, bool LhsDividable, bool RhsDividable>
class hryky::symbolic_computation::ReduceDivideDividable
{
private :
	typedef ReduceDivideLhs<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief simplifieds an operation having by the specific dividend.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceDivideLhs
{
private :
	typedef ReduceDivideRhs<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief simplifieds an operation divided by the specific divisor.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceDivideRhs
{
private :
	typedef ReduceDivide<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief simplifieds a dividing operation.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceDivide
{
private :
	typedef Reduce<LhsT>        lhs;
	typedef Reduce<RhsT>        rhs;
	typedef Divide<lhs, rhs>    divide;
public :
	static bool const value =
		lhs::value || rhs::value || IsAtom<divide>::value;
	typedef typename ReduceIfC<value, divide>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief specializes division.
 */
template <hryky_template_param>
class ReduceImpl<DivideImpl<hryky_template_arg> >
{
private :
	typedef ReduceDivideSame<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
//------------------------------------------------------------------------------
// reduces a division whose divisor is same to the dividend.
//------------------------------------------------------------------------------
/**
  @brief divides by same type.
 */
template <typename LhsT>
class ReduceDivideSame<LhsT, LhsT>
{
public :
	typedef typename Integer<
		typename Divide<LhsT, LhsT>::eval_type, 1>::type type;
	static bool const value = true;
};
//------------------------------------------------------------------------------
// reduces a division whose term is dividable.
//------------------------------------------------------------------------------
/**
  @brief divides dividend by divisor.
 */
template <hryky_template_param, bool RhsDividable>
class ReduceDivideDividable<hryky_template_arg, true, RhsDividable>
{
public :
	typedef typename Reduce<
		Dividable<LhsT, RhsT> >::type type;
	static bool const value = true;
};
/**
  @brief divides dividend by divisor.
 */
template <hryky_template_param>
class ReduceDivideDividable<hryky_template_arg, false, true>
{
public :
	typedef typename Reduce<Divide<
		Integer<typename LhsT::eval_type, 1>,
		Dividable<RhsT, LhsT>
	> >::type type;
	static bool const value = true;
};
//------------------------------------------------------------------------------
// reduces a division with the specific dividend.
//------------------------------------------------------------------------------
/**
  @brief divides the complement term.
 */
template <hryky_template_param>
class ReduceDivideLhs<ComplementImpl<LhsT>, RhsT>
{
public :
	typedef typename Reduce<Complement<Divide<LhsT, RhsT> > >::type type;
	static bool const value = true;
};
/**
  @brief reduces other division at LHS.
  
  prefers to reduce division.
 */
template <typename LLhsT, typename LRhsT,typename RhsT>
class ReduceDivideLhs<DivideImpl<LLhsT, LRhsT>, RhsT>
{
public :
	typedef typename Reduce<Divide<LLhsT, Mul<LRhsT, RhsT> > >::type type;
	static bool const value = true;
};
/**
  @brief divides multiplication.
 */
template <typename LLhsT, typename LRhsT,typename RhsT>
class ReduceDivideLhs<MultiplyImpl<LLhsT, LRhsT>, RhsT>
{
private :
	typedef Reduce<RhsT>                    rhs;
	typedef Reduce<LLhsT>                   llhs;
	typedef Reduce<LRhsT>                   lrhs;
	typedef ReduceBinary<llhs, lrhs, Mul>   lhs;
	typedef ReduceBinary<llhs, rhs, Divide> llhs_rhs;
	typedef ReduceBinary<lrhs, rhs, Divide> lrhs_rhs;
public :
	/**
	  prefers to preserve the order of operations.
	 */
	typedef typename ReduceIfC<
		lhs::value,
		Divide<lhs, rhs>,
		ReduceIfC<
			lrhs_rhs::value,
			Mul<llhs, lrhs_rhs>,
			ReduceIfC<
				llhs_rhs::value,
				Mul<llhs_rhs, lrhs>,
				ReduceIfC<
					rhs::value,
					Divide<lhs, rhs>
				>
			>
		>
	>::type type;

	static bool const value = (
		llhs_rhs::value || lrhs_rhs::value || rhs::value || lhs::value);
};
//------------------------------------------------------------------------------
// reduces a division with the specific divisor.
//------------------------------------------------------------------------------
/**
  @brief divides by complement term.
 */
template <hryky_template_param>
class ReduceDivideRhs<LhsT, ComplementImpl<RhsT> >
{
public :
	typedef typename Reduce<Complement<Divide<LhsT, RhsT> > >::type type;
	static bool const value = true;
};
/**
  @brief reduces division having other division at RHS.

  prefers to reduce divide.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class ReduceDivideRhs<LhsT, DivideImpl<RLhsT, RRhsT> >
{
public :
	typedef typename Reduce<Divide<Mul<LhsT, RRhsT>, RLhsT> >::type type;
	static bool const value = true;
};
/**
  @brief reduces division having multiplication at RHS.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class ReduceDivideRhs<LhsT, MultiplyImpl<RLhsT, RRhsT> >
{
private :
	typedef ReduceDivide<LhsT, Mul<RLhsT, RRhsT> > next;
	typedef Dividable<LhsT, RLhsT> lhs_rlhs;
	typedef Dividable<LhsT, RRhsT> lhs_rrhs;
	typedef Dividable<RLhsT, LhsT> rlhs_lhs;
	typedef Dividable<RRhsT, LhsT> rrhs_lhs;
	typedef Integer<typename LhsT::eval_type, 1> one;
public :
	typedef typename ReduceIfC<
		lhs_rlhs::value,
		Divide<lhs_rlhs, RRhsT>,
		ReduceIfC<
			lhs_rrhs::value,
			Divide<lhs_rrhs, RLhsT>,
			ReduceIfC<
				rlhs_lhs::value,
				Divide<one, Mul<rlhs_lhs, RRhsT> >,
				ReduceIfC<
					rrhs_lhs::value,
					Divide<one, Mul<RLhsT, rrhs_lhs> >,
					typename next::type
				>
			>
		>
	>::type type;
	static bool const value = (
		lhs_rlhs::value ||
		lhs_rrhs::value ||
		rlhs_lhs::value ||
		rrhs_lhs::value ||
		next::value);
};
//------------------------------------------------------------------------------
// reduces a dividing operation.
//------------------------------------------------------------------------------
/**
  @brief divides by an exponent having the same base.
 */
template <typename LhsT, int Exponent>
class ReduceDivide<LhsT, IntPowerImpl<LhsT, Exponent> >
{
public :
	typedef typename Reduce<IntPower<LhsT, 1 - Exponent> >::type type;
	static bool const value = true;
};
/**
  @brief divides an exponent by the base.
 */
template <typename RhsT, int Exponent>
class ReduceDivide<IntPowerImpl<RhsT, Exponent>, RhsT>
{
public :
	typedef typename Reduce<IntPower<RhsT, Exponent - 1> >::type type;
	static bool const value = true;
};
/**
  @brief divide an exponent by an other exponent with the same base.
 */
template <typename TermT, int LhsExponent, int RhsExponent>
class ReduceDivide<
	IntPowerImpl<TermT, LhsExponent>,
	IntPowerImpl<TermT, RhsExponent>
>
{
public :
	typedef typename Reduce<
		IntPower<TermT, LhsExponent - RhsExponent> >::type type;
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
#endif // SYMBOLIC_COMPUTATION_REDUCE_DIVIDE_H_20131116011652720
// end of file
