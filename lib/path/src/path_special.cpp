/**
  @file     path_special.cpp
  @brief    retrieves the special path.
  @author   HRYKY
  @version  $Id: path_special.cpp 363 2014-07-10 10:46:29Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/config.h"
#include "hryky/path/path_special.h"
#if HRYKY_PLATFORM_WINDOWS
#   include "hryky/path/path_win32_special.h"
#endif
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace path
{
namespace
{
#if HRYKY_PLATFORM_WINDOWS
	namespace impl = hryky::path::win32;
#endif
} // namespace "anonymous"
} // namespace path
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the directory for this application.
 */
hryky::path_type hryky::path::application()
{
	return impl::application();
}
/**
  @brief retrieves the path to executable.
 */
hryky::path_type hryky::path::executable()
{
	return impl::executable();
}
/**
  @brief creates a temporary path.
 */
hryky::path_type hryky::path::tempfile()
{
	return impl::tempfile();
}
//------------------------------------------------------------------------------
// defines static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace path
{
namespace
{
} // namespace "anonymous"
} // namespace path
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
