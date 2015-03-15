/**
  @file     sdl_opengl_context.cpp
  @brief    manages the context of OpenGL in SDL.
  @author   HRYKY
  @version  $Id: sdl_opengl_context.cpp 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/sdl/sdl_opengl_context.h"
#include "hryky/sdl/sdl_opengl_version.h"
#include "hryky/sdl/sdl_window_context.h"
#include "hryky/sdl/sdl_window_color.h"
#include "hryky/raii/autofunc.h"
#include "hryky/json/json_writer.h"
#include "hryky/stream.h"
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
  @brief creates an instance associating with the window.
 */
hryky::sdl::opengl::Context::Context(window_type const & window)
	: raw_()
{
	if (!this->reset(window)) {
		hryky_log_err(
			"failed to create OpenGL Context by SDL.");
		return;
	}
}
/**
  @brief move constructor.
 */
hryky::sdl::opengl::Context::Context(this_type && rhs)
	: hryky_move_member(raw)
{
	rhs.raw_ = 0;
}
/**
  @brief destructor.
 */
hryky::sdl::opengl::Context::~Context()
{
	this->clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::sdl::opengl::Context::swap(this_type & src)
{
	hryky_swap_member(raw);
}
/**
  @brief retrieves the raw resource.
 */
hryky::sdl::opengl::Context::raw_type
hryky::sdl::opengl::Context::raw() const
{
	return this->raw_;
}
/**
  @brief confirms whether this instance is invalid.
 */
bool hryky::sdl::opengl::Context::is_null() const
{
	return 0 == this->raw_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief releases the internal resources.
 */
void hryky::sdl::opengl::Context::clear()
{
	if (0 != this->raw_) {
		::SDL_GL_DeleteContext(this->raw_);
		this->raw_ = 0;
	}
}
/**
  @brief provisions the internal resources.
 */
bool hryky::sdl::opengl::Context::reset(window_type const & window)
{
	this->clear();

	window::Context::raw_type const raw_window = window.raw();
	
	// associates the OpenGL context to the window.
	raw_type const raw = ::SDL_GL_CreateContext(raw_window);
	AutoFunc1<void, raw_type, SDL_GL_DeleteContext>
		delete_raw(raw);

	if (0 == raw) {
		hryky_log_err(
			"failed to associate OpenGL context to window"
			<< (json::writer()
				<< "opengl_context" << raw
				<< "SDL_error" << ::SDL_GetError()
				));
		return false;
	}

	Version const version(Version().load());
	version.prefer();
	
	window::Color const color(window::Color().load());
	color.prefer();

	// confirms actual version of OpenGL
	hryky_log_notice(
		"OpenGL context is initialized with:"
		<< (json::writer()
			<< "openGLVersion" << version
			<< "color" << color
			));

	this->raw_ = raw;

	delete_raw.disable();
	
	return true;
}
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
