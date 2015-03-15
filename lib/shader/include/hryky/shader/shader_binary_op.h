/**
  @file     shader_binary_op.h
  @brief    expresses a binary operation.
  @author   HRYKY
  @version  $Id: shader_binary_op.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_BINARY_OP_H_20140803150552295
#define SHADER_BINARY_OP_H_20140803150552295
#include "hryky/shader/shader_node_ptr.h"
#include "hryky/shader/shader_dispatchee.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename DerivedT
#define hryky_template_arg \
	DerivedT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// expresses a binary operation.
	template <hryky_template_param>
	class BinaryOp;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief expresses a binary operation.
 */
template <hryky_template_param>
class hryky::shader::BinaryOp :
	public Dispatchee<DerivedT>,
	public WithSwap<BinaryOp<hryky_template_arg> >
{
public :

	typedef Dispatchee<DerivedT> base_type;
	typedef BinaryOp<hryky_template_arg> this_type;

	/// default constructor.
	BinaryOp();

	/// creates an instance with both terms.
	BinaryOp(node_type const & lhs, node_type const & rhs);

	/// copy constructor.
	BinaryOp(this_type const &);

	/// move constructor.
	BinaryOp(this_type &&);

	/// destructor.
	~BinaryOp();

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to_impl(StreamT & out) const;

	/// retrieves the expression at LHS.
	node_type const & lhs() const;

	/// retrieves the expression at RHS.
	node_type const & rhs() const;

protected :

private :
	hryky_delete_this_copy_assign_op(BinaryOp);

	node_type lhs_;
	node_type rhs_;

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
hryky::shader::BinaryOp<hryky_template_arg>::BinaryOp()
	: base_type()
	  , lhs_()
	  , rhs_()
{
}
/**
  @brief creates an instance with both terms.
 */
template <hryky_template_param>
hryky::shader::BinaryOp<hryky_template_arg>::BinaryOp(
	node_type const & lhs, node_type const & rhs)
	: base_type()
	  , lhs_(lhs)
	  , rhs_(rhs)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::shader::BinaryOp<hryky_template_arg>::BinaryOp(
	this_type const & rhs)
	: base_type(rhs)
	  , hryky_copy_member(lhs)
	  , hryky_copy_member(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::shader::BinaryOp<hryky_template_arg>::BinaryOp(
	this_type && rhs)
	: base_type(std::move(rhs))
	  , hryky_move_member(lhs)
	  , hryky_move_member(rhs)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::shader::BinaryOp<hryky_template_arg>::~BinaryOp()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::shader::BinaryOp<hryky_template_arg>::clear()
{
	hryky::clear(this->rhs_);
	hryky::clear(this->lhs_);
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::shader::BinaryOp<hryky_template_arg>::swap(
	this_type & src)
{
	this->base_type::swap(src);
	hryky_swap_member(lhs);
	hryky_swap_member(rhs);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::shader::BinaryOp<hryky_template_arg>::write_to_impl(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(lhs);
	hryky_write_member(rhs);
	return out;
}
/**
  @brief retrieves the expression at LHS.
 */
template <hryky_template_param>
hryky::shader::node_type const & 
hryky::shader::BinaryOp<hryky_template_arg>::lhs() const
{
	return this->lhs_;
}
/**
  @brief retrieves the expression at RHS.
 */
template <hryky_template_param>
hryky::shader::node_type const & 
hryky::shader::BinaryOp<hryky_template_arg>::rhs() const
{
	return this->rhs_;
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
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SHADER_BINARY_OP_H_20140803150552295
// end of file
