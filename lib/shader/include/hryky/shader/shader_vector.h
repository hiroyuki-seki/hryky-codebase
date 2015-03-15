/**
  @file     shader_vector.h
  @brief    specifies a variable as vector.
  @author   HRYKY
  @version  $Id: shader_vector.h 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#ifndef SHADER_VECTOR_H_20140803174105403
#define SHADER_VECTOR_H_20140803174105403
#include "hryky/shader/shader_variable.h"
#include "hryky/shader/shader_term_ptr.h"
#include "hryky/shader/shader_coder.h"
#include "hryky/shader/shader_type_of.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, \
	size_t Dimension
#define hryky_template_arg \
	ValueT, Dimension
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// specifies a variable as vector.
	template <
		typename ValueT = float,
		size_t Dimension = 4
	>
	class Vector;

	template <typename DerivedT>
	class VariablePtr;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief specifies a variable as vector.
 */
template <hryky_template_param>
class hryky::shader::Vector :
	public Variable<Vector<hryky_template_arg> >,
	public WithSwap<Vector<hryky_template_arg> >
{
public :

	typedef Vector<hryky_template_arg> this_type;
	typedef Variable<this_type> base_type;
	typedef String<> identifier_type;

	/// default constructor.
	Vector();

	/// creates an instance with the identifier.
	Vector(identifier_type const & identifier);

	/// copy constructor.
	Vector(this_type const &);

	/// move constructor.
	Vector(this_type &&);

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// destructor.
	~Vector();

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to_impl(StreamT & out) const;

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
namespace detail
{
/**
  writes the type of Vector<float>.
 */
template <hryky_template_param>
class IsCodeAsIs<TypeOf<Vector<hryky_template_arg> > >
{
public :
	typedef false_type type;
	static type::value_type const value = type::value;
};
} // namespace detail
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::shader::Vector<hryky_template_arg>::Vector()
	: base_type()
{
}
/**
  @brief creates an instance with the identifier.
 */
template <hryky_template_param>
hryky::shader::Vector<hryky_template_arg>::Vector(
	identifier_type const & identifier)
	: base_type(identifier)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::shader::Vector<hryky_template_arg>::Vector(
	this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::shader::Vector<hryky_template_arg>::Vector(
	this_type && rhs)
	: base_type(std::move(rhs))
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::shader::Vector<hryky_template_arg>::~Vector()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::shader::Vector<hryky_template_arg>::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::shader::Vector<hryky_template_arg>::swap(
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
hryky::shader::Vector<hryky_template_arg>::write_to_impl(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("vector");
	this->base_type::write_to_impl(out);
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
	/// creates a vector with 4 float components.
	template <size_t Size>
	VariablePtr<Vector<float, 4> > vec4(
		char const (&identifier)[Size]);

namespace detail
{
	/// writes out the type of Vector<float, N>.
	template <size_t Dimension>
	Coder & code(
		Coder & lhs,
		TypeOf<Vector<float, Dimension> > const &);

	/// writes out the type of Vector<int, N>.
	template <size_t Dimension>
	Coder & code(
		Coder & lhs,
		TypeOf<Vector<int, Dimension> > const &);

	/// writes out the type of Vector<bool, N>.
	template <size_t Dimension>
	Coder & code(
		Coder & lhs,
		TypeOf<Vector<bool, Dimension> > const &);

} // namespace detail
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a vector with 4 float components.
 */
template <size_t Size>
hryky::shader::VariablePtr<hryky::shader::Vector<float, 4> >
hryky::shader::vec4(
	char const (&identifier)[Size])
{
	typedef Vector<float, 4> value_type;
	allocator::Mempool<value_type> allocator;
	return VariablePtr<value_type>(allocator::instantiate_by(
		allocator, identifier));
}
/**
  @brief writes out the type of Vector<float, N>.
 */
template <size_t Dimension>
hryky::shader::Coder &
hryky::shader::detail::code(
	Coder & lhs,
	TypeOf<Vector<float, Dimension> > const &)
{
	return lhs << "vec" << Dimension;
}
/**
  @brief writes out the type of Vector<int, N>.
 */
template <size_t Dimension>
hryky::shader::Coder &
hryky::shader::detail::code(
	Coder & lhs,
	TypeOf<Vector<int, Dimension> > const &)
{
	return lhs << "ivec" << Dimension;
}
/**
  @brief writes out the type of Vector<bool, N>.
 */
template <size_t Dimension>
hryky::shader::Coder &
hryky::shader::detail::code(
	Coder & lhs,
	TypeOf<Vector<bool, Dimension> > const &)
{
	return lhs << "bvec" << Dimension;
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SHADER_VECTOR_H_20140803174105403
// end of file
