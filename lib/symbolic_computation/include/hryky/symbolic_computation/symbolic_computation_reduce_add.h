/**
  @file     symbolic_computation_reduce_add.h
  @brief    confirms the possibility to reduce an addition.
  @author   HRYKY
  @version  $Id: symbolic_computation_reduce_add.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_SYMPLIFY_ADD_H_20131012123908193
#define SYMBOLIC_COMPUTATION_SYMPLIFY_ADD_H_20131012123908193
#include "hryky/symbolic_computation/symbolic_computation_simplify.h"
#include "hryky/symbolic_computation/symbolic_computation_is_zero.h"
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
	template <typename EvalT, int Value>
	class Integer;

	template <typename EvalT, int Dividend, int Divisor>
	class Fraction;

	template <typename EvalT, int Dividend, int Divisor>
	class FractionImpl;

	template <typename TermT>
	class ComplementImpl;

	template <hryky_template_param>
	class Mul;

	template <hryky_template_param>
	class MultiplyImpl;

	template <hryky_template_param>
	class Sub;

	template <hryky_template_param>
	class SubtractImpl;

	template <hryky_template_param>
	class Add;

	template <hryky_template_param>
	class AddImpl;

	template <hryky_template_param>
	class ReduceAddSame;

	template <hryky_template_param>
	class ReduceAddComplement;

	template <hryky_template_param>
	class ReduceAddLhs;

	template <hryky_template_param>
	class ReduceAddRhs;

	template <hryky_template_param>
	class ReduceAddBothMul;

	template <hryky_template_param>
	class ReduceAdd;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief reduces addition between same types.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceAddSame
{
private :
	typedef ReduceAddComplement<LhsT, RhsT> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief reduces addition whose terms are complement each other.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceAddComplement
{
private :
	typedef ReduceAddLhs<LhsT, RhsT> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief reduces the addition to other operation at LHS.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceAddLhs
{
private :
	typedef ReduceAddRhs<LhsT, RhsT> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief reduces the addition to other operation at RHS.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceAddRhs
{
private :
	typedef ReduceAddBothMul<LhsT, RhsT> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief reduces addition to multiplication based on distributive law.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceAddBothMul
{
private :
	typedef ReduceAdd<LhsT, RhsT> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief reduces addition.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceAdd
{
private :
	typedef Reduce<LhsT>    lhs;
	typedef Reduce<RhsT>    rhs;
	typedef Add<lhs, rhs>   add;
public :
	static bool const value = 
		lhs::value || rhs::value || IsAtom<add>::value;
	typedef typename ReduceIfC<value, add>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief reduces addition.
 */
