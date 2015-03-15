/**
  @file     shader_block.h
  @brief    expresses statements.
  @author   HRYKY
  @version  $Id: shader_block.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_BLOCK_H_20140803161025340
#define SHADER_BLOCK_H_20140803161025340
#include "hryky/vector.h"
#include "hryky/shader/shader_dispatchee.h"
#include "hryky/shader/shader_node_ptr.h"
#include "hryky/retention/retention_value.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename DerivedT, typename NodePtrT
#define hryky_template_arg \
	DerivedT, NodePtrT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// expresses statements.
	template <
		typename DerivedT,
		typename NodePtrT = NodePtr
	>
	class Block;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief expresses statements.
 */
template <hryky_template_param>
class hryky::shader::Block :
	public Dispatchee<DerivedT>,
	public WithSwap<Block<hryky_template_arg> >,
	private retention::Value<hryky::Vector<NodePtrT> >
{
public :

	typedef Dispatchee<DerivedT> base_type;
	typedef Block<hryky_template_arg> this_type;
	typedef hryky::Vector<NodePtrT> nodes_type;

	/// default constructor.
	Block();

	/// copy constructor.
	Block(this_type const &);

	/// move constructor.
	Block(this_type &&);

	/// destructor.
	~Block();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// appends a node.
	this_type & append(NodePtrT const & src);

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to_impl(StreamT & out) const;

protected :

	/// retrieves the immutable nodes.
	nodes_type const & nodes() const;

	/// retrieves the mutable nodes.
	nodes_type & nodes();

private :
	typedef retention::Value<hryky::Vector<NodePtrT> > retain_type;
	
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
  @brief default constructor.
 */
template <hryky_template_param>
hryky::shader::Block<hryky_template_arg>::Block()
	: base_type()
	  , retain_type()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::shader::Block<hryky_template_arg>::Block(
	this_type const & rhs)
	: base_type(rhs)
	  , retain_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::shader::Block<hryky_template_arg>::Block(
	this_type && rhs)
	: base_type(std::move(rhs))
	  , retain_type(std::move(rhs))
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::shader::Block<hryky_template_arg>::~Block()
{
}
/**
  @brief appends a node.
 */
template <hryky_template_param>
hryky::shader::Block<hryky_template_arg> & 
hryky::shader::Block<hryky_template_arg>::append(
	NodePtrT const & src)
{
	this->nodes().push_back(src);
	return *this;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::shader::Block<hryky_template_arg>::clear()
{
	this->retain_type::clear();
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::shader::Block<hryky_template_arg>::swap(
	this_type & src)
{
	this->base_type::swap(src);
	this->retain_type::swap(src);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::shader::Block<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->write_to_impl(out);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::shader::Block<hryky_template_arg>::write_to_impl(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("statements");
	this->retain_type::write_to(out);
	return out;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the immutable nodes.
 */
template <hryky_template_param>
typename hryky::shader::Block<hryky_template_arg>::nodes_type const & 
hryky::shader::Block<hryky_template_arg>::nodes() const
{
	return *this->get();
}
/**
  @brief retrieves the mutable nodes.
 */
template <hryky_template_param>
typename hryky::shader::Block<hryky_template_arg>::nodes_type & 
hryky::shader::Block<hryky_template_arg>::nodes()
{
	return *this->get();
}
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
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SHADER_BLOCK_H_20140803161025340
// end of file
