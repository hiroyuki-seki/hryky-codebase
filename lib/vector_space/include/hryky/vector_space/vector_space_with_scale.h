/**
  @file     vector_space_with_scale.h
  @brief    features with multiplication by a scalar value.
  @author   HRYKY
  @version  $Id: vector_space_with_scale.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef VECTOR_SPACE_WITH_SCALE_H_20131103221105591
#define VECTOR_SPACE_WITH_SCALE_H_20131103221105591
#include "hryky/type_traits/as_parameter.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ScalarT, typename DerivedT
#define hryky_template_arg \
	ScalarT, DerivedT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace vector_space
{
	/// features with multiplication by a scalar value.
	template <hryky_template_param>
	class WithScale;

} // namespace vector_space
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief features with multiplication by a scalar value.
 */
template <hryky_template_param>
class hryky::vector_space::WithScale
{
private :
	typedef typename AsParameter<ScalarT>::type scalar_param_type;

public :

	/// multiplies by a scalar value.
	DerivedT operator*(scalar_param_type scalar) const;

	/// assigns the result of scaling.
	DerivedT & operator*=(scalar_param_type scalar);

	/// divides by a scalar value.
	DerivedT operator/(scalar_param_type scalar) const;

	/// assigns the result of scaling with a reciprocal number.
	DerivedT & operator/=(scalar_param_type scalar);

private :
	
	/// retrieves the mutable instance as derived class.
	DerivedT & derived();

	/// retrieves the immutable instance as derived class.
	DerivedT const & derived() const;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace vector_space
{
} // namespace vector_space
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief multiplies by a scalar value.
 */
template <hryky_template_param>
DerivedT hryky::vector_space::WithScale<hryky_template_arg>::operator*(
	scalar_param_type scalar) const
{
	DerivedT ret(this->derived());
	return ret *= scalar;
}
/**
  @brief assigns the result of scaling.
 */
template <hryky_template_param>
DerivedT & hryky::vector_space::WithScale<hryky_template_arg>::operator*=(
	scalar_param_type scalar)
{
	this->derived().foreach([scalar](DerivedT::reference dest) {
		dest *= scalar;
	});
	return this->derived();
}
/**
  @brief divides by a scalar value.
 */
template <hryky_template_param>
DerivedT hryky::vector_space::WithScale<hryky_template_arg>::operator/(
	scalar_param_type scalar) const
{
	DerivedT ret(this->derived());
	return ret /= scalar;
}
/**
  @brief assigns the result of scaling.
 */
template <hryky_template_param>
DerivedT & hryky::vector_space::WithScale<hryky_template_arg>::operator/=(
	scalar_param_type scalar)
{
	return this->operator*(1 / scalar);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the mutable instance as derived class.
 */
template <hryky_template_param>
DerivedT &
hryky::vector_space::WithScale<hryky_template_arg>::derived()
{
	return *static_cast<DerivedT *>(this);
}
/**
  @brief retrieves the immutable instance as derived class.
 */
template <hryky_template_param>
DerivedT const &
hryky::vector_space::WithScale<hryky_template_arg>::derived() const
{
	return *static_cast<DerivedT const *>(this);
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace vector_space
{
	/// multiplies a vector by a scalar from left.
	template <hryky_template_param>
	DerivedT operator*(
		ScalarT const lhs, WithScale<hryky_template_arg> const & rhs);

} // namespace vector_space
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief multiplies a vector by a scalar from left.
 */
template <hryky_template_param>
DerivedT hryky::vector_space::operator*(
	ScalarT const lhs, WithScale<hryky_template_arg> const & rhs)
{
	return rhs * lhs;
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // VECTOR_SPACE_WITH_SCALE_H_20131103221105591
// end of file
