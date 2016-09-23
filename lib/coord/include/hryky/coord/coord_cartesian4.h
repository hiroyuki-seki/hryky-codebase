/**
  @file     coord_cartesian4.h
  @brief    retains a 4D coordinates by Certesian coordinate system.
  @author   HRYKY
  @version  $Id: coord_cartesian4.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef COORD_CARTESIAN4_H_20131102175949416
#define COORD_CARTESIAN4_H_20131102175949416
#include "hryky/coord/coord_cartesian_base.h"
#include "hryky/coord/coord_cartesian_with_x.h"
#include "hryky/coord/coord_cartesian_with_y.h"
#include "hryky/coord/coord_cartesian_with_z.h"
#include "hryky/coord/coord_cartesian_with_w.h"
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
	/// retains a 4D coordinates by Certesian coordinate system.
	template <hryky_template_param>
	class Cartesian4;

} // namespace coord
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a 4D coordinates by Certesian coordinate system.
 */
template <typename ValueT>
class hryky::coord::Cartesian4 :
	public cartesian::Base<ValueT, 4, Cartesian4<hryky_template_arg> >,
	public cartesian::WithX<Cartesian4<hryky_template_arg>, ValueT>,
	public cartesian::WithY<Cartesian4<hryky_template_arg>, ValueT>,
	public cartesian::WithZ<Cartesian4<hryky_template_arg>, ValueT>,
	public cartesian::WithW<Cartesian4<hryky_template_arg>, ValueT>
{
public :

	typedef Cartesian4<hryky_template_arg>          this_type;
	typedef cartesian::Base<ValueT, 4, this_type>   base_type;

	/// default constructor.
	Cartesian4();

	/// copy constructor.
	Cartesian4(this_type const & rhs);

	/// move constructor.
	Cartesian4(this_type && rhs);

	/// constructs with a scalar value.
	explicit Cartesian4(scalar_param_type scalar);

	/// constructs with all elements.
	Cartesian4(
		scalar_param_type x,
		scalar_param_type y,
		scalar_param_type z,
		scalar_param_type w);

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// assigns all elements.
	void assign(
		scalar_param_type x,
		scalar_param_type y,
		scalar_param_type z,
		scalar_param_type w);

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

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
hryky::coord::Cartesian4<hryky_template_arg>::Cartesian4()
	: base_type()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::coord::Cartesian4<hryky_template_arg>::Cartesian4(
	this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::coord::Cartesian4<hryky_template_arg>::Cartesian4(this_type && rhs)
	: base_type(::std::move(rhs))
{
}
/**
  @brief constructs with a scalar value.
 */
template <hryky_template_param>
hryky::coord::Cartesian4<hryky_template_arg>::Cartesian4(
	scalar_param_type scalar)
	: base_type(scalar)
{
}
/**
  @brief constructs with all elements.
 */
template <hryky_template_param>
hryky::coord::Cartesian4<hryky_template_arg>::Cartesian4(
	scalar_param_type x,
	scalar_param_type y,
	scalar_param_type z,
	scalar_param_type w)
	: base_type()
{
	this->assign(x, y, z, w);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::coord::Cartesian4<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->base_type::write_to(out);
}
/**
  @brief assigns all elements.
 */
template <hryky_template_param>
void hryky::coord::Cartesian4<hryky_template_arg>::assign(
	scalar_param_type x,
	scalar_param_type y,
	scalar_param_type z,
	scalar_param_type w)
{
	this->x(x);
	this->y(y);
	this->z(z);
	this->w(w);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::coord::Cartesian4<hryky_template_arg>::swap(this_type & src)
{
	this->base_type::swap(src);
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
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // COORD_CARTESIAN4_H_20131102175949416
// end of file
