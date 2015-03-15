/**
  @file         batch_facility.h
  @brief        manages workers which executes plenty of same tasks.
  @author       HRYKY
  @version      $Id: batch_facility.h 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
  @addtogroup   task
  @{
 */
#ifndef BATCH_FACILITY_H_20111124003850693
#define BATCH_FACILITY_H_20111124003850693
#include "hryky/exclusion/exclusion_stack.h"
#include "hryky/flow/flow_facility.h"
#include "hryky/flow/flow_node_join.h"
#include "hryky/foreach.h"
#include "hryky/intrusive_ptr.h"
#include "hryky/nullptr.h"
#include "hryky/std/std_iterator.h"
#include "hryky/type_traits/as_parameter.h"
#include "hryky/with_stream_out.h"
#include "hryky/without_copy.h"
#include "hryky/is_null.h"
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
	/// manages workers which executes plenty of same tasks
	template <hryky_template_param>
	class Facility;

	template <hryky_template_param>
	class Worker;
}

namespace task
{
	class Conveyer;
} // namespace task

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief manages workers which executes plenty of same tasks.
 */
template <hryky_template_param>
class hryky::batch::Facility :
	public WithStreamOut<Facility<hryky_template_arg> >,
	private WithoutCopy
{
public :

	typedef TaskT                           task_type;
	typedef Facility<task_type>             this_type;
	typedef Worker<task_type>               worker_type;
	typedef IntrusivePtr<worker_type>       worker_pointer;

	typedef typename AsParameter<task_type>::type task_parameter_type;

	typedef size_t    size_type;

	/**
	  default constructor.

	   The facility to control the flow and the memory pool are determined
	  from the default ones.
	 */
	Facility();

	/**
	  constructs with the memory pool.
	  
	  The facility to control the flow is determined from the default one.
	 */
	Facility(mempool_type const mempool);

	/**
	  constructs with the flow control and the memory pool.
	 */
	Facility(
		flow::facility_type & flow_facility,
		mempool_type const mempool);

	/// destructor
	~Facility();

	/// releases the internal resources.
	void clear();

	/**
	  @brief    passes a task to a worker.
	  @param    task is an executable task.
	  @return   success or failure.
	  
	   This function merely distributes a task to a worker. Until the worker
	  is assigned to the thread execution, the task will not  be executed.
	 */
	bool distribute(task_parameter_type task);

	/**
	  @brief    passes multiple tasks to workers.
	  @param    begin is the beginning of the container of tasks.
	  @param    end is the beginning of the container of tasks.
	  @return   success or failure.
	 */
	template < typename InputIteratorT >
	bool distribute(InputIteratorT begin, InputIteratorT end);

	/**
	  @brief    attaches all workers to concurrent units.
	  @return   success or failure.

	   If the workers are not attached to each concurrent unit, they are
	  added to the waiting queue of the each concurrent unit synchronously.
	  
	   This function includes the synchronization using exclusive control.
	  (i.e. The calling context may be suspended for log periods.)
	 */
	bool attach();

	/**
	  @brief    appends and executes a task.
	  @param    task is an executable task.
	 */
	bool attach_with(task_parameter_type task);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// indicates the number of tasks by each worker.
	void grab_size(size_t const grab_size);

	/// retrieves the facility to control the flow of tasks.
	flow::facility_type * flow_facility();

	/// assigns a node disposed at the end of the flow.
	flow::node_type const & then(flow::node_type const & src);

	/**
	  waits until the all distributed worker finishes their tasks
	  or the specified duration has elapsed.
	 */
	bool join(exclusion::duration_type const & duration);

	/**
	  waits until the all distributed worker finishes their tasks.
	 */
	void join();

	/// retrieves the memory pool used in this instance.
	mempool_type mempool() const;

	/// inactivates the worker.
	void inactivate(worker_type & worker);

protected :

private :

	typedef Vector<worker_pointer> workers_type;
	typedef exclusion::Stack<workers_type> workers_stack_type;

	hryky_delete_this_copy_constructor(Facility);
	hryky_delete_this_copy_assign_op(Facility);
	
	/// prepares the container for workers if it hasn't exist.
	bool supply_inactives();

	/// prepares the joinable node if it hasn't exist.
	bool ensure_join();

	/// brings out one inactive worker.
	worker_pointer pop_inactive();

	/// brings out inactive workers.
	bool pop_inactives(workers_type & dest, size_type const size);

	/// retrieves the minimum number of workers.
	size_type min_workers_size() const;

	/// creates new workers.
	bool create_workers(workers_type & dest, size_type const size);

	/// attaches the worker to the concurrent unit.
	bool activate(worker_pointer const & worker);

	flow::facility_type *   flow_facility_;
	flow::join_type         join_node_;
	workers_stack_type      inactives_;
	size_type               grab_size_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::batch::Facility<hryky_template_arg>::Facility()
	: flow_facility_(flow::facility_registry_type::instance())
	  , join_node_()
	  , inactives_()
	  , grab_size_()
{
}
/**
  @brief constructs with the memory pool.
 */
template <hryky_template_param>
hryky::batch::Facility<hryky_template_arg>::Facility(mempool_type const mempool)
	: flow_facility_(flow::facility_registry_type::instance())
	  , join_node_()
	  , inactives_(workers_type(mempool))
	  , grab_size_()
{
}
/**
  @brief constructor with the facility to control the flow of tasks.
 */
template <hryky_template_param>
hryky::batch::Facility<hryky_template_arg>::Facility(
	flow::facility_type & flow_facility, mempool_type const mempool)
	: flow_facility_(&flow_facility)
	  , join_node_()
	  , inactives_(workers_type(mempool))
	  , grab_size_()
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::batch::Facility<hryky_template_arg>::~Facility()
{
	this->join();
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::batch::Facility<hryky_template_arg>::clear()
{
	hryky::clear(this->grab_size_);
	hryky::clear(this->inactives_);
	hryky::clear(this->flow_facility_);
}
/**
  @brief indicates the number of tasks by each worker.
 */
template <hryky_template_param>
void hryky::batch::Facility<hryky_template_arg>::grab_size(size_t const src)
{
	this->grab_size_ = src;
}
/**
  @brief passes a task to a worker.
 */
template <hryky_template_param>
bool hryky::batch::Facility<hryky_template_arg>::distribute(
	task_parameter_type task)
{
	worker_pointer const inactive = this->pop_inactive();
	if (hryky_is_null(inactive)) {
		hryky_log_err("failed to retrieve an inactive worker.");
		return false;
	}

	if (!inactive->append(task)) {
		hryky_log_alert("failed to append a task to the worker.");
		return false;
	}

	this->inactives_.push(inactive);

	return true;
}
/**
  @brief passes multiple tasks to workers.
 */
template <hryky_template_param>
template < typename InputIteratorT >
bool hryky::batch::Facility<hryky_template_arg>::distribute(
	InputIteratorT begin, InputIteratorT end)
{
	size_type const min_workers_size = this->min_workers_size();
	workers_type workers(this->mempool());
	if (!this->pop_inactives(workers, min_workers_size)) {
		hryky_log_err("failed to retrieve inactive workers.");
		return false;
	}

	typedef ::std::iterator_traits<InputIteratorT>::difference_type
		difference_type;

	typedef workers_type::size_type size_type;

	size_type const workers_size = workers.size();

	size_type const tasks_size = static_cast<size_type>(
		::std::distance(begin, end));
	size_type const tasks_per_worker =
		(tasks_size + workers_size - 1u) / workers_size;

	InputIteratorT tasks_itr = begin;
	Foreach<workers_type> worker(workers);
	size_type total_distributed_size = 0;
	
	while (end != tasks_itr) {
		size_type const rest_tasks_size =
			tasks_size - total_distributed_size;
		size_type const distributed_size = ::std::min<size_type>(
			rest_tasks_size, tasks_per_worker);

		InputIteratorT const next_tasks_itr = ::std::next(
			tasks_itr,
			static_cast<difference_type>(distributed_size));

		if (!(*worker)->append(tasks_itr, next_tasks_itr)) {
			hryky_log_err(
				"failed to append tasks to the worker."
				<< (json::writer()
					<< hryky_stream_denote(total_distributed_size)
					<< hryky_stream_denote(distributed_size)));
			return false;
		}

		if (!(++worker).valid()) {
			worker.restart();
		}

		tasks_itr = next_tasks_itr;
		total_distributed_size += distributed_size;
	}

	if (!this->inactives_.push(workers.begin(), workers.end())) {
		hryky_log_alert("failed to append the inactive workers.");
		return false;
	}

	return true;
}
/**
  @brief attaches the all inactive workers to concurrent units.
 */
template <hryky_template_param>
bool hryky::batch::Facility<hryky_template_arg>::attach()
{
	if (hryky_is_null(this->flow_facility_)) {
		hryky_log_alert(
			"The facility to control the flow of tasks is null.");
		return false;
	}

	if (!this->ensure_join()) {
		hryky_log_alert(
			"failed to prepare a node to wait the completion.");
		return false;
	}

	mempool_type const mempool = this->mempool();
	workers_type workers(mempool);

	this->inactives_.swap(workers);

	// removes empty workers.
	workers_type actives(mempool);
	{
		workers_type inactives(mempool);

		hryky::foreach(
			workers, [&actives, &inactives](worker_pointer & worker) {
				if (worker->empty()) {
					inactives.push_back(worker);
				}
				else {
					actives.push_back(worker);
				}
			});

		if (!this->inactives_.push(inactives.begin(), inactives.end())) {
			hryky_log_alert("failed to append inactive workers.");
			return false;
		}
	}

	return actives.every([this](worker_pointer & active) {
		if (!this->activate(active)) {
			hryky_log_err(
				"failed to attach the worker to the concurrent unit.");
			return false;
		}
		return true;
	});
}
/**
  @brief distributes a task to a worker and executes the task.
 */
template <hryky_template_param>
bool hryky::batch::Facility<hryky_template_arg>::attach_with(
	task_parameter_type task)
{
	if (hryky_is_null(this->flow_facility_)) {
		hryky_log_alert(
			"The facility to control the flow of tasks is null.");
		return false;
	}
	
	worker_pointer const inactive = this->pop_inactive();
	if (hryky_is_null(inactive)) {
		hryky_log_alert("failed to retrieves an inactive worker.");
		return false;
	}
	
	if (!inactive->append(task)) {
		hryky_log_err("failed to distribute a task to the worker");
		return false;
	}

	if (!this->activate(inactive)) {
		hryky_log_err("failed to attach the worker to the concurrent unit.");
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
hryky::batch::Facility<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(grab_size);
	hryky_write_member(inactives);
	hryky_write_pointer_member(join_node);
	hryky_write_pointer_member(flow_facility);
	
	return out;
}
/**
  @brief retrieves the facility to control the flow of tasks.
 */
template <hryky_template_param>
hryky::flow::facility_type *
hryky::batch::Facility<hryky_template_arg>::flow_facility()
{
	return this->flow_facility_;
}
/**
  @brief assigns a node disposed at the end of the flow.
 */
template <hryky_template_param>
hryky::flow::node_type const &
hryky::batch::Facility<hryky_template_arg>::then(
	flow::node_type const & src)
{
	if (!this->ensure_join()) {
		hryky_log_alert(
			"failed to prepare a node to wait the completion");
		return flow::null();
	}
	return this->join_node_->append(src);
}
/**
  @brief waits until the all distributed worker finishes their tasks
    or the specified duration has elapsed.
 */
template <hryky_template_param>
bool
hryky::batch::Facility<hryky_template_arg>::join(
	exclusion::duration_type const & duration)
{
	if (hryky_is_null(this->flow_facility_)) {
		hryky_log_alert(
			"The facility to control the flow of task is null.");
		return false;
	}
	return this->flow_facility_->join(duration);
}
/**
  @brief waits until the all distributed worker finishes their tasks.
 */
template <hryky_template_param>
void hryky::batch::Facility<hryky_template_arg>::join()
{
	if (hryky_is_null(this->flow_facility_)) {
		hryky_log_alert(
			"The facility to control the flow of task is null.");
		return;
	}
	this->flow_facility_->join();
}
/**
  @brief retrieves the memory pool used in this instance.
 */
template <hryky_template_param>
hryky::mempool_type hryky::batch::Facility<hryky_template_arg>::mempool() const
{
	return this->inactives_.container().get_allocator().mempool();
}
/**
  @brief inactivates the worker.
 */
template <hryky_template_param>
void hryky::batch::Facility<hryky_template_arg>::inactivate(worker_type & worker)
{
	this->inactives_.push(worker_pointer(&worker));
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief prepares the joinable node if it hasn't exist.
 */
template <hryky_template_param>
bool hryky::batch::Facility<hryky_template_arg>::ensure_join()
{
	if (!hryky_is_null(this->join_node_)) {
		return true;
	}

	if (hryky_is_null((this->join_node_ = flow::join(
		*this->flow_facility_, this->mempool())))) {
		hryky_log_alert(
			"failed to instantiate a node to wait the preceding nodes");
		return false;
	}
	
	return true;
}
/**
  @brief prepares the container for workers.
 */
template <hryky_template_param>
bool hryky::batch::Facility<hryky_template_arg>::supply_inactives()
{
	mempool_type const mempool = this->mempool();
	size_t const workers_size = this->min_workers_size();

	workers_type workers(mempool);
	if (!this->create_workers(workers, workers_size)) {
		hryky_log_alert(
			"failed to allocate workers."
			<< (json::writer()
				<< hryky_stream_denote(workers_size)));
		return false;
	}

	this->inactives_.push(workers.begin(), workers.end());
	
	return true;
}
/**
  @brief brings out one inactive worker.
 */
template <hryky_template_param>
typename hryky::batch::Facility<hryky_template_arg>::worker_pointer 
hryky::batch::Facility<hryky_template_arg>::pop_inactive()
{
	worker_pointer inactive;
	this->inactives_.pop(inactive);

	while (hryky_is_null(inactive)) {
		if (!this->supply_inactives()) {
			hryky_log_alert("failed to make up for the missing workers.");
			return worker_pointer();
		}

		this->inactives_.pop(inactive);
	}

	return inactive;
}
/**
  @brief brings out inactive workers.
 */
template <hryky_template_param>
bool hryky::batch::Facility<hryky_template_arg>::pop_inactives(
	workers_type & dest, size_type const size)
{
	workers_type workers(dest.get_allocator());
	
	this->inactives_.pop(::std::back_inserter(workers), size);

	while (size > workers.size()) {
		size_type const supplied_size = size - workers.size();
		if (!this->supply_inactives()) {
			hryky_log_err("failed to make up for the missing workers.");
			return false;
		}

		this->inactives_.pop(::std::back_inserter(workers), supplied_size);
	}

	dest.swap(workers);

	return true;
}
/**
  @brief retrieves the minimum number of workers.
 */
template <hryky_template_param>
typename hryky::batch::Facility<hryky_template_arg>::size_type 
hryky::batch::Facility<hryky_template_arg>::min_workers_size() const
{
	return thread::hardware_concurrency();
}
/**
  @brief creates new workers.
 */
template <hryky_template_param>
bool hryky::batch::Facility<hryky_template_arg>::create_workers(
	workers_type & dest, size_type const size)
{
	if (hryky_is_null(this->flow_facility_)) {
		hryky_log_alert("The facility to control the flow is null.");
		return false;
	}
	
	mempool_type const mempool = this->mempool();
	
	if (!dest.resize(size)) {
		hryky_log_err("failed to allocate workers.");
		return false;
	}

	return dest.every([this, mempool](worker_pointer & worker) {
		if (hryky_is_null(worker = mempool::instantiate<worker_type>(
			mempool, *this, *this->flow_facility_, mempool).release())) {
			hryky_log_err("failed to allocate a worker");
			return false;
		}
		worker->reserve(this->grab_size_);
		return true;
	});
}
/**
  @brief attaches the worker to the concurrent unit.
 */
template <hryky_template_param>
bool hryky::batch::Facility<hryky_template_arg>::activate(
	worker_pointer const & worker)
{
	if (!this->ensure_join()) {
		hryky_log_alert("failed to prepare a node to wait the completion.");
		return false;
	}

	// connects the waiting node to detect the completion.
	this->join_node_->join(worker);

	// attaches the worker to the concurrent unit.
	if (!this->flow_facility_->attach(*worker)) {
		hryky_log_err(
			"failed to attach the worker to the concurrent unit.");
		return false;
	}
	
	return true;
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
#endif // BATCH_FACILITY_H_20111124003850693
/// @}
// end of file
