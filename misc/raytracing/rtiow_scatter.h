/**
  @file     rtiow_scatter.h
  @brief    retains the information for scattering.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_SCATTER_H_20160724145548288
#define RTIOW_SCATTER_H_20160724145548288
#include "./rtiow_ray.h"
#include "hryky/with_is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename RayT, typename AttenuationT
#define hryky_template_arg \
	RayT, AttenuationT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
	/// retains the information for scattering.
	template <hryky_template_param>
	class Scatter;

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information for scattering.
 */
template <
	typename RayT = hryky::rtiow::Ray<>,
	typename AttenuationT = typename RayT::vector_type
>
class hryky::rtiow::Scatter
	: public hryky::WithIsNull<Scatter<hryky_template_arg> >
{
public :

	typedef Scatter<hryky_template_arg> this_type;
	typedef RayT ray_type;
	typedef AttenuationT attenuation_type;

	/// default constructor.
	Scatter();

	/// instantiates with parameters.
	Scatter(ray_type const & ray, attenuation_type const & attenuation);

	/// copy constructor.
	Scatter(this_type const &);

	/// move constructor.
	Scatter(this_type &&);

	/// destructor.
	~Scatter();

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

	/// confirms whether the whole of ray is absorbed.
	bool is_null() const;

	/// retrieves the attenuation.
	attenuation_type const & attenuation() const;

	/// retrieves the scattered ray.
	ray_type const & ray() const;

protected :

private :

	ray_type ray_;
	attenuation_type attenuation_;

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
hryky::rtiow::Scatter<hryky_template_arg>::Scatter()
	: ray_()
	  , attenuation_()
{
}
/**
  @brief instantiates with parameters.
 */
template <hryky_template_param>
hryky::rtiow::Scatter<hryky_template_arg>::Scatter(
	ray_type const & ray,
	attenuation_type const & attenuation)
	: ray_(ray)
	  , attenuation_(attenuation)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::Scatter<hryky_template_arg>::Scatter(this_type const & rhs)
	: hryky_copy_member(ray)
	  , hryky_copy_member(attenuation)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::Scatter<hryky_template_arg>::Scatter(this_type && rhs)
	: hryky_move_member(ray)
	  , hryky_move_member(attenuation)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::Scatter<hryky_template_arg>::~Scatter()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::Scatter<hryky_template_arg>::clear()
{
	hryky::clear(this->attenuation_);
	hryky::clear(this->ray_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::Scatter<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(ray);
	hryky_swap_member(attenuation);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::Scatter<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}
/**
  @brief confirms whether the whole of ray is absorbed.
 */
template <hryky_template_param>
bool hryky::rtiow::Scatter<hryky_template_arg>::is_null() const
{
	return attenuation_type() == this->attenuation_;
}
/**
  @brief retrieves the attenuation.
 */
template <hryky_template_param>
typename hryky::rtiow::Scatter<hryky_template_arg>::attenuation_type const & 
hryky::rtiow::Scatter<hryky_template_arg>::attenuation() const
{
	return this->attenuation_;
}
/**
  @brief retrieves the scattered ray.
 */
template <hryky_template_param>
typename hryky::rtiow::Scatter<hryky_template_arg>::ray_type const & 
hryky::rtiow::Scatter<hryky_template_arg>::ray() const
{
	return this->ray_;
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
	/// creates a scatter.
	template <hryky_template_param>
	Scatter<hryky_template_arg> scatter(
		RayT const & ray, AttenuationT const & attenuation);

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a scatter.
 */
template <hryky_template_param>
hryky::rtiow::Scatter<hryky_template_arg>
hryky::rtiow::scatter(
	RayT const & ray, AttenuationT const & attenuation)
{
	return Scatter<hryky_template_arg>(ray, attenuation);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RTIOW_SCATTER_H_20160724145548288
// end of file
