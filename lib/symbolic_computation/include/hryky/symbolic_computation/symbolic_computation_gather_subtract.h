/**
  @file     symbolic_computation_gather_subtract.h
  @brief    collects up the terms having the same multiplier.
  @author   HRYKY
  @version  $Id: symbolic_computation_gather_subtract.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_GATHER_SUBTRACT_H_20131128072950979
#define SYMBOLIC_COMPUTATION_GATHER_SUBTRACT_H_20131128072950979
#include "hryky/symbolic_computation/symbolic_computation_gather.h"
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
	/// collects up the terms having the same multiplier.
	template <hryky_template_param>
	class GatherSub;

	template <hryky_template_param>
	class GatherSubLhs;

	template <hryky_template_param>
	class GatherSubRhs;

	template <typename LhsT, typename RhsT>
	class Sub;

	template <typename LhsT, typename RhsT>
	class SubtractImpl;

	template <typename LhsT, typename RhsT>
	class Mul;

	template <typename LhsT, typename RhsT>
	class MultiplyImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief extracts multiplier from the subtraction having other operation at LHS.
 */
template <hryky_template_param>
class hryky::symbolic_computation::GatherSubLhs
{
public :
	typedef typename GatherSubRhs<hryky_template_arg>::type type;

};
/**
  @brief extracts multiplier from the subtraction having other operation at RHS.
 */
template <hryky_template_param>
class hryky::symbolic_computation::GatherSubRhs
{
public :
	typedef typename GatherSub<hryky_template_arg>::type type;

};
/**
  @brief collects up the terms having the same multiplier.
 */
template <hryky_template_param>
class hryky::symbolic_computation::GatherSub
{
public :
	typedef typename Sub<Gather<LhsT>, Gather<RhsT> >::type type;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief restricts the specialization for subtraction.
 */
template <hryky_template_param>
class GatherImpl<SubtractImpl<hryky_template_arg> >
{
public :
	typedef typename GatherSubLhs<hryky_template_arg>::type type;
};
/**
  @brief extracts multipliers from subtraction having multiplication at LHS.
 */
template <typename LLhsT, typename LRhsT, typename RhsT>
class GatherSubLhs<MultiplyImpl<LLhsT, LRhsT>, RhsT>
{
public :
	typedef typename ConditionalC<
		Dividable<RhsT, LLhsT>::value,
		Mul<LLhsT, Sub<LRhsT, RhsT> >,
		typename ConditionalC<
			Dividable<RhsT, LRhsT>::value,
			Mul<Sub<LLhsT, RhsT>, LRhsT>,
			GatherSubRhs<MultiplyImpl<LLhsT, LRhsT>, RhsT>
		>::type
	>::type type;
};
/**
  @brief extracts multipliers from subtraction having multiplication at RHS.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class GatherSubRhs<LhsT, MultiplyImpl<RLhsT, RRhsT> >
{
public :
	typedef typename ConditionalC<
		Dividable<LhsT, RLhsT>::value,
		Mul<RLhsT, Sub<LhsT, RRhsT> >,
		typename ConditionalC<
			Dividable<LhsT, RRhsT>::value,
			Mul<Sub<LhsT, RLhsT>, RRhsT>,
			GatherSub<LhsT, MultiplyImpl<RLhsT, RRhsT> >
		>::type
	>::type type;
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
#endif // SYMBOLIC_COMPUTATION_GATHER_SUBTRACT_H_20131128072950979
// end of file
