/**
  @file         task_worker_observer_base.h
  @brief        notifies events in hryky::task::worker::Base.
  @author       HRYKY
  @version      $Id: task_worker_observer_base.h 347 2014-04-13 07:49:18Z hryky.private@gmail.com $
 */
#ifndef TASK_WORKER_OBSERVER_BASE_H_20130217001520677
#define TASK_WORKER_OBSERVER_BASE_H_20130217001520677
#include "hryky/pragma.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/without_new.h"
#include "hryky/intrusive_ptr_trait.h"
#include "hryky/intrusive_ptr.h"
//------------------------------------------------------------------------------
// disables warnings
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
	/// notifies events in hryky::task::worker::Base.
	class Base;

	/// intermediates to hryky::task::worker::observer::Base.
	template <typename ClientT>
	class Adapter;

} // namespace observer

	typedef IntrusivePtr<observer::Base> observer_type;

} // namespace worker

} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief notifies events in hryky::task::worker::Base.
 */
class hryky::task::worker::observer::Base :
	public IntrusivePtrTrait<>,
	public WithStreamOut<Base>,
	public WithSwap<Base>
{
public :

	typedef Base                this_type;
	typedef IntrusivePtrTrait<> intrusive_ptr_trait;
	typedef worker::Base        worker_type;

	/// default constructor.
	Base();

	/// instantiates with memory pool.
	Base(mempool::Ptr const & mempool);

	/// copy constructor.
	Base(this_type const &);

	/// move constructor.
	Base(this_type &&);

	/// destructor.
	~Base();

	/// assignment operator.
	hryky_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/**
	  @brief interchanges the each internal resources of two instances.
	 */
	void swap(this_type & src);
	
	/**
	  @brief callback function called just before the worker is attached.
	  @param worker is the attached worker.

	  - derived class must implement attach_impl().
	 */
	void on_attach(worker_type & worker);

	/**
	  @brief callback function called just before the worker is detached.
	  @param worker is the attached worker.

	  - derived class must implement detach_impl().
	 */
	void on_detach(worker_type & worker);

	/**
	  @brief callback function called just after some error occurs.

	  - derived class can implement error_impl().
	 */
	void on_error(worker_type & param);
	
protected :

private :

	virtual void on_attach_impl(worker_type &) = 0;
	virtual void on_detach_impl(worker_type &) = 0;
	virtual void on_error_impl(worker_type &) = 0;

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
hryky::task::worker::observer::Base::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("intrusive_ptr_trait")
		<< static_cast<intrusive_ptr_trait const>(*this);
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
#endif // TASK_WORKER_OBSERVER_BASE_H_20130217001520677
// end of file
