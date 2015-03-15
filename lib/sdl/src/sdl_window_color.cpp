/**
  @file     sdl_window_color.cpp
  @brief    manages the color of window.
  @author   HRYKY
  @version  $Id: sdl_window_color.cpp 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/sdl/sdl_window_color.h"
#include "hryky/json.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace sdl
{
namespace window
{
namespace
{
	Color g_preferred;
	
} // namespace "anonymous"
} // namespace window
} // namespace sdl
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
  @brief default constructor.
 */
hryky::sdl::window::Color::Color()
	: red_(8)
	  , green_(8)
	  , blue_(8)
	  , alpha_(8)
{
}
/**
  @brief copy constructor.
 */
hryky::sdl::window::Color::Color(this_type const & rhs)
	: hryky_copy_member(red)
	  , hryky_copy_member(green)
	  , hryky_copy_member(blue)
	  , hryky_copy_member(alpha)
{
}
/**
  @brief move constructor.
 */
hryky::sdl::window::Color::Color(this_type && rhs)
	: hryky_move_member(red)
	  , hryky_move_member(green)
	  , hryky_move_member(blue)
	  , hryky_move_member(alpha)
{
}
/**
  @brief destructor.
 */
hryky::sdl::window::Color::~Color()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::sdl::window::Color::clear()
{
	hryky::clear(this->red_);
	hryky::clear(this->green_);
	hryky::clear(this->blue_);
	hryky::clear(this->alpha_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::sdl::window::Color::swap(this_type & src)
{
	hryky_swap_member(red);
	hryky_swap_member(green);
	hryky_swap_member(blue);
	hryky_swap_member(alpha);
}
/**
  @brief requires the preferred settings.
 */
void hryky::sdl::window::Color::prefer() const
{
	g_preferred = *this;
}
/**
  @brief applies this configuration to SDL system.
 */
void hryky::sdl::window::Color::store() const
{
	this->prefer();
	
	::SDL_GL_SetAttribute(SDL_GL_RED_SIZE, this->red_);
	::SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, this->green_);
	::SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, this->blue_);
	::SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, this->alpha_);
}
/**
  @brief retrieves the configuration applied to SDL System.
 */
hryky::sdl::window::Color &
hryky::sdl::window::Color::load()
{
	int red;
	::SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &red);
	int green;
	::SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &green);
	int blue;
	::SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &blue);
	int alpha;
	::SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &alpha);

	this->red_ = static_cast<uint8_t>(red);
	this->green_ = static_cast<uint8_t>(green);
	this->blue_ = static_cast<uint8_t>(blue);
	this->alpha_ = static_cast<uint8_t>(alpha);
	
	return *this;
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
// defines functions used in this file
//------------------------------------------------------------------------------
namespace hryky
{
namespace sdl
{
namespace window
{
namespace
{
} // namespace "anonymous"
} // namespace window
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
