/**
  @file         flow_node_function.h
  @brief        A unit to dispose the concurrent function.
  @author       HRYKY
  @version      $Id: flow_node_function.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef FLOW_NODE_FUNCTION_H_20130303213959569
#define FLOW_NODE_FUNCTION_H_20130303213959569
#include "hryky/flow/flow_control_common.h"
#include "hryky/flow/flow_facility.h"
#include "hryky/flow/flow_node_base.h"
#include "hryky/intrusive_ptr.h"
#include "hryky/mempool/mempool_ptr.h"
#include "hryky/with_stream_out.h"
#include "hryky/is_null.h"
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
namespace flow
{
namespace node
{
	/// A unit to dispose the concurrent function.
	template <hryky_template_param>
	class Function;

} // namespace node
} // namespace flow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief A unit to dispose the concurrent function.
 */
template <hryky_template_param>
class hryky::flow::node::Function :
	public Base,
	public WithStreamOut<Function<hryky_template_arg> >
{
public :

	typedef Function<hryky_template_arg>    this_type;
	typedef Base                            base_type;

	/// constructor with a function.
	Function(
		FunctorT const & functor,
		facility_type & facility,
		mempool::Ptr const & mempool);

	/// destructor.
	~Function();

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :

	hryky_delete_default_constructor(Function);
	hryky_delete_this_copy_constructor(Function);
	hryky_delete_this_copy_assign_op(Function);

	/// disposes the function as task.
	virtual void run_impl();

	FunctorT functor_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace flow
{
namespace node
{
} // namespace node
} // namespace flow
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor with a function.
 */
template <hryky_template_param>
hryky::flow::node::Function<hryky_template_arg>::Function(
	FunctorT const & functor,
	facility_type & facility,
	mempool::Ptr const & mempool)
	: base_type(facility, mempool)
	  , functor_(functor)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::flow::node::Function<hryky_template_arg>::~Function()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::flow::node::Function<hryky_template_arg>::clear()
{
	this->base_type::clear();
}
//------------------------------------------------------------------------------
// defines public member functions of hryky::flow::node::Base
//------------------------------------------------------------------------------
/**
  @brief append a new succeeding node executing a function.
 */
template <hryky_template_param>
hryky::flow::node_type
hryky::flow::node::Base::call(FunctorT const & functor)
{
	return this->append(flow::function(
		functor, *this->facility_, this->allocator().mempool()));
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::flow::node::Function<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << static_cast<base_type const>(*this);
	return out;
}
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief disposes the function as task.
 */
template <hryky_template_param>
void hryky::flow::node::Function<hryky_template_arg>::run_impl()
{
	control::kind_type const controller(this->functor_(node_type(this)));

	switch (controller.raw()) {
	case control::Kind::next:
		this->forward();
		break;
	case control::Kind::again:
		this->attach();
		break;
	case control::Kind::abort:
		break;
	default:
		hryky_log_alert(
			"The returned value is invalid for the flow control. "
			"The proceeding of the flow will stop.");
		break;
	}
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace flow
{
	/**
	  instantiate a node to dispose an arbitrary functor.
	  @param functor is the functor to be disposed on the concurrent unit.
	  @param facility attaches the @a function to the concurrent unit.
	  @param mempool is the memory pool for dynamic allocation.
	 */
	template <hryky_template_param>
	node_type function(
		FunctorT const & functor,
		facility_type & facility,
		mempool::Ptr const & mempool);

	/**
	  instantiates a node to dispose an arbitrary functor.
	  @param functor is the functor to be disposed on the concurrent unit.

	  The facility and the memory pool are determined from the default ones.
	 */
	template <hryky_template_param>
	node_type function(FunctorT const & functor);

namespace node
{

} // namespace node
} // namespace flow
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief instantiate a node to dispose an arbitrary functor.
 */
template <hryky_template_param>
hryky::flow::node_type
hryky::flow::function(
	FunctorT const & functor,
	facility_type & facility,
	mempool::Ptr const & mempool)
{
	auto instance = mempool::instantiate<node::Function<FunctorT> >(
		mempool, functor, facility, mempool);
	if (hryky_is_null(instance)) {
		hryky_log_err("failed to allocate the memory of function node");
		return node_type();
	}

	return node_type(instance.release());
}
/**
  @brief instantiates a node to dispose an arbitrary functor.
 */
template <hryky_template_param>
hryky::flow::node_type
hryky::flow::function(FunctorT const & functor)
{
	facility_type * const facility =
		ScopedRegistry<facility_type>::instance();
	if (hryky_is_null(facility)) {
		hryky_log_alert(
			"The facility for a function is not instantiate.");
		return node_type();
	}
	
	return function(functor, *facility, mempool::Ptr());
}
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // FLOW_NODE_FUNCTION_H_20130303213959569
// end of file
