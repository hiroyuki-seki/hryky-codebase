/**
  @file     symbolic_computation_identity_matrix.h
  @brief    represents an identity matrix with arbitrary size.
  @author   HRYKY
  @version  $Id: symbolic_computation_identity_matrix.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_IDENTITY_MATRIX_H_20131113085220036
#define SYMBOLIC_COMPUTATION_IDENTITY_MATRIX_H_20131113085220036
#include "hryky/symbolic_computation/symbolic_computation_integer.h"
#include "hryky/symbolic_computation/symbolic_computation_vector.h"
#include "hryky/type_traits/conditional.h"
#include "hryky/type_traits/value_type_of.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	size_t Size, typename EvalT
#define hryky_template_arg \
	Size, EvalT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// represents an identity matrix with arbitrary size.
	template <hryky_template_param>
	class IdentityMatrix;

	/// defines column vectors of identity matrix recursively.
	template <size_t Column, size_t Size, typename EvalT>
	class IdentityMatrixColumns;

	/// defines elements of identity matrix recursively.
	template <size_t Row, size_t Column, typename EvalT>
	class IdentityMatrixElements;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief represents an identity matrix with arbitrary size.
 */
template <size_t Size, typename EvalT>
class hryky::symbolic_computation::IdentityMatrix :
	public WithStreamOut<IdentityMatrix<hryky_template_arg> >,
	public Evalable<IdentityMatrix<hryky_template_arg>, EvalT>
{
public :
	typedef typename IdentityMatrixColumns<Size, Size, EvalT>::type type;
};
/**
  @brief defines a column vector of identity matrix recursively.
 */
template <size_t Column, size_t Size, typename EvalT>
class hryky::symbolic_computation::IdentityMatrixColumns
{
public :
	typedef V<
		IdentityMatrixElements<
			Size, Column, typename ValueTypeOf<EvalT>::type>,
		IdentityMatrixColumns<
			Column - 1, Size, EvalT>,
		EvalT
	> type;
};
/**
  @brief defines elements of identity matrix recursively.
 */
template <size_t Row, size_t Column, typename EvalT>
class hryky::symbolic_computation::IdentityMatrixElements
{
public :
	typedef V<
		ConditionalC<
			Row == Column,
			Integer<typename ValueTypeOf<EvalT>::type, 1>,
			Integer<typename ValueTypeOf<EvalT>::type, 0>
		>,
		IdentityMatrixElements<Row - 1, Column, EvalT>,
		EvalT
	> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief terminates the recursion of IdentityMatrixColumns.
 */
template <size_t Size, typename EvalT>
class IdentityMatrixColumns<0, Size, EvalT>
{
public :
	typedef Terminator type;
};
/**
  @brief terminates the recursion of IdentityMatrixElements.
 */
template <size_t Column, typename EvalT>
class IdentityMatrixElements<0, Column, EvalT>
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
#endif // SYMBOLIC_COMPUTATION_IDENTITY_MATRIX_H_20131113085220036
// end of file
