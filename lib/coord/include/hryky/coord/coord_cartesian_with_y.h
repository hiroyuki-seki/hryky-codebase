/**
  @file     coord_cartesian_with_y.h
  @brief    features cartesian coordinates having the Y coordinate.
  @author   HRYKY
  @version  $Id: coord_cartesian_with_y.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef COORD_CARTESIAN_WITH_Y_H_20131102131906221
#define COORD_CARTESIAN_WITH_Y_H_20131102131906221
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
	/// features cartesian coordinates having the Y coordinate.
	template <hryky_template_param>
	class WithY;

} // namespace cartesian
} // namespace coord
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief features cartesian coordinates having the Y coordinate.
 */
template <typename DerivedT, typename ValueT, size_t Index = 1>
class hryky::coord::cartesian::WithY
{
public :
	typedef typename AsParameter<ValueT>::type param_type;

	/// retrieves the Y coordinate.
	param_type y() const;

	/// assigns a value to the Y coordinate.
	void y(param_type src);

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
  @brief retrieves the Y coordinate.
 */
template <hryky_template_param>
typename hryky::coord::cartesian::WithY<hryky_template_arg>::param_type 
hryky::coord::cartesian::WithY<hryky_template_arg>::y() const
{
	return this->derived()[Index];
}
/**
  @brief assigns a value to the Y coordinate.
 */
template <hryky_template_param>
void hryky::coord::cartesian::WithY<hryky_template_arg>::y(param_type src)
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
hryky::coord::cartesian::WithY<hryky_template_arg>::derived() const
{
	return *static_cast<DerivedT const *>(this);
}
/**
  @brief retrieves the mutable instance as derived class.
 */
template <hryky_template_param>
DerivedT & 
hryky::coord::cartesian::WithY<hryky_template_arg>::derived()
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
#endif // COORD_CARTESIAN_WITH_Y_H_20131102131906221
// end of file
