/**
  @file     shader_variable.h
  @brief    expresses a variable.
  @author   HRYKY
  @version  $Id: shader_variable.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_VARIABLE_H_20140803142718268
#define SHADER_VARIABLE_H_20140803142718268
#include "hryky/literal_string.h"
#include "hryky/retention/retention_value.h"
#include "hryky/shader/shader_interpolation.h"
#include "hryky/shader/shader_layout.h"
#include "hryky/shader/shader_parameter.h"
#include "hryky/shader/shader_precision.h"
#include "hryky/shader/shader_storage.h"
#include "hryky/shader/shader_dispatchee.h"
#include "hryky/shader/shader_type_ptr.h"
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
	/// expresses a variable.
	template <
		typename DerivedT
	>
	class Variable;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief expresses a variable.
 */
template <hryky_template_param>
class hryky::shader::Variable :
	public Dispatchee<DerivedT>,
	public WithSwap<Variable<hryky_template_arg> >,
	private retention::Value<String<> >
{
public :

	typedef Variable<hryky_template_arg> this_type;
	typedef Dispatchee<DerivedT> base_type;
	typedef String<> identifier_type;
	
	/// default constructor.
	Variable();

	/// creates an instance with the identifier.
	Variable(identifier_type const & identifier);

	/// copy constructor.
	Variable(this_type const &);

	/// move constructor.
	Variable(this_type &&);

	/// destructor.
	~Variable();

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
	StreamT & write_to_impl(StreamT & out) const;

	/// writes out the code of this variable.
	Coder & code_impl(Coder & coder) const;

	/// writes out the declaration of node.
	Coder & declare_impl(Coder & coder) const;

	/// qualifies this variable with a Storage Qualifier.
	void as(storage_type const & src);

	/// qualifies this variable with a Layout Qualifier.
	void as(layout_type const & src);

	/// qualifies this variable with a Interpolation Qualifier.
	void as(interpolation_type const & src);

	/// qualifies this variable with a Parameter Qualifier.
	void as(parameter_type const & src);

	/// qualifies this variable with a Precision Qualifier.
	void as(precision_type const & src);

protected :

	/// retrieves the identifier.
	identifier_type const & identifier() const;

private :
	typedef retention::Value<String<> > retain_type;

	storage_type        storage_;
	layout_type         layout_;
	interpolation_type  interpolation_;
	parameter_type      parameter_;
	precision_type      precision_;
	TypePtr             type_;

	union
	{
		uint32_t flags_;
		struct Flag
		{
			bool invariant_:1;
			bool coherent_:1;
			bool volatile_:1;
			bool restrict_:1;
			bool readonly_:1;
			bool writeonly_:1;
		} flag_;
	};
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
hryky::shader::Variable<hryky_template_arg>::Variable()
	: base_type()
	  , retain_type()
	  , storage_()
	  , layout_()
	  , interpolation_()
	  , parameter_()
	  , precision_()
	  , type_()
	  , flags_()
{
}
/**
  @brief creates an instance with the identifier.
 */
template <hryky_template_param>
hryky::shader::Variable<hryky_template_arg>::Variable(
	identifier_type const & identifier)
	: base_type()
	  , retain_type(identifier)
	  , storage_()
	  , layout_()
	  , interpolation_()
	  , parameter_()
	  , precision_()
	  , type_()
	  , flags_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::shader::Variable<hryky_template_arg>::Variable(
	this_type const & rhs)
	: base_type(rhs)
	  , retain_type(rhs)
	  , hryky_copy_member(storage)
	  , hryky_copy_member(layout)
	  , hryky_copy_member(interpolation)
	  , hryky_copy_member(parameter)
	  , hryky_copy_member(precision)
	  , hryky_copy_member(type)
	  , hryky_copy_member(flags)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::shader::Variable<hryky_template_arg>::Variable(
	this_type && rhs)
	: base_type(std::move(rhs))
	  , retain_type(std::move(rhs))
	  , hryky_move_member(storage)
	  , hryky_move_member(layout)
	  , hryky_move_member(interpolation)
	  , hryky_move_member(parameter)
	  , hryky_move_member(precision)
	  , hryky_move_member(type)
	  , hryky_move_member(flags)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::shader::Variable<hryky_template_arg>::~Variable()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::shader::Variable<hryky_template_arg>::clear()
{
	hryky::clear(this->flags_);
	hryky::clear(this->type_);
	hryky::clear(this->precision_);
	hryky::clear(this->parameter_);
	hryky::clear(this->interpolation_);
	hryky::clear(this->layout_);
	hryky::clear(this->storage_);
	this->retain_type::clear();
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::shader::Variable<hryky_template_arg>::swap(
	this_type & src)
{
	this->base_type::swap(src);
	this->retain_type::swap(src);
	hryky_swap_member(storage);
	hryky_swap_member(layout);
	hryky_swap_member(interpolation);
	hryky_swap_member(parameter);
	hryky_swap_member(precision);
	hryky_swap_member(type);
	hryky_swap_member(flags);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::shader::Variable<hryky_template_arg>::write_to_impl(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("variable");
	this->retain_type::write_to(out);
	hryky_write_member(storage);
	hryky_write_member(layout);
	hryky_write_member(interpolation);
	hryky_write_member(parameter);
	hryky_write_member(precision);
	hryky_write_member(type);
	return out;
}
/**
  @brief writes out the code of this variable.
 */
template <hryky_template_param>
hryky::shader::Coder &
hryky::shader::Variable<hryky_template_arg>::code_impl(
	Coder & coder) const
{
	return coder << this->identifier();
}
/**
  @brief writes out the declaration of node.
 */
template <hryky_template_param>
hryky::shader::Coder &
hryky::shader::Variable<hryky_template_arg>::declare_impl(
	Coder & coder) const
{
	return (
		coder
		<< this->storage_ << ' '
		<< TypeOf<DerivedT>() << ' '
		<< this->identifier());
}
/**
  @brief qualifies this variable with a Storage Qualifier.
 */
template <hryky_template_param>
void hryky::shader::Variable<hryky_template_arg>::as(
	storage_type const & src)
{
	this->storage_ = src;
}
/**
  @brief qualifies this variable with a Layout Qualifier.
 */
template <hryky_template_param>
void hryky::shader::Variable<hryky_template_arg>::as(
	layout_type const & src)
{
	this->layout_ = src;
}
/**
  @brief qualifies this variable with a Interpolation Qualifier.
 */
template <hryky_template_param>
void hryky::shader::Variable<hryky_template_arg>::as(
	interpolation_type const & src)
{
	this->interpolation_ = src;
}
/**
  @brief qualifies this variable with a Parameter Qualifier.
 */
template <hryky_template_param>
void hryky::shader::Variable<hryky_template_arg>::as(
	parameter_type const & src)
{
	this->parameter_ = src;
}
/**
  @brief qualifies this variable with a Precision Qualifier.
 */
template <hryky_template_param>
void hryky::shader::Variable<hryky_template_arg>::as(
	precision_type const & src)
{
	this->precision_ = src;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the identifier.
 */
template <hryky_template_param>
typename hryky::shader::Variable<hryky_template_arg>::identifier_type const & 
hryky::shader::Variable<hryky_template_arg>::identifier() const
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
#endif // SHADER_VARIABLE_H_20140803142718268
// end of file
