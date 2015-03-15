/**
  @file     shader_term_ptr.h
  @brief    retains a pointer to an operand.
  @author   HRYKY
  @version  $Id: shader_term_ptr.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_TERM_PTR_H_20140820081002006
#define SHADER_TERM_PTR_H_20140820081002006
#include "hryky/intrusive_ptr.h"
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
	/// retains a pointer to an operand.
	template <typename NodeT>
	class TermPtr;

	class Multiply;
	class Assign;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a pointer to an operand.
 */
template <hryky_template_param>
class hryky::shader::TermPtr :
	public IntrusivePtr<NodeT>
{
public :

	typedef IntrusivePtr<NodeT > base_type;

	typedef TermPtr<hryky_template_arg> this_type;

	/// default constructor.
	TermPtr();

	/// creates an intance from pointer.
	TermPtr(NodeT * const ptr, bool const add_ref = true);

	/// copy constructor.
	TermPtr(this_type const &);

	/// move constructor.
	TermPtr(this_type &&);

	/// destructor.
	~TermPtr();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// creates a multiplication.
	template <typename RhsT>
	TermPtr<Multiply> operator*(TermPtr<RhsT> const & rhs) const;

	/// creates an assignment.
	template <typename RhsT>
	TermPtr<Assign> operator=(TermPtr<RhsT> const & rhs) const;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

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
hryky::shader::TermPtr<hryky_template_arg>::TermPtr()
	: base_type()
{
}
/**
  @brief creates an intance from pointer.
 */
template <hryky_template_param>
hryky::shader::TermPtr<hryky_template_arg>::TermPtr(
	NodeT * const ptr, bool const add_ref)
	: base_type(ptr, add_ref)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::shader::TermPtr<hryky_template_arg>::TermPtr(
	this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::shader::TermPtr<hryky_template_arg>::TermPtr(
	this_type && rhs)
	: base_type(std::move(rhs))
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::shader::TermPtr<hryky_template_arg>::~TermPtr()
{
}
/**
  @brief creates a multiplication.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::shader::TermPtr<hryky::shader::Multiply> 
hryky::shader::TermPtr<hryky_template_arg>::operator*(
	TermPtr<RhsT> const & rhs) const
{
	allocator::Mempool<Multiply> allocator;
	return TermPtr<Multiply>(allocator::instantiate_by(
		allocator, *this, rhs));
}
/**
  @brief creates an assignment.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::shader::TermPtr<hryky::shader::Assign> 
hryky::shader::TermPtr<hryky_template_arg>::operator=(
	TermPtr<RhsT> const & rhs) const
{
	allocator::Mempool<Assign> allocator;
	return TermPtr<Assign>(allocator::instantiate_by(
		allocator, *this, rhs));
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::shader::TermPtr<hryky_template_arg>::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::shader::TermPtr<hryky_template_arg>::swap(
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
hryky::shader::TermPtr<hryky_template_arg>::write_to(
	StreamT & out) const
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
	/// creates a TermPtr from a Term.
	template <hryky_template_param>
	TermPtr<hryky_template_arg> term(NodeT const & src);

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a TermPtr from a Term.
 */
template <hryky_template_param>
hryky::shader::TermPtr<hryky_template_arg>
hryky::shader::term(NodeT const & src)
{
	typename NodeT::allocator_type::template rebind<NodeT>::other
		allocator(src.allocator());
	return TermPtr<NodeT>(allocator::instantiate_by(
		allocator, src));
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SHADER_TERM_PTR_H_20140820081002006
// end of file
