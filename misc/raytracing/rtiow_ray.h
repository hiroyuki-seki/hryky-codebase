/**
  @file     rtiow_ray.h
  @brief    retains a half line.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_RAY_H_20160703132553226
#define RTIOW_RAY_H_20160703132553226
#include "./rtiow_vec3.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename VectorT
#define hryky_template_arg \
	VectorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
	/// retains a half line.
	template <hryky_template_param>
	class Ray;

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a half line.
 */
template <
	typename VectorT = hryky::rtiow::Vec3<>
>
class hryky::rtiow::Ray
{
public :

	typedef Ray<hryky_template_arg> this_type;
	typedef VectorT vector_type;

	/// default constructor.
	Ray();

	/// instantiates with an origin and a direction.
	Ray(vector_type const & origin, vector_type const & direction);

	/// copy constructor.
	Ray(this_type const &);

	/// move constructor.
	Ray(this_type &&);

	/// destructor.
	~Ray();

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

	/// retrieves the origin of this ray.
	vector_type const & origin() const;

	/// retrieves the direction of this ray.
	vector_type const & direction() const;

	/// creates a position.
	template <typename RateT>
	vector_type point(RateT const & rate) const;

	/// confirms whether an rate is valid.
	template <typename RateT>
	bool verify(RateT const & rate) const;

protected :

private :

	vector_type origin_;
	vector_type direction_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::rtiow::Ray<hryky_template_arg>::Ray()
	: origin_()
	  , direction_()
{
}

/**
  @brief instantiates with an origin and a direction.
 */
template <hryky_template_param>
hryky::rtiow::Ray<hryky_template_arg>::Ray(
	vector_type const & origin, vector_type const & direction)
	: origin_(origin)
	  , direction_(direction)
{
}

/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::Ray<hryky_template_arg>::Ray(this_type const & rhs)
	: hryky_copy_member(origin)
	  , hryky_copy_member(direction)
{
}

/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::Ray<hryky_template_arg>::Ray(this_type && rhs)
	: hryky_move_member(origin)
	  , hryky_move_member(direction)
{
}

/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::Ray<hryky_template_arg>::~Ray()
{
}

/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::Ray<hryky_template_arg>::clear()
{
	hryky::clear(this->direction_);
	hryky::clear(this->origin_);
}

/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::Ray<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(origin);
	hryky_swap_member(direction);
}

/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::Ray<hryky_template_arg>::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}

/**
  @brief retrieves the origin of this ray.
 */
template <hryky_template_param>
typename hryky::rtiow::Ray<hryky_template_arg>::vector_type const &
hryky::rtiow::Ray<hryky_template_arg>::origin() const
{
	return this->origin_;
}

/**
  @brief retrieves the direction of this ray.
 */
template <hryky_template_param>
typename hryky::rtiow::Ray<hryky_template_arg>::vector_type const &
hryky::rtiow::Ray<hryky_template_arg>::direction() const
{
	return this->direction_;
}

/**
  @brief creates a position.
 */
template <hryky_template_param>
template <typename RateT>
typename hryky::rtiow::Ray<hryky_template_arg>::vector_type
hryky::rtiow::Ray<hryky_template_arg>::point(
	RateT const & rate) const
{
	return this->origin_ + rate * this->direction_;
}

/**
  @brief confirms whether an rate is valid.
 */
template <hryky_template_param>
template <typename RateT>
bool hryky::rtiow::Ray<hryky_template_arg>::verify(RateT const & rate) const
{
	return 0.001f < rate;
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
namespace rtiow
{
	/// creates a ray.
	template <hryky_template_param>
	Ray<hryky_template_arg> ray(
		VectorT const & origin, VectorT const & direction);

	/// prints values to a stream.
	template <typename StreamT, hryky_template_param>
	StreamT & operator<<(
		StreamT & lhs, Ray<hryky_template_arg> const & rhs);

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a ray.
 */
template <hryky_template_param>
hryky::rtiow::Ray<hryky_template_arg> hryky::rtiow::ray(
	VectorT const & origin, VectorT const & direction)
{
	return Ray<hryky_template_arg>(origin, direction);
}

/**
  @brief prints values to a stream.
 */
template <typename StreamT, hryky_template_param>
StreamT & hryky::rtiow::operator<<(
	StreamT & lhs, Ray<hryky_template_arg> const & rhs)
{
	return (
		lhs
		<< "{origin:[" << rhs.origin() << "]"
		<< ",direction:[" << rhs.direction() << "]"
		<< "}");
}

//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RTIOW_RAY_H_20160703132553226
// end of file
