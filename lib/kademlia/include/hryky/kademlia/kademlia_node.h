/**
  @file     kademlia_node.h
  @brief    The information of a node in the Kademlia network.
  @author   HRYKY
  @version  $Id: kademlia_node.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef KADEMLIA_NODE_H_20130915195152494
#define KADEMLIA_NODE_H_20130915195152494
#include "hryky/definition.h"
#include "hryky/ip/ip_v6_entity.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace kademlia
{
	/// The information of a node in the Kademlia network.
	class Node;

} // namespace kademlia
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The information of a node in the Kademlia network.
 */
class hryky::kademlia::Node :
	public WithStreamOut<Node>,
	public WithSwap<Node>
{
public :

	typedef Node this_type;

	/// default constructor.
	Node();

	/// copy constructor.
	Node(this_type const &);

	/// move constructor.
	Node(this_type &&);

	/// destructor.
	~Node();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :

	typedef ip::v6::Entity ip_type;

	ip_type ip_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace kademlia
{
} // namespace kademlia
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::kademlia::Node::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(ip);

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
namespace kademlia
{
} // namespace kademlia
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // KADEMLIA_NODE_H_20130915195152494
// end of file
