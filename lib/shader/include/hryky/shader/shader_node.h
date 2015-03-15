/**
  @file     shader_node.h
  @brief    The base class of expression.
  @author   HRYKY
  @version  $Id: shader_node.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_NODE_H_20140803112625143
#define SHADER_NODE_H_20140803112625143
#include "hryky/intrusive_ptr_trait.h"
#include "hryky/with_stream_out.h"
#include "hryky/shader/shader_dispatcher.h"
#include "hryky/shader/shader_coder.h"
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
	/// The base class of expression.
	class Node;

	template <typename OutputT>
	class WriteTo;

	class Coder;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The base class of expression.
 */
class hryky::shader::Node :
	public IntrusivePtrTrait<>,
	public WithStreamOut<Node>
{
public :

	typedef Node this_type;
	typedef Dispatcher dispatcher_type;
	typedef ImmutableDispatcher const_dispatcher_type;

	/// destructor.
	~Node();

	/// writes this information by string.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// writes this information by string.
	template <typename StreamT>
	StreamT & write_to_impl(StreamT & out) const;

	/// passes this concrete class to a dispatcher.
	void dispatch(dispatcher_type & dispatcher);

	/// passes this immutable concrete class to a dispatcher.
	void dispatch(const_dispatcher_type & dispatcher) const;

	/// writes the information as the code of shader.
	Coder & code(Coder & coder) const;

	/// wirtes the code as declaration.
	Coder & declare(Coder & coder) const;

	/// writes the information as the code of shader.
	Coder & code_impl(Coder & coder) const;

	/// writes out the declaration of node.
	Coder & declare_impl(Coder & coder) const;

protected :

	/// default constructor.
	Node();

	/// copy constructor.
	Node(this_type const &);

	/// move constructor.
	Node(this_type &&);

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

private :
	hryky_delete_copy_assign_op(Node);

	/// implements dispatch(dispatcher_type &).
	virtual void dispatch_impl(dispatcher_type &) = 0;

	/// implements dispatch(dispatcher_type &).
	virtual void dispatch_impl(const_dispatcher_type &) const = 0;

	typedef IntrusivePtrTrait<> intrusive_ptr_trait;

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
  @brief writes this information by string.
 */
template <typename StreamT>
StreamT &
hryky::shader::Node::write_to(StreamT & out) const
{
	WriteTo<StreamT> write_to(out);
	this->dispatch(write_to);
	return out;
}
/**
  @brief writes this information by string.
 */
template <typename StreamT>
StreamT &
hryky::shader::Node::write_to_impl(StreamT & out) const
{
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
namespace shader
{
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SHADER_NODE_H_20140803112625143
// end of file
