/**
  @file     vec3.h
  @brief    contains three elements.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef VEC3_H_20160628180738421
#define VEC3_H_20160628180738421
#include "hryky/definition.h"
#include "hryky/clear.h"
#include "hryky/swap.h"
#include "hryky/foreach.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT
#define hryky_template_arg \
	ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace rtiow
{
	/// contains three elements.
	template <hryky_template_param>
	class Vec3;

} // namespace rtiow
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief contains three elements.
 */
template <typename ValueT = float>
class rtiow::Vec3
{
public :

	typedef Vec3<hryky_template_arg> this_type;
	typedef ValueT value_type;

	/// default constructor.
	Vec3();

	/// instantiates with an element.
	template <typename A1T>
	Vec3(A1T a1);

	/// instantiates with three elements.
	template <typename A1T, typename A2T, typename A3T>
	Vec3(A1T x, A2T y, A3T z);

	/// copy constructor.
	Vec3(this_type const &);

	/// move constructor.
	Vec3(this_type &&);

	/// destructor.
	~Vec3();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// retrieves an element.
	template <typename IndexT>
	ValueT operator[](IndexT index) const;

	/// retrieves the reference to an element.
	template <typename IndexT>
	ValueT & operator[](IndexT index);

	/// unary operator '+'.
	this_type const & operator+() const;

	/// unary operator '+' as mutable.
	this_type & operator+();

	/// unary operator '-'.
	this_type operator-() const;

	/// operator '+='.
	this_type & operator+=(this_type const & rhs);

	/// operator '-='.
	this_type & operator-=(this_type const & rhs);

	/// operator '*='.
	this_type & operator*=(this_type const & rhs);

	/// operator '*=' with a scalar value.
	template <typename RhsT>
	this_type & operator*=(RhsT rhs);

	/// operator '/='.
	this_type & operator/=(this_type const & rhs);

	/// operator '/=' with a scalar value.
	template <typename RhsT>
	this_type & operator/=(RhsT rhs);

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// retrieves the x element.
	ValueT x() const;

	/// retrieves the y element.
	ValueT y() const;

	/// retrieves the z element.
	ValueT z() const;

	/// retrieves the length of this vector.
	ValueT length() const;

	/// the square of length.
	ValueT slength() const;

protected :

private :

	typedef value_type values_type[3];

