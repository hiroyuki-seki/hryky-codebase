/**
  @file     symbolic_computation_align_add.h
  @brief    sorts operations in addition.
  @author   HRYKY
  @version  $Id: symbolic_computation_align_add.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_ALIGN_ADD_H_20131124203656525
#define SYMBOLIC_COMPUTATION_ALIGN_ADD_H_20131124203656525
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
	/// sorts operations in addition.
	template <hryky_template_param>
	class AlignAdd;

	template <hryky_template_param>
	class Add;

	template <hryky_template_param>
	class AddImpl;

	template <hryky_template_param>
	class Sub;

	template <hryky_template_param>
	class SubtractImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief sorts operations in addition.
 */
template <hryky_template_param>
class hryky::symbolic_computation::AlignAdd
{
public :
	typedef typename Add<Align<LhsT>, Align<RhsT> >::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief constrains the specialization to additional operation.
 */
template <hryky_template_param>
class AlignImpl<AddImpl<hryky_template_arg> >
{
public :
	typedef typename AlignAdd<hryky_template_arg>::type type;
};
/**
  @brief moves an addition from RHS to LHS.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class AlignAdd<LhsT, AddImpl<RLhsT, RRhsT> >
{
public :
	typedef typename Align<Add<Add<LhsT, RLhsT>, RRhsT> >::type type;
};
/**
  @brief moves a subtraction from RHS to LHS.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class AlignAdd<LhsT, SubtractImpl<RLhsT, RRhsT> >
{
public :
	typedef typename Align<Sub<Add<LhsT, RLhsT>, RRhsT> >::type type;
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
#endif // SYMBOLIC_COMPUTATION_ALIGN_ADD_H_20131124203656525
// end of file
