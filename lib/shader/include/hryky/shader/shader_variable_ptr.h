/**
  @file     shader_variable_ptr.h
  @brief    retains an instance of shader::Variable.
  @author   HRYKY
  @version  $Id: shader_variable_ptr.h 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#ifndef SHADER_VARIABLE_PTR_H_20140821161842346
#define SHADER_VARIABLE_PTR_H_20140821161842346
#include "hryky/intrusive_ptr.h"
#include "hryky/shader/shader_variable.h"
#include "hryky/shader/shader_term_ptr.h"
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
	/// retains an instance of shader::Variable.
	template <typename NodeT>
	class VariablePtr;

	class Assign;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains an instance of shader::Variable.
 */
template <hryky_template_param>
class hryky::shader::VariablePtr :
	public TermPtr<NodeT>
{
public :

	typedef TermPtr<NodeT> base_type;
	typedef VariablePtr<hryky_template_arg> this_type;

	/// default constructor.
	VariablePtr();

	/// creates an instance with the pointer.
	VariablePtr(pointer const ptr, bool const add_ref = true);

	/// copy constructor.
	VariablePtr(this_type const &);

	/// move constructor.
	VariablePtr(this_type &&);

	/// destructor.
	~VariablePtr();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

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
hryky::shader::VariablePtr<hryky_template_arg>::VariablePtr()
	: base_type()
{
}
/**
  @brief creates an instance with the pointer.
 */
template <hryky_template_param>
hryky::shader::VariablePtr<hryky_template_arg>::VariablePtr(
	pointer const ptr, bool const add_ref)
	: base_type(ptr, add_ref)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::shader::VariablePtr<hryky_template_arg>::VariablePtr(
	this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::shader::VariablePtr<hryky_template_arg>::VariablePtr(
	this_type && rhs)
	: base_type(std::move(rhs))
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::shader::VariablePtr<hryky_template_arg>::~VariablePtr()
{
}
/**
  @brief creates an assignment.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::shader::TermPtr<hryky::shader::Assign> 
hryky::shader::VariablePtr<hryky_template_arg>::operator=(
	TermPtr<RhsT> const & rhs) const
{
	return this->base_type::operator=(rhs);
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::shader::VariablePtr<hryky_template_arg>::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::shader::VariablePtr<hryky_template_arg>::swap(
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
hryky::shader::VariablePtr<hryky_template_arg>::write_to(
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
#endif // SHADER_VARIABLE_PTR_H_20140821161842346
// end of file
