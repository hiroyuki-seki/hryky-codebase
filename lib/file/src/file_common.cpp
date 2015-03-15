/**
  @file     file_common.cpp
  @brief    The common definitions for hryky::file.
  @author   HRYKY
  @version  $Id: file_common.cpp 363 2014-07-10 10:46:29Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/file/file_common.h"
#include "hryky/log.h"
#include "hryky/json.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace file
{
namespace
{
} // namespace "anonymous"
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates the directory for file.
 */
bool hryky::file::mkdir(path_type const & path)
{
	path_type dir = path;
	dir << "../";
	if (!dir.mkdir()) {
		hryky_log_err(
			"failed to create a directory for "
			<< (json::writer() << hryky_stream_denote(path)));
		return false;
	}
	return true;
}
//------------------------------------------------------------------------------
// defines static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace file
{
namespace
{
} // namespace "anonymous"
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
