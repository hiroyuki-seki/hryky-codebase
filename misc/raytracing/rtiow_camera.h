/**
  @file     rtiow_camera.h
  @brief    retains the information of view.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_CAMERA_H_20160717170529378
#define RTIOW_CAMERA_H_20160717170529378
#include "./rtiow_vec3.h"
#include "./rtiow_ray_half.h"
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

	template <typename ValueT>
	class Degree;

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
	typedef ray::Half<vector_type> ray_type;

	/// default constructor.
	Camera();

	/// creates an instance from a vertical FOV and an aspect ratio.
	template <typename DegreeT, typename AspectT>
	Camera(Degree<DegreeT> const & vfov, AspectT aspect);

	/// creates an instance from parameters.
	template <typename DegreeT, typename AspectT>
	Camera(
		vector_type const & from,
		vector_type const & at,
		vector_type const & up,
		Degree<DegreeT> const & vfov,
		AspectT aspect);

	/// instantiates with an aperture.
	template <
		typename DegreeT,
		typename AspectT,
		typename ApertureT,
		typename FocusT >
	Camera(
		vector_type const & from,
		vector_type const & at,
		vector_type const & up,
		DegreeT const & vfov,
		AspectT const & aspect,
		ApertureT const & aperture,
		FocusT const & focus_dist);

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
	ray_type ray(float const u, float const v) const;

	/// creates a new ray randomized by the aperture.
	template <typename RandomizerT >
	ray_type ray(
		float const u,
		float const v,
		RandomizerT & randomizer) const;

protected :

private :

	vector_type origin_;
	vector_type lower_left_;
	vector_type horizontal_;
	vector_type vertical_;
	vector_type basis_[3];
	float lens_radius_;

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
	  , basis_()
	  , lens_radius_(1.0f)
{
}

/**
  @brief creates an instance from a vertical FOV and an aspect ratio.
 */
template <hryky_template_param>
template <typename DegreeT, typename AspectT>
hryky::rtiow::Camera<hryky_template_arg>::Camera(
	Degree<DegreeT> const & vfov, AspectT aspect)
	: origin_(0.0f)
	, basis_()
	, lens_radius_(1.0f)
{
	auto const vfov_radian = radian(vfov);
	auto const half_height = ::std::tan(vfov_radian.get() / 2.0f);
	auto const half_width = aspect * half_height;
	
	this->lower_left_ = vector_type(-half_width, -half_height, -1.0f);
	this->horizontal_ = vector_type(2.0f * half_width, 0.0f, 0.0f);
	this->vertical_ = vector_type(0.0f, 2.0f * half_height, 0.0f);
}

/**
  @brief creates an instance from parameters.
 */
template <hryky_template_param>
template <typename DegreeT, typename AspectT>
hryky::rtiow::Camera<hryky_template_arg>::Camera(
	vector_type const & from,
	vector_type const & at,
	vector_type const & up,
	Degree<DegreeT> const & vfov,
	AspectT aspect)
	: origin_(from)
	, lens_radius_(1.0f)
{
	auto const vfov_radian = radian(vfov);
	auto const half_height = ::std::tan(vfov_radian.get() / 2.0f);
	auto const half_width = aspect * half_height;
	this->basis_[2] = normalize(from - at);
	this->basis_[0] = normalize(cross(up, this->basis_[2]));
	this->basis_[1] = cross(this->basis_[2], this->basis_[0]);
	
	this->lower_left_ = (
		this->origin_
		- half_width * this->basis_[0]
		- half_height * this->basis_[1]
		- this->basis_[2]);
	this->horizontal_ = 2.0f * half_width * this->basis_[0];
	this->vertical_ = 2.0f * half_height * this->basis_[1];
}

/**
  @brief instantiates with an aperture.
 */
template <hryky_template_param >
template <
	typename DegreeT,
	typename AspectT,
	typename ApertureT,
	typename FocusT
>
hryky::rtiow::Camera<hryky_template_arg >::Camera(
	vector_type const & from,
	vector_type const & at,
	vector_type const & up,
	DegreeT const & vfov,
	AspectT const & aspect,
	ApertureT const & aperture,
	FocusT const & focus_dist)
	: origin_(from)
{
	auto const vfov_radian = radian(vfov);
	auto const half_height = ::std::tan(vfov_radian.get() / 2.0f);
	auto const half_width = aspect * half_height;
	this->basis_[2] = normalize(from - at);
	this->basis_[0] = normalize(cross(up, this->basis_[2]));
	this->basis_[1] = cross(this->basis_[2], this->basis_[0]);
	
	this->lower_left_ = (
		this->origin_
		- focus_dist * half_width * this->basis_[0]
		- focus_dist * half_height * this->basis_[1]
		- focus_dist * this->basis_[2]);
	this->horizontal_ = 2.0f * focus_dist * half_width * this->basis_[0];
	this->vertical_ = 2.0f * focus_dist * half_height * this->basis_[1];
	this->lens_radius_ = aperture / 2.0f;
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
	  , hryky_copy_member(basis)
	  , hryky_copy_member(lens_radius)
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
	  , hryky_move_member(basis)
	  , hryky_move_member(lens_radius)
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
	hryky::clear(this->lens_radius_);
	hryky::clear(this->basis_);
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
	hryky_swap_member(basis);
	hryky_swap_member(lens_radius);
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
typename hryky::rtiow::Camera<hryky_template_arg>::ray_type
hryky::rtiow::Camera<hryky_template_arg>::ray(
	float const u, float const v) const
{
	return ray_type(
		this->origin_,
		this->lower_left_
		+ u * this->horizontal_
		+ v * this->vertical_
		- this->origin_);
}

/**
  @brief creates a new ray randomized by the aperture.
 */
template <hryky_template_param >
template <typename RandomizerT >
typename hryky::rtiow::Camera<hryky_template_arg >::ray_type
hryky::rtiow::Camera<hryky_template_arg >::ray(
	float const u,
	float const v,
	RandomizerT & randomizer) const
{
	auto const rd = this->lens_radius_ * randomizer.in_disk();
	auto const offset = rd[0] * this->basis_[0] + rd[1] * this->basis_[1];

	return ray_type(
		this->origin_ + offset,
		this->lower_left_
		+ u * this->horizontal_
		+ v * this->vertical_
		- this->origin_
		- offset);
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
