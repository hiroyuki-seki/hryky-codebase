/**
  @file     symbolic_computation_scatter_multiply.h
  @brief    distributes the multiplier to other terms.
  @author   HRYKY
  @version  $Id: symbolic_computation_scatter_multiply.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_SCATTER_MULTIPLY_H_20131124171205383
#define SYMBOLIC_COMPUTATION_SCATTER_MULTIPLY_H_20131124171205383
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
	/// distributes the multiplier to other terms.
	template <hryky_template_param>
	class ScatterMul;

	template <hryky_template_param>
	class ScatterMulLhs;

	template <hryky_template_param>
	class ScatterMulRhs;

	template <hryky_template_param>
	class Mul;

	template <hryky_template_param>
	class MultiplyImpl;

	template <typename LhsT, typename RhsT>
	class Add;

	template <typename LhsT, typename RhsT>
	class AddImpl;

	template <typename LhsT, typename RhsT>
	class Sub;

	template <typename LhsT, typename RhsT>
	class SubtractImpl;

	template <typename LhsT, typename RhsT>
	class Divide;

	template <typename LhsT, typename RhsT>
	class DivideImpl;

	template <typename TermT>
	class Complement;

	template <typename TermT>
	class ComplementImpl;

	template <typename OpT, typename IndexT, typename FirstT, typename LastT>
	class Sum;

	template <typename OpT, typename IndexT, typename FirstT, typename LastT>
	class SummationImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief distributes the multiplier at RHS to the operation at LHS.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ScatterMulLhs
{
public :
	typedef typename ScatterMulRhs<hryky_template_arg>::type type;
};
/**
  @brief distributes the multiplier at LHS to the operation at RHS.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ScatterMulRhs
{
public :
	typedef typename ScatterMul<hryky_template_arg>::type type;
};
/**
  @brief distributes the multiplier to other terms.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ScatterMul
{
public :
	typedef typename Mul<Scatter<LhsT>, Scatter<RhsT> >::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief constrains the scatter for multiplication.
 */
template <hryky_template_param>
class ScatterImpl<MultiplyImpl<hryky_template_arg> >
{
public :
	typedef typename ScatterMulLhs<hryky_template_arg>::type type;
};
//------------------------------------------------------------------------------
// constrains the specializations for other operation at LHS
//------------------------------------------------------------------------------
/**
  @brief distributes the multiplier at RHS to the addition at LHS.
 */
template <typename LLhsT, typename LRhsT, typename RhsT>
class ScatterMulLhs<AddImpl<LLhsT, LRhsT>, RhsT>
{
public :
	typedef typename Scatter<
		Add<Mul<LLhsT, RhsT>, Mul<LRhsT, RhsT> > >::type type;
};
/**
  @brief distributes the multiplier at RHS to the subtraction at LHS.
 */
template <typename LLhsT, typename LRhsT, typename RhsT>
class ScatterMulLhs<SubtractImpl<LLhsT, LRhsT>, RhsT>
{
public :
	typedef typename Scatter<
		Sub<Mul<LLhsT, RhsT>, Mul<LRhsT, RhsT> > >::type type;
};
/**
  @brief distributes the multiplier at RHS to the division at LHS.
 */
template <typename LLhsT, typename LRhsT, typename RhsT>
class ScatterMulLhs<DivideImpl<LLhsT, LRhsT>, RhsT>
{
public :
	typedef typename Scatter<
		Divide<Mul<LLhsT, RhsT>, LRhsT> >::type type;
};
/**
  @brief distributes the multiplier at RHS to the complement at LHS.
 */
template <typename LhsT, typename RhsT>
class ScatterMulLhs<ComplementImpl<LhsT>, RhsT>
{
public :
	typedef typename Scatter<
		Complement<Mul<LhsT, RhsT> > >::type type;
};
/**
  @brief distributes the multiplier at RHS to the summation at LHS.
 */
template <
	typename LhsT,
	typename RhsT,
	typename IndexT,
	typename FirstT,
	typename LastT
>
class ScatterMulLhs<SummationImpl<LhsT, IndexT, FirstT, LastT>, RhsT>
{
public :
	typedef typename Scatter<
		Sum<Mul<LhsT, RhsT>, IndexT, FirstT, LastT> >::type type;
};
//------------------------------------------------------------------------------
// constrains the specializations for other operation at RHS
//------------------------------------------------------------------------------
/**
  @brief distributes the multiplier at LHS to the addition at RHS.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class ScatterMulRhs<LhsT, AddImpl<RLhsT, RRhsT> >
{
public :
	typedef typename Scatter<
		Add<Mul<LhsT, RLhsT>, Mul<LhsT, RRhsT> > >::type type;
};
/**
  @brief distributes the multiplier at LHS to the subtraction at RHS.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class ScatterMulRhs<LhsT, SubtractImpl<RLhsT, RRhsT> >
{
public :
	typedef typename Scatter<
		Sub<Mul<LhsT, RLhsT>, Mul<LhsT, RRhsT> > >::type type;
};
/**
  @brief distributes the multiplier at LHS to the division at RHS.
 */
template <typename LhsT, typename RLhsT, typename RRhsT>
class ScatterMulRhs<LhsT, DivideImpl<RLhsT, RRhsT> >
{
public :
	typedef typename Scatter<
		Divide<Mul<LhsT, RLhsT>, RRhsT> >::type type;
};
/**
  @brief distributes the multiplier at LHS to the complement at RHS.
 */
template <typename LhsT, typename RhsT>
class ScatterMulRhs<LhsT, ComplementImpl<RhsT> >
{
public :
	typedef typename Scatter<
		Complement<Mul<LhsT, RhsT> > >::type type;
};
/**
  @brief distributes the multiplier at LHS to the summation at RHS.
 */
template <
	typename LhsT,
	typename RhsT,
	typename IndexT,
	typename FirstT,
	typename LastT
>
class ScatterMulRhs<LhsT, SummationImpl<RhsT, IndexT, FirstT, LastT> >
{
public :
	typedef typename Scatter<
		Sum<Mul<LhsT, RhsT>, IndexT, FirstT, LastT> >::type type;
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
#endif // SYMBOLIC_COMPUTATION_SCATTER_MULTIPLY_H_20131124171205383
// end of file
