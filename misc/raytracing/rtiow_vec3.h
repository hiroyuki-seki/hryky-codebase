/**
  @file     vec3.h
  @brief    contains three elements.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef VEC3_H_20160628180738421
#define VEC3_H_20160628180738421
#include <cmath>
#include "hryky/definition.h"
#include "hryky/clear.h"
#include "hryky/swap.h"
#include "hryky/foreach.h"
#include "hryky/type_traits/add_const_reference.h"
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
namespace hryky
{
namespace rtiow
{
	/// contains three elements.
	template <hryky_template_param>
	class Vec3;

} // namespace rtiow
namespace stream
{
namespace map
{
	template <typename StreamT>
	class Scope;
	
} // namespace map
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief contains three elements.
 */
template <typename ValueT = float>
class hryky::rtiow::Vec3
{
public :

	typedef Vec3<hryky_template_arg> this_type;
	typedef ValueT value_type;
	typedef typename hryky::AddConstReference<ValueT>::type const_reference;

	/// default constructor.
	Vec3();

	/// instantiates with other vector.
	template <typename OtherT>
	Vec3(Vec3<OtherT> const & rhs);

	/// instantiates with an element.
	Vec3(const_reference a1);

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

	/// binary operator '=='.
	bool operator==(this_type const & rhs) const;

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

	/// binary operator '+'.
	this_type operator+(this_type const & rhs) const;

	/// binary operator '+' with an arbitrary scalar.
	template <typename RhsT>
	this_type operator+(RhsT rhs) const;

	/// binary operator '-'.
	this_type operator-(this_type const & rhs) const;

	/// binary operator '-' with an arbitrary scalar.
	template <typename RhsT>
	this_type operator-(RhsT rhs) const;

	/// binary operator '*'.
	this_type operator*(this_type const & rhs) const;

	/// binary operator '*' with an arbitrary scalar.
	template <typename RhsT>
	this_type operator*(RhsT rhs) const;

protected :

private :

	typedef value_type values_type[3];

