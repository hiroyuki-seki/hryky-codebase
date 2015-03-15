/**
  @file     symbolic_computation_reduce_subtract.h
  @brief    reduces subtractions.
  @author   HRYKY
  @version  $Id: symbolic_computation_reduce_subtract.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_REDUCE_SUBTRACT_H_20131115203714525
#define SYMBOLIC_COMPUTATION_REDUCE_SUBTRACT_H_20131115203714525
#include "hryky/symbolic_computation/symbolic_computation_simplify.h"
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

	template <hryky_template_param>
	class Sub;

	template <hryky_template_param>
	class SubtractImpl;

	template <hryky_template_param>
	class Add;

	template <hryky_template_param>
	class AddImpl;

	template <typename TermT>
	class Complement;

	template <hryky_template_param>
	class ReduceSubSame;

	template <hryky_template_param>
	class ReduceSubLhs;

	template <hryky_template_param>
	class ReduceSubRhs;

	template <hryky_template_param>
	class ReduceSub;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief reduces the subtraction each of whose term has same type.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceSubSame
{
private :
	typedef ReduceSubLhs<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief reduces the operation in subtraction in regard to LHS.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceSubLhs
{
private :
	typedef ReduceSubRhs<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief reduces the operation in subtraction in regard to RHS.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceSubRhs
{
private :
	typedef ReduceSub<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief reduces the subtraction.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceSub
{
private :
	typedef Reduce<LhsT>    lhs;
	typedef Reduce<RhsT>    rhs;
	typedef Sub<lhs, rhs>   sub;
public :
	static bool const value =
		lhs::value || rhs::value || IsAtom<sub>::value;
	typedef typename ReduceIfC<value, sub>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
//------------------------------------------------------------------------------
// reduces subtraction.
//------------------------------------------------------------------------------
template <hryky_template_param>
class ReduceImpl<SubtractImpl<hryky_template_arg> >
{
private :
	typedef ReduceSubSame<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
//------------------------------------------------------------------------------
// reduces subtraction each of whose term has same type.
//------------------------------------------------------------------------------
/**
  @brief reduces to zero.
 */
template <typename TermT>
class ReduceSubSame<TermT, TermT>
{
public :
	typedef typename Integer<typename TermT::eval_type, 0>::type type;
	static bool const value = true;
};
//------------------------------------------------------------------------------
// reduces subtraction with other operation at LHS.
//------------------------------------------------------------------------------
/**
  @brief subtracts from the preceding subtraction.
 */
template <typename LLhsT, typename LRhsT, typename RhsT>
class ReduceSubLhs<SubtractImpl<LLhsT, LRhsT>, RhsT>
{
private :
	typedef Reduce<RhsT>                    rhs;
	typedef Reduce<LLhsT>                   llhs;
	typedef Reduce<LRhsT>                   lrhs;
	typedef ReduceBinary<llhs, lrhs, Sub>   lhs;
	typedef ReduceBinary<llhs, rhs, Sub>    llhs_rhs;
	typedef ReduceBinary<lrhs, rhs, Add>    lrhs_rhs;
public :
	typedef typename ReduceIf<
		lrhs_rhs,
		Sub<llhs, lrhs_rhs>,
		ReduceIf<
			lhs,
			Sub<lhs, rhs>,
			ReduceIf<
				llhs_rhs,
				Sub<llhs_rhs, lrhs>,
				ReduceIf<
					rhs,
					Sub<lhs, rhs>
				>
			>
		>
	>::type type;
	static bool const value =
		lhs::value || rhs::value || llhs_rhs::value || lrhs_rhs::value;
};
/**
  @brief subtracts from the preceding addition.
 */
template <typename LLhsT, typename LRhsT, typename RhsT>
class ReduceSubLhs<AddImpl<LLhsT, LRhsT>, RhsT>
{
private :
	typedef Reduce<RhsT>                    rhs;
	typedef Reduce<LLhsT>                   llhs;
	typedef Reduce<LRhsT>                   lrhs;
	typedef ReduceBinary<llhs, lrhs, Add>   lhs;
	typedef ReduceBinary<llhs, rhs, Sub>    llhs_rhs;
	typedef ReduceBinary<lrhs, rhs, Sub>    lrhs_rhs;
public :
	typedef typename ReduceIf<
		lrhs_rhs,
		Add<llhs, lrhs_rhs>,
		ReduceIf<
			lhs,
			Sub<lhs, rhs>,
			ReduceIf<
				llhs_rhs,
				Add<llhs_rhs, lrhs>,
				ReduceIf<
					rhs,
					Sub<lhs, rhs>
				>
			>
		>
	>::type type;
	static bool const value =
		lhs::value || rhs::value || llhs_rhs::value || lrhs_rhs::value;
};
/**
  @brief reduces an multiplication at RHS of subtraction.
 */
