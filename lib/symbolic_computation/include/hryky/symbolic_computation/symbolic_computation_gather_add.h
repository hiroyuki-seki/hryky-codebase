/**
  @file     symbolic_computation_gather_add.h
  @brief    collects up the terms having the same multiplier.
  @author   HRYKY
  @version  $Id: symbolic_computation_gather_add.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_GATHER_ADD_H_20131125232001638
#define SYMBOLIC_COMPUTATION_GATHER_ADD_H_20131125232001638
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
	class GatherAdd;

	template <hryky_template_param>
	class GatherAddLhs;

	template <hryky_template_param>
	class GatherAddRhs;

	template <hryky_template_param>
	class Add;

	template <hryky_template_param>
	class AddImpl;

	template <hryky_template_param>
	class Sub;

	template <hryky_template_param>
	class SubtractImpl;

	template <hryky_template_param>
	class Mul;

	template <hryky_template_param>
	class MultiplyImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief extracts multipliers from addtion having other operation at LHS.
 */
template <typename LhsT, typename RhsT>
class hryky::symbolic_computation::GatherAddLhs
{
public :
	typedef typename GatherAddRhs<hryky_template_arg>::type type;
};
/**
  @brief extracts multipliers from addtion having other operation at RHS.
 */
template <typename LhsT, typename RhsT>
class hryky::symbolic_computation::GatherAddRhs
{
public :
	typedef typename GatherAdd<hryky_template_arg>::type type;
};
/**
  @brief collects up the terms having the same multiplier.
 */
template <typename LhsT, typename RhsT>
class hryky::symbolic_computation::GatherAdd
{
public :
	typedef typename Add<Gather<LhsT>, Gather<RhsT> >::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief restricts the specialization for additional operation.
 */
template <hryky_template_param>
class GatherImpl<AddImpl<hryky_template_arg> >
{
public :
	typedef typename GatherAddLhs<hryky_template_arg>::type type;
};
/**
  @brief extracts multipliers from addtion having multiplication at LHS.
 */
template <typename LLhsT, typename LRhsT, typename RhsT>
class GatherAddLhs<MultiplyImpl<LLhsT, LRhsT>, RhsT>
{
public :
	typedef typename ConditionalC<
		Dividable<RhsT, LLhsT>::value,
		Mul<LLhsT, Add<LRhsT, RhsT> >,
		typename ConditionalC<
			Dividable<RhsT, LRhsT>::value,
			Mul<Add<LLhsT, RhsT>, LRhsT>,
			Add<Gather<Mul<LLhsT, LRhsT> >, Gather<RhsT> >
		>::type
	>::type type;
};
/**
  @brief extracts multipliers from addtion having multiplication at RHS.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class GatherAddRhs<LhsT, MultiplyImpl<RLhsT, RRhsT> >
{
public :
	typedef typename ConditionalC<
		Dividable<LhsT, RLhsT>::value,
		Mul<RLhsT, Add<LhsT, RRhsT>>,
		typename ConditionalC<
			Dividable<LhsT, RRhsT>::value,
			Mul<Add<LhsT, RLhsT>, RRhsT>,
			Add<Gather<LhsT>, Gather<Mul<RLhsT, RRhsT> > >
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
#endif // SYMBOLIC_COMPUTATION_GATHER_ADD_H_20131125232001638
// end of file