	values_type values_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::rtiow::Vec3<hryky_template_arg>::Vec3()
	: values_()
{
}
/**
  @brief instantiates with other vector.
 */
template <hryky_template_param>
template <typename OtherT>
hryky::rtiow::Vec3<hryky_template_arg>::Vec3(Vec3<OtherT> const & rhs)
{
	this->values_[0] = static_cast<value_type>(rhs[0]);
	this->values_[1] = static_cast<value_type>(rhs[1]);
	this->values_[2] = static_cast<value_type>(rhs[2]);
}
/**
  @brief instantiates with three elements.
 */
template <hryky_template_param>
template <typename A1T, typename A2T, typename A3T>
hryky::rtiow::Vec3<hryky_template_arg>::Vec3(A1T x, A2T y, A3T z)
{
	this->values_[0] = static_cast<value_type>(x);
	this->values_[1] = static_cast<value_type>(y);
	this->values_[2] = static_cast<value_type>(z);
}
/**
  @brief instantiates with an element.
 */
template <hryky_template_param>
hryky::rtiow::Vec3<hryky_template_arg>::Vec3(const_reference a1)
{
	this->values_[0] = a1;
	this->values_[1] = a1;
	this->values_[2] = a1;
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::Vec3<hryky_template_arg>::Vec3(this_type const & rhs)
{
	::std::copy(&rhs.values_[0], &rhs.values_[3], &this->values_[0]);
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::Vec3<hryky_template_arg>::Vec3(this_type && rhs)
{
	::std::copy(&rhs.values_[0], &rhs.values_[3], &this->values_[0]);
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::Vec3<hryky_template_arg>::~Vec3()
{
}
/**
  @brief binary operator '=='.
 */
template <hryky_template_param>
bool hryky::rtiow::Vec3<hryky_template_arg>::operator==(
	this_type const & rhs) const
{
	return (
		(*this)[0] == rhs[0]
		&& (*this)[1] == rhs[1]
		&& (*this)[2] == rhs[2]);
}
/**
  @brief retrieves an element.
 */
template <hryky_template_param>
template <typename IndexT>
ValueT
hryky::rtiow::Vec3<hryky_template_arg>::operator[](IndexT index) const
{
	return this->values_[index];
}
/**
  @brief retrieves the reference to an element.
 */
template <hryky_template_param>
template <typename IndexT>
ValueT &
hryky::rtiow::Vec3<hryky_template_arg>::operator[](IndexT index)
{
	return this->values_[index];
}
/**
  @brief unary operator '+'.
 */
template <hryky_template_param>
hryky::rtiow::Vec3<hryky_template_arg> const & 
hryky::rtiow::Vec3<hryky_template_arg>::operator+() const
{
	return *this;
}
/**
  @brief unary operator '+' as mutable.
 */
template <hryky_template_param>
hryky::rtiow::Vec3<hryky_template_arg> & 
hryky::rtiow::Vec3<hryky_template_arg>::operator+()
{
	return *this;
}
/**
  @brief unary operator '-'.
 */
template <hryky_template_param>
hryky::rtiow::Vec3<hryky_template_arg> 
hryky::rtiow::Vec3<hryky_template_arg>::operator-() const
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
hryky::rtiow::Vec3<hryky_template_arg> & 
hryky::rtiow::Vec3<hryky_template_arg>::operator+=(
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
hryky::rtiow::Vec3<hryky_template_arg> & 
hryky::rtiow::Vec3<hryky_template_arg>::operator-=(
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
hryky::rtiow::Vec3<hryky_template_arg> & 
hryky::rtiow::Vec3<hryky_template_arg>::operator*=(
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
hryky::rtiow::Vec3<hryky_template_arg> &
hryky::rtiow::Vec3<hryky_template_arg>::operator*=(RhsT rhs)
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
hryky::rtiow::Vec3<hryky_template_arg> & 
hryky::rtiow::Vec3<hryky_template_arg>::operator/=(
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
hryky::rtiow::Vec3<hryky_template_arg> &
hryky::rtiow::Vec3<hryky_template_arg>::operator/=(RhsT rhs)
{
	return this->operator*=(value_type(1) / rhs);
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::Vec3<hryky_template_arg>::clear()
{
	hryky::clear(this->values_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::Vec3<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(values);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::rtiow::Vec3<hryky_template_arg>::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}
/**
  @brief retrieves the x element.
 */
template <hryky_template_param>
ValueT hryky::rtiow::Vec3<hryky_template_arg>::x() const
{
	return this->values_[0];
}
/**
  @brief retrieves the y element.
 */
template <hryky_template_param>
ValueT hryky::rtiow::Vec3<hryky_template_arg>::y() const
{
	return this->values_[1];
}
/**
  @brief retrieves the z element.
 */
template <hryky_template_param>
ValueT hryky::rtiow::Vec3<hryky_template_arg>::z() const
{
	return this->values_[2];
}
/**
  @brief retrieves the length of this vector.
 */
template <hryky_template_param>
ValueT
hryky::rtiow::Vec3<hryky_template_arg>::length() const
{
	return ::std::sqrt(this->slength());
}
/**
  @brief the square of length.
 */
template <hryky_template_param>
ValueT hryky::rtiow::Vec3<hryky_template_arg>::slength() const
{
	return (
		(*this)[0] * (*this)[0]
		+ (*this)[1] * (*this)[1]
		+ (*this)[2] * (*this)[2]);
}
/**
  @brief binary operator '+'.
 */
template <hryky_template_param>
hryky::rtiow::Vec3<hryky_template_arg> 
hryky::rtiow::Vec3<hryky_template_arg>::operator+(
	this_type const & rhs) const
{
	return this_type(
		(*this)[0] + rhs[0],
		(*this)[1] + rhs[1],
		(*this)[2] + rhs[2]);
}
/**
  @brief binary operator '+' with an arbitrary scalar.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::rtiow::Vec3<hryky_template_arg> 
hryky::rtiow::Vec3<hryky_template_arg>::operator+(
	RhsT rhs) const
{
	return this_type(
		(*this)[0] + rhs,
		(*this)[1] + rhs,
		(*this)[2] + rhs);
}
/**
  @brief binary operator '-'.
 */
template <hryky_template_param>
hryky::rtiow::Vec3<hryky_template_arg> 
hryky::rtiow::Vec3<hryky_template_arg>::operator-(
	this_type const & rhs) const
{
	return this_type(
		(*this)[0] - rhs[0],
		(*this)[1] - rhs[1],
		(*this)[2] - rhs[2]);
}
/**
  @brief binary operator '-' with an arbitrary scalar.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::rtiow::Vec3<hryky_template_arg> 
hryky::rtiow::Vec3<hryky_template_arg>::operator-(
	RhsT rhs) const
{
	return this_type(
		(*this)[0] - rhs,
		(*this)[1] - rhs,
		(*this)[2] - rhs);
}
/**
  @brief binary operator '*'.
 */
template <hryky_template_param>
hryky::rtiow::Vec3<hryky_template_arg> 
hryky::rtiow::Vec3<hryky_template_arg>::operator*(
	this_type const & rhs) const
{
	return this_type(
		(*this)[0] * rhs[0],
		(*this)[1] * rhs[1],
		(*this)[2] * rhs[2]);
}
/**
  @brief binary operator '*' with an arbitrary scalar.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::rtiow::Vec3<hryky_template_arg> 
hryky::rtiow::Vec3<hryky_template_arg>::operator*(
	RhsT rhs) const
{
	return this_type(
		(*this)[0] * rhs,
		(*this)[1] * rhs,
		(*this)[2] * rhs);
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
namespace rtiow
{
	/// prints values to a stream.
	template <hryky_template_param, typename StreamT>
	StreamT & operator<<(
		StreamT & lhs, Vec3<hryky_template_arg> const & rhs);

	/// multiplies each element by a scalar.
	template <hryky_template_param>
	Vec3<hryky_template_arg> operator*(
		typename Vec3<hryky_template_arg>::const_reference lhs,
		Vec3<hryky_template_arg> const & rhs);

	/// divides each element by a scalar.
	template <hryky_template_param>
	Vec3<hryky_template_arg> operator/(
		Vec3<hryky_template_arg> const & lhs,
		typename Vec3<hryky_template_arg>::const_reference rhs);

	/// normalizes a vector.
	template <hryky_template_param>
	Vec3<hryky_template_arg> normalize(
		Vec3<hryky_template_arg> const & src);

	/// calculates dot product.
	template <hryky_template_param>
	ValueT dot(
		Vec3<hryky_template_arg> const & lhs,
		Vec3<hryky_template_arg> const & rhs);

	/// calculates square root of each element.
	template <hryky_template_param>
	Vec3<hryky_template_arg> sqrt(
		Vec3<hryky_template_arg> const & src);

	/// calculates the reflected vector.
	template <typename InT, typename NormalT>
	InT reflect(InT const & in, NormalT const & normal);

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief prints values to a stream.
 */
template <hryky_template_param, typename StreamT>
StreamT &
hryky::rtiow::operator<<(
	StreamT & lhs,
	Vec3<hryky_template_arg> const & rhs)
{
	return lhs << rhs[0] << " " << rhs[1] << " " << rhs[2];
}
/**
  @brief multiplies each element by a scalar.
 */
template <hryky_template_param>
hryky::rtiow::Vec3<hryky_template_arg> hryky::rtiow::operator*(
	typename Vec3<hryky_template_arg>::const_reference lhs,
	Vec3<hryky_template_arg> const & rhs)
{
	return Vec3<hryky_template_arg>(
		lhs * rhs[0],
		lhs * rhs[1],
		lhs * rhs[2]);
}
/**
  @brief divides each element by a scalar.
 */
template <hryky_template_param>
hryky::rtiow::Vec3<hryky_template_arg>
hryky::rtiow::operator/(
	Vec3<hryky_template_arg> const & lhs,
	typename Vec3<hryky_template_arg>::const_reference rhs)
{
	return Vec3<hryky_template_arg>(
		lhs[0] / rhs,
		lhs[1] / rhs,
		lhs[2] / rhs);
}
/**
  @brief normalizes a vector.
 */
template <hryky_template_param>
hryky::rtiow::Vec3<hryky_template_arg>
hryky::rtiow::normalize(
	Vec3<hryky_template_arg> const & src)
{
	return src / src.length();
}
/**
  @brief calculates dot product.
 */
template <hryky_template_param>
ValueT hryky::rtiow::dot(
	Vec3<hryky_template_arg> const & lhs,
	Vec3<hryky_template_arg> const & rhs)
{
	return (
		lhs[0] * rhs[0]
		+ lhs[1] * rhs[1]
		+ lhs[2] * rhs[2]);
}
/**
  @brief calculates square root of each element.
 */
template <hryky_template_param>
hryky::rtiow::Vec3<hryky_template_arg> 
hryky::rtiow::sqrt(
	Vec3<hryky_template_arg> const & src)
{
	return Vec3<hryky_template_arg>(
		::std::sqrt(src[0]),
		::std::sqrt(src[1]),
		::std::sqrt(src[2]));
}
/**
  @brief calculates the reflected vector.
 */
template <typename InT, typename NormalT>
InT hryky::rtiow::reflect(InT const & in, NormalT const & normal)
{
	return in - 2.0f * dot(in, normal) * normal;
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // VEC3_H_20160628180738421
// end of file
