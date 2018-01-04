/**
  @file     rtiow_hittable_container.h
  @brief    checks if a ray intersects with any hitable objects in container.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_HITTABLE_CONTAINER_H_20170116152729310
#define RTIOW_HITTABLE_CONTAINER_H_20170116152729310
#include <vector>
#include <memory>
#include "hryky/tuple.h"
#include "hryky/is_null.h"
#include "./rtiow_ray_segment.h"
#include "./rtiow_hittable_base.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename RayT, typename RandomizerT, typename ContainerT
#define hryky_template_arg \
	RayT, RandomizerT, ContainerT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
namespace hittable
{
	/// checks if a ray intersects with any hitable objects in container.
	template <hryky_template_param>
	class Container;

} // namespace hittable
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief checks if a ray intersects with any hitable objects in container.
 */
template <
	typename RayT = hryky::rtiow::ray::Base<>
	, typename RandomizerT = hryky::rtiow::Randomizer<>
	, typename ContainerT = ::std::vector<
		::std::shared_ptr<hryky::rtiow::hittable::Base<> const> >
>
class hryky::rtiow::hittable::Container
	: public Base<RayT, RandomizerT>
{
public :

	typedef Base<RayT, RandomizerT> base_type;
	typedef typename base_type::ray_type ray_type;
	typedef typename base_type::randomizer_type randomizer_type;
	typedef typename base_type::hit_type hit_type;
	typedef Container<hryky_template_arg> this_type;
	typedef ContainerT container_type;

	/// default constructor.
	Container();

	/// instantiates with a container.
	Container(container_type const & container);

	/// copy constructor.
	Container(this_type const &);

	/// move constructor.
	Container(this_type &&);

	/// destructor.
	~Container();

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

	/// retrieves the container.
	ContainerT & get();

protected :

private :

	/// checks if a ray intersects with any hitable objects in container.
	virtual hit_type hit_impl(
		ray_type const & ray, randomizer_type & randomizer) const;

	/// checks if a ray intersects with any hitable objects in container.
	template <typename InputItr>
	hit_type hit_range(
		ray_type const & ray,
		randomizer_type & randomizer,
		InputItr first,
		InputItr last) const;

	container_type container_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
namespace hittable
{
} // namespace hittable
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::rtiow::hittable::Container<hryky_template_arg>::Container()
	: container_()
{
}

/**
  @brief instantiates with a container.
 */
template <hryky_template_param>
hryky::rtiow::hittable::Container<hryky_template_arg>::Container(
	container_type const & container)
	: container_(container)
{
}

/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::hittable::Container<hryky_template_arg>::Container(
	this_type const & rhs)
	: hryky_copy_member(container)
{
}

/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::hittable::Container<hryky_template_arg>::Container(
	this_type && rhs)
	: hryky_move_member(container)
{
}

/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::hittable::Container<hryky_template_arg>::~Container()
{
}

/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::hittable::Container<hryky_template_arg>::clear()
{
	hryky::clear(this->container_);
}

/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::hittable::Container<hryky_template_arg>::swap(
	this_type & src)
{
	hryky_swap_member(container);
}

/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::rtiow::hittable::Container<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}

/**
  @brief retrieves the container.
 */
template <hryky_template_param>
ContainerT & hryky::rtiow::hittable::Container<hryky_template_arg>::get()
{
	return this->container_;
}

//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief checks if a ray intersects with any hitable objects in container.
 */
template <hryky_template_param>
typename hryky::rtiow::hittable::Container<hryky_template_arg>::hit_type
hryky::rtiow::hittable::Container<hryky_template_arg>::hit_impl(
	ray_type const & ray, randomizer_type & randomizer) const
{
	return this->hit_range(
		ray,
		randomizer,
		this->container_.begin(),
		this->container_.end());
}

/**
  @brief checks if a ray intersects with any hitable objects in container.
 */
template <hryky_template_param>
template <typename InputItr>
typename hryky::rtiow::hittable::Container<hryky_template_arg>::hit_type
hryky::rtiow::hittable::Container<hryky_template_arg>::hit_range(
	ray_type const & ray,
	randomizer_type & randomizer,
	InputItr first,
	InputItr last) const
{
	InputItr itr = first;
	for (; last != itr; ++itr) {
		auto const hit = (*itr)->hit(ray, randomizer);
		if (hryky_is_null(hit)) {
			continue;
		}

		auto const next = this->hit_range(
			ray::Segment<typename ray_type::coord_type>(
				ray.origin(),
				hit.pos() - ray.origin()),
			randomizer,
			itr + 1u,
			last);
	
		return hryky_is_null(next) ? hit : next;
	}

	return hit_type();
}

//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
namespace hittable
{
} // namespace hittable
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
#endif // RTIOW_HITTABLE_CONTAINER_H_20170116152729310
// end of file
