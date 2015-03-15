/**
  @file     shader_declare.h
  @brief    writes out the declaration of node.
  @author   HRYKY
  @version  $Id: shader_declare.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_DECLARE_H_20140821103526107
#define SHADER_DECLARE_H_20140821103526107
#include "hryky/shader/shader_assign.h"
#include "hryky/shader/shader_coder.h"
#include "hryky/shader/shader_dispatcher.h"
#include "hryky/shader/shader_function.h"
#include "hryky/shader/shader_functions.h"
#include "hryky/shader/shader_inputs.h"
#include "hryky/shader/shader_matrix.h"
#include "hryky/shader/shader_multiply.h"
#include "hryky/shader/shader_outputs.h"
#include "hryky/shader/shader_uniforms.h"
#include "hryky/shader/shader_vector.h"
#include "hryky/shader/shader_literal.h"
#include "hryky/shader/shader_type_base.h"
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
	/// writes out the declaration of node.
	class Declare;

	class Coder;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief writes out the declaration of node.
 */
class hryky::shader::Declare :
	public ImmutableDispatcherImpl<Declare>
{
public :

	typedef ImmutableDispatcherImpl<Declare> base_type;

	typedef Declare this_type;

	/// creates an instance with a coder.
	Declare(Coder & coder);

	/// writes out the declaration of node.
	template <typename NodeT>
	void operator()(NodeT const & node);

protected :

private :
	hryky_delete_default_constructor(Declare);
	hryky_delete_copy_constructor(Declare);
	hryky_delete_copy_assign_op(Declare);

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
  @brief writes out the declaration of node.
 */
template <typename NodeT>
void hryky::shader::Declare::operator()(NodeT const & node)
{
	node.declare_impl(this->coder_);
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
#endif // SHADER_DECLARE_H_20140821103526107
// end of file
