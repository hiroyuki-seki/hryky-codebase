/**
  @file     shader_input.h
  @brief    collects input variables.
  @author   HRYKY
  @version  $Id: shader_inputs.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_INPUTS_H_20140803165940374
#define SHADER_INPUTS_H_20140803165940374
#include "hryky/shader/shader_global_variables.h"
#include "hryky/shader/shader_node_ptr.h"
#include "hryky/shader/shader_variable.h"
#include "hryky/shader/shader_variable_ptr.h"
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
	/// collects input variables.
	class Inputs;
	class Coder;

	template <typename DerivedT>
	class TermPtr;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief collects input variables.
 */
class hryky::shader::Inputs :
	public global::Variables<Inputs>,
	public WithSwap<Inputs>
{
public :

	typedef Inputs this_type;
	typedef global::Variables<this_type> base_type;

	/// default constructor.
	Inputs();

	/// copy constructor.
	Inputs(this_type const &);

	/// move constructor.
	Inputs(this_type &&);

	/// destructor.
	~Inputs();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// appends a variable as input.
	template <typename RhsT>
	this_type & operator<<(VariablePtr<RhsT> const & rhs);

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
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief appends a variable as input.
 */
template <typename RhsT>
hryky::shader::Inputs &
hryky::shader::Inputs::operator<<(
	VariablePtr<RhsT> const & rhs)
{
	rhs->as(Storage::Kind::in);
	this->append(rhs);
	return *this;
}
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT &
hryky::shader::Inputs::write_to_impl(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("input");
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
#endif // SHADER_INPUTS_H_20140803165940374
// end of file
