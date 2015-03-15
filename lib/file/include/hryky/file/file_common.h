/**
  @file     file_common.h
  @brief    The common definitions for hryky::file.
  @author   HRYKY
  @version  $Id: file_common.h 363 2014-07-10 10:46:29Z hryky.private@gmail.com $
 */
#ifndef FILE_COMMON_H_20140707192013472
#define FILE_COMMON_H_20140707192013472
#include "hryky/path.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace file
{
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace file
{
	/// creates the directory for file.
	bool mkdir(path_type const & path);

} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // FILE_COMMON_H_20140707192013472
// end of file
