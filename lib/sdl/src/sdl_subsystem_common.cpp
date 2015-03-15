/**
  @file     sdl_subsystem_common.cpp
  @brief    common definition of SDL subsystem.
  @author   HRYKY
  @version  $Id: sdl_subsystem_common.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/foreach.h"
#include "hryky/sdl/sdl_common.h"
#include "hryky/sdl/sdl_subsystem_common.h"
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
namespace subsystem
{
	LiteralString<> const g_tokens[Kind::num] = {
		LiteralString<>("timer"),
		LiteralString<>("audio"),
		LiteralString<>("video"),
		LiteralString<>("joystick"),
		LiteralString<>("haptic"),
	};

namespace
{
} // namespace "anonymous"
} // namespace subsystem
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief converts the subsystem::flag_type to the raw SDL flag.
 */
hryky::sdl::subsystem::raw_flag_type
hryky::sdl::subsystem::raw_flag_of(flag_type const & flag)
{
	raw_flag_type sdl_flag = 0;
	raw_flag_type const sdl_each_flag[flag_type::kind_type::num] = {
		SDL_INIT_TIMER,
		SDL_INIT_AUDIO,
		SDL_INIT_VIDEO,
		SDL_INIT_JOYSTICK,
		SDL_INIT_HAPTIC,
	};

	flag.foreach_at([&sdl_flag, &sdl_each_flag](
		flag_type::value_type const flag, flag_type::size_type const index) {
		sdl_flag |= (flag ? sdl_each_flag[index] : 0);
	});
	return sdl_flag;
}
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace sdl
{
namespace subsystem
{
namespace
{
} // namespace "anonymous"
} // namespace subsystem
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
