/**
  @file         win32_common.h
  @brief        common utilities for win32.
  @author       HRYKY
  @version      $Id: win32_common.h 360 2014-07-05 06:59:57Z hryky.private@gmail.com $
 */
#ifndef WIN32_COMMON_H_20130209095950083
#define WIN32_COMMON_H_20130209095950083
#include "hryky/string.h"
#include "hryky/windows.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace win32
{
} // namespace win32
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
namespace win32
{
	/// retrieves the string representing the last error of Win32 API.
	hryky::String<> last_error();

	/// converts the ID of error to string.
	hryky::String<> format_error(DWORD const id);

} // namespace win32
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // WIN32_COMMON_H_20130209095950083
// end of file
