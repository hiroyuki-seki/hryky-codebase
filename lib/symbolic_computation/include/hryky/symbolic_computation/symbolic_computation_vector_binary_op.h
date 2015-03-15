/**
  @file     symbolic_computation_vector_binary_op.h
  @brief    applies a binary operation to each element between two vectors.
  @author   HRYKY
  @version  $Id: symbolic_computation_vector_binary_op.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_VECTOR_BINARY_OP_H_20131113180400419
#define SYMBOLIC_COMPUTATION_VECTOR_BINARY_OP_H_20131113180400419
#include "hryky/symbolic_computation/symbolic_computation_terminator.h"
#include "hryky/symbolic_computation/symbolic_computation_vector_length.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename LhsT, \
	typename RhsT, \
	template <typename, typename> class OpT
#define hryky_template_arg \
	LhsT, RhsT, OpT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// applies a binary operation to each element between two vectors.
	template <
		hryky_template_param,
		typename EvalT = typename OpT<LhsT, RhsT>::type::eval_type
	>
	class VectorBinaryOp;

	/// applies a binary operation without evaluated type.
	template <hryky_template_param>
	class VectorBinaryOpInternal;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief applies a binary operation to each element between two vectors.
 */
template <hryky_template_param, typename EvalT>
class hryky::symbolic_computation::VectorBinaryOp
{
private :
	typedef typename LhsT::type lhs_type;
	typedef typename RhsT::type rhs_type;
public :
	static_assert(
		VectorLength<lhs_type>::value == VectorLength<rhs_type>::value,
		"The binary operation for each element failed. "
		"Two vectors don't have same length.");

	typedef typename V<
		OpT<
			typename lhs_type::element_type,
			typename rhs_type::element_type>,
		VectorBinaryOpInternal<
			typename lhs_type::rest_type,
			typename rhs_type::rest_type,
			OpT>,
		EvalT
	>::type type;
};
/**
  @brief applies a binary operation without evaluated type.
 */
template <hryky_template_param>
class hryky::symbolic_computation::VectorBinaryOpInternal
{
private :
	typedef typename LhsT::type lhs_type;
	typedef typename RhsT::type rhs_type;
public :
	typedef typename V<
		OpT<
			typename lhs_type::element_type,
			typename rhs_type::element_type
		>,
		VectorBinaryOpInternal<
			typename lhs_type::rest_type,
			typename rhs_type::rest_type,
			OpT
		>
	>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief terminates the recursion of VectorBinaryOpInternal.
 */
template <template <typename, typename> class OpT>
class VectorBinaryOpInternal<Terminator, Terminator, OpT>
{
public :
	typedef Terminator type;
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
#endif // SYMBOLIC_COMPUTATION_VECTOR_BINARY_OP_H_20131113180400419
// end of file
