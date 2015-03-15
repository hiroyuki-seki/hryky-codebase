/**
  @file         flow_node_join.h
  @brief        waits for the completion of the nodes.
  @author       HRYKY
  @version      $Id: flow_node_join.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef FLOW_NODE_JOIN_H_20130324104503114
#define FLOW_NODE_JOIN_H_20130324104503114
#include "hryky/flow/flow_facility.h"
#include "hryky/flow/flow_node_base.h"
#include "hryky/exclusion/exclusion_variable.h"
#include "hryky/scoped_registry.h"
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
namespace node
{
	/// waits for the completion of the nodes.
	class Join;

} // namespace node

typedef IntrusivePtr<node::Join> join_type;

} // namespace flow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief waits for the completion of the nodes.
 */
class hryky::flow::node::Join :
	public Base
{
public :

	typedef Base base_type;
	typedef Join this_type;

	/// default constructor.
	Join();

	/// constructor.
	Join(facility_type & facility, mempool::Ptr const & mempool);

	/// destructor.
	~Join();

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/**
	  @brief enregisters a node whose completion this instance waits for.
	  @param src notifies the completion to this node.
	  @return This instance.

	   If the @a src has been already completed, this node is immediately
	  disposed asynchronously. To wait multiple nodes whose completion are
	  indeterminable, the following appropriate join(...) functions has to
	  be used.

	   If the number of awaited nodes whose completion are indeterminable
	  is greater than the maximum number of arguments of the following join()
	  function, Join::acquire() and Base::append() functions should be used.
	 */
	this_type * join(node_type const & src);

	/// enregisters two nodes whose completions this instance waits for.
	this_type * join(node_type const & src0, node_type const & src1);

	/// enregisters three nodes whose completions this instance waits for.
	this_type * join(
		node_type const & src0, node_type const & src1,
		node_type const & src3);

	/// enregisters four nodes whose completions this instance waits for.
	this_type * join(
		node_type const & src0, node_type const & src1,
		node_type const & src2, node_type const & src3);

	/// enregisters five nodes whose completions this instance waits for.
	this_type * join(
		node_type const & src0, node_type const & src1,
		node_type const & src2, node_type const & src3,
		node_type const & src4);

	/// enregisters six nodes whose completions this instance waits for.
	this_type * join(
		node_type const & src0, node_type const & src1,
		node_type const & src2, node_type const & src3,
		node_type const & src4, node_type const & src5);

	/// enregisters seven nodes whose completions this instance waits for.
	this_type * join(
		node_type const & src0, node_type const & src1,
		node_type const & src2, node_type const & src3,
		node_type const & src4, node_type const & src5,
		node_type const & src6);

	/// enregisters eight nodes whose completions this instance waits for.
	this_type * join(
		node_type const & src0, node_type const & src1,
		node_type const & src2, node_type const & src3,
		node_type const & src4, node_type const & src5,
		node_type const & src6, node_type const & src7);

	/**
	  @brief indicates the number of the awaited nodes.
	  @param src is the additional number of the awaited nodes.
	  @return This instance.

	   This function increases the expected number of the completion of
	  the awaited nodes. The expected nodes have to call Base::next() or
	  Base::append() to notify their completions to this node.

	   Meanwhile, Join::join() functions expand the expected number of the
	  completions in the functions and connects the nodes. The sequential usage
	  of Join::acquire() and Base::append() is equivalent to the usage of
	  a join() function.
	 */
	this_type * acquire(size_t const src);

protected :

private :

	typedef exclusion::Variable<size_t> counter_type;

	hryky_delete_this_copy_constructor(Join);
	hryky_delete_this_copy_assign_op(Join);

	/// disposes the succeeding node if the enregisterred flows have been completed.
	virtual void run_impl();

	counter_type counter_;

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
hryky::flow::node::Join::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	out << stream::denote("base") << static_cast<base_type const>(*this);
	hryky_write_member(counter);
	
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
	/**
	  instantiates a new node waiting for the completion of the preceding nodes.
	  @param facility attaches the @a function to the concurrent unit.
	  @param mempool is the memory pool for dynamic allocation.
	 */
	join_type join(
		facility_type & facility,
		mempool::Ptr const & mempool);

	/**
	  instantiates a new node waiting for the completion of the preceding nodes.

	   The facility and the memory pool are determined from the default ones.
	 */
	hryky::flow::join_type join();

namespace node
{
} // namespace node
} // namespace flow
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // FLOW_NODE_JOIN_H_20130324104503114
// end of file
