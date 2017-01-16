/**
  @file     rtiow_material_lambertian.h
  @brief    retains parameters of a material for Lambertian.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_MATERIAL_LAMBERTIAN_H_20170116161452343
#define RTIOW_MATERIAL_LAMBERTIAN_H_20170116161452343
#include "./rtiow_material_base.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename AlbedoT, typename ScatterT, typename RandomizerT
#define hryky_template_arg \
	AlbedoT, ScatterT, RandomizerT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
	/// retains parameters of a material for Lambertian.
	template <hryky_template_param>
	class Lambertian;

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains parameters of a material for Lambertian.
 */
template <
	typename AlbedoT = hryky::rtiow::Vec3<>
	, typename ScatterT = hryky::rtiow::Scatter<>
	, typename RandomizerT = hryky::rtiow::Randomizer<>
>
class hryky::rtiow::material::Lambertian
	: public Base<AlbedoT, ScatterT, RandomizerT>
{
public :

	typedef Base<AlbedoT, ScatterT, RandomizerT> base_type;
	typedef Lambertian<hryky_template_arg> this_type;
	typedef typedef typename base_type::albedo_type albedo_type;
	typedef typedef typename base_type::scatter_type scatter_type;
	typedef typedef typename base_type::randomizer_type randomizer_type;
	typedef typedef typename base_type::ray_type ray_type;
	typedef typedef typename base_type::coord_type coord_type;

	/// default constructor.
	Lambertian();

	/// instantiates with the albedo.
	Lambertian(albedo_type const & albedo);

	/// copy constructor.
	Lambertian(this_type const &);

	/// move constructor.
	Lambertian(this_type &&);

	/// destructor.
	~Lambertian();

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
hryky::rtiow::material::Lambertian<hryky_template_arg>::Lambertian()
	: base_type()
{
}
/**
  @brief instantiates with the albedo.
 */
template <hryky_template_param>
hryky::rtiow::material::Lambertian<hryky_template_arg>::Lambertian(
	albedo_type const & albedo)
	: base_type(albedo)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::material::Lambertian<hryky_template_arg>::Lambertian(this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::material::Lambertian<hryky_template_arg>::Lambertian(this_type && rhs)
	: base_type(::std::move(rhs))
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::material::Lambertian<hryky_template_arg>::~Lambertian()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::material::Lambertian<hryky_template_arg>::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::material::Lambertian<hryky_template_arg>::swap(this_type & src)
{
	this->base_type::swap(src);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::material::Lambertian<hryky_template_arg>::write_to(
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
  @brief calculates the scattered ray.
 */
template <hryky_template_param>
hryky::rtiow::material::Lambertian<hryky_template_arg>::scatter_type
hryky::rtiow::material::Lambertian<hryky_template_arg>::reflect_impl(
	coord_type const & in,
	coord_type const & pos,
	coord_type const & normal,
	randomizer_type & randomizer) const
{
	auto const target = pos + normal + randomizer.in_sphere();
	
	return scatter_type(ray_type(pos, target - pos), this->albedo());
}
//------------------------------------------------------------------------------
// declares global functions
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
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RTIOW_MATERIAL_LAMBERTIAN_H_20170116161452343
// end of file
