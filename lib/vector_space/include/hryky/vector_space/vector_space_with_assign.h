/**
  @file     vector_space_with_assign.h
  @brief    features to assign a scalar value to each element.
  @author   HRYKY
  @version  $Id: vector_space_with_assign.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef VECTOR_SPACE_WITH_ASSIGN_H_20131103224730616
#define VECTOR_SPACE_WITH_ASSIGN_H_20131103224730616
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
	/// features to assign a scalar value to each element.
	template <hryky_template_param>
	class WithAssign;

} // namespace vector_space
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief features to assign a scalar value to each element.
 */
template <typename ScalarT, typename DerivedT>
class hryky::vector_space::WithAssign
{
private :
	typedef typename AsParameter<ScalarT>::type scalar_param_type;
	
public :

	/// assigns a scalar value to all elements.
	void assign(scalar_param_type scalar);

	/// assigns a scalar value by assignment operator.
	DerivedT & operator=(scalar_param_type scalar);

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
  @brief assigns a scalar value to all elements.
 */
template <hryky_template_param>
void hryky::vector_space::WithAssign<hryky_template_arg>::assign(
	scalar_param_type scalar)
{
	this->derived().foreach([scalar](DerivedT::reference src) {
		src = scalar;
	});
}
/**
  @brief assigns a scalar value by assignment operator.
 */
template <hryky_template_param>
DerivedT & hryky::vector_space::WithAssign<hryky_template_arg>::operator=(
	scalar_param_type scalar)
{
	this->assign(scalar);
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
hryky::vector_space::WithAssign<hryky_template_arg>::derived()
{
	return *static_cast<DerivedT *>(this);
}
/**
  @brief retrieves the immutable instance as derived class.
 */
template <hryky_template_param>
DerivedT const &
hryky::vector_space::WithAssign<hryky_template_arg>::derived() const
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
#endif // VECTOR_SPACE_WITH_ASSIGN_H_20131103224730616
// end of file
