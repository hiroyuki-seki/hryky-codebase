/**
  @file     sdl_common.h
  @brief    common definition to utilize SDL.
  @author   HRYKY
  @version  $Id: sdl_common.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef SDL_COMMON_H_20130504144042278
#define SDL_COMMON_H_20130504144042278
#include "hryky/config.h"
#include "hryky/pragma.h"
#include "hryky/windows.h"
#include "hryky/gl.h"

#if HRYKY_USE_SDL
#   pragma hryky_pragma_push_warning
#       pragma hryky_pragma_disable_warning_undef
#       pragma hryky_pragma_disable_warning_padded
#       include <SDL/SDL.h>

#       ifdef WIN32_LEAN_AND_MEAN
            // WIN32_LEAN_AND_MEAN is forcibly defined in SDL_opengl.h
#           undef WIN32_LEAN_AND_MEAN
#       endif
#       include <SDL/SDL_opengl.h>
#   pragma hryky_pragma_pop_warning
#endif // HRYKY_USE_SDL
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace sdl
{
} // namespace sdl
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
namespace sdl
{
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SDL_COMMON_H_20130504144042278
// end of file
