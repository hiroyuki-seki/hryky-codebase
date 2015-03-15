/**
  @file     symbolic_computation_vector_unary_op.h
  @brief    applies an unary operation to each element of vector.
  @author   HRYKY
  @version  $Id: symbolic_computation_vector_unary_op.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_VECTOR_UNARY_OP_H_20131113184453447
#define SYMBOLIC_COMPUTATION_VECTOR_UNARY_OP_H_20131113184453447
#include "hryky/symbolic_computation/symbolic_computation_terminator.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TermT, template <typename> class OpT
#define hryky_template_arg \
	TermT, OpT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// applies an unary operation to each element of vector.
	template <
		hryky_template_param,
		typename EvalT = typename OpT<term_type>::type::eval_type>
	class VectorUnaryOp;

	/// applies an unary operation without evaluated type.
	template <hryky_template_param>
	class VectorUnaryOpInternal;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief applies an unary operation to each element of vector.
 */
template <hryky_template_param, typename EvalT>
class hryky::symbolic_computation::VectorUnaryOp
{
private :
	typedef typename TermT::type term_type;
public :
	typedef typename V<
		OpT<typename term_type::element_type>,
		VectorUnaryOpInternal<
			typename term_type::rest_type, OpT>,
		EvalT
	>::type type;
};
/**
  @brief applies an unary operation without evaluated type.
 */
template <hryky_template_param>
class hryky::symbolic_computation::VectorUnaryOpInternal
{
private :
	typedef typename TermT::type term_type;
public :
	typedef typename V<
		OpT<typename term_type::element_type>,
		VectorUnaryOpInternal<
			typename term_type::rest_type, OpT>
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
  @brief terminates the recursion of VectorUnaryOpInternal.
 */
template <template <typename> class OpT>
class VectorUnaryOpInternal<Terminator, OpT>
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
#endif // SYMBOLIC_COMPUTATION_VECTOR_UNARY_OP_H_20131113184453447
// end of file