template <hryky_template_param>
class ReduceImpl<AddImpl<LhsT, RhsT> >
{
private :
	typedef ReduceAddSame<LhsT, RhsT> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
//------------------------------------------------------------------------------
// reduces an additional operation between same types.
//------------------------------------------------------------------------------
/**
  @brief reduces an additional operation between same types.
 */
template <typename TermT>
class ReduceAddSame<TermT, TermT>
{
private :
	typedef Reduce<Mul<Integer<typename TermT::eval_type, 2>, TermT> >
		simplified;
public :
	typedef typename simplified::type type;
	static bool const value = true;
};
//------------------------------------------------------------------------------
// reduces an additional operation whose terms are complement.
//------------------------------------------------------------------------------
/**
  @brief RHS is complement to LHS.
 */
template <typename LhsT>
class ReduceAddComplement<LhsT, ComplementImpl<LhsT> >
{
public :
	typedef typename Integer<typename LhsT::eval_type, 0>::type type;
	static bool const value = true;
};
/**
  @brief LHS is complement to RHS.
 */
template <typename RhsT>
class ReduceAddComplement<ComplementImpl<RhsT>, RhsT>
{
public :
	typedef typename Integer<typename RhsT::eval_type, 0>::type type;
	static bool const value = true;
};
//------------------------------------------------------------------------------
// reduces an addition to other operation at LHS.
//------------------------------------------------------------------------------
/**
  @brief add a rhs to the preceding subtraction.
 */
template <typename RhsT, typename LLhsT, typename LRhsT>
class ReduceAddLhs<SubtractImpl<LLhsT, LRhsT>, RhsT>
{
private :
	typedef Reduce<RhsT>                    rhs;
	typedef Reduce<LLhsT>                   llhs;
	typedef Reduce<LRhsT>                   lrhs;
	typedef ReduceBinary<llhs, lrhs, Sub>   lhs;
	typedef ReduceBinary<llhs, rhs, Add>    llhs_rhs;
	typedef ReduceBinary<rhs, lrhs, Sub>    rhs_lrhs;

public :
	typedef typename ReduceIf<
		rhs_lrhs,
		Add<llhs, rhs_lrhs>,
		ReduceIf<
			lhs,
			Add<lhs, rhs>,
			ReduceIf<
				llhs_rhs,
				Sub<llhs_rhs, lrhs>,
				ReduceIf<
					rhs,
					Add<lhs, rhs>
				>
			>
		>
	>::type type;
	static bool const value = (
		rhs::value ||
		llhs_rhs::value ||
		rhs_lrhs::value ||
		lhs::value);
};
/**
  @brief reduces an addition at LHS of addition.
 */
template <typename RhsT, typename LLhsT, typename LRhsT>
class ReduceAddLhs<AddImpl<LLhsT, LRhsT>, RhsT >
{
private :
	typedef Reduce<RhsT>                    rhs;
	typedef Reduce<LLhsT>                   llhs;
	typedef Reduce<LRhsT>                   lrhs;
	typedef ReduceBinary<llhs, lrhs, Add>   lhs;
	typedef ReduceBinary<llhs, rhs, Add>    llhs_rhs;
	typedef ReduceBinary<lrhs, rhs, Add>    lrhs_rhs;

public :
	/**
	  prefers to preserve the order of rhss.
	 */
	typedef typename ReduceIf<
		lhs,
		Add<lhs, rhs>,
		ReduceIf<
			lrhs_rhs,
			Add<llhs, lrhs_rhs>,
			ReduceIf<
				llhs_rhs,
				Add<llhs_rhs, lrhs>,
				ReduceIf<
					rhs,
					Add<lhs, rhs>
				>
			>
		>
	>::type type;
	static bool const value =
		llhs_rhs::value || lrhs_rhs::value || rhs::value || lhs::value;
};
/**
  @brief reduces an multiplication at RHS of addition.
 */
template <hryky_template_param>
class ReduceAddLhs<MultiplyImpl<LhsT, RhsT>, RhsT>
{
public :
	typedef typename Reduce<
		Mul<Add<
			LhsT, Integer<typename LhsT::eval_type, 1> >, RhsT> >::type type;
	static bool const value = true;
};
/**
  @brief reduces an multiplication at RHS of addition.
 */
template <hryky_template_param>
class ReduceAddLhs<MultiplyImpl<RhsT, LhsT>, RhsT>
{
public :
	typedef typename Reduce<
		Mul<Add<
			LhsT, Integer<typename LhsT::eval_type, 1> >, RhsT> >::type type;
	static bool const value = true;
};
/**
  @brief reduces an addition with complement term to subtraction.
 */
template <hryky_template_param>
class ReduceAddLhs<ComplementImpl<LhsT>, RhsT>
{
public :
	typedef typename Reduce<Sub<RhsT, LhsT> >::type type;
	static bool const value = true;
};
//------------------------------------------------------------------------------
// reduces an addition to other operation at RHS.
//------------------------------------------------------------------------------
/**
  @brief add a lhs to the following subtraction.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class ReduceAddRhs<LhsT, SubtractImpl<RLhsT, RRhsT> >
{
private :
	typedef Reduce<LhsT>                    lhs;
	typedef Reduce<RLhsT>                   rlhs;
	typedef Reduce<RRhsT>                   rrhs;
	typedef ReduceBinary<rlhs, rrhs, Sub>   rhs;
	typedef ReduceBinary<lhs, rlhs, Add>    lhs_rlhs;
	typedef ReduceBinary<lhs, rrhs, Sub>    lhs_rrhs;

public :
	typedef typename ReduceIf<
		lhs_rlhs,
		Sub<lhs_rlhs, rrhs>,
		ReduceIf<
			rhs,
			Add<lhs, rhs>,
			ReduceIf<
				lhs_rrhs,
				Add<rlhs, lhs_rrhs>,
				ReduceIf<
					lhs,
					Add<lhs, rhs>
				>
			>
		>
	>::type type;
	static bool const value =
		lhs::value || lhs_rlhs::value || lhs_rrhs::value || rhs::value;
};
/**
  @brief reduces an addition at RHS of addition.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class ReduceAddRhs<LhsT, AddImpl<RLhsT, RRhsT> >
{
private :
	typedef Reduce<LhsT>                    lhs;
	typedef Reduce<RLhsT>                   rlhs;
	typedef Reduce<RRhsT>                   rrhs;
	typedef ReduceBinary<rlhs, rrhs, Add>   rhs;
	typedef ReduceBinary<lhs, rlhs, Add>    lhs_rlhs;
	typedef ReduceBinary<lhs, rrhs, Add>    lhs_rrhs;

public :
	/**
	  prefers to preserve the order of lhss.
	 */
	typedef typename ReduceIf<
		lhs_rlhs,
		Add<lhs_rlhs, rrhs>,
		ReduceIf<
			rhs,
			Add<lhs, rhs>,
			ReduceIf<
				lhs_rrhs,
				Add<rlhs, lhs_rrhs>,
				ReduceIf<
					lhs,
					Add<lhs, rhs>
				>
			>
		>
	>::type type;
	static bool const value =
		lhs_rlhs::value || lhs_rrhs::value || lhs::value || rhs::value;
};
/**
  @brief reduces an multiplication at RHS of addition.
 */
