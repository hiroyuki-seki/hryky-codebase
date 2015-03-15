/**
  @file     vector_space_axiom.h
  @brief    features the axiom in a vector space.
  @author   HRYKY
  @version  $Id: vector_space_axiom.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef VECTOR_SPACE_AXIOM_H_20131031152152306
#define VECTOR_SPACE_AXIOM_H_20131031152152306
#include "hryky/vector_space/vector_space_with_scale.h"
#include "hryky/vector_space/vector_space_with_add.h"
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
	/// features the axiom in a vector space.
	template <hryky_template_param>
	class Axiom;

} // namespace vector_space
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief features the axiom in a vector space.
 */
template <hryky_template_param>
class hryky::vector_space::Axiom :
	public WithScale<ScalarT, DerivedT>,
	public WithAdd<DerivedT>
{
public :

protected :

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
hryky::vector_space::Axiom<hryky_template_arg>::derived()
{
	return *static_cast<DerivedT *>(this);
}
/**
  @brief retrieves the immutable instance as derived class.
 */
template <hryky_template_param>
DerivedT const &
hryky::vector_space::Axiom<hryky_template_arg>::derived() const
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
#endif // VECTOR_SPACE_AXIOM_H_20131031152152306
// end of file
