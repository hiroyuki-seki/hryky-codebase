/**
  @file     shader_function.h
  @brief    expresses the definition of function.
  @author   HRYKY
  @version  $Id: shader_function.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_FUNCTION_H_20140803160547337
#define SHADER_FUNCTION_H_20140803160547337
#include "hryky/retention/retention_value.h"
#include "hryky/shader/shader_arguments.h"
#include "hryky/shader/shader_node_ptr.h"
#include "hryky/shader/shader_statements.h"
#include "hryky/shader/shader_type_ptr.h"
#include "hryky/string.h"
#include "hryky/vector.h"
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
	/// expresses the definition of function.
	class Function;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief expresses the definition of function.
 */
class hryky::shader::Function :
	public Statements<Function>
{
public :

	typedef Function this_type;
	typedef Statements<this_type> base_type;
	typedef String<> name_type;
	typedef TypePtr rettype_type;
	typedef Arguments arguments_type;

	/// default constructor.
	Function();

	/// creates a function without a returned value.
	Function(name_type const & name);

	/// copy constructor.
	Function(this_type const &);

	/// move constructor.
	Function(this_type &&);

	/// destructor.
	~Function();

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to_impl(StreamT & out) const;

	/// retrieves the container of arguments.
	arguments_type & arguments();

	/// writes out the code of node.
	Coder & code_impl(Coder & coder) const;
	
	/// writes out the prototype of function.
	Coder & declare_impl(Coder & coder) const;

protected :

private :
	hryky_delete_this_copy_assign_op(Function);

	name_type name_;
	rettype_type rettype_;
	arguments_type arguments_;

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
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT &
hryky::shader::Function::write_to_impl(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(name);
	out << stream::denote("block");
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
#endif // SHADER_FUNCTION_H_20140803160547337
// end of file
