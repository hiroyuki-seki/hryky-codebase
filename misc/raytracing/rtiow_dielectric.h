/**
  @file     rtiow_dielectric.h
  @brief    retains information of a dielectric material.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_DIELECTRIC_H_20160731131811220
#define RTIOW_DIELECTRIC_H_20160731131811220
#include "./rtiow_vec3.h"
#include "./rtiow_scatter.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename AlbedoT, typename RefractionT
#define hryky_template_arg \
	AlbedoT, RefractionT
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
	typename AlbedoT = hryky::rtiow::Vec3<>,
	typename RefractionT = float
>
class hryky::rtiow::Dielectric
{
public :

	typedef Dielectric<hryky_template_arg> this_type;
	typedef AlbedoT albedo_type;
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

	/// calculates the scattered ray.
	template <typename VectorT, typename RandomizerT>
	Scatter<> scatter(
		VectorT const & in,
		VectorT const & pos,
		VectorT const & normal,
		RandomizerT & randomizer) const;

protected :

private :

	albedo_type albedo_;
	refraction_type refraction_;

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
hryky::rtiow::Dielectric<hryky_template_arg>::Dielectric()
	: albedo_(1.0f, 1.0f, 1.0f)
	  , refraction_(1.0f)
{
}

/**
  @brief instantiates with parameters.
 */
template <hryky_template_param>
hryky::rtiow::Dielectric<hryky_template_arg>::Dielectric(
	refraction_type const refraction)
	: albedo_(1.0f, 1.0f, 1.0f)
	  , refraction_(1.0f)
{
}

/**
  @brief instantiates with parameters.
 */
template <hryky_template_param>
hryky::rtiow::Dielectric<hryky_template_arg>::Dielectric(
	albedo_type const & albedo, refraction_type const refraction)
	: albedo_(albedo)
	  , refraction_(refraction)
{
}

/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::Dielectric<hryky_template_arg>::Dielectric(this_type const & rhs)
	: hryky_copy_member(albedo)
	  , hryky_copy_member(refraction)
{
}

/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::Dielectric<hryky_template_arg>::Dielectric(this_type && rhs)
	: hryky_move_member(albedo)
	  , hryky_move_member(refraction)
{
}

/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::Dielectric<hryky_template_arg>::~Dielectric()
{
}

/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::Dielectric<hryky_template_arg>::clear()
{
	hryky::clear(this->albedo_);
	hryky::clear(this->refraction_);
}

/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::Dielectric<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(albedo);
	hryky_swap_member(refraction);
}

/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::Dielectric<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}

/**
  @brief calculates the scattered ray.
 */
template <hryky_template_param>
template <typename VectorT, typename RandomizerT>
hryky::rtiow::Scatter<>
hryky::rtiow::Dielectric<hryky_template_arg>::scatter(
	VectorT const & in,
	VectorT const & pos,
	VectorT const & normal,
	RandomizerT & randomizer) const
{
	auto schlick = [](float const cos, float const refraction) {
		auto const r0 = (1.0f - refraction) / (1.0f + refraction);
		auto const sq_r0 = r0 * r0;
		return sq_r0 + (1.0f - sq_r0) * ::std::pow(1.0f - cos, 5);
	};
	
	VectorT outward_normal = normal;
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

	VectorT refracted;
	if (!refract(refracted, in, outward_normal, refraction)
		|| randomizer() < schlick(cos, this->refraction_)) {
		return Scatter<>(ray(pos, reflect(in, normal)), this->albedo_);
	}

#if RTIOW_DEBUG
	(::std::cout << "# refracted:"
	 << "{dir:[" << refracted << "]"
	 << ",pos:[" << pos << "]"
	 << ",refraction:" << refraction
	 << ",in:[" << in << "]"
	 << "}" << ::std::endl);
#endif
	
	return Scatter<>(ray(pos, refracted), this->albedo_);
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
#endif // RTIOW_DIELECTRIC_H_20160731131811220
// end of file
