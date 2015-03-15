/**
  @file         exclusion_cond.h
  @brief        exclusion object : condition variable.
  @author       HRYKY
  @version      $Id: exclusion_cond.h 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
  @addtogroup   exclusion_control
  @{
 */
#ifndef EXCLUSION_COND_H_20120414021923763
#define EXCLUSION_COND_H_20120414021923763
#if HRYKY_USE_BOOST_EXCLUSION
#   include "hryky/boost.h"
#else
#   include "hryky/std/std_condition_variable.h"
#endif
#include "hryky/exclusion/exclusion_mutex.h"
#include "hryky/exclusion/exclusion_common.h"
#include "hryky/without_copy.h"
#include "hryky/with_stream_out.h"
#include "hryky/raii/scoped_increment.h"
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
	/// exclusion object : condition variable.
	class Cond;
}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief exclusion object : condition variable.
 */
class hryky::exclusion::Cond :
	public WithStreamOut<Cond>,
	private WithoutCopy
{
public :

	typedef Cond this_type;

	/// default constructor.
	Cond();

	/// destructor.
	~Cond();

	/// releases the internal resources.
	void clear();

	/// invokes the waiting threads which has called wait.
	void notify();

	/**
	  @brief    suspends the current thread until the other thread notifies
	            through this object.
	 */
	template < typename LockT >
	void join(LockT & lock);

	/**
	  @brief    suspends the current thread until other thread notifies
	            through this object.

	  If the specified time elapsed while the thread is suspending,
	  this function returns false.
	 */
	template < typename LockT, typename DurationT >
	bool join(LockT & lock, DurationT const & duration);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

#if HRYKY_USE_BOOST_EXCLUSION
	typedef boost::condition_variable raw_type;
#else
	typedef ::std::condition_variable   raw_type;
#endif

	hryky_delete_this_copy_constructor(Cond);
	hryky_delete_this_copy_assign_op(Cond);

	/// invokes the all waiting threads which have called this object.
	void notify_all();

	/// invokes the one waiting thread which has called join().
	void notify_one();

	raw_type    raw_;
	size_t      waiting_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace exclusion
{
} // namespace exclusion
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief    suspends the current thread until other thread notifies
            through this object.
 */
template <typename LockT>
void hryky::exclusion::Cond::join(LockT & lock)
{
	auto const increment = scoped_increment(this->waiting_);
	
	this->raw_.wait(lock.raw());
}
/**
  @brief    suspends the current thread until other thread notifies
            through this object.

  If the specified time elapsed while the thread is suspending,
  this function returns false.
 */
template <typename LockT, typename DurationT>
bool hryky::exclusion::Cond::join(
	LockT & lock, DurationT const & duration)
{
	auto const increment = scoped_increment(this->waiting_);
	
#if HRYKY_USE_BOOST_EXCLUSION
	bool const result = this->raw_.timed_wait(
		lock.raw(),
		boost::posix_time::milliseconds(
			chrono::milliseconds(duration).count()));
#else
	bool const result = ::std::cv_status::no_timeout ==
		this->raw_.wait_for(lock.raw(), duration.std());
#endif
	return result;
}
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::exclusion::Cond::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(waiting);
	return out;
}
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
	/// represents a condition variable.
	typedef Cond cond_type;

}
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // EXCLUSION_COND_H_20120414021923763
/// @}
// end of file
