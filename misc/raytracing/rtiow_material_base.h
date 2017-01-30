/**
  @file     rtiow_material_base.h
  @brief    abstracts the features of a material.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_MATERIAL_BASE_H_20170116155149327
#define RTIOW_MATERIAL_BASE_H_20170116155149327
#include "./rtiow_vec3.h"
#include "./rtiow_scatter.h"
#include "./rtiow_randomizer.h"
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
namespace material
{
	/// abstracts the features of a material.
	template <hryky_template_param>
	class Base;

} // namespace material
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief abstracts the features of a material.
 */
template <
	typename AlbedoT = hryky::rtiow::Vec3<>
	, typename ScatterT = hryky::rtiow::Scatter<>
	, typename RandomizerT = hryky::rtiow::Randomizer<>
>
class hryky::rtiow::material::Base
{
public :

	typedef Base<hryky_template_arg> this_type;
	typedef AlbedoT albedo_type;
	typedef ScatterT scatter_type;
	typedef typename scatter_type::ray_type ray_type;
	typedef typename ray_type::coord_type coord_type;
	typedef RandomizerT randomizer_type;

	/// default constructor.
	Base();

	/// instantiates with an albedo.
	Base(albedo_type const & albedo);

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

	/// calculates the scattered ray.
	scatter_type reflect(
		coord_type const & in,
		coord_type const & pos,
		coord_type const & normal,
		randomizer_type & randomizer) const;

	/// retrieves the albedo.
	albedo_type const & albedo() const;

protected :

private :

	/// implements reflect.
	virtual scatter_type reflect_impl(
		coord_type const & in,
		coord_type const & pos,
		coord_type const & normal,
		randomizer_type & randomizer) const = 0;

	albedo_type albedo_;
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
hryky::rtiow::material::Base<hryky_template_arg>::Base()
	: albedo_()
{
}
/**
  @brief instantiates with an albedo.
 */
template <hryky_template_param>
hryky::rtiow::material::Base<hryky_template_arg>::Base(
	albedo_type const & albedo)
	: albedo_(albedo)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::material::Base<hryky_template_arg>::Base(this_type const & rhs)
	: hryky_copy_member(albedo)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::material::Base<hryky_template_arg>::Base(this_type && rhs)
	: hryky_move_member(albedo)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::material::Base<hryky_template_arg>::~Base()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::material::Base<hryky_template_arg>::clear()
{
	hryky::clear(this->albedo_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::material::Base<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(albedo);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::material::Base<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}
/**
  @brief calculates the scattered ray.
 */
template <hryky_template_param>
typename hryky::rtiow::material::Base<hryky_template_arg>::scatter_type 
hryky::rtiow::material::Base<hryky_template_arg>::reflect(
	coord_type const & in,
	coord_type const & pos,
	coord_type const & normal,
	randomizer_type & randomizer) const
{
	return this->reflect_impl(in, pos, normal, randomizer);
}
/**
  @brief retrieves the albedo.
 */
template <hryky_template_param>
typename hryky::rtiow::material::Base<hryky_template_arg>::albedo_type const & 
hryky::rtiow::material::Base<hryky_template_arg>::albedo() const
{
	return this->albedo_;
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
#endif // RTIOW_MATERIAL_BASE_H_20170116155149327
// end of file
