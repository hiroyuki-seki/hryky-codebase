/**
  @file     coord_cartesian3.h
  @brief    retains a 3D coordinates by Cartesian coordiante system.
  @author   HRYKY
  @version  $Id: coord_cartesian3.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef COORD_CARTESIAN3_H_20130504135915249
#define COORD_CARTESIAN3_H_20130504135915249
#include "hryky/coord/coord_cartesian_base.h"
#include "hryky/coord/coord_cartesian_with_x.h"
#include "hryky/coord/coord_cartesian_with_y.h"
#include "hryky/coord/coord_cartesian_with_z.h"
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
namespace coord
{
	/// retains a 3D coordinates by Cartesian coordiante system.
	template <typename ValueT>
	class Cartesian3;

} // namespace coord
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the three-dimensional coordinate specified by Cartesian coordinate system.
 */
template <hryky_template_param>
class hryky::coord::Cartesian3 :
	public cartesian::Base<ValueT, 3, Cartesian3<hryky_template_arg> >,
	public cartesian::WithX<Cartesian3<hryky_template_arg>, ValueT>,
	public cartesian::WithY<Cartesian3<hryky_template_arg>, ValueT>,
	public cartesian::WithZ<Cartesian3<hryky_template_arg>, ValueT>
{
public :

	typedef Cartesian3<hryky_template_arg>          this_type;
	typedef cartesian::Base<ValueT, 3, this_type>   base_type;

	/// default constructor.
	Cartesian3();

	/// copy constructor.
	Cartesian3(this_type const & rhs);

	/// constructs with a scalar value.
	explicit Cartesian3(scalar_param_type scalar);

	/// constructs with elements.
	Cartesian3(scalar_param_type x, scalar_param_type y, scalar_param_type z);

	/// move constructor.
	Cartesian3(this_type && rhs);

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// assigns all elements.
	void assign(scalar_param_type x, scalar_param_type y, scalar_param_type z);

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace coord
{
} // namespace coord
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::coord::Cartesian3<hryky_template_arg>::Cartesian3()
	: base_type()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::coord::Cartesian3<hryky_template_arg>::Cartesian3(
	this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::coord::Cartesian3<hryky_template_arg>::Cartesian3(this_type && rhs)
	: base_type(::std::move(rhs))
{
}
/**
  @brief constructs with a scalar value.
 */
template <hryky_template_param>
hryky::coord::Cartesian3<hryky_template_arg>::Cartesian3(
	scalar_param_type scalar)
	: base_type(scalar)
{
}
/**
  @brief constructs with elements.
 */
template <hryky_template_param>
hryky::coord::Cartesian3<hryky_template_arg>::Cartesian3(
	scalar_param_type x, scalar_param_type y, scalar_param_type z)
	: base_type()
{
	this->assign(x, y, z);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & 
hryky::coord::Cartesian3<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->base_type::write_to(out);
}
/**
  @brief assigns all elements.
 */
template <hryky_template_param>
void hryky::coord::Cartesian3<hryky_template_arg>::assign(
	scalar_param_type x, scalar_param_type y, scalar_param_type z)
{
	this->x(x);
	this->y(y);
	this->z(z);
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
namespace coord
{

} // namespace coord
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // COORD_CARTESIAN3_H_20130504135915249
// end of file
