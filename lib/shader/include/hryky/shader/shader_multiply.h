/**
  @file     shader_multiply.h
  @brief    expresses a multiplication.
  @author   HRYKY
  @version  $Id: shader_multiply.h 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#ifndef SHADER_MULTIPLY_H_20140803151517302
#define SHADER_MULTIPLY_H_20140803151517302
#include "hryky/shader/shader_binary_op.h"
#include "hryky/shader/shader_term_ptr.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
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
	/// expresses a multiplication.
	class Multiply;

	class Coder;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief expresses a multiplication.
 */
class hryky::shader::Multiply :
	public BinaryOp<Multiply>,
	public WithSwap<Multiply>

{
public :

	typedef Multiply this_type;
	typedef BinaryOp<this_type> base_type;

	/// default constructor.
	Multiply();

	/// creates an instance with both terms.
	template <typename LhsT, typename RhsT>
	Multiply(TermPtr<LhsT> const & lhs, TermPtr<RhsT> const & rhs);

	/// copy constructor.
	Multiply(this_type const &);

	/// move constructor.
	Multiply(this_type &&);

	/// destructor.
	~Multiply();

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to_impl(StreamT & out) const;

	/// writes out the code of multiplication.
	Coder & code_impl(Coder & coder) const;

protected :

private :
	hryky_delete_this_copy_assign_op(Multiply);
	
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
  @brief creates an instance with both terms.
 */
template <typename LhsT, typename RhsT>
hryky::shader::Multiply::Multiply(
	TermPtr<LhsT> const & lhs, TermPtr<RhsT> const & rhs)
	: base_type(lhs, rhs)
{
}
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::shader::Multiply::write_to_impl(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("multiply");
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
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#endif // SHADER_MULTIPLY_H_20140803151517302
// end of file
