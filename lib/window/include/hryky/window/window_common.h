/**
  @file         window_common.h
  @brief        common definitions for window module.
  @author       HRYKY
  @version      $Id: window_common.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef WINDOW_COMMON_H_20120203173009395
#define WINDOW_COMMON_H_20120203173009395
#include "hryky/geometry/geometry_rect.h"
#include "hryky/coord/coord_cartesian2.h"
#include "hryky/string.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace window
{
	/// represents the region of a window
	typedef geometry::Rect< coord::Cartesian2<int32_t> > region_type;

	/// represents the caption of window
	typedef String<> caption_type;

	/// represents the refresh rate of display.
	typedef uint16_t refresh_rate_type;

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
#endif // WINDOW_COMMON_H_20120203173009395
// end of file
