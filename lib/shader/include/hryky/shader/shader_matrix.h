/**
  @file     shader_matrix.h
  @brief    specifies a variable as matrix.
  @author   HRYKY
  @version  $Id: shader_matrix.h 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#ifndef SHADER_MATRIX_H_20140803180312418
#define SHADER_MATRIX_H_20140803180312418
#include "hryky/shader/shader_variable.h"
#include "hryky/shader/shader_type_of.h"
#include "hryky/retention/retention_value.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	size_t Rows, size_t Columns
#define hryky_template_arg \
	Rows, Columns
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// specifies a variable as matrix.
	template <
		size_t Rows = 4,
		size_t Columns = 4
	>
	class Matrix;

	template <typename DerivedT>
	class VariablePtr;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief specifies a variable as matrix.
 */
template <hryky_template_param>
class hryky::shader::Matrix :
	public Variable<Matrix<hryky_template_arg> >,
	public WithSwap<Matrix<hryky_template_arg> >
{
public :

	struct TypeOf
	{
	};

	typedef Matrix<hryky_template_arg> this_type;
	typedef Variable<this_type> base_type;
	typedef String<> identifier_type;

	/// default constructor.
	Matrix();

	/// creates an instance with the identifier.
	Matrix(identifier_type const & identifier);

	/// copy constructor.
	Matrix(this_type const &);

	/// move constructor.
	Matrix(this_type &&);

	/// destructor.
	~Matrix();

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
  writes the type of Matrix.
 */
template <hryky_template_param>
class IsCodeAsIs<TypeOf<Matrix<hryky_template_arg> > >
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
hryky::shader::Matrix<hryky_template_arg>::Matrix()
	: base_type()
{
}
/**
  @brief creates an instance with the identifier.
 */
template <hryky_template_param>
hryky::shader::Matrix<hryky_template_arg>::Matrix(
	identifier_type const & identifier)
	: base_type(identifier)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::shader::Matrix<hryky_template_arg>::Matrix(
	this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::shader::Matrix<hryky_template_arg>::Matrix(
	this_type && rhs)
	: base_type(std::move(rhs))
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::shader::Matrix<hryky_template_arg>::~Matrix()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::shader::Matrix<hryky_template_arg>::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::shader::Matrix<hryky_template_arg>::swap(
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
hryky::shader::Matrix<hryky_template_arg>::write_to_impl(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("matrix");
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
	/// creates a matrix with 4 columns and 4 rows.
	template <size_t Size>
	VariablePtr<Matrix<4, 4> > mat4(
		char const (&identifier)[Size]);

namespace detail
{
	/// writes out the type of Matrix.
	template <hryky_template_param>
	Coder & code(
		Coder & lhs,
		TypeOf<Matrix<hryky_template_arg> > const &);

} // namespace detail
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a matrix with 4 columns and 4 rows.
 */
template <size_t Size>
hryky::shader::VariablePtr<hryky::shader::Matrix<4, 4> >
hryky::shader::mat4(
	char const (&identifier)[Size])
{
	typedef Matrix<4, 4> value_type;
	allocator::Mempool<value_type> allocator;
	return VariablePtr<value_type>(allocator::instantiate_by(
		allocator, identifier));
}
/**
  @brief writes out the type of Matrix.
 */
template <hryky_template_param>
hryky::shader::Coder &
hryky::shader::detail::code(
	Coder & lhs,
	TypeOf<Matrix<hryky_template_arg> > const &)
{
	return lhs << "mat" << Columns << 'x' << Rows;
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SHADER_MATRIX_H_20140803180312418
// end of file
