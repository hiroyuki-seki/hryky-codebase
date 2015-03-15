/**
  @file     shader_write_to.h
  @brief    dispatches the function write_to() polymorphically.
  @author   HRYKY
  @version  $Id: shader_write_to.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_WRITE_TO_H_20140819112247140
#define SHADER_WRITE_TO_H_20140819112247140
#include "hryky/shader/shader_dispatcher.h"
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
#define hryky_template_param \
	typename OutputT
#define hryky_template_arg \
	OutputT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// dispatches the function write_to() polymorphically.
	template <typename OutputT>
	class WriteTo;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief dispatches the function write_to() polymorphically.
 */
template <hryky_template_param>
class hryky::shader::WriteTo :
	public ImmutableDispatcherImpl<WriteTo<hryky_template_arg> >
{
public :

	typedef WriteTo<hryky_template_arg> this_type;
	typedef ImmutableDispatcherImpl<this_type> base_type;

	/// creates an instance with the output.
	WriteTo(OutputT & output);

	/// writes the information of node.
	template <typename NodeT>
	void operator()(NodeT const & node) const;

protected :

private :
	hryky_delete_default_constructor(WriteTo);
	hryky_delete_this_copy_constructor(WriteTo);
	hryky_delete_this_copy_assign_op(this_type);

	OutputT & output_;
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
  @brief creates an instance with the output.
 */
template <hryky_template_param>
hryky::shader::WriteTo<hryky_template_arg>::WriteTo(
	OutputT & output)
	: base_type()
	  , output_(output)
{
}
/**
  @brief writes the information of node.
 */
template <hryky_template_param>
template <typename NodeT>
void hryky::shader::WriteTo<hryky_template_arg>::operator()(
	NodeT const & node) const
{
	node.write_to_impl(this->output_);
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
#undef hryky_template_param
#undef hryky_template_arg
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // SHADER_WRITE_TO_H_20140819112247140
// end of file
