/**
  @file     sdl_display_mode.cpp
  @brief    retains ::SDL_DisplayMode.
  @author   HRYKY
  @version  $Id: sdl_display_mode.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/sdl/sdl_display_mode.h"
#include "hryky/clear.h"
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
namespace
{
} // namespace "anonymous"
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
hryky::sdl::DisplayMode::DisplayMode()
	: raw_()
{
}
/**
  @brief copy constructor.
 */
hryky::sdl::DisplayMode::DisplayMode(this_type const & rhs)
	: hryky_copy_member(raw)
{
}
/**
  @brief move constructor.
 */
hryky::sdl::DisplayMode::DisplayMode(this_type && rhs)
	: hryky_move_member(raw)
{
}
/**
  @brief destructor.
 */
hryky::sdl::DisplayMode::~DisplayMode()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::sdl::DisplayMode::clear()
{
	hryky::clear(this->raw_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::sdl::DisplayMode::swap(this_type & src)
{
	::std::swap(this->raw_, src.raw_);
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
namespace sdl
{
namespace
{
} // namespace "anonymous"
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