template <hryky_template_param>
class ReduceSubLhs<MultiplyImpl<hryky_template_arg>, RhsT>
{
public :
	typedef typename Reduce<
		Mul<Sub<
			LhsT, Integer<typename LhsT::eval_type, 1> >, RhsT> >::type type;
	static bool const value = true;
};
/**
  @brief reduces an multiplication at RHS of subtraction.
 */
template <hryky_template_param>
class ReduceSubLhs<MultiplyImpl<RhsT, LhsT>, RhsT>
{
public :
	typedef typename Reduce<
		Mul<Sub<
			LhsT, Integer<typename LhsT::eval_type, 1> >, RhsT> >::type type;
	static bool const value = true;
};
/**
  @brief reduces a complement term at LHS.
 */
template <hryky_template_param>
class ReduceSubLhs<ComplementImpl<LhsT>, RhsT>
{
public :
	typedef typename Reduce<Complement<Add<LhsT, RhsT> > >::type type;
	static bool const value = true;
};
//------------------------------------------------------------------------------
// reduces subtraction with other operation at RHS.
//------------------------------------------------------------------------------
/**
  @brief subtracts by the following subtraction.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class ReduceSubRhs<LhsT, SubtractImpl<RLhsT, RRhsT> >
{
private :
	typedef Reduce<LhsT>                    lhs;
	typedef Reduce<RLhsT>                   rlhs;
	typedef Reduce<RRhsT>                   rrhs;
	typedef ReduceBinary<rlhs, rrhs, Sub>   rhs;
	typedef ReduceBinary<lhs, rlhs, Sub>    lhs_rlhs;
	typedef ReduceBinary<lhs, rrhs, Add>    lhs_rrhs;
public :
	typedef typename ReduceIf<
		lhs_rlhs,
		Add<lhs_rlhs, rrhs>,
		ReduceIf<
			rhs,
			Sub<lhs, rhs>,
			ReduceIf<
				lhs_rrhs,
				Sub<lhs_rrhs, rlhs>,
				ReduceIf<
					lhs,
					Sub<lhs, rhs>
				>
			>
		>
	>::type type;
	static bool const value =
		rhs::value || lhs::value || lhs_rlhs::value || lhs_rrhs::value;
};
/**
  @brief subtracts by the following addition.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class ReduceSubRhs<LhsT, AddImpl<RLhsT, RRhsT> >
{
private :
	typedef Reduce<LhsT>                    lhs;
	typedef Reduce<RLhsT>                   rlhs;
	typedef Reduce<RRhsT>                   rrhs;
	typedef ReduceBinary<rlhs, rrhs, Add>   rhs;
	typedef ReduceBinary<lhs, rlhs, Sub>    lhs_rlhs;
	typedef ReduceBinary<lhs, rrhs, Sub>    lhs_rrhs;
public :
	typedef typename ReduceIf<
		lhs_rlhs,
		Sub<lhs_rlhs, rrhs>,
		ReduceIf<
			rhs,
			Sub<lhs, rhs>,
			ReduceIf<
				lhs_rrhs,
				Sub<lhs_rrhs, rlhs>,
				ReduceIf<
					lhs,
					Sub<lhs, rhs>
				>
			>
		>
	>::type type;
	static bool const value =
		rhs::value || lhs::value || lhs_rlhs::value || lhs_rrhs::value;
};
/**
  @brief reduces an multiplication at RHS of subtraction.
 */
template <hryky_template_param>
class ReduceSubRhs<LhsT, MultiplyImpl<hryky_template_arg> >
{
public :
	typedef typename Reduce<
		Mul<LhsT, Sub<
			Integer<typename RhsT::eval_type, 1>, RhsT> > >::type type;
	static bool const value = true;
};
/**
  @brief reduces an multiplication at RHS of subtraction.
 */
template <hryky_template_param>
class ReduceSubRhs<LhsT, MultiplyImpl<RhsT, LhsT> >
{
public :
	typedef typename Reduce<
		Mul<LhsT, Sub<
			Integer<typename RhsT::eval_type, 1>, RhsT> > >::type type;
	static bool const value = true;
};
/**
  @brief reduces a complement term at RHS.
 */
template <hryky_template_param>
class ReduceSubRhs<LhsT, ComplementImpl<RhsT> >
{
public :
	typedef typename Reduce<Add<LhsT, RhsT> >::type type;
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
#endif // SYMBOLIC_COMPUTATION_REDUCE_SUBTRACT_H_20131115203714525
// end of file
