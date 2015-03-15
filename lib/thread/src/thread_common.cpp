/**
  @file         thread_common.cpp
  @brief        common definitions of hryky::thread.
  @author       HRYKY
  @version      $Id: thread_common.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/thread/thread_common.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace thread
{
namespace
{
} // namespace "anonymous"
} // namespace thread
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the number of concurrent units on this hardware.
 */
hryky::thread::raw_processor_id_type
hryky::thread::hardware_concurrency()
{
#if HRYKY_USE_BOOST_EXCLUSION
	return static_cast<raw_processor_id_type>(
		boost::thread::hardware_concurrency());
#else
	return static_cast<raw_processor_id_type>(
		::std::thread::hardware_concurrency());
#endif
}
//------------------------------------------------------------------------------
// global functions in external namespace
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace thread
{
namespace
{
} // namespace "anonymous"
} // namespace thread
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
