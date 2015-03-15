/**
  @file     shader_code.h
  @brief    dispatch the function code() polymorphically.
  @author   HRYKY
  @version  $Id: shader_code.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_CODE_H_20140820191303467
#define SHADER_CODE_H_20140820191303467
#include "hryky/shader/shader_assign.h"
#include "hryky/shader/shader_coder.h"
#include "hryky/shader/shader_dispatcher.h"
#include "hryky/shader/shader_function.h"
#include "hryky/shader/shader_functions.h"
#include "hryky/shader/shader_inputs.h"
#include "hryky/shader/shader_literal.h"
#include "hryky/shader/shader_matrix.h"
#include "hryky/shader/shader_multiply.h"
#include "hryky/shader/shader_outputs.h"
#include "hryky/shader/shader_type_base.h"
#include "hryky/shader/shader_uniforms.h"
#include "hryky/shader/shader_vector.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_virtual_functions
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
	/// dispatch the function code() polymorphically.
	class Code;

	class Coder;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief dispatch the function code() polymorphically.
 */
class hryky::shader::Code :
	public ImmutableDispatcherImpl<Code>
{
public :

	typedef ImmutableDispatcherImpl<Code> base_type;
	typedef Code this_type;

	/// creates an instance with a coder.
	Code(Coder & coder);

	/// writes the information as the code of shader.
	template <typename NodeT>
	void operator()(NodeT const & node) const;

protected :

private :
	hryky_delete_default_constructor(Code);
	hryky_delete_copy_constructor(Code);
	hryky_delete_copy_assign_op(Code);

	Coder & coder_;

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
  @brief writes the information as the code of shader.
 */
template <typename NodeT>
void hryky::shader::Code::operator()(NodeT const & node) const
{
	node.code_impl(this->coder_);
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
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // SHADER_CODE_H_20140820191303467
// end of file
