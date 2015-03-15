/**
  @file     sdl_window_context.cpp
  @brief    manages a Window GUI for SDL.
  @author   HRYKY
  @version  $Id: sdl_window_context.cpp 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/raii.h"
#include "hryky/sdl/sdl_window_context.h"
#include "hryky/sdl/sdl_window_color.h"
#include "hryky/sdl/sdl_opengl_context.h"
#include "hryky/sdl/sdl_opengl_version.h"
#include "hryky/json/json_writer.h"
#include "hryky/is_null.h"
#include "hryky/clear.h"
#include "hryky/mempool.h"
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
hryky::sdl::window::Context::Context()
	: raw_()
	  , flags_()
{
	if (!this->reset()) {
		hryky_log_err(
			"failed to initialize SDL Window by the default parameters.");
		return;
	}
}
/**
  @brief creates an instance with the parameters.
 */
hryky::sdl::window::Context::Context(Reset const & param)
{
	if (!this->reset(param)) {
		hryky_log_err(
			"failed to initialize a SDL Window with parameters.");
		return;
	}
}
/**
  @brief move constructor.
 */
hryky::sdl::window::Context::Context(this_type && rhs)
	: hryky_move_member(raw)
	  , hryky_move_member(flags)
{
	hryky::clear(rhs.raw_);
	hryky::clear(rhs.flags_);
}
/**
  @brief destructor.
 */
hryky::sdl::window::Context::~Context()
{
	this->clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::sdl::window::Context::swap(this_type & src)
{
	hryky_swap_member(raw);
	hryky_swap_member(flags);
}
/**
  @brief displaies this window at fullscreen mode.
 */
bool hryky::sdl::window::Context::fullscreen(
	Fullscreen const & param)
{
	if (hryky_is_null(this->raw_)) {
		hryky_log_err("The window hasn't been created.");
		return false;
	}
	
	if (this->flag_.fullscreen_) {
		::SDL_SetWindowFullscreen(this->raw_, SDL_FALSE);
		this->flag_.fullscreen_ = false;
	}

	SDL_DisplayMode const display_mode =
	{
		param.format,
		param.width,
		param.height,
		param.refresh_rate,
		0, // driverdata
	};

	if (0 != ::SDL_SetWindowDisplayMode(this->raw_, &display_mode)) {
		hryky_log_err(
			"failed to get the closest display mode"
			<< (json::writer()
				<< "SDL_error" << ::SDL_GetError()
				// << "mode" << display_mode
				));
		return false;
	}

	if (0 != ::SDL_SetWindowFullscreen(this->raw_, SDL_TRUE)) {
		hryky_log_err(
			"failed to set the fullscreen window"
			<< (json::writer()
				<< "SDL_error" << ::SDL_GetError()
				// << "mode" << display_mode
				));
		return false;
	}

	this->flag_.fullscreen_ = true;
	
	return true;
}
/**
  @brief reflects the result of rendering to the window.
 */
void hryky::sdl::window::Context::update() const
{
	if (this->is_null() || !this->flag_.use_opengl_) {
		return;
	}
	::SDL_GL_SwapWindow(this->raw_);
}
/**
  @brief retrieves the raw window.
 */
hryky::sdl::window::Context::raw_type
hryky::sdl::window::Context::raw() const
{
	return this->raw_;
}
/**
  @brief associates a context of OpenGL to this window.
 */
bool hryky::sdl::window::Context::opengl_context(
	sdl::opengl::Context const & context) const
{
	if (0 != ::SDL_GL_MakeCurrent(this->raw(), context.raw())) {
		hryky_log_err(
			"failed to associate OpenGL context to window"
			<< (json::writer()
				<< "openglContext" << context
				<< "SDLError" << ::SDL_GetError()
				<< "openGLVersion" << opengl::Version().load()
				));
		return false;
	}

	return true;
}
/**
  @brief confirms whether this instance is invalid.
 */
bool hryky::sdl::window::Context::is_null() const
{
	return hryky_is_null(this->raw_);
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
void hryky::sdl::window::Context::clear()
{
	if (this->flag_.fullscreen_) {
		::SDL_SetWindowFullscreen(this->raw_, SDL_FALSE);
		this->flag_.fullscreen_ = false;
	}

	if (!hryky_is_null(this->raw_)) {
		::SDL_DestroyWindow(this->raw_);
		this->raw_ = hryky_nullptr;
	}
}
/**
  @brief rebuilds the internal resources with the default parameters.
 */
bool hryky::sdl::window::Context::reset()
{
	SDL_DisplayMode desktop_mode;
	if (0 != SDL_GetDesktopDisplayMode(0, &desktop_mode)) {
		return false;
	}
	
	Reset const param = {
		"SDL Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		static_cast<int>(desktop_mode.w * 0.75f), // width
		static_cast<int>(desktop_mode.h * 0.75f), // height
		true, // use_opengl
		false, // hidden
	};
	
	return this->reset(param);
}
/**
  @brief releases the existing resources and creates new resources.
 */
bool hryky::sdl::window::Context::reset(Reset const & param)
{
	/**
	  @attention
	  - This function call is needed in order to use higher version of OpenGL.
	 */
	::SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	Color const color;
	color.store();

	opengl::Version const gl_version;
	gl_version.store();

	hryky_log_notice(
		"SDL Window is initialized with :"
		<< (json::writer()
			<< "openGLVersion" << gl_version
			<< "color" << color
			));

	::SDL_WindowFlags const window_flags
		= static_cast< ::SDL_WindowFlags >(
			(param.use_opengl ? SDL_WINDOW_OPENGL : 0)
			| (param.hidden ? SDL_WINDOW_HIDDEN : 0));
	
	// creates a window
	raw_type const raw = ::SDL_CreateWindow(
		param.caption,
		param.x,
		param.y,
		param.width,
		param.height,
		window_flags);
	if (hryky_is_null(raw)) {
		hryky_log_err(
			"failed to create window"
			<< (json::writer()
				<< "sdlError" << ::SDL_GetError()
				<< "caption" << param.caption
				<< "x" << param.x
				<< "y" << param.y
				<< "width" << param.width
				<< "height" << param.height
				<< "flags" << window_flags
				));
		return false;
	}
	AutoFunc1<void, raw_type, SDL_DestroyWindow> delete_raw(raw);

	this->flag_.use_opengl_ = param.use_opengl;
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
