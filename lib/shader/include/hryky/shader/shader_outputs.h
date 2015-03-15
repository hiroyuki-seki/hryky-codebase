/**
  @file     shader_outputs.h
  @brief    collects output variables.
  @author   HRYKY
  @version  $Id: shader_outputs.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_OUTPUTS_H_20140803172932395
#define SHADER_OUTPUTS_H_20140803172932395
#include "hryky/vector.h"
#include "hryky/shader/shader_global_variables.h"
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
	/// collects output variables.
	class Outputs;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief collects output variables.
 */
class hryky::shader::Outputs :
	public global::Variables<Outputs>,
	public WithSwap<Outputs>
{
public :

	typedef Outputs this_type;
	typedef global::Variables<this_type> base_type;

	/// default constructor.
	Outputs();

	/// copy constructor.
	Outputs(this_type const &);

	/// move constructor.
	Outputs(this_type &&);

	/// destructor.
	~Outputs();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// appends a variable as an output variable.
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
  @brief appends a variable as an output variable.
 */
template <typename RhsT>
hryky::shader::Outputs &
hryky::shader::Outputs::operator<<(
	VariablePtr<RhsT> const & rhs)
{
	rhs->as(Storage::Kind::out);
	this->append(rhs);
	return *this;
}
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT &
hryky::shader::Outputs::write_to_impl(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("output");
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
#endif // SHADER_OUTPUTS_H_20140803172932395
// end of file
