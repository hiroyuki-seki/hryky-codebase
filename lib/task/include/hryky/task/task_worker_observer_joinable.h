/**
  @file         task_worker_observer_joinable.h
  @brief        observes the end of the process of tasks.
  @author       HRYKY
  @version      $Id: task_worker_observer_joinable.h 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
 */
#ifndef TASK_WORKER_OBSERVER_JOINABLE_H_20130317110336127
#define TASK_WORKER_OBSERVER_JOINABLE_H_20130317110336127
#include "hryky/exclusion/exclusion_counter.h"
#include "hryky/task/task_worker_observer_base.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// disable warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_virtual_destructor
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
namespace worker
{
	class Base;
namespace observer
{
	/// observes the end of the process of tasks.
	class Joinable;

} // namespace observer
} // namespace worker
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief observes the end of the process of tasks.
 */
class hryky::task::worker::observer::Joinable :
	public Base,
	public WithStreamOut<Joinable>,
	public WithSwap<Joinable>
{
public :

	typedef Base                        base_type;
	typedef Joinable                    this_type;
	typedef worker::Base                worker_type;
	typedef exclusion::duration_type    duration_type;

	/// default constructor.
	Joinable();

	/// instantiates with memory pool.
	Joinable(mempool::Ptr const & mempool);

	/// copy constructor.
	Joinable(this_type const &);

	/// move constructor.
	Joinable(this_type &&);

	/// destructor.
	~Joinable();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/**
	  @brief    suspends the current thread until all workers are detached
	            from concurrent units.
	  @return   success or failure.

	   The caller context might be suspended for long periods. There might be
	  deadlock if exclusion controls are not used appropriately. <em>Derived
	  instance MUST call this method before implementations of workers are
	  destructed.</em>

	    The attachment and detachment of the worker is notified through the
	  observer of the worker. To use join(), the worker must be attached this
	  observer before the worker begins to execute on the concurrent unit.
	 */
	void join();

	/**
	  waits until the all distributed workers finish their tasks or the
	  specified duration has elapsed.
	 */
	bool join(duration_type const & duration);

	/**
	  confirmes whether the all distributed workers completed their tasks.

	  This function doesn't block the current context unlike join().
	 */
	bool completed() const;

protected :

	/// increments the number of attached workers.
	size_t acquire();

	/// decrements the number of attached workers.
	size_t restore();

private :

	typedef exclusion::Counter<> counter_type;

	/// notifies to attach a new worker.
	virtual void on_attach_impl(worker_type &);

	/// notifies to detach the attached worker.
	virtual void on_detach_impl(worker_type &);

	/// notifies an error occurred in the attached worker.
	virtual void on_error_impl(worker_type &);

	counter_type working_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace task
{
namespace worker
{
namespace observer
{
} // namespace observer
} // namespace worker
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::task::worker::observer::Joinable::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("base")
		<< static_cast<base_type const>(*this);
	hryky_write_member(working);
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
namespace observer
{
} // namespace observer
} // namespace worker
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // TASK_WORKER_OBSERVER_JOINABLE_H_20130317110336127
// end of file
