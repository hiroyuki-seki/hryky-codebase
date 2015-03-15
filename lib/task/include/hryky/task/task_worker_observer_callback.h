/**
  @file         task_worker_observer_callback.h
  @brief        invokes the callback function when the all workers have completed their tasks.
  @author       HRYKY
  @version      $Id: task_worker_observer_callback.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef TASK_WORKER_OBSERVER_CALLBACK_H_20130325155109327
#define TASK_WORKER_OBSERVER_CALLBACK_H_20130325155109327
#include "hryky/task/task_worker_observer_joinable.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename FunctorT
#define hryky_template_arg \
	FunctorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace task
{
namespace worker
{
namespace observer
{
	/**
	  invokes the callback function when the all workers have
	  completed their tasks.
	 */
	template <hryky_template_param>
	class Callback;

} // namespace observer
} // namespace worker
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief invokes the callback function when the all workers have completed
    their tasks.
 */
template <hryky_template_param>
class hryky::task::worker::observer::Callback :
	public Joinable
{
public :

	typedef Joinable base_type;
	typedef Callback<hryky_template_arg> this_type;

	/// constructor.
	Callback(FunctorT const & functor);

	/// destructor.
	~Callback();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

	hryky_delete_default_constructor(Callback);
	hryky_delete_this_copy_constructor(Callback);
	hryky_delete_this_copy_assign_op(Callback);

	/// notifies to detach the worker.
	virtual void on_detach_impl(worker_type &);

	FunctorT functor_;

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
  @brief constructor.
 */
template <hryky_template_param>
hryky::task::worker::observer::Callback<hryky_template_arg>::Callback(
	FunctorT const & functor)
	: base_type()
	  , functor_(functor)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::task::worker::observer::Callback<hryky_template_arg>::~Callback()
{
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::task::worker::observer::Callback<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->base_type::write_to(out);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief notifies to detach the worker.
 */
template <hryky_template_param>
void
hryky::task::worker::observer::Callback<hryky_template_arg>::on_detach_impl(
	worker_type &)
{
	if (0 == this->restore()) {
		this->functor_();
	}
}
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
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // TASK_WORKER_OBSERVER_CALLBACK_H_20130325155109327
// end of file
