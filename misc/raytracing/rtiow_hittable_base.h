/**
  @file     rtiow_hittable_base.h
  @brief    The interface having hit() .
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_HITTABLE_BASE_H_20170116142641268
#define RTIOW_HITTABLE_BASE_H_20170116142641268
#include "./rtiow_randomizer.h"
#include "./rtiow_hit.h"
#include "./rtiow_ray_base.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename RayT, typename RandomizerT
#define hryky_template_arg \
	RayT, RandomizerT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
namespace hittable
{
	/// The interface having hit() .
	template <hryky_template_param>
	class Base;

} // namespace hittable
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The interface having hit() .
 */
template <
	typename RayT = hryky::rtiow::ray::Base<>
	, typename RandomizerT = hryky::rtiow::Randomizer<>
>
class hryky::rtiow::hittable::Base
{
public :

	typedef Base<hryky_template_arg> this_type;
	typedef Hit<> hit_type;
	typedef RayT ray_type;
	typedef RandomizerT randomizer_type;

	/// default constructor.
	Base();

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

	/// checks if a ray intersects with this object.
	hit_type hit(
		ray_type const & ray, randomizer_type & randomizer) const;

	/// checks if a ray intersects with this object with the default randomizer.
	hit_type hit(ray_type const & ray) const;

protected :

private :

	/// implements hit().
	virtual hit_type hit_impl(
		ray_type const & ray, randomizer_type & randomizer) const = 0;

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
template <typename RayT, typename RandomizerT>
hryky::rtiow::hittable::Base<RayT, RandomizerT>::Base()
{
}
/**
  @brief copy constructor.
 */
template <typename RayT, typename RandomizerT>
hryky::rtiow::hittable::Base<RayT, RandomizerT>::Base(this_type const & rhs)
{
}
/**
  @brief move constructor.
 */
template <typename RayT, typename RandomizerT>
hryky::rtiow::hittable::Base<RayT, RandomizerT>::Base(this_type && rhs)
{
}
/**
  @brief destructor.
 */
template <typename RayT, typename RandomizerT>
hryky::rtiow::hittable::Base<RayT, RandomizerT>::~Base()
{
}
/**
  @brief releases the internal resources.
 */
template <typename RayT, typename RandomizerT>
void hryky::rtiow::hittable::Base<RayT, RandomizerT>::clear()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <typename RayT, typename RandomizerT>
void hryky::rtiow::hittable::Base<RayT, RandomizerT>::swap(this_type & src)
{
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::hittable::Base<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}
/**
  @brief checks if a ray intersects with this object.
 */
template <hryky_template_param>
typename hryky::rtiow::hittable::Base<hryky_template_arg>::hit_type
hryky::rtiow::hittable::Base<hryky_template_arg>::hit(
	ray_type const & ray, randomizer_type & randomizer) const
{
	return this->hit_impl(ray, randomizer);
}
/**
  @brief checks if a ray intersects with this object with the default randomizer.
 */
template <hryky_template_param>
typename hryky::rtiow::hittable::Base<hryky_template_arg>::hit_type 
hryky::rtiow::hittable::Base<hryky_template_arg>::hit(
	ray_type const & ray) const
{
	randomizer_type randomizer;
	return this->hit_impl(ray, randomizer);
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
#endif // RTIOW_HITTABLE_BASE_H_20170116142641268
// end of file
