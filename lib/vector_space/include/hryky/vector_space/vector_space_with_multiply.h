/**
  @file     vector_space_with_multiply.h
  @brief    features with multiplication on each element.
  @author   HRYKY
  @version  $Id: vector_space_with_multiply.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef VECTOR_SPACE_WITH_MULTIPLY_H_20131103222724602
#define VECTOR_SPACE_WITH_MULTIPLY_H_20131103222724602
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename DerivedT
#define hryky_template_arg \
	DerivedT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace vector_space
{
	/// features with multiplication on each element.
	template <hryky_template_param>
	class WithMultiply;

} // namespace vector_space
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief features with multiplication on each element.
 */
template <hryky_template_param>
class hryky::vector_space::WithMultiply
{
public :

	/// multiplies each component.
	DerivedT operator*(DerivedT const & rhs) const;

	/// multiplies by an other vector.
	DerivedT & operator*=(DerivedT const & rhs);

	/// divides each component.
	DerivedT operator/(DerivedT const & rhs) const;

	/// divides by an other vector.
	DerivedT & operator/=(DerivedT const & rhs);

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
  @brief multiplies each component.
 */
template <hryky_template_param>
DerivedT hryky::vector_space::WithMultiply<hryky_template_arg>::operator*(
	DerivedT const & rhs) const
{
	DerivedT ret(this->derived());
	return ret *= rhs;
}
/**
  @brief multiplies by an other vector.
 */
template <hryky_template_param>
DerivedT & 
hryky::vector_space::WithMultiply<hryky_template_arg>::operator*=(
	DerivedT const & rhs)
{
	this->derived().foreach_at([&rhs](
		DerivedT::reference dest, DerivedT::size_type const index) {
		dest *= rhs[index];
	});
	return this->derived();
}
/**
  @brief divides each component.
 */
template <hryky_template_param>
DerivedT hryky::vector_space::WithMultiply<hryky_template_arg>::operator/(
	DerivedT const & rhs) const
{
	DerivedT ret(this->derived());
	return ret /= rhs;
}
/**
  @brief divides by an other vector.
 */
template <hryky_template_param>
DerivedT & 
hryky::vector_space::WithMultiply<hryky_template_arg>::operator/=(
	DerivedT const & rhs)
{
	this->derived().foreach_at([&rhs](
		DerivedT::reference dest, DerivedT::size_type const index) {
		dest /= rhs[index];
	});
	return this->derived();
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
hryky::vector_space::WithMultiply<hryky_template_arg>::derived()
{
	return *static_cast<DerivedT *>(this);
}
/**
  @brief retrieves the immutable instance as derived class.
 */
template <hryky_template_param>
DerivedT const &
hryky::vector_space::WithMultiply<hryky_template_arg>::derived() const
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
} // namespace vector_space
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // VECTOR_SPACE_WITH_MULTIPLY_H_20131103222724602
// end of file
