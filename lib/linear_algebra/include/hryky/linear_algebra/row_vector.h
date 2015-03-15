/**
  @file     row_vector.h
  @brief    conducts a container as row vector.
  @author   HRYKY
  @version  $Id: row_vector.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef ROW_VECTOR_H_20131102212741560
#define ROW_VECTOR_H_20131102212741560
#include "hryky/type_traits/as_parameter.h"
#include "hryky/inner_product.h"
#include "hryky/capacity_of.h"
#include "hryky/linear_algebra/transpose_of.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	template <typename, size_t> class ContainerT, \
	typename ValueT, \
	size_t Size
#define hryky_template_arg \
	ContainerT, ValueT, Size
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// conducts a container as row vector.
	template <hryky_template_param>
	class RowVector;

	template <hryky_template_param>
	class ColumnVector;

	template <
		template <typename, size_t> class ContainerT,
		typename ValueT,
		size_t Rows,
		size_t Columns
	>
	class Matrix;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief conducts a container as row vector.
 */
template <hryky_template_param>
class hryky::RowVector :
	public ContainerT<ValueT, Size>
{
public :
	typedef RowVector<hryky_template_arg>   this_type;
	typedef ContainerT<ValueT, Size>        base_type;

	/// calculates the inner product with a column vector.
	ValueT operator*(
		ColumnVector<ContainerT, ValueT, Size> const & rhs) const;

	/// multiplies by a matrix from right.
	template <size_t Columns>
	RowVector<ContainerT, ValueT, Columns>
		operator*(
			Matrix<ContainerT, ValueT, Size, Columns> const & rhs) const;

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief transposes a row vector to a column vector.
 */
template <hryky_template_param>
class TransposeOf<RowVector<hryky_template_arg> >
{
public :
	typedef ColumnVector<ContainerT, ValueT, Size> type;
};
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief calculates the inner product with a column vector.
 */
template <hryky_template_param>
ValueT
hryky::RowVector<hryky_template_arg>::operator*(
	ColumnVector<ContainerT, ValueT, Size> const & rhs) const
{
	ValueT ret = ValueT();
	this->foreach_at([&ret, &rhs](const_reference lhs, size_type const index) {
		ret += hryky::inner_product(lhs, rhs[index]);
	});
	return ret;
}
/**
  @brief multiplies by a matrix from right.
 */
template <hryky_template_param>
template <size_t Columns>
hryky::RowVector<ContainerT, ValueT, Columns> 
hryky::RowVector<hryky_template_arg>::operator*(
	Matrix<ContainerT, ValueT, Size, Columns> const & rhs) const
{
	typedef Matrix<ContainerT, ValueT, Size, Columns> rhs_type;
	typedef RowVector<ContainerT, ValueT, Columns> result_type;

	result_type result;
	this_type const & lhs = *this;
	
	rhs.foreach_at([&result, &lhs](
		rhs_type::const_reference rhs_column,
		rhs_type::size_type const column_id) {
		result[column_id] = hryky::inner_product(lhs, rhs_column);
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
namespace linear_algebra
{
} // namespace linear_algebra
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // ROW_VECTOR_H_20131102212741560
// end of file
