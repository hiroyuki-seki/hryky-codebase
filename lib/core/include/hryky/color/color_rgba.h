/**
  @file         color_rgba.h
  @brief        represents a color format which comprises RGBA.
  @author       HRYKY
  @version      $Id: color_rgba.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef COLOR_RGBA_H_20120220153826318
#define COLOR_RGBA_H_20120220153826318
#include "hryky/type_traits/as_parameter.h"
#include "hryky/swap.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename RedT, typename GreenT, typename BlueT, typename AlphaT
#define hryky_template_arg \
	RedT, GreenT, BlueT, AlphaT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace color
{
	/// represents a color format which comprises RGBA.
	template <hryky_template_param>
	class Rgba;
}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief represents a color format which comprises RGBA.
 */
template <
	typename RedT,
	typename GreenT = RedT,
	typename BlueT = RedT,
	typename AlphaT = RedT>
class hryky::color::Rgba :
	public WithStreamOut<Rgba<hryky_template_arg> >,
	public WithSwap<Rgba<hryky_template_arg> >
{
public :
	typedef RedT    red_type;
	typedef GreenT  green_type;
	typedef BlueT   blue_type;
	typedef AlphaT  alpha_type;

	typedef hryky::color::Rgba<hryky_template_arg> this_type;
	
	typedef typename AsParameter<red_type>::type       red_param_type;
	typedef typename AsParameter<green_type>::type     green_param_type;
	typedef typename AsParameter<blue_type>::type      blue_param_type;
	typedef typename AsParameter<alpha_type>::type     alpha_param_type;

	/// default constructor.
	Rgba();

	/// copy constructor.
	Rgba(this_type const & rhs);

	/// move constructor.
	Rgba(this_type && rhs);

	/// constructs with elements.
	Rgba(
		red_param_type red,
		green_param_type green,
		blue_param_type blue,
		alpha_param_type alpha);

	/// destructor.
	~Rgba();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// compares to equal.
	bool operator==(this_type const & rhs) const;

	/// compare to not equal.
	bool operator!=(this_type const & rhs) const;

	/// retrieves the element of red.
	red_param_type red() const;

	/// retrieves the element of green.
	green_param_type green() const;

	/// retrieves the element of blue.
	blue_param_type blue() const;

	/// retrieves the element of alpha.
	alpha_param_type alpha() const;

	/// assigns red element.
	this_type & red(red_param_type src);

	/// assigns green element.
	this_type & green(green_param_type src);

	/// assigns blue element.
	this_type & blue(blue_param_type src);

	/// assigns alpha element.
	this_type & alpha(alpha_param_type src);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :

	red_type        red_;
	green_type      green_;
	blue_type       blue_;
	alpha_type      alpha_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace color
{
} // namespace color
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::color::Rgba<hryky_template_arg>::Rgba()
	: red_()
	  , green_()
	  , blue_()
	  , alpha_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::color::Rgba<hryky_template_arg>::Rgba(this_type const & rhs)
	: hryky_copy_member(red)
	  , hryky_copy_member(green)
	  , hryky_copy_member(blue)
	  , hryky_copy_member(alpha)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::color::Rgba<hryky_template_arg>::Rgba(this_type && rhs)
	: hryky_move_member(red)
	  , hryky_move_member(green)
	  , hryky_move_member(blue)
	  , hryky_move_member(alpha)
{
}
/**
  @brief constructs with elements.
 */
template <hryky_template_param>
hryky::color::Rgba<hryky_template_arg>::Rgba(
	red_param_type red,
	green_param_type green,
	blue_param_type blue,
	alpha_param_type alpha)
	: red_(red)
	  , green_(green)
	  , blue_(blue)
	  , alpha_(alpha)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::color::Rgba<hryky_template_arg>::~Rgba()
{
}
/**
  @brief compares to equal.
 */
template <hryky_template_param>
bool hryky::color::Rgba<hryky_template_arg>::operator==(
	this_type const & rhs) const
{
	return (
		this->red_ == rhs.red_
		&& this->green_ == rhs.green_
		&& this->blue_ == rhs.blue_
		&& this->alpha_ == rhs.alpha_);
}
/**
  @brief compare to not equal.
 */
template <hryky_template_param>
bool hryky::color::Rgba<hryky_template_arg>::operator!=(
	this_type const & rhs) const
{
	return !this->operator==(rhs);
}
/**
  @brief retrieves the element of red.
 */
template <hryky_template_param>
typename hryky::color::Rgba<hryky_template_arg>::red_param_type
hryky::color::Rgba<hryky_template_arg>::red() const
{
	return this->red_;
}
/**
  @brief retrieves the element of green.
 */
template <hryky_template_param>
typename hryky::color::Rgba<hryky_template_arg>::green_param_type
hryky::color::Rgba<hryky_template_arg>::green() const
{
	return this->green_;
}
/**
  @brief retrieves the element of blue.
 */
template <hryky_template_param>
typename hryky::color::Rgba<hryky_template_arg>::blue_param_type
hryky::color::Rgba<hryky_template_arg>::blue() const
{
	return this->blue_;
}
/**
  @brief retrieves the element of alpha.
 */
template <hryky_template_param>
typename hryky::color::Rgba<hryky_template_arg>::alpha_param_type
hryky::color::Rgba<hryky_template_arg>::alpha() const
{
	return this->alpha_;
}
/**
  @brief assigns red element.
 */
template <hryky_template_param>
hryky::color::Rgba<hryky_template_arg> &
hryky::color::Rgba<hryky_template_arg>::red(red_param_type src)
{
	this->red_ = src;
	return *this;
}
/**
  @brief assigns green element.
 */
template <hryky_template_param>
hryky::color::Rgba<hryky_template_arg> &
hryky::color::Rgba<hryky_template_arg>::green(green_param_type src)
{
	this->green_ = src;
	return *this;
}
/**
  @brief assigns blue element.
 */
template <hryky_template_param>
hryky::color::Rgba<hryky_template_arg> &
hryky::color::Rgba<hryky_template_arg>::blue(blue_param_type src)
{
	this->blue_ = src;
	return *this;
}
/**
  @brief assigns alpha element.
 */
template <hryky_template_param>
hryky::color::Rgba<hryky_template_arg> &
hryky::color::Rgba<hryky_template_arg>::alpha(alpha_param_type src)
{
	this->alpha_ = src;
	return *this;
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::color::Rgba<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(red);
	hryky_write_member(green);
	hryky_write_member(blue);
	hryky_write_member(alpha);
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::color::Rgba<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(red);
	hryky_swap_member(green);
	hryky_swap_member(blue);
	hryky_swap_member(alpha);
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
namespace color
{

} // namespace color
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // COLOR_RGBA_H_20120220153826318
// end of file
