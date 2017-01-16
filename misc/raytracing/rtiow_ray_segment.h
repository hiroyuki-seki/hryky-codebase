/**
  @file     rtiow_ray_segment.h
  @brief    retains a segment.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_RAY_SEGMENT_H_20170116151131299
#define RTIOW_RAY_SEGMENT_H_20170116151131299
#include "./rtiow_vec3.h"
#include "./rtiow_ray_base.h"
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
	/// retains a segment.
	template <hryky_template_param>
	class Segment;

} // namespace ray
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a segment.
 */
template <typename CoordT = hryky::rtiow::Vec3<> >
class hryky::rtiow::ray::Segment
	: public Base<CoordT>
{
public :

	typedef Base<CoordT> base_type;
	typedef Segment<hryky_template_arg> this_type;
	typedef typename base_type::coord_type coord_type;
	typedef typename base_type::rate_type rate_type;

	/// default constructor.
	Segment();

	/// constructor.
	Segment(coord_type const & origin, coord_type const & direction);

	/// copy constructor.
	Segment(this_type const &);

	/// move constructor.
	Segment(this_type &&);

	/// destructor.
	~Segment();

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

	/// confirms whether an rate is valid.
	template <typename RateT>
	bool verify(RateT const & rate) const;

protected :

private :

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
hryky::rtiow::ray::Segment<hryky_template_arg>::Segment()
	: base_type()
{
}
/**
  @brief constructor.
 */
template <hryky_template_param>
hryky::rtiow::ray::Segment<hryky_template_arg>::Segment(
	coord_type const & origin, coord_type const & direction)
	: base_type(origin, direction)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::ray::Segment<hryky_template_arg>::Segment(this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::ray::Segment<hryky_template_arg>::Segment(this_type && rhs)
	: base_type(::std::move(rhs))
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::ray::Segment<hryky_template_arg>::~Segment()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::ray::Segment<hryky_template_arg>::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::ray::Segment<hryky_template_arg>::swap(this_type & src)
{
	this->base_type::swap(src);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::ray::Segment<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief confirms whether an rate is valid.
 */
template <hryky_template_param>
bool hryky::rtiow::ray::Segment<hryky_template_arg>::verify_impl(
	rate_type const rate) const
{
	return 0.001f < rate && 1.0f > rate;
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
#endif // RTIOW_RAY_SEGMENT_H_20170116151131299
// end of file
