/**
  @file     rtiow_material_dielectric.h
  @brief    retains information of a dielectric material.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_MATERIAL_DIELECTRIC_H_20170116162354349
#define RTIOW_MATERIAL_DIELECTRIC_H_20170116162354349
#include "./rtiow_vec3.h"
#include "./rtiow_scatter.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename AlbedoT, \
	typename ScatterT, \
	typename RandomizerT, \
	typename RefractionT
#define hryky_template_arg \
	AlbedoT, ScatterT, RandomizerT, RefractionT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
	/// retains information of a dielectric material.
	template <hryky_template_param>
	class Dielectric;

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains information of a dielectric material.
 */
template <
	typename AlbedoT = hryky::rtiow::Vec3<>
	, typename ScatterT = hryky::rtiow::Scatter<>
	, typename RandomizerT = hryky::rtiow::Randomizer<>
	, typename RefractionT = float
>
class hryky::rtiow::material::Dielectric
	: public Base<AlbedoT, ScatterT, RandomizerT>
{
public :

	typedef Base<AlbedoT, ScatterT, RandomizerT> base_type;
	typedef typename base_type::scatter_type scatter_type;
	typedef typename base_type::albedo_type albedo_type;
	typedef typename base_type::randomizer_type randomizer_type;
	typedef typename base_type::ray_type ray_type;
	typedef typename base_type::coord_type coord_type;
	typedef Dielectric<hryky_template_arg> this_type;
	typedef RefractionT refraction_type;

	/// default constructor.
	Dielectric();

	/// instantiates with parameters.
	Dielectric(
		albedo_type const & albedo,
		refraction_type const refraction);

	/// instantiates with parameters.
	Dielectric(refraction_type const refraction);

	/// copy constructor.
	Dielectric(this_type const &);

	/// move constructor.
	Dielectric(this_type &&);

	/// destructor.
	~Dielectric();

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

protected :

private :

	/// calculates the scattered ray.
	virtual scatter_type reflect_impl(
		coord_type const & in,
		coord_type const & pos,
		coord_type const & normal,
		randomizer_type & randomizer) const;

	refraction_type refraction_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
namespace material
{
} // namespace material
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::rtiow::material::Dielectric<hryky_template_arg>::Dielectric()
	: base_type(albedo_type(1.0f, 1.0f, 1.0f))
	  , refraction_(1.0f)
{
}
/**
  @brief instantiates with parameters.
 */
template <hryky_template_param>
hryky::rtiow::material::Dielectric<hryky_template_arg>::Dielectric(
	refraction_type const refraction)
	: base_type(albedo_type(1.0f, 1.0f, 1.0f))
	  , refraction_(1.0f)
{
}
/**
  @brief instantiates with parameters.
 */
template <hryky_template_param>
hryky::rtiow::material::Dielectric<hryky_template_arg>::Dielectric(
	albedo_type const & albedo, refraction_type const refraction)
	: base_type(albedo)
	  , refraction_(refraction)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::material::Dielectric<hryky_template_arg>::Dielectric(this_type const & rhs)
	: base_type(rhs)
	  , hryky_copy_member(refraction)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::material::Dielectric<hryky_template_arg>::Dielectric(this_type && rhs)
	: base_type(::std::move(rhs))
	  , hryky_move_member(refraction)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::material::Dielectric<hryky_template_arg>::~Dielectric()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::material::Dielectric<hryky_template_arg>::clear()
{
	hryky::clear(this->refraction_);
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::material::Dielectric<hryky_template_arg>::swap(this_type & src)
{
	this->base_type::swap(src);
	hryky_swap_member(refraction);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::material::Dielectric<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}
/**
  @brief calculates the scattered ray.
 */
template <hryky_template_param>
hryky::rtiow::material::Dielectric<hryky_template_arg>::scatter_type
hryky::rtiow::material::Dielectric<hryky_template_arg>::reflect_impl(
	coord_type const & in,
	coord_type const & pos,
	coord_type const & normal,
	randomizer_type & randomizer) const
{
	auto schlick = [](float const cos, float const refraction) {
		auto const r0 = (1.0f - refraction) / (1.0f + refraction);
		auto const sq_r0 = r0 * r0;
		return sq_r0 + (1.0f - sq_r0) * ::std::pow(1.0f - cos, 5);
	};
	
	coord_type outward_normal = normal;
	refraction_type refraction = this->refraction_;
	float cos;
	if (0.0f < dot(in, normal)) {
		outward_normal = -outward_normal;
		cos = refraction * dot(in, normal) / in.length();
	}
	else {
		refraction = 1.0f / refraction;
		cos = -dot(in, normal) / in.length();
	}

	coord_type refracted;
	if (!refract(refracted, in, outward_normal, refraction)
		|| randomizer() < schlick(cos, this->refraction_)) {
		return scatter_type(ray_type(pos, reflect(in, normal)), this->albedo_);
	}

#if RTIOW_DEBUG
	(::std::cout << "# refracted:"
	 << "{dir:[" << refracted << "]"
	 << ",pos:[" << pos << "]"
	 << ",refraction:" << refraction
	 << ",in:[" << in << "]"
	 << "}" << ::std::endl);
#endif
	
	return scatter_type(ray_type(pos, refracted), this->albedo_);
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
#endif // RTIOW_MATERIAL_DIELECTRIC_H_20170116162354349
// end of file
