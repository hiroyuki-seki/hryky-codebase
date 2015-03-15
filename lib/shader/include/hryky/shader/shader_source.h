/**
  @file     shader_source.h
  @brief    retains one compilation unit.
  @author   HRYKY
  @version  $Id: shader_source.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_SOURCE_H_20140803180953423
#define SHADER_SOURCE_H_20140803180953423
#include "hryky/clear.h"
#include "hryky/shader/shader_block_ptr.h"
#include "hryky/shader/shader_coder.h"
#include "hryky/shader/shader_function_ptr.h"
#include "hryky/shader/shader_functions.h"
#include "hryky/shader/shader_inputs.h"
#include "hryky/shader/shader_node.h"
#include "hryky/shader/shader_node.h"
#include "hryky/shader/shader_outputs.h"
#include "hryky/shader/shader_uniforms.h"
#include "hryky/shader/shader_vector.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename DerivedT
#define hryky_template_arg \
	DerivedT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// retains one compilation unit.
	template <hryky_template_param>
	class Source;

	class FunctionPtr;

	class Coder;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains one compilation unit.
 */
template <hryky_template_param>
class hryky::shader::Source :
	public WithStreamOut<Source<hryky_template_arg> >,
	public WithSwap<Source<hryky_template_arg> >,
	public WithCode<DerivedT>
{
public :

	typedef Source<hryky_template_arg> this_type;
	typedef Inputs inputs_type;
	typedef Outputs outputs_type;
	typedef Uniforms uniforms_type;
	typedef Functions functions_type;

	/// appends a definition of function.
	DerivedT & operator<<(FunctionPtr const & src);

	/// retreives the mutable collection for inputs variables.
	inputs_type & inputs();

	/// retreives the mutable collection for uniform variables.
	uniforms_type & uniforms();

	/// retreives the mutable collection for output variables.
	outputs_type & outputs();

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// writes the information as the code of shader.
	Coder & code(Coder & coder) const;

protected :

	/// default constructor.
	Source();

	/// copy constructor.
	Source(this_type const &);

	/// move constructor.
	Source(this_type &&);

	/// destructor.
	~Source();

private :
	hryky_delete_this_copy_assign_op(this_type);

	/// appends reference counter of each node.
	void add_ref();

	inputs_type inputs_;
	outputs_type outputs_;
	uniforms_type uniforms_;
	functions_type functions_;

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
  @brief default constructor.
 */
template <hryky_template_param>
hryky::shader::Source<hryky_template_arg>::Source()
	: inputs_()
	  , outputs_()
	  , uniforms_()
	  , functions_()
{
	this->add_ref();
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::shader::Source<hryky_template_arg>::Source(
	this_type const & rhs)
	: hryky_copy_member(inputs)
	  , hryky_copy_member(outputs)
	  , hryky_copy_member(uniforms)
	  , hryky_copy_member(functions)
{
	this->add_ref();
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::shader::Source<hryky_template_arg>::Source(
	this_type && rhs)
	: hryky_move_member(inputs)
	  , hryky_move_member(outputs)
	  , hryky_move_member(uniforms)
	  , hryky_move_member(functions)
{
	this->add_ref();
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::shader::Source<hryky_template_arg>::~Source()
{
}
/**
  @brief appends a definition of function.
 */
template <hryky_template_param>
DerivedT &
hryky::shader::Source<hryky_template_arg>::operator<<(
	FunctionPtr const & src)
{
	this->functions_.append(src);
	return *static_cast<DerivedT *>(this);
}
/**
  @brief retreives the mutable collection for input variables.
 */
template <hryky_template_param>
typename hryky::shader::Source<hryky_template_arg>::inputs_type &
hryky::shader::Source<hryky_template_arg>::inputs()
{
	return this->inputs_;
}
/**
  @brief retreives the mutable collection for uniform variables.
 */
template <hryky_template_param>
typename hryky::shader::Source<hryky_template_arg>::uniforms_type &
hryky::shader::Source<hryky_template_arg>::uniforms()
{
	return this->uniforms_;
}
/**
  @brief retreives the mutable collection for output variables.
 */
template <hryky_template_param>
typename hryky::shader::Source<hryky_template_arg>::outputs_type &
hryky::shader::Source<hryky_template_arg>::outputs()
{
	return this->outputs_;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::shader::Source<hryky_template_arg>::clear()
{
	hryky::clear(this->functions_);
	hryky::clear(this->uniforms_);
	hryky::clear(this->outputs_);
	hryky::clear(this->inputs_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::shader::Source<hryky_template_arg>::swap(
	this_type & src)
{
	hryky_swap_member(inputs);
	hryky_swap_member(outputs);
	hryky_swap_member(uniforms);
	hryky_swap_member(functions);
}
/**
  @brief writes the information as the code of shader.
 */
template <hryky_template_param>
hryky::shader::Coder &
hryky::shader::Source<hryky_template_arg>::code(
	Coder & coder) const
{
	return (coder
			<< this->inputs_
			<< this->outputs_
			<< this->uniforms_
			<< this->functions_);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::shader::Source<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(inputs);
	hryky_write_member(outputs);
	hryky_write_member(uniforms);
	hryky_write_member(functions);
	return out;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief appends reference counter of each node.
 */
template <hryky_template_param>
void hryky::shader::Source<hryky_template_arg>::add_ref()
{
	this->inputs_.add_ref();
	this->outputs_.add_ref();
	this->uniforms_.add_ref();
	this->functions_.add_ref();
}
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
#endif // SHADER_SOURCE_H_20140803180953423
// end of file
