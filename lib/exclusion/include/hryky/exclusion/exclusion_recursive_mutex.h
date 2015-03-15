/**
  @file         exclusion_recursive_mutex.h
  @brief        exclusion object : mutex which can be called recursively.
  @author       HRYKY
  @version      $Id: exclusion_recursive_mutex.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
  @addtogroup   exclusion_control
  @{
 */
#ifndef EXCLUSION_RECURSIVE_MUTEX_H_20120417235001659
#define EXCLUSION_RECURSIVE_MUTEX_H_20120417235001659
#if HRYKY_USE_BOOST_EXCLUSION
#   include "hryky/boost.h"
#else
#   include "hryky/std/std_mutex.h"
#endif
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace exclusion
{
	/// exclusion object : mutex which can be called recursively.
	class RecursiveMutex;

	/// represents a mutex.
	typedef RecursiveMutex recursive_mutex_type;
}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief exclusion object : mutex which can be called recursively.
 */
class hryky::exclusion::RecursiveMutex
{
public :

	typedef RecursiveMutex          this_type;

#if HRYKY_USE_BOOST_EXCLUSION
	typedef boost::recursive_mutex  raw_type;
#else
	typedef ::std::recursive_mutex    raw_type;
#endif

	/// default constructor.
	RecursiveMutex();

	/// suspends the current thread until the ownership is obtained.
	void lock();

	/// releases the ownership.
	void unlock();

	/// retrieves the mutable raw object.
	raw_type & raw();

protected :

private :

	hryky_delete_this_copy_constructor(RecursiveMutex);
	hryky_delete_this_copy_assign_op(RecursiveMutex);

	raw_type    raw_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace exclusion
{
}
}
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace exclusion
{
}
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // EXCLUSION_RECURSIVE_MUTEX_H_20120417235001659
/// @}
// end of file
