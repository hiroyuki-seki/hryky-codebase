/**
  @file         thread_common.h
  @brief        common definitions of thread module.
  @author       HRYKY
  @version      $Id: thread_common.h 335 2014-03-16 03:00:56Z hryky.private@gmail.com $
 */
#ifndef THREAD_COMMON_H_20120218180633421
#define THREAD_COMMON_H_20120218180633421

#if HRYKY_PLATFORM_WINDOWS
#   include "hryky/thread/thread_common.win32.h"

#elif HRYKY_PLATFORM_POSIX

#endif
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace thread
{
} // namespace thread
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
namespace thread
{
	/// retrieves the number of concurrent units on this hardware.
	raw_processor_id_type hardware_concurrency();

} // namespace thread
} // namespace hryky
//------------------------------------------------------------------------------
// define global functions
//------------------------------------------------------------------------------
#endif // THREAD_COMMON_H_20120218180633421
// end of file
