/**
  @file         pixel_format.cpp
  @brief        represents pixel format.
  @author       HRYKY
  @version      $Id: pixel_format.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/sdl/sdl_common.h"
#include "hryky/pixel/pixel_format.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace pixel
{
namespace
{
	typedef Format::Traits::Order order_type;
	
	Format::Traits const g_traits_table[Format::Kind::num] =
	{
		{ "invalid",    order_type::invalid,    0, },
		{ "r8g8b8x8",   order_type::rgbx,       4, },
		{ "b8g8r8x8",   order_type::bgrx,       4, },
		{ "r8g8b8a8",   order_type::rgba,       4, },
		{ "b8g8r8a8",   order_type::bgra,       4, },
		{ "a8r8g8b8",   order_type::argb,       4, },
		{ "a8b8g8r8",   order_type::abgr,       4, },
		{ "r8g8b8",     order_type::rgb,        3, },
		{ "b8g8r8",     order_type::bgr,        3, },
		{ "r5g6b5",     order_type::rgb,        2, },
		{ "b5g6r5",     order_type::bgr,        2, },
	};
}
}
}
//------------------------------------------------------------------------------
// static variable
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
#if HRYKY_USE_SDL
/**
  @brief constructor with SDL_PIXELFORMAT.
 */
hryky::pixel::Format::Format(SDLFormat const & sdl_format)
	: kind_(Kind::invalid)
{
	switch (sdl_format.raw_) {
	case SDL_PIXELFORMAT_RGBX8888:  this->kind_ = Kind::r8g8b8x8; break;
	case SDL_PIXELFORMAT_BGRX8888:  this->kind_ = Kind::b8g8r8x8; break;
	case SDL_PIXELFORMAT_RGBA8888:  this->kind_ = Kind::r8g8b8a8; break;
	case SDL_PIXELFORMAT_BGRA8888:  this->kind_ = Kind::b8g8r8a8; break;
	case SDL_PIXELFORMAT_ARGB8888:  this->kind_ = Kind::a8r8g8b8; break;
	case SDL_PIXELFORMAT_ABGR8888:  this->kind_ = Kind::a8b8g8r8; break;
	case SDL_PIXELFORMAT_RGB888:    this->kind_ = Kind::r8g8b8; break;
	case SDL_PIXELFORMAT_BGR888:    this->kind_ = Kind::b8g8r8; break;
	case SDL_PIXELFORMAT_RGB565:    this->kind_ = Kind::r5g6b5; break;
	case SDL_PIXELFORMAT_BGR565:    this->kind_ = Kind::b5g6r5; break;
	default:
		break;
	}
	return;
}
/**
  @brief retrieves SDL_PIXELFORMAT.
 */
hryky::uint32_t hryky::pixel::Format::sdl_format() const
{
	switch (this->kind_) {
	case Kind::r8g8b8x8:
		return static_cast<uint32_t>(SDL_PIXELFORMAT_RGBX8888);
	case Kind::b8g8r8x8:
		return static_cast<uint32_t>(SDL_PIXELFORMAT_BGRX8888);
	case Kind::r8g8b8a8:
		return static_cast<uint32_t>(SDL_PIXELFORMAT_RGBA8888);
	case Kind::b8g8r8a8:
		return static_cast<uint32_t>(SDL_PIXELFORMAT_BGRA8888);
	case Kind::a8r8g8b8:
		return static_cast<uint32_t>(SDL_PIXELFORMAT_ARGB8888);
	case Kind::a8b8g8r8:
		return static_cast<uint32_t>(SDL_PIXELFORMAT_ABGR8888);
	case Kind::r8g8b8:
		return static_cast<uint32_t>(SDL_PIXELFORMAT_RGB888);
	case Kind::b8g8r8:
		return static_cast<uint32_t>(SDL_PIXELFORMAT_BGR888);
	case Kind::r5g6b5:
		return static_cast<uint32_t>(SDL_PIXELFORMAT_RGB565);
	case Kind::b5g6r5:
		return static_cast<uint32_t>(SDL_PIXELFORMAT_BGR565);
	default:
		return static_cast<uint32_t>(SDL_PIXELFORMAT_UNKNOWN);
	}
}
#endif // HRYKY_USE_SDL
/**
  @brief retrieves the characteristic of a pixel format.
 */
hryky::pixel::Format::Traits const &
hryky::pixel::Format::traits() const
{
	kind_type const kind = this->kind();

	if (0 > kind || Kind::num <= kind) {
		return g_traits_table[Kind::invalid];
	}

	return g_traits_table[kind];
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::pixel::Format::swap(this_type & src)
{
	hryky_swap_member(kind);
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
namespace
{
}
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
