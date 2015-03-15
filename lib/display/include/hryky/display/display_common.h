/**
  @file         display_common.h
  @brief        common definitions of display module.
  @author       HRYKY
  @version      $Id: display_common.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef DISPLAY_COMMON_H_20120128123149188
#define DISPLAY_COMMON_H_20120128123149188
#include "hryky/coord/coord_cartesian2.h"
#include "hryky/pixel/pixel_format.h"
#include "hryky/std/std_cstdint.h"
#include "hryky/string.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace display
{
	class Driver;
	class Screen;
	class Mode;

	/// search a display configuration.
	class Traverse;

	/// distinguishes video drivers.
	typedef size_t driver_id_type;
	
	/// distinguishes video screen.
	typedef size_t screen_id_type;

	/// distinguishes video mode.
	typedef size_t mode_id_type;

	/// represents the refresh rate of display
	typedef uint16_t refresh_rate_type;

	/// represents the kind of video drivers.
	typedef String<> driver_name_type;

	/// represents the size of the region of display.
	typedef coord::Cartesian2<size_t> size_type;

	/// represents the pixel format of display.
	typedef pixel::Format format_type;

	/// represents invalid driver.
	driver_id_type const g_invalid_driver_id = static_cast<driver_id_type>(-1);

	/// represents invalid display.
	screen_id_type const g_invalid_screen_id = static_cast<screen_id_type>(-1);

}
}
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// define global functions
//------------------------------------------------------------------------------
#endif // DISPLAY_COMMON_H_20120128123149188
// end of file
