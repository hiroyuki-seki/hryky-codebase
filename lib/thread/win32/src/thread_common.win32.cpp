/**
  @file     thread_common.win32.cpp
  @brief    The common definitions for hryky::thread on the Win32 platform.
  @author   HRYKY
  @version  $Id: thread_common.win32.cpp 347 2014-04-13 07:49:18Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/windows.h"
#include "hryky/thread/thread_common.h"
#include "hryky/json/json_writer.h"
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
  @brief associates the thread with a particular CPU.
 */
bool hryky::thread::set_affinity(
	native_handle_type const native_handle,
	raw_processor_id_type const processor_id)
{
#if 1 // uses ::SetThreadIdealProcessor
	DWORD const ret = ::SetThreadIdealProcessor(native_handle, processor_id);

	if (static_cast<DWORD>(-1) == ret) {
		hryky_log_warning(
			"failed to set an ideal processor for a thread"
			<< (json::writer()
				<< "native_handle" << native_handle
				<< "processor_id" << processor_id
				<< "native error code" << ::GetLastError()));
		return false;
	}
	else {
		hryky_log_debug(
			"sets an ideal processor for a thread"
			<< (json::writer()
				<< "native_handle" << native_handle
				<< "from" << ret
				<< "to" << processor_id));
	}

#else // uses ::SetThreadAffinityMask
	DWORD mask = 1 << processor_id;

	DWORD_PTR const ret = ::SetThreadAffinityMask(
		native_handle, reinterpret_cast<DWORD_PTR>(&mask));

	if (static_cast<DWORD>(0) == ret) {
		hryky_log_warning(
			"failed to set a thread affinity mask for a thread"
			<< (json::writer()
				<< "native_handle" << native_handle
				<< "processor_id" << processor_id
				<< "native error code" << ::GetLastError()));
		return false;
	}
	else {
		hryky_log_debug(
			"sets a thread affinity mask for a thread"
			<< (json::writer()
				<< "native_handle" << native_handle
				<< "from" << ret
				<< "to" << mask));
	}
#endif
	return true;
}
//------------------------------------------------------------------------------
// defines static functions
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
