/**
  @file     shader_global_variables.h
  @brief    organizes the common functionalties to handle global variables.
  @author   HRYKY
  @version  $Id: shader_global_variables.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_GLOBAL_VARIABLES_H_20140824083454024
#define SHADER_GLOBAL_VARIABLES_H_20140824083454024
#include "hryky/shader/shader_block.h"
#include "hryky/shader/shader_declaration_of.h"
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
	class Coder;

namespace global
{
	/// organizes the common functionalties to handle global variables.
	template <typename DerivedT>
	class Variables;

} // namespace global
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief organizes the common functionalties to handle global variables.
 */
template <hryky_template_param>
class hryky::shader::global::Variables :
	public Block<DerivedT>
{
public :

	typedef Variables<hryky_template_arg> this_type;
	typedef Block<DerivedT> base_type;

	/// writes the information as the code of shader.
	Coder & code_impl(Coder & coder) const;

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
namespace global
{
} // namespace global
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief writes the information as the code of shader.
 */
template <hryky_template_param>
hryky::shader::Coder &
hryky::shader::global::Variables<hryky_template_arg>::code_impl(
	Coder & coder) const
{
	this->nodes().foreach([&coder](node_type const & node) {
		coder << declaration_of(*node) << ";" << hryky::endl;
	});
	return coder;
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
namespace global
{
} // namespace global
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
#endif // SHADER_GLOBAL_VARIABLES_H_20140824083454024
// end of file
