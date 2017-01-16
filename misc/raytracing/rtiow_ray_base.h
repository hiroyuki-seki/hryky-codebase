/**
  @file     rtiow_ray_base.h
  @brief    abstracts the features of a ray.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_RAY_BASE_H_20170116145046285
#define RTIOW_RAY_BASE_H_20170116145046285
#include "./rtiow_vec3.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename CoordT
#define hryky_template_arg \
	CoordT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
namespace ray
{
	/// abstracts the features of a ray.
	template <hryky_template_param>
	class Base;

} // namespace ray
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief abstracts the features of a ray.
 */
template <
	typename CoordT = hryky::rtiow::Vec3<>
>
class hryky::rtiow::ray::Base
{
public :

	typedef Base<hryky_template_arg> this_type;
	typedef CoordT coord_type;
	typedef CoordT::value_type rate_type;

	/// default constructor.
	Base();

	/// instantiates with the origin and the direction.
	Base(coord_type const & origin, coord_type const & direction);

	/// copy constructor.
	Base(this_type const &);

	/// move constructor.
	Base(this_type &&);

	/// destructor.
	~Base();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// confirms whether the rate is valid on this ray.
	bool verify(rate_type const rate) const;

protected :

private :

	/// implements verify().
	virtual bool verify_impl(rate_type const rate) const;

	coord_type origin_;
	coord_type direction_;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
namespace ray
{
} // namespace ray
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::rtiow::ray::Base<hryky_template_arg>::Base()
	: origin_()
	  , direction_()
{
}
/**
  @brief instantiates with the origin and the direction.
 */
template <hryky_template_param>
hryky::rtiow::ray::Base<hryky_template_arg>::Base(
	coord_type const & origin, coord_type const & direction)
	: origin_(origin)
	  , direction_(direction)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::ray::Base<hryky_template_arg>::Base(this_type const & rhs)
	: hryky_copy_member(origin)
	  , hryky_copy_member(direction)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::ray::Base<hryky_template_arg>::Base(this_type && rhs)
	: hryky_move_member(origin)
	  , hryky_move_member(direction)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::ray::Base<hryky_template_arg>::~Base()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::ray::Base<hryky_template_arg>::clear()
{
	hryky::clear(this->direction_);
	hryky::clear(this->origin_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::ray::Base<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(origin);
	hryky_swap_member(direction);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::ray::Base<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}
/**
  @brief retrieves the origin of this ray.
 */
template <hryky_template_param>
typename hryky::rtiow::ray::Base<hryky_template_arg>::coord_type const &
hryky::rtiow::ray::Base<hryky_template_arg>::origin() const
{
	return this->origin_;
}
/**
  @brief retrieves the direction of this ray.
 */
template <hryky_template_param>
typename hryky::rtiow::ray::Base<hryky_template_arg>::coord_type const &
hryky::rtiow::ray::Base<hryky_template_arg>::direction() const
{
	return this->direction_;
}
/**
  @brief creates a position.
 */
template <hryky_template_param>
template <typename RateT>
typename hryky::rtiow::ray::Base<hryky_template_arg>::coord_type
hryky::rtiow::ray::Base<hryky_template_arg>::point(
	RateT const & rate) const
{
	return this->origin_ + rate * this->direction_;
}
/**
  @brief confirms whether the rate is valid on this ray.
 */
template <hryky_template_param>
bool hryky::rtiow::ray::Base<hryky_template_arg>::verify(
	rate_type const rate) const
{
	return this->verify_impl(rate);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief implements verify().
 */
template <hryky_template_param>
bool hryky::rtiow::ray::Base<hryky_template_arg>::verify_impl(
	rate_type const rate) const
{
	return false;
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
namespace ray
{
} // namespace ray
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RTIOW_RAY_BASE_H_20170116145046285
// end of file
