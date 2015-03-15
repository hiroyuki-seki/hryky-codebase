/**
  @file     shader_assign.h
  @brief    expresses an assignment.
  @author   HRYKY
  @version  $Id: shader_assign.h 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#ifndef SHADER_ASSIGN_H_20140803155903332
#define SHADER_ASSIGN_H_20140803155903332
#include "hryky/shader/shader_binary_op.h"
#include "hryky/shader/shader_term_ptr.h"
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
	/// expresses an assignment.
	class Assign;

	class Coder;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief expresses an assignment.
 */
class hryky::shader::Assign :
	public BinaryOp<Assign>
{
public :

	typedef Assign this_type;
	typedef BinaryOp<this_type> base_type;

	/// default constructor.
	Assign();

	/// creates an instance with both terms.
	template <typename LhsT, typename RhsT>
	Assign(TermPtr<LhsT> const & lhs, TermPtr<RhsT> const & rhs);

	/// copy constructor.
	Assign(this_type const &);

	/// move constructor.
	Assign(this_type &&);

	/// destructor.
	~Assign();

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to_impl(StreamT & out) const;

	/// writes out the code of assignment.
	Coder & code_impl(Coder & coder) const;

protected :

private :
	hryky_delete_this_copy_assign_op(Assign);

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
hryky::shader::Assign::Assign(
	TermPtr<LhsT> const & lhs, TermPtr<RhsT> const & rhs)
	: base_type(lhs, rhs)
{
}
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT &
hryky::shader::Assign::write_to_impl(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("assign");
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
#endif // SHADER_ASSIGN_H_20140803155903332
// end of file
