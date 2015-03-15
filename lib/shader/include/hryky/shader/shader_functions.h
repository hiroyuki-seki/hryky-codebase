/**
  @file     shader_functions.h
  @brief    composes functions in the global scope.
  @author   HRYKY
  @version  $Id: shader_functions.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_GLOBAL_H_20140803205124535
#define SHADER_GLOBAL_H_20140803205124535
#include "hryky/shader/shader_block.h"
#include "hryky/shader/shader_function_ptr.h"
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
	/// composes functions in the global scope.
	class Functions;

	class FunctionPtr;
	class Coder;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief composes functions in the global scope.
 */
class hryky::shader::Functions :
	public Block<Functions, FunctionPtr>,
	public WithSwap<Functions>
{
public :

	typedef Functions this_type;
	typedef Block<this_type, FunctionPtr> base_type;

	/// default constructor.
	Functions();

	/// copy constructor.
	Functions(this_type const &);

	/// move constructor.
	Functions(this_type &&);

	/// destructor.
	~Functions();

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to_impl(StreamT & out) const;

	/// writes out the code of this node.
	Coder & code_impl(Coder & coder) const;

protected :

private :
	hryky_delete_this_copy_assign_op(Functions);

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
hryky::shader::Functions::write_to_impl(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("functions");
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
#endif // SHADER_GLOBAL_H_20140803205124535
// end of file
