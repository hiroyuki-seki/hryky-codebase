/**
  @file     clock_common.cpp
  @brief    The common definitions for hryky::clock.
  @author   HRYKY
  @version  $Id: clock_common.cpp 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clock/clock_common.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace clock
{
namespace
{
} // namespace "anonymous"
} // namespace clock
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the current clock.
 */
hryky::clock::time_point hryky::clock::now()
{
	return clock_type::now();
}
//------------------------------------------------------------------------------
// defines static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace clock
{
namespace
{
} // namespace "anonymous"
} // namespace clock
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
