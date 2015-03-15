/**
  @file     shader_node_ptr.h
  @brief    retains a pointer to Node.
  @author   HRYKY
  @version  $Id: shader_node_ptr.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_NODE_PTR_H_20140819100102084
#define SHADER_NODE_PTR_H_20140819100102084
#include "hryky/intrusive_ptr.h"
#include "hryky/with_stream_out.h"
#include "hryky/shader/shader_with_code.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// retains a pointer to Node.
	class NodePtr;

	typedef NodePtr node_type;

	class Node;
	class Coder;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a pointer to Node.
 */
class hryky::shader::NodePtr :
	public IntrusivePtr<Node>,
	public WithStreamOut<NodePtr>,
	public WithCode<NodePtr>
{
public :

	typedef IntrusivePtr<Node> base_type;

	typedef NodePtr this_type;

	/// default constructor.
	NodePtr();

	/// creates an instance from a pointer of derived class.
	template <typename RhsT>
	NodePtr(IntrusivePtr<RhsT> const & rhs);

	/// creates an instance with the pointer.
	NodePtr(pointer const ptr, bool const add_ref = true);

	/// copy constructor.
	NodePtr(this_type const &);

	/// move constructor.
	NodePtr(this_type &&);

	/// destructor.
	~NodePtr();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// writes out the code of node.
	Coder & code(Coder & coder) const;

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief creates an instance from a pointer of derived class.
 */
template <typename RhsT>
hryky::shader::NodePtr::NodePtr(IntrusivePtr<RhsT> const & rhs)
	: base_type(rhs)
{
}
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT &
hryky::shader::NodePtr::write_to(StreamT & out) const
{
	if (hryky_is_null(*this)) {
		return this->base_type::write_to(out);
	}
	else {
		return (*this)->write_to(out);
	}
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
namespace shader
{
	/// creates a node from derived instance.
	template <typename DerivedT>
	node_type node(DerivedT const & src);

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a node from derived instance.
 */
template <typename DerivedT>
hryky::shader::node_type
hryky::shader::node(DerivedT const & src)
{
	typename DerivedT::allocator_type::template rebind<DerivedT>::other
		allocator(src.allocator());
	return node_type(allocator::instantiate_by(allocator, src));
}
#endif // SHADER_NODE_PTR_H_20140819100102084
// end of file
