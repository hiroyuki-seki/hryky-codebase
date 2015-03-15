/**
  @file     sdl_opengl_version.cpp
  @brief    applies the preferred version of OpenGL.
  @author   HRYKY
  @version  $Id: sdl_opengl_version.cpp 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/sdl/sdl_opengl_version.h"
#include "hryky/sdl/sdl_common.h"
#include "hryky/clear.h"
#include "hryky/swap.h"
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
namespace opengl
{
namespace
{
	Version g_preferred;
	
} // namespace "anonymous"
} // namespace opengl
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
hryky::sdl::opengl::Version::Version()
	: major_(g_preferred.major())
	  , minor_(g_preferred.minor())
{
}
/**
  @brief constructs with the specified version.
 */
hryky::sdl::opengl::Version::Version(
	major_type const major, minor_type const minor)
	: major_(major)
	  , minor_(minor)
{
}
/**
  @brief copy constructor.
 */
hryky::sdl::opengl::Version::Version(this_type const & rhs)
	: hryky_copy_member(major)
	  , hryky_copy_member(minor)
{
}
/**
  @brief move constructor.
 */
hryky::sdl::opengl::Version::Version(this_type && rhs)
	: hryky_move_member(major)
	  , hryky_move_member(minor)
{
}
/**
  @brief destructor.
 */
hryky::sdl::opengl::Version::~Version()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::sdl::opengl::Version::clear()
{
	hryky::clear(this->major_);
	hryky::clear(this->minor_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::sdl::opengl::Version::swap(this_type & src)
{
	hryky_swap_member(major);
	hryky_swap_member(minor);
}
/**
  @brief applies the preferred version to the current context.
 */
void hryky::sdl::opengl::Version::prefer() const 
{
	g_preferred = *this;
}
/**
  @brief retrieves the major version.
 */
hryky::sdl::opengl::Version::major_type 
hryky::sdl::opengl::Version::major() const
{
	return this->major_;
}
/**
  @brief retrieves the minor version.
 */
hryky::sdl::opengl::Version::minor_type 
hryky::sdl::opengl::Version::minor() const
{
	return this->minor_;
}
/**
  @brief applies the configuration to SDL system.
 */
void hryky::sdl::opengl::Version::store() const
{
	g_preferred = *this;

	::SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_MAJOR_VERSION, this->major());
	::SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_MINOR_VERSION, this->minor());
}
/**
  @brief retrieves the configuration initialized by the SDL system.
 */
hryky::sdl::opengl::Version &
hryky::sdl::opengl::Version::load()
{
	major_type major;
	::SDL_GL_GetAttribute(
		SDL_GL_CONTEXT_MAJOR_VERSION, &major);
	
	major_type minor;
	::SDL_GL_GetAttribute(
		SDL_GL_CONTEXT_MINOR_VERSION, &minor);

	this->major_ = major;
	this->minor_ = minor;
	
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
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace sdl
{
namespace opengl
{
namespace
{
} // namespace "anonymous"
} // namespace opengl
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
