/**
  @file     thread_common.win32.h
  @brief    The common definitions for hryky::thread on the Win32 platform.
  @author   HRYKY
  @version  $Id: thread_common.win32.h 335 2014-03-16 03:00:56Z hryky.private@gmail.com $
 */
#ifndef THREAD_COMMON_WIN32_H_20140302092232057
#define THREAD_COMMON_WIN32_H_20140302092232057
#include "hryky/thread/thread_types.h"
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
	typedef uint32_t raw_processor_id_type;
	
} // namespace thread
} // namespace hryky
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
	/// associates the thread with a particular CPU.
	bool set_affinity(
		native_handle_type const native_handle,
		raw_processor_id_type const processor_id);

} // namespace thread
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // THREAD_COMMON_WIN32_H_20140302092232057
// end of file
