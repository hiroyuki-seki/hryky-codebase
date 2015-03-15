/**
  @file         accumulator_resolver.h
  @brief        accomplishes the accumulation.
  @author       HRYKY
  @version      $Id: accumulator_resolver.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef ACCUMULATOR_RESOLVER_H_20130325171911388
#define ACCUMULATOR_RESOLVER_H_20130325171911388
#include "hryky/accumulator/accumulator_task.h"
#include "hryky/batch/batch_facility.h"
#include "hryky/type_traits/as_parameter.h"
#include "hryky/flow/flow_node_base.h"
#include "hryky/iterator/iterator_as_pointer.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename InputIteratorT, typename ResultT
#define hryky_template_arg \
	InputIteratorT, ResultT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace accumulator
{
	/// accomplishes the accumulation.
	template <hryky_template_param>
	class Resolver;

} // namespace accumulator
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief accomplishes the accumulation.
 */
template <hryky_template_param>
class hryky::accumulator::Resolver :
	public flow::node::Base
{
public :

	typedef flow::node::Base                        base_type;
	typedef Resolver<hryky_template_arg>            this_type;
	typedef IntrusivePtr<this_type>                 instance_type;
	typedef ResultT                                 result_type;
	typedef typename AsParameter<result_type>::type result_param_type;
	typedef Task<hryky_template_arg>                task_type;
	typedef batch::Facility<task_type *>            batch_type;

	/// constructor with the memory pool.
	Resolver(flow::facility_type & flow_facility, mempool_type const mempool);

	/// destructor.
	~Resolver();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// retrieves the resolved result.
	result_param_type result() const;

	/**
	  creates tasks to accumulate the each part of the values.
	 */
	bool distribute(
		batch_type & batch,
		InputIteratorT begin,
		InputIteratorT end,
		size_t const max_accumulations_size);

protected :

	/// releases the internal resources.
	void clear();

	/// accumulates the each result by the worker.
	void run_impl();

private :
	
	typedef Vector<task_type> tasks_type;
	
	hryky_delete_default_constructor(Resolver);
	hryky_delete_this_copy_constructor(Resolver);
	hryky_delete_this_copy_assign_op(Resolver);

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	tasks_type tasks_;
	result_type result_;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace accumulator
{
} // namespace accumulator
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor with the memory pool.
 */
template <hryky_template_param>
hryky::accumulator::Resolver<hryky_template_arg>::Resolver(
	flow::facility_type & flow_facility, mempool_type const mempool)
	: base_type(flow_facility, mempool)
	  , tasks_(mempool)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::accumulator::Resolver<hryky_template_arg>::~Resolver()
{
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & 
hryky::accumulator::Resolver<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(result);
	hryky_write_member(tasks);

	return out;
}
/**
  @brief retrieves the resolved result.
 */
template <hryky_template_param>
typename hryky::accumulator::Resolver<hryky_template_arg>::result_param_type
hryky::accumulator::Resolver<hryky_template_arg>::result() const
{
	return this->result_;
}
/**
  @brief creates tasks to accumulate the each part of the values.
 */
template <hryky_template_param>
bool hryky::accumulator::Resolver<hryky_template_arg>::distribute(
	batch_type & batch,
	InputIteratorT begin,
	InputIteratorT end,
	size_t const max_accumulation_size)
{
	typedef tasks_type::difference_type difference_type;
	typedef tasks_type::size_type size_type;
	
	difference_type const total_size = static_cast<difference_type>(
		::std::distance(begin, end));

	if (0 > total_size) {
		hryky_log_err("The range of sources is invalid.");
		return false;
	}

	size_type const tasks_size = (total_size + max_accumulation_size - 1) /
		max_accumulation_size;

	tasks_type tasks(this->tasks_.get_allocator());
	if (!tasks.reserve(tasks_size)) {
		hryky_log_err("failed to allocates the tasks for the accumulation");
		return false;
	}

	// assigns the each part of accumulation.
	{
		typedef Range<InputIteratorT> range_type;
		range_type range(begin, end);
		Foreach<range_type> foreach(range);
		InputIteratorT task_begin = foreach.itr();
		for (; foreach.valid();) {
			size_t const offset = foreach.offset();
			size_t const accumulation_size = (::std::min)(
				max_accumulation_size, total_size - offset);
			
			foreach += accumulation_size;
			InputIteratorT const task_end = foreach.itr();
			tasks.push_back(task_type(task_begin, task_end));
			task_begin = task_end;
		}
	}

	hryky::swap(this->tasks_, tasks);

	batch.grab_size(1);

	if (!batch.distribute(
		iterator::as_pointer(this->tasks_.begin()),
		iterator::as_pointer(this->tasks_.end()))) {
		hryky_log_err(
			"failed to distribute the tasks accumulating the values.");
		return false;
	}

	return true;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::accumulator::Resolver<hryky_template_arg>::clear()
{
	hryky::clear(this->result_);
	hryky::clear(this->tasks_);
}
/**
  @brief accumulates the each result by the worker.
 */
template <hryky_template_param>
void hryky::accumulator::Resolver<hryky_template_arg>::run_impl()
{
	this->result_ = ::std::accumulate(
		this->tasks_.begin(), this->tasks_.end(), result_type(),
		[](result_param_type prev, task_type const & task) {
			return prev + task.result();
		});

	this->forward();
}
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace accumulator
{

} // namespace accumulator
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // ACCUMULATOR_RESOLVER_H_20130325171911388
// end of file
