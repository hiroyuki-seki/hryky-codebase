/**
  @file     path_special.h
  @brief    retrieves the special path.
  @author   HRYKY
  @version  $Id: path_special.h 363 2014-07-10 10:46:29Z hryky.private@gmail.com $
 */
#ifndef PATH_SPECIAL_H_20140705165411370
#define PATH_SPECIAL_H_20140705165411370
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
	/// retrieves the directory for this application.
	path_type application();

	/// retrieves the path to executable.
	path_type executable();

	/// creates a temporary path.
	path_type tempfile();

} // namespace path
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // PATH_SPECIAL_H_20140705165411370
// end of file
