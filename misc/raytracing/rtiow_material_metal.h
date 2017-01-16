/**
  @file     rtiow_material_metal.h
  @brief    retains parameters of a material as a metal.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_MATERIAL_METAL_H_20170116160457336
#define RTIOW_MATERIAL_METAL_H_20170116160457336
#include "./rtiow_material_base.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename AlbedoT, typename ScatterT, typename RandomizerT, typename FuzzT
#define hryky_template_arg \
	AlbedoT, ScatterT, RandomizerT, FuzzT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
	/// retains parameters of a material as a metal.
	template <hryky_template_param>
	class Metal;

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains parameters of a material as a metal.
 */
template <
	typename AlbedoT = hryky::rtiow::Vec3<>
	, typename ScatterT = hryky::rtiow::Scatter<>
	, typename RandomizerT = hryky::rtiow::Randomizer<>
	, typename FuzzT = float
>
class hryky::rtiow::material::Metal
	: public Base<AlbedoT, ScatterT, RandomizerT>
{
public :

	typedef Base<AlbedoT, ScatterT, RandomizerT> base_type;
	typedef Metal<hryky_template_arg> this_type;
	typedef typename base_type::albedo_type albedo_type;
	typedef typename base_type::scatter_type scatter_type;
	typedef typename base_type::randomizer_type randomizer_type;
	typedef typename base_type::coord_type coord_type;
	typedef FuzzT fuzz_type;

	/// default constructor.
	Metal();

	/// instantiates with parameters.
	Metal(albedo_type const & albedo);

	/// instantiates with parameters.
	Metal(albedo_type const & albedo, fuzz_type const fuzz);

	/// copy constructor.
	Metal(this_type const &);

	/// move constructor.
	Metal(this_type &&);

	/// destructor.
	~Metal();

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
	typedef typename base_type::ray_type ray_type;

	/// calculates the scattered ray.
	virtual scatter_type reflect_impl(
		coord_type const & in,
		coord_type const & pos,
		coord_type const & normal,
		RandomizerT & randomizer) const;

	fuzz_type fuzz_;
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
hryky::rtiow::material::Metal<hryky_template_arg>::Metal()
	: base_type()
	  , fuzz_()
{
}
/**
  @brief instantiates with parameters.
 */
template <hryky_template_param>
hryky::rtiow::material::Metal<hryky_template_arg>::Metal(albedo_type const & albedo)
	: base_type(albedo)
	  , fuzz_()
{
}
/**
  @brief instantiates with parameters.
 */
template <hryky_template_param>
hryky::rtiow::material::Metal<hryky_template_arg>::Metal(
	albedo_type const & albedo, fuzz_type const fuzz)
	: base_type(albedo)
	  , fuzz_(fuzz)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::material::Metal<hryky_template_arg>::Metal(this_type const & rhs)
	: base_type(rhs)
	  , hryky_copy_member(fuzz)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::material::Metal<hryky_template_arg>::Metal(this_type && rhs)
	: base_type(::std::move(rhs))
	  , hryky_move_member(fuzz)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::material::Metal<hryky_template_arg>::~Metal()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::material::Metal<hryky_template_arg>::clear()
{
	hryky::clear(this->fuzz_);
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::material::Metal<hryky_template_arg>::swap(this_type & src)
{
	this->base_type::swap(src);
	hryky_swap_member(fuzz);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::material::Metal<hryky_template_arg>::write_to(StreamT & out) const
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
hryky::rtiow::material::Metal<hryky_template_arg>::scatter_type
hryky::rtiow::material::Metal<hryky_template_arg>::reflect_impl(
	coord_type const & in,
	coord_type const & pos,
	coord_type const & normal,
	randomizer_type & randomizer) const
{
	auto const reflected = (
		rtiow::reflect(in, normal)
		+ this->fuzz_ * randomizer.in_sphere());

	return scatter_type(ray_type(pos, reflected), this->albedo());
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
#endif // RTIOW_MATERIAL_METAL_H_20170116160457336
// end of file
