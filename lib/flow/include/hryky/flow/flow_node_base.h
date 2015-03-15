/**
  @file         flow_node_base.h
  @brief        The base class in order to handle the common interface.
  @author       HRYKY
  @version      $Id: flow_node_base.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef FLOW_NODE_BASE_H_20130316235450663
#define FLOW_NODE_BASE_H_20130316235450663
#include "hryky/intrusive_ptr_trait.h"
#include "hryky/intrusive_ptr.h"
#include "hryky/task/task_worker_base.h"
#include "hryky/exclusion/exclusion_variable.h"
#include "hryky/mempool/mempool_ptr.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace flow
{
	class Facility;
	
namespace node
{
	/// The base class in order to handle the common interface.
	class Base;

} // namespace node
typedef IntrusivePtr<node::Base> node_type;

} // namespace flow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The base class in order to handle the common interface.
 */
class hryky::flow::node::Base :
	public task::worker::Base
{
public :

	typedef Base                this_type;
	typedef task::worker::Base  base_type;
	typedef Facility            facility_type;

	/// constructor with a facility.
	Base(facility_type & facility, mempool::Ptr const & mempool);

	/// destructor.
	~Base();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// retrieves the facility to distribute this node with a task worker.
	facility_type * facility();

	/**
	  @brief attaches the instance of oneself through the facility.
	  @return success or failure.

	  This node is asynchronously disposed as the concurrent task.
	 */
	bool attach();

	/**
	  @brief appends a new node at the end of the chain of nodes.
	  @param src is assigned at the end of the chain of nodes.
	  @return The appended node itself.

	   If this node and the all following nodes has been already
	  completed, the @a src is immediately disposed asynchronously.
	 */
	node_type const & append(node_type const & src);

	/**
	  @brief inserts a new node just after this node.
	  @param src is inserted just after the THIS node.
	  @return The inserted not itself.

	   If this node has been already completed, the @a src is immediately
	  disposed asynchronously. This function assumes that the nodes
	  following this node are not disposed yet.
	 */
	node_type const & insert(node_type const & src);

	/**
	  append a new node executing a function.

	  The definition of this function is defined with flow::node::Function.
	 */
	template <typename FunctorT>
	node_type call(FunctorT const & functor);

	/// confirms whether this node had been completed.
	bool completed() const;

protected :

	/// default constructor.
	Base();

	/// releases the internal resources.
	void clear();

	/// disposes the succeeding nodes.
	bool forward();

	/**
	  @brief assigns a new node as the succeeding node.
	  @param src is assigned as the next disposed node.
	  @return The assigned node itself.

	   If this node has been already completed, the @a src is immediately
	  disposed asynchronously.
	 */
	node_type const & next(node_type const & src);

	/**
	  gives the following nodes over the other node.
	 */
	node_type const & consign(node_type const & delegated);

private :

	typedef bool completed_type;

	hryky_delete_this_copy_constructor(Base);
	hryky_delete_this_copy_assign_op(Base);

	facility_type *     facility_;
	exclusion::Mutex    lockable_;
	node_type           next_;
	completed_type      completed_;

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
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::flow::node::Base::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	out << stream::denote("base") << static_cast<base_type const &>(*this);

	hryky_write_member(completed);
	hryky_write_pointer_member(facility);
	hryky_write_pointer_member(next);
	
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
namespace flow
{
	/// retrieves the invalid node.
	node_type const & null();

namespace node
{

} // namespace node
} // namespace flow
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // FLOW_NODE_BASE_H_20130316235450663
// end of file
