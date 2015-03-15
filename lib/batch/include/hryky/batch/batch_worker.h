/**
  @file         batch_worker.h
  @brief        disposes plenty of same tasks.
  @author       HRYKY
  @version      $Id: batch_worker.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
  @addtogroup   task
  @{
 */
#ifndef BATCH_WORKER_H_20111122003830693
#define BATCH_WORKER_H_20111122003830693
#include "hryky/deque.h"
#include "hryky/exclusion/exclusion_lock.h"
#include "hryky/exclusion/exclusion_mutex.h"
#include "hryky/exclusion/exclusion_queue.h"
#include "hryky/flow/flow_facility.h"
#include "hryky/flow/flow_node_base.h"
#include "hryky/foreach.h"
#include "hryky/nullptr.h"
#include "hryky/mempool/mempool_base.h"
#include "hryky/mempool/mempool_global_registry.h"
#include "hryky/profiler/profiler_cumulate.h"
#include "hryky/task/task_common.h"
#include "hryky/task/task_worker_base.h"
#include "hryky/type_traits/add_const.h"
#include "hryky/type_traits/add_reference.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TaskT
#define hryky_template_arg \
	TaskT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace batch
{
	template <hryky_template_param>
	class Facility;
	
	/// disposes plenty of same tasks
	template <hryky_template_param>
	class Worker;
	
} // namespace batch
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief disposes plenty of same tasks.
 */
template <hryky_template_param>
class hryky::batch::Worker :
	public flow::node::Base,
	public WithStreamOut<Worker<hryky_template_arg> >
{
public :

	typedef flow::node::Base                        base_type;
	typedef Worker<TaskT>                           this_type;
	typedef Facility<TaskT>                         facility_type;
	typedef IntrusivePtr<this_type>                 instance_type;
	typedef TaskT                                   task_type;
	typedef TaskT                                   value_type;
	typedef typename AddPointer<TaskT>::type        pointer;
	typedef typename AddReference<TaskT>::type      reference;
	typedef typename AddConstPointer<TaskT>::type   const_pointer;
	typedef typename AddConstReference<TaskT>::type const_reference;
	typedef ::std::size_t                           size_type;
	
	/// constructor with memory pool.
	Worker(
		facility_type & facility,
		flow::facility_type & flow_facility,
		mempool_type const mempool);

	/// destructor
	~Worker();

	/**
	  allocates the buffer of tasks.
	  This function is not thread-safe. 
	 */
	bool reserve(size_type const capacity);

	/**
	  @brief retrieves own facility.
	  @return facility which distributes this instance.
	 */
	facility_type & facility();

	/**
	  @brief appends a task.
	  @param task is a unit of execution.
	 */
	bool append(const_reference task);

	/**
	  @brief appends multiple tasks.
	  @param    begin is the beginning of the container of tasks.
	  @param    end is the end of the container of tasks.
	  @attention
	  - the range of the array of tasks is [begin, end)
	 */
	template < typename InputIteratorT >
	bool append(InputIteratorT begin, InputIteratorT end);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// confirms whether there is no disposed task.
	bool empty() const;

protected :

	/// executes tasks
	virtual void run_impl();

private :

	typedef Vector<task_type>               tasks_type;
	typedef exclusion::Mutex                lockable_type;
	typedef exclusion::Lock<lockable_type>  lock_type;
	typedef exclusion::Queue<Deque<task_type> > tasks_queue_type;

	hryky_delete_default_constructor(Worker);
	hryky_delete_this_copy_constructor(Worker);
	hryky_delete_this_copy_assign_op(Worker);

	/// clears resources
	void clear();

	facility_type &     facility_;
	tasks_type          runnings_;
	tasks_queue_type    waitings_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
template <hryky_template_param>
hryky::batch::Worker<hryky_template_arg>::Worker(
	facility_type & facility,
	flow::facility_type & flow_facility,
	mempool_type const mempool)
	: base_type(flow_facility, mempool)
	  , facility_(facility)
	  , runnings_(mempool)
	  , waitings_(Deque<task_type>(mempool))
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::batch::Worker<hryky_template_arg>::~Worker()
{
}
/**
  @brief allocates the buffer of tasks.
 */
template <hryky_template_param>
bool hryky::batch::Worker<hryky_template_arg>::reserve(size_type const capacity)
{
	return this->runnings_.reserve(capacity);
}
/**
  @brief retrieves the facility.
 */
template <hryky_template_param>
hryky::batch::Facility<hryky_template_arg> &
hryky::batch::Worker<hryky_template_arg>::facility()
{
	return this->facility_;
}
/**
  @brief appends a task.
 */
template <hryky_template_param>
bool hryky::batch::Worker<hryky_template_arg>::append(const_reference task)
{
	if (!this->waitings_.push(task)) {
		hryky_log_err(
			"failed to append a task. "
			<< (json::writer()
				<< *this
				<< hryky_stream_denote(task)));
		return false;
	}
	
	return true;
}
/**
  @brief appends multiple tasks.
 */
template <hryky_template_param>
template < typename InputIteratorT >
bool hryky::batch::Worker<hryky_template_arg>::append(
	InputIteratorT begin, InputIteratorT end)
{
	if (!this->waitings_.push(begin, end)) {
		hryky_log_err(
			"failed to insert multiple tasks"
			<< (json::writer()
				<< *this
				<< hryky_stream_denote(begin)
				<< hryky_stream_denote(end)));
		return false;
	}

	return true;
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::batch::Worker<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->base_type::write_to(out);
}
/**
  @brief confirms whether there is no disposed task.
 */
template <hryky_template_param>
bool hryky::batch::Worker<hryky_template_arg>::empty() const
{
	return this->waitings_.empty();
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief executes tasks.
 */
template <hryky_template_param>
void hryky::batch::Worker<hryky_template_arg>::run_impl()
{
	if (!this->runnings_.empty()) {
		hryky_log_emerg(
			"This worker may be distributed to multiple conveyers.");
	}
	
	if (this->waitings_.empty()) {
		return;
	}

	size_t const grab_size = ::std::min<size_t>(
		this->runnings_.capacity(), this->waitings_.size());

	// brings out tasks from the buffer.
	this->waitings_.pop(
		::std::back_inserter(this->runnings_), grab_size);

	// disposes the tasks.
	this->runnings_.foreach([this](task_type & task) {
		hryky::dereference(task)(*this);
	});
	this->runnings_.resize(0);

	if (!this->waitings_.empty()) {
		// attaches self again in order to dispose the rest tasks.
		this->attach();
	}
	else {
		// forwards the flow of tasks.
		this->forward();

		// inactivates self.
		this->facility().inactivate(*this);
	}
}
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief clears resources.
 */
template <hryky_template_param>
void hryky::batch::Worker<hryky_template_arg>::clear()
{
	hryky::clear(this->runnings_);
	hryky::clear(this->waitings_);
	this->base_type::clear();
}
//------------------------------------------------------------------------------
// inline functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// function prototypes
//------------------------------------------------------------------------------
namespace hryky
{
namespace batch
{

} // namespace batch
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // BATCH_WORKER_H_20111122003830693
/// @}
// end of file
