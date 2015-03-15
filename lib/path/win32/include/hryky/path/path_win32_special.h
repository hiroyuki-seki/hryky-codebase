/**
  @file     path_win32_special.h
  @brief    retrieves the special path on Windows Platform.
  @author   HRYKY
  @version  $Id: path_win32_special.h 363 2014-07-10 10:46:29Z hryky.private@gmail.com $
 */
#ifndef PATH_WIN32_SPECIAL_H_20140705165805373
#define PATH_WIN32_SPECIAL_H_20140705165805373
#include "hryky/path/path_entity.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace path
{
namespace win32
{
} // namespace win32
} // namespace path
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace path
{
namespace win32
{
	/// retrieves the directory for this application.
	path_type application();

	/// retrieves the path to executable.
	path_type executable();

	/// creates a temporary path.
	path_type tempfile();

} // namespace win32
} // namespace path
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // PATH_WIN32_SPECIAL_H_20140705165805373
// end of file
