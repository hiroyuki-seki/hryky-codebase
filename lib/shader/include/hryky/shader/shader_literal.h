/**
  @file     shader_literal.h
  @brief    retains a literal value.
  @author   HRYKY
  @version  $Id: shader_literal.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_LITERAL_H_20140825174901409
#define SHADER_LITERAL_H_20140825174901409
#include "hryky/shader/shader_term_ptr.h"
#include "hryky/shader/shader_dispatchee.h"
#include "hryky/retention/retention_value.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT
#define hryky_template_arg \
	ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// retains a literal value.
	template <typename ValueT>
	class Literal;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a literal value.
 */
template <hryky_template_param>
class hryky::shader::Literal :
	public Dispatchee<Literal<hryky_template_arg> >,
	protected retention::Value<ValueT>
{
public :

	typedef Literal<hryky_template_arg> this_type;
	typedef Dispatchee<this_type> base_type;
	typedef ValueT const initializer_type;

	/// default constructor.
	Literal();

	/// creates an instance with the initial value.
	Literal(initializer_type initilizer);

	/// copy constructor.
	Literal(this_type const &);

	/// move constructor.
	Literal(this_type &&);

	/// destructor.
	~Literal();

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
	StreamT & Write_to_impl(StreamT & out) const;

	/// writes out the code of the literal value.
	Coder & code_impl(Coder & coder) const;

protected :
	typedef retention::Value<ValueT> retain_type;

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
hryky::shader::Literal<hryky_template_arg>::Literal()
	: base_type()
	  , retain_type()
{
}
/**
  @brief creates an instance with the initial value.
 */
template <hryky_template_param>
hryky::shader::Literal<hryky_template_arg>::Literal(
	initializer_type initilizer)
	: base_type()
	  , retain_type(initilizer)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::shader::Literal<hryky_template_arg>::Literal(
	this_type const & rhs)
	: base_type(rhs)
	  , retain_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::shader::Literal<hryky_template_arg>::Literal(
	this_type && rhs)
	: base_type(std::move(rhs))
	  , retain_type(std::move(rhs))
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::shader::Literal<hryky_template_arg>::~Literal()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::shader::Literal<hryky_template_arg>::clear()
{
	this->retain_type::clear();
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::shader::Literal<hryky_template_arg>::swap(
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
StreamT &
hryky::shader::Literal<hryky_template_arg>::Write_to_impl(
	StreamT & out) const
{
	return this->retain_type::Write_to(out);
}
/**
  @brief writes out the code of the literal value.
 */
template <hryky_template_param>
hryky::shader::Coder &
hryky::shader::Literal<hryky_template_arg>::code_impl(
	Coder & coder) const
{
	return coder << *this->get();
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
	/// creates a floating-point value.
	TermPtr<Literal<float> > literal(
		float const value);

namespace detail
{
	/// creates a literal value.
	template <hryky_template_param>
	TermPtr<Literal<hryky_template_arg> > literal(
		ValueT const value);

} // namespace detail
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a floating-point value.
 */
inline
hryky::shader::TermPtr<hryky::shader::Literal<float> >
hryky::shader::literal(
	float const value)
{
	return detail::literal<float>(value);
}
/**
  @brief creates a literal value.
 */
template <hryky_template_param>
hryky::shader::TermPtr<hryky::shader::Literal<hryky_template_arg> > 
hryky::shader::detail::literal(
	ValueT const value)
{
	typedef Literal<hryky_template_arg> value_type;
	allocator::Mempool<value_type> allocator;
	return TermPtr<value_type>(allocator::instantiate_by(
		allocator, value));
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SHADER_LITERAL_H_20140825174901409
// end of file