template <hryky_template_param>
class ReduceAddRhs<LhsT, MultiplyImpl<LhsT, RhsT> >
{
public :
	typedef typename Reduce<
		Mul<LhsT, Add<
			RhsT, Integer<typename RhsT::eval_type, 1> > > >::type type;
	static bool const value = true;
};
/**
  @brief reduces an multiplication at RHS of addition.
 */
template <hryky_template_param>
class ReduceAddRhs<LhsT, MultiplyImpl<RhsT, LhsT> >
{
public :
	typedef typename Reduce<
		Mul<LhsT, Add<
			RhsT, Integer<typename RhsT::eval_type, 1> > > >::type type;
	static bool const value = true;
};
/**
  @brief reduces an addition with complement term to subtraction.
 */
template <hryky_template_param>
class ReduceAddRhs<LhsT, ComplementImpl<RhsT> >
{
public :
	typedef typename Reduce<Sub<LhsT, RhsT> >::type type;
	static bool const value = true;
};
//------------------------------------------------------------------------------
// reduces an additional operation whose multiplication is distributed.
//------------------------------------------------------------------------------
/**
  @brief extracts distributed term from both multiplications.
 */
template <typename LhsT, typename LRhsT, typename RRhsT>
class ReduceAddBothMul<
	MultiplyImpl<LhsT, LRhsT>, MultiplyImpl<LhsT, RRhsT> >
{
public :
	typedef typename Reduce<Mul<LhsT, Add<LRhsT, RRhsT> > >::type type;
	static bool const value = true;
};
/**
  @brief extracts distributed term from both multiplications.
 */
template <typename LLhsT, typename RhsT, typename RLhsT>
class ReduceAddBothMul<
	MultiplyImpl<LLhsT, RhsT>, MultiplyImpl<RLhsT, RhsT> >
{
public :
	typedef typename Reduce<Mul<Add<LLhsT, RLhsT>, RhsT> >::type type;
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
#endif // SYMBOLIC_COMPUTATION_SYMPLIFY_ADD_H_20131012123908193
// end of file
