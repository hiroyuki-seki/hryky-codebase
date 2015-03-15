/**
  @file     symbolic_computation_align_subtract.h
  @brief    aligns operations in subtraction.
  @author   HRYKY
  @version  $Id: symbolic_computation_align_subtract.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_ALIGN_SUBTRACT_H_20131124222144598
#define SYMBOLIC_COMPUTATION_ALIGN_SUBTRACT_H_20131124222144598
#include "hryky/symbolic_computation/symbolic_computation_align.h"
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
	/// aligns operations in subtraction.
	template <hryky_template_param>
	class AlignSub;

	template <hryky_template_param>
	class Sub;

	template <hryky_template_param>
	class SubtractImpl;

	template <hryky_template_param>
	class Add;

	template <hryky_template_param>
	class AddImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief aligns operations in subtraction.
 */
template <typename LhsT, typename RhsT>
class hryky::symbolic_computation::AlignSub
{
public :
	typedef typename Sub<Align<LhsT>, Align<RhsT> >::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief restricts the specialization to subtraction.h
 */
template <hryky_template_param>
class AlignImpl<SubtractImpl<hryky_template_arg> >
{
public :
	typedef typename AlignSub<hryky_template_arg>::type type;
};
/**
  @brief dissolves the addition at RHS.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class AlignSub<LhsT, AddImpl<RLhsT, RRhsT> >
{
public :
	typedef typename Align<Sub<Sub<LhsT, RLhsT>, RRhsT> >::type type;
};
/**
  @brief dissolves the subtraction at RHS.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class AlignSub<LhsT, SubtractImpl<RLhsT, RRhsT> >
{
public :
	typedef typename Align<Add<Sub<LhsT, RLhsT>, RRhsT> >::type type;
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
#endif // SYMBOLIC_COMPUTATION_ALIGN_SUBTRACT_H_20131124222144598
// end of file
