/**
  @file     symbolic_computation_align_multiply.h
  @brief    aligns the operations in multiplication.
  @author   HRYKY
  @version  $Id: symbolic_computation_align_multiply.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_ALIGN_MULTIPLY_H_20131124210023541
#define SYMBOLIC_COMPUTATION_ALIGN_MULTIPLY_H_20131124210023541
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
	/// aligns the operations in multiplication.
	template <hryky_template_param>
	class AlignMul;

	template <hryky_template_param>
	class Mul;

	template <hryky_template_param>
	class MultiplyImpl;

	template <hryky_template_param>
	class Divide;

	template <hryky_template_param>
	class DivideImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief aligns the operations in multiplication.
 */
template <typename LhsT, typename RhsT>
class hryky::symbolic_computation::AlignMul
{
public :
	typedef typename Mul<Align<LhsT>, Align<RhsT> >::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief constraints the specialization to multiplication.
 */
template <hryky_template_param>
class AlignImpl<MultiplyImpl<hryky_template_arg> >
{
public :
	typedef typename AlignMul<hryky_template_arg>::type type;
};
/**
  @brief moves a multiplication from RHS to LHS.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class AlignMul<LhsT, MultiplyImpl<RLhsT, RRhsT> >
{
public :
	typedef typename Align<Mul<Mul<LhsT, RLhsT>, RRhsT> >::type type;
};
/**
  @brief moves a division from RHS to LHS.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class AlignMul<LhsT, DivideImpl<RLhsT, RRhsT> >
{
public :
	typedef typename Align<Divide<Mul<LhsT, RLhsT>, RRhsT> >::type type;
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
#endif // SYMBOLIC_COMPUTATION_ALIGN_MULTIPLY_H_20131124210023541
// end of file
