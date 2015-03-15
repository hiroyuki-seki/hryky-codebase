/**
  @file     shader_block_ptr.h
  @brief    retains a pointer to a block.
  @author   HRYKY
  @version  $Id: shader_block_ptr.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_BLOCK_PTR_H_20140820085258036
#define SHADER_BLOCK_PTR_H_20140820085258036
#include "hryky/shader/shader_node_ptr.h"
#include "hryky/shader/shader_with_code.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename NodeT
#define hryky_template_arg \
	NodeT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// retains a pointer to a block.
	template <typename NodeT>
	class BlockPtr;

	template <typename NodeT>
	class TermPtr;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a pointer to a block.
 */
template <hryky_template_param>
class hryky::shader::BlockPtr :
	public IntrusivePtr<NodeT>,
	public WithCode<BlockPtr<hryky_template_arg> >
{
public :

	typedef IntrusivePtr<NodeT> base_type;

	typedef BlockPtr<hryky_template_arg> this_type;

	/// default constructor.
	BlockPtr();

	/// creates an instance with a pointer.
	BlockPtr(pointer const ptr, bool const add_ref = true);

	/// copy constructor.
	BlockPtr(this_type const &);

	/// move constructor.
	BlockPtr(this_type &&);

	/// destructor.
	~BlockPtr();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// appends a node.
	this_type const & operator<<(node_type const & rhs) const;

	/// appends a node.
	template <typename RhsT>
	this_type const & operator<<(TermPtr<RhsT> const & rhs) const;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// writes the shader-code of this node.
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
  @brief default constructor.
 */
template <hryky_template_param>
hryky::shader::BlockPtr<hryky_template_arg>::BlockPtr()
	: base_type()
{
}
/**
  @brief creates an instance with a pointer.
 */
template <hryky_template_param>
hryky::shader::BlockPtr<hryky_template_arg>::BlockPtr(
	pointer const ptr, bool const add_ref)
	: base_type(ptr, add_ref)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::shader::BlockPtr<hryky_template_arg>::BlockPtr(
	this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::shader::BlockPtr<hryky_template_arg>::BlockPtr(
	this_type && rhs)
	: base_type(std::move(rhs))
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::shader::BlockPtr<hryky_template_arg>::~BlockPtr()
{
}
/**
  @brief appends a node.
 */
template <hryky_template_param>
hryky::shader::BlockPtr<hryky_template_arg> const &
hryky::shader::BlockPtr<hryky_template_arg>::operator<<(
	node_type const & rhs) const
{
	(*this)->append(rhs);
	return *this;
}
/**
  @brief appends a node.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::shader::BlockPtr<hryky_template_arg> const &
hryky::shader::BlockPtr<hryky_template_arg>::operator<<(
	TermPtr<RhsT> const & rhs) const
{
	(*this)->append(rhs);
	return *this;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::shader::BlockPtr<hryky_template_arg>::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::shader::BlockPtr<hryky_template_arg>::swap(
	this_type & src)
{
	this->base_type::swap(src);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::shader::BlockPtr<hryky_template_arg>::write_to(
	StreamT & out) const
{
	if (hryky_is_null(*this)) {
		return this->base_type::write_to(out);
	}
	else {
		return (*this)->write_to(out);
	}
}
/**
  @brief writes the shader-code of this node.
 */
template <hryky_template_param>
hryky::shader::Coder &
hryky::shader::BlockPtr<hryky_template_arg>::code(
	Coder & coder) const
{
	if (!hryky_is_null(*this)) {
		return (*this)->code(coder);
	}
	return coder;
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
	/// creates a pointer to Block.
	template <hryky_template_param>
	BlockPtr<hryky_template_arg> block(NodeT const & src);

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a pointer to Block.
 */
template <hryky_template_param>
hryky::shader::BlockPtr<hryky_template_arg>
hryky::shader::block(NodeT const & src)
{
	allocator::Mempool<NodeT> allocator;
	return BlockPtr<NodeT>(allocator::instantiate_by(
		allocator, src));
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SHADER_BLOCK_PTR_H_20140820085258036
// end of file
