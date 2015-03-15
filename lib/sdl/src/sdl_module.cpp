/**
  @file     sdl_module.cpp
  @brief    manages the presence of the primary system of SDL.
  @author   HRYKY
  @version  $Id: sdl_module.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/sdl/sdl_common.h"
#include "hryky/sdl/sdl_module.h"
#include "hryky/json/json_writer.h"
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
	/// starts to use SDL.
	bool open();

	/// ends the use of SDL.
	void close();

	size_t g_opened = 0u;
	
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
hryky::sdl::Module::Module()
	: initialized_()
{
}
/**
  @brief destructor.
 */
hryky::sdl::Module::~Module()
{
	this->clear();
}
/**
  @brief releases the internal resources.
 */
void hryky::sdl::Module::clear()
{
	if (this->initialized_) {
		this->initialized_ = false;
		sdl::close();
	}
}
/**
  @brief starts using SDL without a subsystem.
 */
bool hryky::sdl::Module::reset()
{
	this->clear();

	if (!sdl::open()) {
		hryky_log_alert("failed to initialize the SDL.");
		return false;
	}

	this->initialized_ = true;

	return true;
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
/**
  @brief initializes SDL.
 */
bool open()
{
	if (0u < g_opened) {
		return true;
	}

	// SDL_SetMainReady();
	if (0 != ::SDL_Init(0)) {
		hryky_log_alert(
			"failed to initialize the SDL."
			<< (json::writer()
				<< "SDL_Error" << ::SDL_GetError()
			));
		return false;
	}

	{
		char const * const hint = "SDL_HINT_RENDER_DRIVER";
		char const * const value = "opengl";

		if (SDL_FALSE == ::SDL_SetHint(hint, value)) {
			hryky_log_warning(
				"failed to give a hint to SDL"
				<< (json::writer()
					<< "hint" << hint
					<< "value" << value));
		}
	}
	{
		char const * const hint = "SDL_HINT_RENDER_OPENGL_SHADERS";
		char const * const value = "1"; // enables shader.

		if (SDL_FALSE == ::SDL_SetHint(hint, value)) {
			hryky_log_warning(
				"failed to give a hint to SDL"
				<< (json::writer()
					<< "hint" << hint
					<< "value" << value));
		}
	}

	++g_opened;

	return true;
}
/**
  @brief ends the use of SDL.
 */
void close()
{
	if (0u == g_opened) {
		return;
	}
	
	if (0u == --g_opened) {
		::SDL_ClearHints();
		::SDL_Quit();
	}
}
} // namespace "anonymous"
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
