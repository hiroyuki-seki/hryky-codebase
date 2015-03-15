/**
  @file     coord_cartesian_with_x.h
  @brief    features cartesian coordinates having the X coordinate.
  @author   HRYKY
  @version  $Id: coord_cartesian_with_x.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef COORD_CARTESIAN_WITH_X_H_20131102130729213
#define COORD_CARTESIAN_WITH_X_H_20131102130729213
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
	/// features cartesian coordinates having the X coordinate.
	template <hryky_template_param>
	class WithX;

} // namespace cartesian
} // namespace coord
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief features cartesian coordinates having the X coordinate.
 */
template <typename DerivedT, typename ValueT, size_t Index = 0>
class hryky::coord::cartesian::WithX
{
public :
	typedef typename AsParameter<ValueT>::type param_type;

	/// retrieves the X coordinate.
	param_type x() const;

	/// assigns a value to the X coordinate.
	void x(param_type src);

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
  @brief retrieves the X coordinate.
 */
template <hryky_template_param>
typename hryky::coord::cartesian::WithX<hryky_template_arg>::param_type 
hryky::coord::cartesian::WithX<hryky_template_arg>::x() const
{
	return this->derived()[Index];
}
/**
  @brief assigns a value to the X coordinate.
 */
template <hryky_template_param>
void hryky::coord::cartesian::WithX<hryky_template_arg>::x(param_type src)
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
hryky::coord::cartesian::WithX<hryky_template_arg>::derived() const
{
	return *static_cast<DerivedT const *>(this);
}
/**
  @brief retrieves the mutable instance as derived class.
 */
template <hryky_template_param>
DerivedT & 
hryky::coord::cartesian::WithX<hryky_template_arg>::derived()
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
#endif // COORD_CARTESIAN_WITH_X_H_20131102130729213
// end of file
