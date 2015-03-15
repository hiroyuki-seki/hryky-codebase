/**
  @file     symbolic_computation_scatter_divide.h
  @brief    applies division to the term in additional operation.
  @author   HRYKY
  @version  $Id: symbolic_computation_scatter_divide.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_SCATTER_DIVIDE_H_20131127230624629
#define SYMBOLIC_COMPUTATION_SCATTER_DIVIDE_H_20131127230624629
#include "hryky/symbolic_computation/symbolic_computation_scatter.h"
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
	/// applies division to the term in additional operation.
	template <hryky_template_param>
	class ScatterDivide;

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

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief applies division to the term in additional operation.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ScatterDivide
{
public :
	typedef typename Divide<Scatter<LhsT>, Scatter<RhsT> >::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief restricts the specialization for division operation.
 */
template <hryky_template_param>
class ScatterImpl<DivideImpl<hryky_template_arg> >
{
public :
	typedef typename ScatterDivide<hryky_template_arg>::type type;
};
/**
  @brief applies the divisor to additional terms at the dividend.
 */
template <typename LLhsT, typename LRhsT, typename RhsT>
class ScatterDivide<AddImpl<LLhsT, LRhsT>, RhsT>
{
public :
	typedef typename Scatter<
		Add<Divide<LLhsT, RhsT>, Divide<LRhsT, RhsT> > >::type type;
};
/**
  @brief applies the divisor to subtractive terms at the dividend.
 */
template <typename LLhsT, typename LRhsT, typename RhsT>
class ScatterDivide<SubtractImpl<LLhsT, LRhsT>, RhsT>
{
public :
	typedef typename Scatter<
		Sub<Divide<LLhsT, RhsT>, Divide<LRhsT, RhsT> > >::type type;
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
#endif // SYMBOLIC_COMPUTATION_SCATTER_DIVIDE_H_20131127230624629
// end of file
