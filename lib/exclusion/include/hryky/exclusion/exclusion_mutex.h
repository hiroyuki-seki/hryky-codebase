/**
  @file         exclusion_mutex.h
  @brief        exclusion object : mutex.
  @author       HRYKY
  @version      $Id: exclusion_mutex.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
  @addtogroup   exclusion_control
  @{
 */
#ifndef EXCLUSION_MUTEX_H_20120414013909735
#define EXCLUSION_MUTEX_H_20120414013909735
#if HRYKY_USE_BOOST_EXCLUSION
#   include "hryky/boost.h"
#else
#   include "hryky/std/std_mutex.h"
#endif
#include "hryky/without_copy.h"
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
	/// exclusion object : mutex.
	class Mutex;

} // namespace exclusion
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief exclusion object : mutex.
 */
class hryky::exclusion::Mutex :
	private WithoutCopy
{
public :

	typedef Mutex           this_type;

#if HRYKY_USE_BOOST_EXCLUSION
	typedef boost::mutex    raw_type;
#else
	typedef ::std::mutex      raw_type;
#endif

	/// default constructor.
	Mutex();

	/// suspends the current thread until the ownership is obtained.
	void lock();

	/// releases the ownership.
	void unlock();

	/// retrieves the mutable raw object.
	raw_type & raw();

protected :

private :

	hryky_delete_this_copy_constructor(Mutex);
	hryky_delete_this_copy_assign_op(Mutex);

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
	/// represents a mutex.
	typedef Mutex                       mutex_type;

}
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // EXCLUSION_MUTEX_H_20120414013909735
/// @}
// end of file
