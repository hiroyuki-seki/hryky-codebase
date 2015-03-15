/**
  @file     opengl_common_internal.h
  @brief    The common definition for the internal use.
  @author   HRYKY
  @version  $Id: opengl_common_internal.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef OPENGL_COMMON_INTERNAL_H_20140105103442107
#define OPENGL_COMMON_INTERNAL_H_20140105103442107
#include "hryky/sdl/sdl_common.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_get_gl_proc(name) \
	if (!hryky::opengl::get_proc(this->##name##_, #name)) { \
		return false; \
	}
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace opengl
{
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace opengl
{
	/// retrieves an OpenGL API.
	template < typename ValueT >
	bool get_proc(ValueT & dest, char const * name);

} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves an OpenGL API.
 */
template < typename ValueT >
bool hryky::opengl::get_proc(ValueT & dest, char const * name)
{
#if HRYKY_USE_SDL
	if (hryky_is_null(
		dest = reinterpret_cast<ValueT>(::SDL_GL_GetProcAddress(name)))) {
		hryky_log_err(
			"failed to get the address of OpenGL API " << name);
		return false;
	}
	return true;
#else // HRYKY_USE_SDL
	return false;
#endif // HRYKY_USE_SDL
}
#endif // OPENGL_COMMON_INTERNAL_H_20140105103442107
// end of file
