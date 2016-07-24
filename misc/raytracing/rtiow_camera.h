/**
  @file     rtiow_camera.h
  @brief    retains the information of view.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_CAMERA_H_20160717170529378
#define RTIOW_CAMERA_H_20160717170529378
#include "./rtiow_vec3.h"
#include "./rtiow_ray.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename VectorT
#define hryky_template_arg \
	VectorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
	/// retains the information of view.
	template <hryky_template_param>
	class Camera;

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information of view.
 */
template <typename VectorT = hryky::rtiow::Vec3<> >
class hryky::rtiow::Camera
{
public :

	typedef Camera<hryky_template_arg> this_type;
	typedef VectorT vector_type;

	/// default constructor.
	Camera();

	/// copy constructor.
	Camera(this_type const &);

	/// move constructor.
	Camera(this_type &&);

	/// destructor.
	~Camera();

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

	/// creates a new ray.
	Ray<VectorT> ray(float const u, float const v) const;

protected :

private :

	vector_type origin_;
	vector_type lower_left_;
	vector_type horizontal_;
	vector_type vertical_;

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
hryky::rtiow::Camera<hryky_template_arg>::Camera()
	: origin_(0.0f)
	  , lower_left_(-2.0f, -1.0f, -1.0f)
	  , horizontal_(4.0f, 0.0f, 0.0f)
	  , vertical_(0.0f, 2.0f, 0.0f)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::Camera<hryky_template_arg>::Camera(this_type const & rhs)
	: hryky_copy_member(origin)
	  , hryky_copy_member(lower_left)
	  , hryky_copy_member(horizontal)
	  , hryky_copy_member(vertical)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::Camera<hryky_template_arg>::Camera(this_type && rhs)
	: hryky_move_member(origin)
	  , hryky_move_member(lower_left)
	  , hryky_move_member(horizontal)
	  , hryky_move_member(vertical)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::Camera<hryky_template_arg>::~Camera()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::Camera<hryky_template_arg>::clear()
{
	hryky::clear(this->vertical_);
	hryky::clear(this->horizontal_);
	hryky::clear(this->lower_left_);
	hryky::clear(this->origin_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::Camera<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(origin);
	hryky_swap_member(lower_left);
	hryky_swap_member(horizontal);
	hryky_swap_member(vertical);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::Camera<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}
/**
  @brief creates a new ray.
 */
template <hryky_template_param>
hryky::rtiow::Ray<VectorT>
hryky::rtiow::Camera<hryky_template_arg>::ray(
	float const u, float const v) const
{
	return Ray<VectorT>(
		this->origin_,
		this->lower_left_
		+ u * this->horizontal_
		+ v * this->vertical_
		- this->origin_);
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
#endif // RTIOW_CAMERA_H_20160717170529378
// end of file
