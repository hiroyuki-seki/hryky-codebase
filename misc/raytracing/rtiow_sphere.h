/**
  @file     rtiow_sphere.h
  @brief    retains the information for a sphere.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_SPHERE_H_20160717111035132
#define RTIOW_SPHERE_H_20160717111035132
#include "./rtiow_vec3.h"
#include "./rtiow_lambertian.h"
#include "./rtiow_hit.h"
#include "./rtiow_randomizer.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename MaterialT, typename CenterT, typename RadiusT
#define hryky_template_arg \
	MaterialT, CenterT, RadiusT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
	/// retains the information for a sphere.
	template <hryky_template_param>
	class Sphere;

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information for a sphere.
 */
template <
	typename MaterialT = hryky::rtiow::Lambertian<>,
	typename CenterT = hryky::rtiow::Vec3<>,
	typename RadiusT = typename CenterT::value_type
>
class hryky::rtiow::Sphere
{
public :

	typedef Sphere<hryky_template_arg> this_type;
	typedef MaterialT material_type;
	typedef CenterT center_type;
	typedef RadiusT radius_type;

	/// default constructor.
	Sphere();

	/// instantiates with a center and a radius.
	Sphere(
		center_type const & center,
		radius_type const & radius);

	/// instantiates with parameters.
	Sphere(
		center_type const & center,
		radius_type const & radius,
		material_type const & material);

	/// copy constructor.
	Sphere(this_type const &);

	/// move constructor.
	Sphere(this_type &&);

	/// destructor.
	~Sphere();

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

	/// retrieves the center of this sphere.
	center_type const & center() const;

	/// retrieves the radius of this sphere.
	radius_type const & radius() const;

	/// retrieves the matrial of this sphere.
	material_type const & material() const;

	/// checks if a ray intersects with this sphere.
	template <typename RayT, typename RandomizerT>
	Hit<> hit(RayT const & ray, RandomizerT & randomizer) const;

	template <typename RayT>
	Hit<> hit(RayT const & ray) const
	{
		Randomizer<> randomizer;
		return this->hit(ray, randomizer);
	}

protected :

private :

	material_type material_;
	center_type center_;
	radius_type radius_;

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
hryky::rtiow::Sphere<hryky_template_arg>::Sphere()
	: center_()
	  , radius_()
	  , material_()
{
}
/**
  @brief instantiates with a center and a radius.
 */
template <hryky_template_param>
hryky::rtiow::Sphere<hryky_template_arg>::Sphere(
	center_type const & center, radius_type const & radius)
	: center_(center)
	  , radius_(radius)
	  , material_()
{
}
/**
  @brief instantiates with parameters.
 */
template <hryky_template_param>
hryky::rtiow::Sphere<hryky_template_arg>::Sphere(
	center_type const & center,
	radius_type const & radius,
	material_type const & material)
	: center_(center)
	  , radius_(radius)
	  , material_(material)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::Sphere<hryky_template_arg>::Sphere(this_type const & rhs)
	: hryky_copy_member(center)
	  , hryky_copy_member(radius)
	  , hryky_copy_member(material)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::Sphere<hryky_template_arg>::Sphere(this_type && rhs)
	: hryky_move_member(center)
	  , hryky_move_member(radius)
	  , hryky_move_member(material)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::Sphere<hryky_template_arg>::~Sphere()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::Sphere<hryky_template_arg>::clear()
{
	hryky::clear(this->material_);
	hryky::clear(this->radius_);
	hryky::clear(this->center_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::Sphere<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(center);
	hryky_swap_member(radius);
	hryky_swap_member(material);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::Sphere<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}
/**
  @brief retrieves the center of this sphere.
 */
template <hryky_template_param>
typename hryky::rtiow::Sphere<hryky_template_arg>::center_type const & 
hryky::rtiow::Sphere<hryky_template_arg>::center() const
{
	return this->center_;
}
/**
  @brief retrieves the radius of this sphere.
 */
template <hryky_template_param>
typename hryky::rtiow::Sphere<hryky_template_arg>::radius_type const & 
hryky::rtiow::Sphere<hryky_template_arg>::radius() const
{
	return this->radius_;
}
/**
  @brief retrieves the matrial of this sphere.
 */
template <hryky_template_param>
typename hryky::rtiow::Sphere<hryky_template_arg>::material_type const & 
hryky::rtiow::Sphere<hryky_template_arg>::material() const
{
	return this->material_;
}
/**
  @brief checks if a ray intersects with this sphere.
 */
template <hryky_template_param>
template <typename RayT, typename RandomizerT>
hryky::rtiow::Hit<>
hryky::rtiow::Sphere<hryky_template_arg>::hit(
	RayT const & ray, RandomizerT & randomizer) const
{
	auto const oc = ray.origin() - this->center();
	auto const a = dot(ray.direction(), ray.direction());
	auto const b = dot(oc, ray.direction());
	auto const c = dot(oc, oc) - this->radius() * this->radius();
	auto const discriminant = b * b - a * c;
	if (decltype(discriminant)() >= discriminant) {
		return Hit<>();
	}

	auto const closer = (-b - ::std::sqrt(discriminant)) / a;
	if (ray.verify(closer)) {
		auto const point = ray.point(closer);
		auto const normal = (point - this->center()) / this->radius();
		return Hit<>(
			this->material_.scatter(
				ray.direction(), point, normal, randomizer),
			point,
			normal,
			closer);
	}

	auto const further = (-b + ::std::sqrt(discriminant)) / a;
	if (ray.verify(further)) {
		auto const point = ray.point(further);
		auto const normal = (point - this->center()) / this->radius();
		return Hit<>(
			this->material_.scatter(
				ray.direction(), point, normal, randomizer),
			point,
			normal,
			further);
	}

	return Hit<>();
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
#endif // RTIOW_SPHERE_H_20160717111035132
// end of file
