/**
  @file     coord_cartesian_with_w.h
  @brief    features cartesian coordinates having the W coordinate.
  @author   HRYKY
  @version  $Id: coord_cartesian_with_w.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef COORD_CARTESIAN_WITH_W_H_20131102144656282
#define COORD_CARTESIAN_WITH_W_H_20131102144656282
#include "hryky/type_traits/as_parameter.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename DerivedT, typename ValueT, size_t Index
#define hryky_template_arg \
	DerivedT, ValueT, Index
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace coord
{
namespace cartesian
{
	/// features cartesian coordinates having the W coordinate.
	template <hryky_template_param>
	class WithW;

} // namespace cartesian
} // namespace coord
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief features cartesian coordinates having the W coordinate.
 */
template <typename DerivedT, typename ValueT, size_t Index = 3>
class hryky::coord::cartesian::WithW
{
public :
	typedef typename AsParameter<ValueT>::type param_type;

	/// retrieves the W coordinate.
	param_type w() const;

	/// assigns a value to the W coordinate.
	void w(param_type src);

private :
	
	/// retrieves the immutable instance as derived class.
	DerivedT const & derived() const;

	/// retrieves the mutable instance as derived class.
	DerivedT & derived();

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace coord
{
namespace cartesian
{
} // namespace cartesian
} // namespace coord
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the W coordinate.
 */
template <hryky_template_param>
typename hryky::coord::cartesian::WithW<hryky_template_arg>::param_type 
hryky::coord::cartesian::WithW<hryky_template_arg>::w() const
{
	return this->derived()[Index];
}
/**
  @brief assigns a value to the W coordinate.
 */
template <hryky_template_param>
void hryky::coord::cartesian::WithW<hryky_template_arg>::w(param_type src)
{
	this->derived()[Index] = src;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the immutable instance as derived class.
 */
template <hryky_template_param>
DerivedT const & 
hryky::coord::cartesian::WithW<hryky_template_arg>::derived() const
{
	return *static_cast<DerivedT const *>(this);
}
/**
  @brief retrieves the mutable instance as derived class.
 */
template <hryky_template_param>
DerivedT & 
hryky::coord::cartesian::WithW<hryky_template_arg>::derived()
{
	return *static_cast<DerivedT *>(this);
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace coord
{
namespace cartesian
{
} // namespace cartesian
} // namespace coord
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // COORD_CARTESIAN_WITH_W_H_20131102144656282
// end of file
