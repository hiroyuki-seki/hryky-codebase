/**
  @file         debug_common.h
  @brief        common definitions of debug module.
  @author       HRYKY
  @version      $Id: debug_common.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef DEBUG_COMMON_H_20120226094658074
#define DEBUG_COMMON_H_20120226094658074
#include "hryky/config.h"
#include "hryky/pragma.h"
#include "hryky/std/std_iostream.h"
#include "hryky/std/std_ostream.h"
#include "hryky/std/std_sstream.h"
#include "hryky/std/std_stdexcept.h"
#include "hryky/windows.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#if defined(NDEBUG)
#   define hryky_debug_break()
#   define hryky_debug_output(cstr)
#else
#   if HRYKY_PLATFORM_WINDOWS
#       define hryky_debug_break() \
	if (::IsDebuggerPresent()) { \
		::DebugBreak(); \
	}
#       define hryky_debug_output(cstr) \
	if (::IsDebuggerPresent()) { \
		::OutputDebugString(cstr); \
	} \
	else { \
		::std::cerr << cstr << ::std::endl; \
	}
#   else
#       define hryky_debug_break()      ///< @todo sends signal.
#       define hryky_debug_output(cstr) (::std::cerr << (cstr))
#   endif
#endif

/**
  @brief throws an exception with description.
  @param exception      is the name of function which instantiates
                        the exception.
  @param what           is Right-Hand-Side of stream".
  @param no_exception   is the statement invoked if
                        the exception mechanism is disabled.

  - @a message is assumed as the Right-Hand-Side of operator<<().
  - @a no_exception can be compilied literally.

  @code
  hryky_throw(
    ::std::exception, "output information" << hryky::endl, return false);
  @endcode

  If the exception mechanism is enabled, the above macro is parsed as below.

  @code
  hryky::ostream::String<hryky::String<> > os;
  os << "output information";
  throw ::std::exception(os.str().c_str());
  @endcode

  If the exception mechanism is disabled, the above macro is parsed as below.

  @code
  return false;
  @endcode
 */
#if HRYKY_USE_EXCEPTION
#   define hryky_throw(exception, what, no_exception) \
{ \
	hryky::ostream::String<hryky::String<> > os;\
	os << hryky_source_position << what;\
	hryky_debug_break(); \
	throw exception(os.str().c_str());\
}
#else // HRYKY_USE_EXCEPTION
#   define hryky_throw(exception, what, no_exception) \
{ \
	hryky_debug_break(); \
	no_exception; \
}
#endif // HRYKY_USE_EXCEPTION

#define hryky_throw_if(condition, exception, what, no_exception) \
	if (condition) { \
		hryky_throw(exception, what, no_exception); \
	}


#if HRYKY_PLATFORM_WINDOWS
#   define hryky_function   __FUNCTION__
#else
#   define hryky_function   __func__
#endif

#define hryky_source_position \
	hryky::debug::Source(__FILE__, hryky_function, __LINE__)

//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace debug
{
}
}
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// define global functions
//------------------------------------------------------------------------------
#endif // DEBUG_COMMON_H_20120226094658074
// end of file
