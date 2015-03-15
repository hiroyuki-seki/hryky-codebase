/**
  @file     symbolic_computation_is_diagonal_matrix.h
  @brief    confirms whether elements outsides diagonal entries are zero.
  @author   HRYKY
  @version  $Id: symbolic_computation_is_diagonal_matrix.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_IS_DIAGONAL_MATRIX_H_20131113150435294
#define SYMBOLIC_COMPUTATION_IS_DIAGONAL_MATRIX_H_20131113150435294
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
	/// confirms whether elements outsides diagonal entries are zero.
	template <hryky_template_param>
	class IsDiagonalMatrix;

	/// confirms whether a column is the part of diagonal matrix.
	template <typename MatrixT, size_t Column>
	class IsDiagonalMatrixColumn;

	/// confirms whether an element is the part of diagonal matrix.
	template <typename VectorT, size_t Row, size_t Column>
	class IsDiagonalMatrixElement;

	

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether elements outsides diagonal entries are zero.
 */
template <typename MatrixT>
class hryky::symbolic_computation::IsDiagonalMatrix
{
private :
	typedef typename MatrixT::type target;
public :
	static bool const value = IsDiagonalMatrixColumn<target, 0>::value;
};
/**
  @brief confirms whether a column is the part of diagonal matrix.
 */
template <typename MatrixT, size_t Column>
class hryky::symbolic_computation::IsDiagonalMatrixColumn
{
private :
	typedef typename MatrixT::type target;
public :
	static bool const value = (
		IsDiagonalMatrixElement<
			typename target::element_type, 0, Column>::value &&
		IsDiagonalMatrixColumn<
			typename target::rest_type, Column + 1>::value);
};
/**
  @brief confirms whether an element is the part of diagonal matrix.
 */
template <typename VectorT, size_t Row, size_t Column>
class hryky::symbolic_computation::IsDiagonalMatrixElement
{
private :
	typedef typename VectorT::type target;
public :
	static bool const value = (
		(Row == Column ||
		 IsZero<typename target::element_type>::value) &&
		IsDiagonalMatrixElement<
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
  @brief terminates the recursion of IsDiagonalMatrixColumn.
 */
template <size_t Column>
class IsDiagonalMatrixColumn<Terminator, Column>
{
public :
	static bool const value = true;
};
/**
  @brief terminates the recursion of IsDiagonalMatrixElement.
 */
template <size_t Row, size_t Column>
class IsDiagonalMatrixElement<Terminator, Row, Column>
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
#endif // SYMBOLIC_COMPUTATION_IS_DIAGONAL_MATRIX_H_20131113150435294
// end of file
