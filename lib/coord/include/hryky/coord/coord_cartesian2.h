/**
  @file     coord_cartesian2.h
  @brief    retains a 2D coordinates by Cartesian coordiante system.
  @author   HRYKY
  @version  $Id: coord_cartesian2.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef COORD_CARTESIAN2_H_20130504135126244
#define COORD_CARTESIAN2_H_20130504135126244
#include "hryky/coord/coord_cartesian_base.h"
#include "hryky/coord/coord_cartesian_with_x.h"
#include "hryky/coord/coord_cartesian_with_y.h"
#include "hryky/capacity_of.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
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
	/// retains the two-dimensional coordinate specified by Cartesian coordinate system.
	template < hryky_template_param >
	class Cartesian2;

} // namespace coord
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the two-dimensional coordinate specified by Cartesian coordinate system.
 */
template < hryky_template_param >
class hryky::coord::Cartesian2 :
	public cartesian::Base<ValueT, 2, Cartesian2<hryky_template_arg> >,
	public cartesian::WithX<Cartesian2<hryky_template_arg>, ValueT>,
	public cartesian::WithY<Cartesian2<hryky_template_arg>, ValueT>
{
public :
	typedef Cartesian2<hryky_template_arg>          this_type;
	typedef cartesian::Base<ValueT, 2, this_type>   base_type;

	/// default constructor
	Cartesian2();

	/// constructs with a scalar value.
	explicit Cartesian2(scalar_param_type scalar);

	/// constructor with elements
	Cartesian2(scalar_param_type x, scalar_param_type y);

	/// copy constructor
	Cartesian2(this_type const & rhs);

	/// copy constructor with move semantics.
	Cartesian2(this_type && rhs);

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// assigns all coordinates
	void assign(scalar_param_type x, scalar_param_type y);

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
hryky::coord::Cartesian2<hryky_template_arg>::Cartesian2()
	: base_type()
{
}
/**
  @brief constructs with a scalar value.
 */
template <hryky_template_param>
hryky::coord::Cartesian2<hryky_template_arg>::Cartesian2(
	scalar_param_type scalar)
	: base_type(scalar)
{
}
/**
  @brief constructor with elements.
 */
template <hryky_template_param>
hryky::coord::Cartesian2<hryky_template_arg>::Cartesian2(
	scalar_param_type x, scalar_param_type y)
	: base_type()
{
	this->x(x);
	this->y(y);
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::coord::Cartesian2<hryky_template_arg>::Cartesian2(
	this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief copy constructor with move semantics.
 */
template <hryky_template_param>
hryky::coord::Cartesian2<hryky_template_arg>::Cartesian2(this_type && rhs)
	: base_type(::std::move(rhs))
{
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & 
hryky::coord::Cartesian2<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->base_type::write_to(out);
}
/**
  @brief assigns all coordinates.
 */
template <hryky_template_param>
void hryky::coord::Cartesian2<hryky_template_arg>::assign(
	scalar_param_type x, scalar_param_type y)
{
	this->x(x);
	this->y(y);
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
//------------------------------------------------------------------------------
// restores warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // COORD_CARTESIAN2_H_20130504135126244
// end of file
