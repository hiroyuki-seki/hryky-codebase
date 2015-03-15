/**
  @file     symbolic_computation_is_square_matrix.h
  @brief    confirms whether the sizes of row and column are same.
  @author   HRYKY
  @version  $Id: symbolic_computation_is_square_matrix.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_IS_SQUARE_MATRIX_H_20131110223039604
#define SYMBOLIC_COMPUTATION_IS_SQUARE_MATRIX_H_20131110223039604
#include "hryky/symbolic_computation/symbolic_computation_vector_length.h"
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
	/// confirms whether the sizes of row and column are same.
	template <hryky_template_param>
	class IsSquareMatrix;

	/// confirms whether the columns have the specified length.
	template <typename MatrixT, size_t Size>
	class AreColumnsSameSize;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether the sizes of row and column are same.
 */
template <typename MatrixT>
class hryky::symbolic_computation::IsSquareMatrix
{
private :
	typedef typename MatrixT::type target;
public :
	static const bool value =
		AreColumnsSameSize<target, VectorLength<target>::value>::value;
};
/**
  @brief confirms whether the columns have the specified length.
 */
template <typename MatrixT, size_t Size>
class hryky::symbolic_computation::AreColumnsSameSize
{
public :
	static const bool value = (
		VectorLength<typename MatrixT::element_type>::value == Size
		&& AreColumnsSameSize<typename MatrixT::rest_type, Size>::value);
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief terminates confirming the size of column.
 */
template <size_t Size>
class AreColumnsSameSize<Terminator, Size>
{
public :
	static const bool value = true;
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
#endif // SYMBOLIC_COMPUTATION_IS_SQUARE_MATRIX_H_20131110223039604
// end of file
