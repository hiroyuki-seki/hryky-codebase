/**
  @file     rtiow_lambertian.h
  @brief    retains parameters of a material for Lambertian.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_LAMBERTIAN_H_20160724140040250
#define RTIOW_LAMBERTIAN_H_20160724140040250
#include "./rtiow_vec3.h"
#include "./rtiow_scatter.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename AlbedoT
#define hryky_template_arg \
	AlbedoT
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
template <typename AlbedoT = hryky::rtiow::Vec3<> >
class hryky::rtiow::Lambertian
{
public :

	typedef Lambertian<hryky_template_arg> this_type;
	typedef AlbedoT albedo_type;

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
hryky::rtiow::Lambertian<hryky_template_arg>::Lambertian()
	: albedo_()
{
}
/**
  @brief instantiates with the albedo.
 */
template <hryky_template_param>
hryky::rtiow::Lambertian<hryky_template_arg>::Lambertian(
	albedo_type const & albedo)
	: albedo_(albedo)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::Lambertian<hryky_template_arg>::Lambertian(this_type const & rhs)
	: hryky_copy_member(albedo)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::Lambertian<hryky_template_arg>::Lambertian(this_type && rhs)
	: hryky_move_member(albedo)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::Lambertian<hryky_template_arg>::~Lambertian()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::Lambertian<hryky_template_arg>::clear()
{
	hryky::clear(this->albedo_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::Lambertian<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(albedo);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::Lambertian<hryky_template_arg>::write_to(
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
hryky::rtiow::Lambertian<hryky_template_arg>::scatter(
	VectorT const & in,
	VectorT const & pos,
	VectorT const & normal,
	RandomizerT & randomizer) const
{
	auto const target = pos + normal + randomizer.in_sphere();
	
	return Scatter<>(ray(pos, target - pos), this->albedo_);
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
#endif // RTIOW_LAMBERTIAN_H_20160724140040250
// end of file