	values_type values_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace rtiow
{
} // namespace rtiow
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
rtiow::Vec3<hryky_template_arg>::Vec3()
	: values_()
{
}
/**
  @brief instantiates with three elements.
 */
template <hryky_template_param>
template <typename A1T, typename A2T, typename A3T>
rtiow::Vec3<hryky_template_arg>::Vec3(A1T x, A2T y, A3T z)
{
	this->values_[0] = x;
	this->values_[1] = y;
	this->values_[2] = z;
}
/**
  @brief instantiates with an element.
 */
template <hryky_template_param>
template <typename A1T>
rtiow::Vec3<hryky_template_arg>::Vec3(A1T a1)
{
	this->values_[0] = a1;
	this->values_[1] = a1;
	this->values_[2] = a1;
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
rtiow::Vec3<hryky_template_arg>::Vec3(this_type const & rhs)
{
	::std::copy(&rhs.values_[0], &rhs.values_[3], &this->values_[0]);
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
rtiow::Vec3<hryky_template_arg>::Vec3(this_type && rhs)
{
	::std::copy(&rhs.values_[0], &rhs.values_[3], &this->values_[0]);
}
/**
  @brief destructor.
 */
template <hryky_template_param>
rtiow::Vec3<hryky_template_arg>::~Vec3()
{
}
/**
  @brief retrieves an element.
 */
template <hryky_template_param>
template <typename IndexT>
ValueT
rtiow::Vec3<hryky_template_arg>::operator[](IndexT index) const
{
	return this->values_[index];
}
/**
  @brief retrieves the reference to an element.
 */
template <hryky_template_param>
template <typename IndexT>
ValueT &
rtiow::Vec3<hryky_template_arg>::operator[](IndexT index)
{
	return this->values_[index];
}
/**
  @brief unary operator '+'.
 */
template <hryky_template_param>
rtiow::Vec3<hryky_template_arg> const & 
rtiow::Vec3<hryky_template_arg>::operator+() const
{
	return *this;
}
/**
  @brief unary operator '+' as mutable.
 */
template <hryky_template_param>
rtiow::Vec3<hryky_template_arg> & 
rtiow::Vec3<hryky_template_arg>::operator+()
{
	return *this;
}
/**
  @brief unary operator '-'.
 */
template <hryky_template_param>
rtiow::Vec3<hryky_template_arg> 
rtiow::Vec3<hryky_template_arg>::operator-() const
{
	return this_type(
		-this->values_[0],
		-this->values_[0],
		-this->values_[0]);
}
/**
  @brief operator '+='.
 */
template <hryky_template_param>
rtiow::Vec3<hryky_template_arg> & 
rtiow::Vec3<hryky_template_arg>::operator+=(
	this_type const & rhs)
{
	this->values_[0] += rhs.values_[0];
	this->values_[1] += rhs.values_[1];
	this->values_[2] += rhs.values_[2];
	return *this;
}
/**
  @brief operator '-='.
 */
template <hryky_template_param>
rtiow::Vec3<hryky_template_arg> & 
rtiow::Vec3<hryky_template_arg>::operator-=(
	this_type const & rhs)
{
	this->values_[0] -= rhs.values_[0];
	this->values_[1] -= rhs.values_[1];
	this->values_[2] -= rhs.values_[2];
	return *this;
}
/**
  @brief operator '*='.
 */
template <hryky_template_param>
rtiow::Vec3<hryky_template_arg> & 
rtiow::Vec3<hryky_template_arg>::operator*=(
	this_type const & rhs)
{
	this->values_[0] *= rhs.values_[0];
	this->values_[1] *= rhs.values_[1];
	this->values_[2] *= rhs.values_[2];
	return *this;
}
/**
  @brief operator '*=' with a scalar value.
 */
template <hryky_template_param>
template <typename RhsT>
rtiow::Vec3<hryky_template_arg> &
rtiow::Vec3<hryky_template_arg>::operator*=(RhsT rhs)
{
	this->values_[0] *= rhs;
	this->values_[1] *= rhs;
	this->values_[2] *= rhs;
	return *this;
}
/**
  @brief operator '/='.
 */
template <hryky_template_param>
rtiow::Vec3<hryky_template_arg> & 
rtiow::Vec3<hryky_template_arg>::operator/=(
	this_type const & rhs)
{
	this->values_[0] /= rhs.values_[0];
	this->values_[1] /= rhs.values_[1];
	this->values_[2] /= rhs.values_[2];
	return *this;
}
/**
  @brief operator '/=' with a scalar value.
 */
template <hryky_template_param>
template <typename RhsT>
rtiow::Vec3<hryky_template_arg> &
rtiow::Vec3<hryky_template_arg>::operator/=(RhsT rhs)
{
	return this->operator*=(1 / rhs);
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void rtiow::Vec3<hryky_template_arg>::clear()
{
	hryky::clear(this->values_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void rtiow::Vec3<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(values);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
rtiow::Vec3<hryky_template_arg>::write_to(StreamT & out) const
{
	return out;
}
/**
  @brief retrieves the x element.
 */
template <hryky_template_param>
ValueT rtiow::Vec3<hryky_template_arg>::x() const
{
	return this->values_[0];
}
/**
  @brief retrieves the y element.
 */
template <hryky_template_param>
ValueT rtiow::Vec3<hryky_template_arg>::y() const
{
	return this->values_[1];
}
/**
  @brief retrieves the z element.
 */
template <hryky_template_param>
ValueT rtiow::Vec3<hryky_template_arg>::z() const
{
	return this->values_[2];
}
/**
  @brief retrieves the length of this vector.
 */
template <hryky_template_param>
ValueT
rtiow::Vec3<hryky_template_arg>::length() const
{
	return sqrt(this->slength());
}
/**
  @brief the square of length.
 */
template <hryky_template_param>
ValueT rtiow::Vec3<hryky_template_arg>::slength() const
{
	return (
		(*this)[0] * (*this)[0]
		+ (*this)[1] * (*this)[1]
		+ (*this)[2] * (*this)[2]);
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
namespace rtiow
{
} // namespace rtiow
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // VEC3_H_20160628180738421
// end of file
