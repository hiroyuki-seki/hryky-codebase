/**
  @file     shader_uniform.h
  @brief    collects uniform variables.
  @author   HRYKY
  @version  $Id: shader_uniforms.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_UNIFORMS_H_20140803173244397
#define SHADER_UNIFORMS_H_20140803173244397
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
	/// collects uniform variables.
	class Uniforms;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief collects uniform variables.
 */
class hryky::shader::Uniforms :
	public global::Variables<Uniforms>,
	public WithSwap<Uniforms>
{
public :

	typedef Uniforms this_type;
	typedef global::Variables<this_type> base_type;

	/// default constructor.
	Uniforms();

	/// copy constructor.
	Uniforms(this_type const &);

	/// move constructor.
	Uniforms(this_type &&);

	/// destructor.
	~Uniforms();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// appends a variable as an uniform variable.
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
  @brief appends a variable as an uniform variable.
 */
template <typename RhsT>
hryky::shader::Uniforms &
hryky::shader::Uniforms::operator<<(
	VariablePtr<RhsT> const & rhs)
{
	rhs->as(Storage::Kind::uniform);
	this->append(rhs);
	return *this;
}
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT &
hryky::shader::Uniforms::write_to_impl(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("uniform");
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
#endif // SHADER_UNIFORMS_H_20140803173244397
// end of file
