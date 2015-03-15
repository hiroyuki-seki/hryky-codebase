/**
  @file     matrix.h
  @brief    conducts a 2D container as a matrix in linear algebra.
  @author   HRYKY
  @version  $Id: matrix.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef MATRIX_H_20131104114858159
#define MATRIX_H_20131104114858159
#include "hryky/capacity_of.h"
#include "hryky/linear_algebra/transpose_of.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	template<typename, size_t> class ContainerT, \
	typename ValueT, \
	size_t Rows, \
	size_t Columns
#define hryky_template_arg \
	ContainerT, ValueT, Rows, Columns
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// conducts a 2D container as a matrix in linear algebra.
	template <hryky_template_param>
	class Matrix;

	template <
		template<typename, size_t> class ContainerT,
		typename ValueT,
		size_t Size
	>
	class ColumnVector;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief conducts a 2D container as a matrix in linear algebra.

   The order of internal elements is column-major. For instance, the element at
  the second row and the third column is located at ContainerT[2][1] (on the
  zero-origin).
 */
template <
	template <typename, size_t> class ContainerT,
	typename ValueT,
	size_t Rows,
	size_t Columns
>
class hryky::Matrix :
	public ContainerT<ContainerT<ValueT, Rows>, Columns>
{
public :

	typedef Matrix<hryky_template_arg>          this_type;
	typedef ContainerT<ValueT, Rows>            column_type;
	typedef ContainerT<column_type, Columns>    base_type;

	/// multiplies this matrix by an other matrix from right.
	template <size_t RhsColumns>
	Matrix<ContainerT, ValueT, Rows, RhsColumns> operator*(
		Matrix<ContainerT, ValueT, Columns, RhsColumns> const & rhs) const;

	/// multiplies by a column vector from right.
	ColumnVector<ContainerT, ValueT, Rows> operator*(
		ColumnVector<ContainerT, ValueT, Columns> const & rhs) const;

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief transposes a Matrix
 */
template <hryky_template_param>
class TransposeOf<Matrix<hryky_template_arg> >
{
public :
	typedef Matrix<ContainerT, ValueT, Columns, Rows> type;
};
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief multiplies this matrix by an other matrix from right.
 */
template <hryky_template_param>
template <size_t RhsColumns>
hryky::Matrix<ContainerT, ValueT, Rows, RhsColumns>
hryky::Matrix<hryky_template_arg>::operator*(
	Matrix<ContainerT, ValueT, Columns, RhsColumns> const & rhs) const
{
	typedef Matrix<ContainerT, ValueT, Columns, RhsColumns> rhs_type;
	typedef Matrix<ContainerT, ValueT, Rows, RhsColumns> result_type;
	result_type result = result_type();

	this_type const & lhs = *this;
	lhs.foreach_at([&rhs, &result](
		const_reference lhs_column, size_type const lhs_column_id) {
		rhs.foreach_at([&lhs_column, lhs_column_id, &result](
			rhs_type::const_reference rhs_column,
			rhs_type::size_type const rhs_column_id) {
			result[rhs_column_id] += lhs_column * rhs_column[lhs_column_id];
		});
	});

	return result;
}
/**
  @brief multiplies by a column vector from right.
 */
template <hryky_template_param>
hryky::ColumnVector<ContainerT, ValueT, Rows> 
hryky::Matrix<hryky_template_arg>::operator*(
	ColumnVector<ContainerT, ValueT, Columns> const & rhs) const
{
	typedef ColumnVector<ContainerT, ValueT, Columns> rhs_type;
	typedef ColumnVector<ContainerT, ValueT, Rows> result_type;
	result_type result = result_type();

	this_type const & lhs = *this;
	lhs.foreach_at([&rhs, &result](
		const_reference lhs_column, size_type const lhs_column_id) {
		result += lhs_column * rhs[lhs_column_id];
	});
	
	return result;
}
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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // MATRIX_H_20131104114858159
// end of file
