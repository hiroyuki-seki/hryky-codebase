/**
  @file         windows.h
  @brief        include files and macros for WIN32.
  @author       HRYKY
  @version      $Id: windows.h 362 2014-07-07 09:43:31Z hryky.private@gmail.com $
 */
#ifndef WINDOWS_H_20120911112707143
#define WINDOWS_H_20120911112707143
#include "hryky/config.h"
#include "hryky/pragma.h"
#if HRYKY_PLATFORM_WINDOWS

#pragma hryky_pragma_push_warning
#pragma warning(disable:4127)
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#pragma warning(disable:4514)
#pragma warning(disable:4548)
#pragma warning(disable:4571)
#pragma warning(disable:4625)
#pragma warning(disable:4626)
#pragma warning(disable:4640)
#pragma warning(disable:4668)
#pragma warning(disable:4820)
#pragma warning(disable:4917)

#if !defined(WINVER)
#    define WINVER               0x0601 // _WIN32_WINNT_WIN7
#endif
#if !defined(_WIN32_WINNT)
#    define _WIN32_WINNT         0x0601 // _WIN32_WINNT_WIN7
#endif
#if !defined(NTDDI_VERSION)
#    define NTDDI_VERSION        0x06010000 // NTDDI_WIN7
#endif

#include <windows.h>

#if NTDDI_VISTA <= NTDDI_VERSION
#    include <Knownfolders.h>
#endif

#if defined(NDEBUG)
#    include <stdlib.h>
#else
#    define _CRTDBG_MAP_ALLOC
#    include <stdlib.h>
#    include <crtdbg.h>
#endif
#include <shlobj.h>
#include "Shlwapi.h"
#include "Shellapi.h"
#pragma hryky_pragma_pop_warning

//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#if defined(interface)
#   undef interface
#endif
#if defined(max)
#   undef max
#endif
#if defined(min)
#   undef min
#endif
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HRYKY_PLATFORM_WINDOWS
#endif // WINDOWS_H_20120911112707143
// end of file
