/**
  @file         display_mode.h
  @brief        retains the information of the resolution and color format of a display.
  @author       HRYKY
  @version      $Id: display_mode.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef DISPLAY_MODE_H_20120128130453211
#define DISPLAY_MODE_H_20120128130453211
#include "hryky/config.h"
#include "hryky/display/display_config.h"
#include "hryky/display/display_common.h"
#include "hryky/pixel/pixel_format.h"
#include "hryky/sdl/sdl_common.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace display
{
	/// retains the information of the resolution and color format of a display.
	class Mode;

	typedef Mode mode_type;

}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information of the resolution and color format of a display.
 */
class hryky::display::Mode :
	public WithStreamOut<Mode>,
	public WithSwap<Mode>
{
public :
	typedef hryky::display::Mode                    this_type;

	/// parameters for reset()
	struct ResetParameter : WithoutCopy
	{
		typedef ResetParameter this_type;
#if HRYKY_USE_SDL
		ResetParameter(
			::SDL_DisplayMode & raw_mode)
			: format_(format_type::SDLFormat(raw_mode.format))
			  , size_(
				  static_cast<size_t>(raw_mode.w),
				  static_cast<size_t>(raw_mode.h))
			  , refresh_rate_(static_cast<refresh_rate_type>(
				  raw_mode.refresh_rate))
		{}
#endif // HRYKY_USE_SDL
		
		ResetParameter(
			format_type const & format,
			size_type const & size,
			refresh_rate_type refresh_rate)
			: format_(format)
			  , size_(size)
			  , refresh_rate_(refresh_rate)
		{}

	private :
		hryky_delete_this_copy_constructor(ResetParameter);
		hryky_delete_this_copy_assign_op(ResetParameter);
		
		hryky_accessor_read(format_type,        format);
		hryky_accessor_read(size_type,          size);
		hryky_accessor_read(refresh_rate_type,  refresh_rate);
	};

	/// default constructor.
	Mode();

	/// destructor.
	~Mode();

	/// copy constructor.
	Mode(Mode const &);

	/// move constructor.
	Mode(this_type && rhs);

	/// assignment operator.
	Mode & operator=(Mode const & rhs);

	/// releases the internal resources.
	void clear();

	/// clears the existing resources and creates new resources.
	bool reset(ResetParameter const & param);

	/// retrieves the refresh rate (Hz) of display
	refresh_rate_type refresh_rate() const {
		return this->refresh_rate_;
	}

	/// retrieves the pixel format
	format_type const & format() const {
		return this->format_;
	}

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/**
	  traverses the all display configurations in this mode.
	  @param driver_name is the name of the driver which retains this mode.
	  @param functor is called for each display mode.
	  @retval true when the operation is not canceled by user.
	  @retval false when the operation is canceled by user.

	   The function 'bool functor(display::Config &)' is called during the
	  iteration of display modes.
	 */
	template < typename FunctorT >
	bool traverse(
		driver_name_type const & driver_name,
		FunctorT const & functor) const;

	/// retrieves the size of display of the current mode.
	size_type const & size() const;

	/// retrieves the width of the display.
	size_t width() const;

	/// retrieves the height of the display.
	size_t height() const;

protected :

private :

	format_type         format_;
	size_type           size_;
	refresh_rate_type   refresh_rate_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief traverses the all display configurations in this mode.
 */
template < typename FunctorT >
bool hryky::display::Mode::traverse(
	driver_name_type const & driver_name,
	FunctorT const & functor) const
{
	return functor(
		Config(
			driver_name,
			this->format_,
			this->size_,
			this->refresh_rate_)
		);
}
/**
  @brief outputs the information of Mode as text.
 */
template <typename StreamT>
StreamT &
hryky::display::Mode::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	
	hryky_write_member(format);
	hryky_write_member(size);
	hryky_write_member(refresh_rate);
	
	return out;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// global function prototype
//------------------------------------------------------------------------------
namespace hryky
{
namespace display
{
}
}
#endif // DISPLAY_MODE_H_20120128130453211
// end of file
