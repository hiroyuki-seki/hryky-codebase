/**
  @file     column_vector.h
  @brief    conducts a container as column vector.
  @author   HRYKY
  @version  $Id: column_vector.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef COLUMN_VECTOR_H_20131102223142605
#define COLUMN_VECTOR_H_20131102223142605
#include "hryky/capacity_of.h"
#include "hryky/conjugate.h"
#include "hryky/type_traits/as_parameter.h"
#include "hryky/inner_product.h"
#include "hryky/linear_algebra/matrix.h"
#include "hryky/linear_algebra/transpose_of.h"
#include "hryky/vector_space/vector_space_with_scale.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	template <typename, size_t> class ContainerT, typename ValueT, size_t Size
#define hryky_template_arg \
	ContainerT, ValueT, Size
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// conducts a container as column vector.
	template <hryky_template_param>
	class ColumnVector;

	template <hryky_template_param>
	class RowVector;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief conducts a container as column vector.
 */
template <hryky_template_param>
class hryky::ColumnVector :
	public ContainerT<ValueT, Size>,
	public vector_space::WithScale<ValueT, ColumnVector<hryky_template_arg> >
{
public :
	typedef ColumnVector<hryky_template_arg>    this_type;
	typedef ContainerT<ValueT, Size>            base_type;
	typedef typename AsParameter<ValueT>::type  scalar_param_type;

	typedef vector_space::WithScale<ValueT, this_type> with_scale_type;

	/// calculates the outer product with a row vector.
	template <size_t Columns>
	Matrix<ContainerT, ValueT, Size, Columns> operator*(
		RowVector<ContainerT, ValueT, Columns> const & rhs) const;

	this_type operator*(scalar_param_type scalar) const
	{
		return this->with_scale_type::operator*(scalar);
	}

	this_type & operator*=(scalar_param_type scalar)
	{
		return this->with_scale_type::operator*=(scalar);
	}

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief transposes a column vector to a row vector.
 */
template <hryky_template_param>
class TransposeOf<ColumnVector<hryky_template_arg> >
{
public :
	typedef RowVector<ContainerT, ValueT, Size> type;
};
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief calculates the outer product with a row vector.
 */
template <hryky_template_param>
template <size_t Columns>
hryky::Matrix<ContainerT, ValueT, Size, Columns>
hryky::ColumnVector<hryky_template_arg>::operator*(
	RowVector<ContainerT, ValueT, Columns> const & rhs) const
{
	typedef Matrix<ContainerT, ValueT, Size, Columns> matrix_type;
	matrix_type ret;

	this_type const & lhs = *this;

	rhs.foreach_at([&ret, &lhs](
		const_reference rhs_value, size_type const column_id) {
		ret[column_id] = lhs * hryky::conj(rhs_value);
	});
	return ret;
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
#endif // COLUMN_VECTOR_H_20131102223142605
// end of file
