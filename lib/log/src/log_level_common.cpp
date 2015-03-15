/**
  @file         log_level_common.cpp
  @brief        common defintions for hryky::log::level.
  @author       HRYKY
  @version      $Id: log_level_common.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/log/log_level_common.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace log
{
namespace level
{
	LiteralString<> const g_tokens[Kind::num] = {
		LiteralString<>("debug"),
		LiteralString<>("info"),
		LiteralString<>("notice"),
		LiteralString<>("warning"),
		LiteralString<>("err"),
		LiteralString<>("crit"),
		LiteralString<>("alert"),
		LiteralString<>("emerg"),
	};
	
namespace
{
} // namespace "anonymous"
} // namespace level
} // namespace log
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace log
{
namespace level
{
namespace
{
} // namespace "anonymous"
} // namespace level
} // namespace log
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
