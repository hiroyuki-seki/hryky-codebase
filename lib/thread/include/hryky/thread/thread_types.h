/**
  @file     thread_types.h
  @brief    defines types for the native thread.
  @author   HRYKY
  @version  $Id: thread_types.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef THREAD_TYPES_H_20140302092626060
#define THREAD_TYPES_H_20140302092626060
#if HRYKY_USE_BOOST_EXCLUSION
#   include "hryky/boost.h"
#else
#   include "hryky/std/std_thread.h"
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
#if HRYKY_USE_BOOST_EXCLUSION
	typedef boost::thread::id                   id_type;
	typedef boost::thread::native_handle_type   native_handle_type;
	namespace this_thread = boost::this_thread;
#else
	typedef ::std::thread::id                     id_type;
	typedef ::std::thread::native_handle_type     native_handle_type;
	namespace this_thread = ::std::this_thread;
#endif
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
} // namespace thread
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// global cuntion in external namespace
//------------------------------------------------------------------------------
#if HRYKY_USE_BOOST_EXCLUSION
namespace boost
#else
namespace std
#endif
{
	/**
	  @brief appends a thread::id to an output string-stream.
	 */
	template <typename StreamT>
	StreamT & operator<<(StreamT & lhs, thread::id const & rhs)
	{
		return lhs.write(hash<thread::id>()(rhs));
	}
} // namespace boost/std
#endif // THREAD_TYPES_H_20140302092626060
// end of file
