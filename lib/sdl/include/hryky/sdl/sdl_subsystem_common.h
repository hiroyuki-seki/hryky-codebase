/**
  @file     sdl_subsystem_common.h
  @brief    common definition of SDL subsystem.
  @author   HRYKY
  @version  $Id: sdl_subsystem_common.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef SDL_SUBSYSTEM_COMMON_H_20130512163736359
#define SDL_SUBSYSTEM_COMMON_H_20130512163736359
#include "hryky/literal_string.h"
#include "hryky/flag.h"
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
namespace subsystem
{
	struct Kind {
		enum Raw {
			timer,
			audio,
			video,
			joystick,
			haptic,
			num,
		};
	};
	
	extern LiteralString<> const g_tokens[Kind::num];

	typedef Flag<
		Kind,
		Kind::num,
		LiteralString<>,
		subsystem::g_tokens> flag_type;

	typedef uint32_t raw_flag_type;

} // namespace subsystem
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
namespace subsystem
{
	/// converts the flag_type to the raw SDL flag.
	raw_flag_type raw_flag_of(flag_type const & flag);

} // namespace subsystem
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SDL_SUBSYSTEM_COMMON_H_20130512163736359
// end of file
