/**
  @file     symbolic_computation_is_identity_matrix.h
  @brief    confirms whether a matrix is identity matrix.
  @author   HRYKY
  @version  $Id: symbolic_computation_is_identity_matrix.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_IS_IDENTITY_MATRIX_H_20131112231419634
#define SYMBOLIC_COMPUTATION_IS_IDENTITY_MATRIX_H_20131112231419634
#include "hryky/symbolic_computation/symbolic_computation_is_square_matrix.h"
#include "hryky/symbolic_computation/symbolic_computation_is_one.h"
#include "hryky/symbolic_computation/symbolic_computation_is_zero.h"
#include "hryky/symbolic_computation/symbolic_computation_terminator.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename MatrixT
#define hryky_template_arg \
	MatrixT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// confirms whether a matrix is identity matrix.
	template <hryky_template_param>
	class IsIdentityMatrix;

	/// confirms whether a column is the part of identity matrix.
	template <typename MatrixT, size_t Column>
	class IsIdentityMatrixColumn;

	/// confirms whether an element is the part of identity matrix.
	template <typename VectorT, size_t Row, size_t Column>
	class IsIdentityMatrixElement;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether a matrix is identity matrix.
 */
template <typename MatrixT>
class hryky::symbolic_computation::IsIdentityMatrix
{
private :
	typedef typename MatrixT::type target;
public :
	static bool const value = IsSquareMatrix<target>::value &&
		IsIdentityMatrixColumn<target, 0>::value;
};
/**
  @brief confirms whether a column is the part of identity matrix.
 */
template <typename MatrixT, size_t Column>
class hryky::symbolic_computation::IsIdentityMatrixColumn
{
private :
	typedef typename MatrixT::type target;
public :
	static bool const value = (
		IsIdentityMatrixElement<
			typename target::element_type, 0, Column>::value &&
		IsIdentityMatrixColumn<
			typename target::rest_type, Column + 1>::value);
};
/**
  @brief confirms whether an element is the part of identity matrix.
 */
template <typename VectorT, size_t Row, size_t Column>
class hryky::symbolic_computation::IsIdentityMatrixElement
{
private :
	typedef typename VectorT::type target;
public :
	static bool const value = (
		(Row == Column ?
		 IsOne<typename target::element_type>::value :
		 IsZero<typename target::element_type>::value) &&
		IsIdentityMatrixElement<
			typename target::rest_type, Row + 1, Column>::value);
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief terminates the recursion of IsIdentityMatrixColumn.
 */
template <size_t Column>
class IsIdentityMatrixColumn<Terminator, Column>
{
public :
	static bool const value = true;
};
/**
  @brief terminates the recursion of IsIdentityMatrixElement.
 */
template <size_t Row, size_t Column>
class IsIdentityMatrixElement<Terminator, Row, Column>
{
public :
	static bool const value = true;
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
#endif // SYMBOLIC_COMPUTATION_IS_IDENTITY_MATRIX_H_20131112231419634
// end of file
