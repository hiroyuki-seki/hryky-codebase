/**
  @file         accumulator_facility.h
  @brief        retains the concurent informations.
  @author       HRYKY
  @version      $Id: accumulator_facility.h 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
 */
#ifndef ACCUMULATOR_FACILITY_H_20130325140014250
#define ACCUMULATOR_FACILITY_H_20130325140014250
#include "hryky/accumulator/accumulator_resolver.h"
#include "hryky/mempool/mempool_ptr.h"
#include "hryky/without_copy.h"
#include "hryky/task/task_factory.h"
#include "hryky/type_traits/as_parameter.h"
#include "hryky/vector.h"
#include "hryky/with_stream_out.h"
#include "hryky/is_null.h"
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
	/// retains the concurent informations.
	template <
		typename InputIteratorT,
		typename ResultT
			= typename ::std::iterator_traits<InputIteratorT>::value_type
	>
	class Facility;

} // namespace accumulator
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the concurent informations.
 */
template <hryky_template_param>
class hryky::accumulator::Facility :
	public WithStreamOut<Facility<hryky_template_arg> >,
	private WithoutCopy
{
public :

	typedef Facility<hryky_template_arg>        this_type;
	typedef ResultT                             result_type;
	typedef typename AsParameter<ResultT>::type result_param_type;

	/// default constructor.
	Facility();

	/// constructor with the memory pool.
	Facility(mempool_type const mempool);

	/// constructor with the memory pool and the facility to control the flow.
	Facility(flow::facility_type & flow_facility, mempool_type const mempool);

	/// destructor.
	~Facility();

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;
	
	/**
	  @brief starts the accumulation.
	 */
	bool accumulate(
		InputIteratorT begin,
		InputIteratorT end,
		size_t const max_accumulations_size);

	/// confirms whether the asynchronous task has been completed.
	bool completed() const;

	/// retrieves the result of the accumulation.
	result_param_type result() const;

	/// waits until the accumulation is completed.
	void join();

	/// waits until the accumulation is completed or the specified period of time elapses.
	bool join(exclusion::duration_type const duration);

	/// retrieves the memory pool used in this instance.
	mempool_type mempool() const;

	/// retrieves the facility to control the flow of tasks.
	flow::facility_type * flow_facility();

protected :

private :

	typedef Resolver<hryky_template_arg> resolver_type;
	typedef typename resolver_type::batch_type batch_type;

	static ResultT const dummy_result_;

	hryky_delete_this_copy_constructor(Facility);
	hryky_delete_this_copy_assign_op(Facility);

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// prepares the node to calculate the result of the accumulation.
	bool ensure_resolver();

	flow::facility_type *                   flow_facility_;
	batch_type                              batch_;
	typename resolver_type::instance_type   resolver_;
	mempool::Ptr const                      mempool_;

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
  @brief default constructor.
 */
template <hryky_template_param>
hryky::accumulator::Facility<hryky_template_arg>::Facility()
	: flow_facility_(flow::facility_registry_type::instance())
	  , batch_()
	  , resolver_()
	  , mempool_()
{
}
/**
  @brief constructor with the memory pool.
 */
template <hryky_template_param>
hryky::accumulator::Facility<hryky_template_arg>::Facility(
	mempool_type const mempool)
	: flow_facility_(flow::facility_registry_type::instance())
	  , batch_(mempool)
	  , resolver_()
	  , mempool_(mempool)
{
}
/**
  @brief constructor with the memory pool and the concurrent facility.
 */
template <hryky_template_param>
hryky::accumulator::Facility<hryky_template_arg>::Facility(
	flow::facility_type & flow_facility, mempool_type const mempool)
	: flow_facility_(&flow_facility)
	  , batch_(flow_facility, mempool)
	  , resolver_()
	  , mempool_(mempool)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::accumulator::Facility<hryky_template_arg>::~Facility()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::accumulator::Facility<hryky_template_arg>::clear()
{
	hryky::clear(this->resolver_);
	hryky::clear(this->batch_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & 
hryky::accumulator::Facility<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(batch);
	hryky_write_pointer_member(resolver);
	
	return out;
}
/**
  @brief starts the accumulation.
 */
template <hryky_template_param>
bool hryky::accumulator::Facility<hryky_template_arg>::accumulate(
	InputIteratorT begin, InputIteratorT end, size_t const max_accumulations_size)
{
	if (!this->ensure_resolver()) {
		hryky_log_alert("failed to prepare the resolver of accumulation.");
		return false;
	}

	if (!this->resolver_->distribute(
		this->batch_, begin, end, max_accumulations_size)) {
		hryky_log_err("failed to distribute tasks.");
		return false;
	}

	if (!this->batch_.attach()) {
		hryky_log_err("failed to attach the workers to concurrent units.");
		return false;
	}
	
	return true;
}
/**
  @brief confirms whether the asynchronous task has been completed.
 */
template <hryky_template_param>
bool hryky::accumulator::Facility<hryky_template_arg>::completed() const
{
	if (hryky_is_null(this->resolver_)) {
		hryky_log_warning("An accumulation is not operated.");
		return true;
	}
	return this->resolver_->completed();
}
/**
  @brief retrieves the result of the accumulation.
 */
template <hryky_template_param>
typename hryky::accumulator::Facility<hryky_template_arg>::result_param_type
hryky::accumulator::Facility<hryky_template_arg>::result() const
{
	if (hryky_is_null(this->resolver_)) {
		hryky_log_warning("An accumulation is not operated.");
		return this_type::dummy_result_;
	}
	return this->resolver_->result();
}
/**
  @brief waits until the accumulation is completed.
 */
template <hryky_template_param>
void hryky::accumulator::Facility<hryky_template_arg>::join()
{
	this->batch_.join();
}
/**
  @brief waits until the accumulation is completed or the specified period of time elapses.
 */
template <hryky_template_param>
bool hryky::accumulator::Facility<hryky_template_arg>::join(
	exclusion::duration_type const duration)
{
	return this->batch_.join(duration);
}
/**
  @brief retrieves the memory pool used in this instance.
 */
template <hryky_template_param>
hryky::mempool_type 
hryky::accumulator::Facility<hryky_template_arg>::mempool() const
{
	return this->mempool_.get();
}
/**
  @brief retrieves the facility to control the flow of tasks.
 */
template <hryky_template_param>
hryky::flow::facility_type * 
hryky::accumulator::Facility<hryky_template_arg>::flow_facility()
{
	return this->flow_facility_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief prepares the node to calculate the result of the accumulation.
 */
template <hryky_template_param>
bool hryky::accumulator::Facility<hryky_template_arg>::ensure_resolver()
{
	if (!hryky_is_null(this->resolver_)) {
		return true;
	}

	flow::facility_type * const flow_facility = this->flow_facility();

	if (hryky_is_null(flow_facility)) {
		hryky_log_alert("The facility to control the flow is null.");
		return false;
	}

	if (hryky_is_null(this->resolver_ = mempool::instantiate<resolver_type>(
		this->mempool(), *flow_facility, this->mempool()).release())) {
		hryky_log_err("failed to instantiate the resolver of accumulation.");
		return false;
	}

	this->batch_.then(this->resolver_);
	
	return true;
}
/**
  dummy value for the invalid value.
 */
template <hryky_template_param>
ResultT const
hryky::accumulator::Facility<hryky_template_arg>::dummy_result_ = ResultT();
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
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // ACCUMULATOR_FACILITY_H_20130325140014250
// end of file
