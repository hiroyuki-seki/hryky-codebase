/**
  @file     window_context_fullscreen.cpp
  @brief    A parameter for window::context_type::fullscreen().
  @author   HRYKY
  @version  $Id: window_context_fullscreen.cpp 360 2014-07-05 06:59:57Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/window/window_context_fullscreen.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace window
{
namespace context
{
namespace
{
} // namespace "anonymous"
} // namespace context
} // namespace window
} // namespace hryky
//------------------------------------------------------------------------------
// static variable
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor with the size of window.
 */
hryky::window::context::Fullscreen::Fullscreen(
	size_t const width, size_t const height)
	: width_(width)
	  , height_(height)
	  , format_(pixel::Format::Kind::r8g8b8)
	  , refresh_rate_(60)
{
}
/**
  @brief copy constructor.
 */
hryky::window::context::Fullscreen::Fullscreen(this_type const & rhs)
	: hryky_copy_member(width)
	, hryky_copy_member(height)
	, hryky_copy_member(format)
	, hryky_copy_member(refresh_rate)
{
}
/**
  @brief move constructor.
 */
hryky::window::context::Fullscreen::Fullscreen(this_type && rhs)
	: hryky_move_member(width)
	, hryky_move_member(height)
	, hryky_move_member(format)
	, hryky_move_member(refresh_rate)
{
}
/**
  @brief destructor.
 */
hryky::window::context::Fullscreen::~Fullscreen()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::window::context::Fullscreen::clear()
{
	hryky::clear(this->refresh_rate_);
	hryky::clear(this->format_);
	hryky::clear(this->height_);
	hryky::clear(this->width_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::window::context::Fullscreen::swap(this_type & src)
{
	hryky_swap_member(width);
	hryky_swap_member(height);
	hryky_swap_member(format);
	hryky_swap_member(refresh_rate);
}
/**
  @brief retrieves the width of fullscreen.
 */
hryky::size_t hryky::window::context::Fullscreen::width() const
{
	return this->width_;
}
/**
  @brief retrieves the height of fullscreen.
 */
hryky::size_t hryky::window::context::Fullscreen::height() const
{
	return this->height_;
}
/**
  @brief retrieves the pixel format of fullscreen.
 */
hryky::pixel::Format const &
hryky::window::context::Fullscreen::format() const
{
	return this->format_;
}
/**
  @brief retrieves the refresh rate of fullscreen.
 */
hryky::window::refresh_rate_type 
hryky::window::context::Fullscreen::refresh_rate() const
{
	return this->refresh_rate_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace window
{
namespace context
{
namespace
{
} // namespace "anonymous"
} // namespace context
} // namespace window
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
