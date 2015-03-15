/**
  @file         task_worker_base.h
  @brief        executes tasks.
  @author       HRYKY
  @version      $Id: task_worker_base.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
  @addtogroup   task
  @{
 */
#ifndef TASK_WORKER_BASE_H_20111119163724359
#define TASK_WORKER_BASE_H_20111119163724359
#include "hryky/without_copy.h"
#include "hryky/task/task_common.h"
#include "hryky/clock/clock_common.h"
#include "hryky/intrusive_ptr_trait.h"
#include "hryky/intrusive_ptr.h"
#include "hryky/exclusion/exclusion_variable.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace task
{
	class Conveyer;

/// modules to execute tasks on concurrent units.
namespace worker
{
	/// executes tasks
	class Base;

namespace observer
{
	class Base;
}
typedef IntrusivePtr<observer::Base> observer_type;

} // namespace worker

} // namespace task
namespace exclusion
{
	template < typename LockableT >
	class Lock;
} // namespace exclusion
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief    executes tasks.

  - The derived class has to implement run_impl().
  - The pause in the run_impl() affects the other workers in the same
    concurrent unit. The function which can block the process over a long
    duration should NOT be used in the run_impl().
 */
class hryky::task::worker::Base :
	public WithStreamOut<Base>,
	public IntrusivePtrTrait<>,
	private WithoutCopy
{
public :

	typedef Base                this_type;
	typedef IntrusivePtrTrait<> intrusive_ptr_trait;
	typedef Conveyer            conveyer_type;

	/// default constructor
	Base();

	/// constructor with mempool.
	Base(mempool::Ptr const & mempool);

	/// destrunctor
	~Base();

	/// releases the internal resources.
	void clear();

	/**
	  @brief attaches itself to the corresponding thread.
	  @param conveyer is the thread context disposing workers.
	  @return success or failure.
	  
	  - This function becomes effective immediately.
	  
	  @attention
	  - you must not call this function again while the worker
	    is attached to the concurrent unit.
	 */
	bool attach(conveyer_type & conveyer);

	/// notifies that some error occurs.
	void error();

	/// assigns a new observer.
	void observer(observer_type const & src);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :
	
	friend class Conveyer;

	hryky_delete_this_copy_constructor(Base);
	hryky_delete_this_copy_assign_op(Base);

	/// executes tasks
	virtual void run_impl() = 0;

	/**
	  @brief executes derived work.
	  @note
	  - This function is called from the concurrent unit.
	 */
	void run();

	/// notifies the detachment from conveyer.
	void detach();

	/// confirms whether the equality.
	bool operator==(this_type const & rhs) const;

	observer_type observer_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::task::worker::Base::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_pointer_member(observer);
	
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
namespace task
{
namespace worker
{
}
}
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // TASK_WORKER_BASE_H_20111119163724359
/// @}
// end of file
