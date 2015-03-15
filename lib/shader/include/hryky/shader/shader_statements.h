/**
  @file     shader_statements.h
  @brief    bundles statements.
  @author   HRYKY
  @version  $Id: shader_statements.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_STATEMENTS_H_20140824153232314
#define SHADER_STATEMENTS_H_20140824153232314
#include "hryky/shader/shader_block.h"
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
	/// bundles statements.
	template <typename DerivedT>
	class Statements;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief bundles statements.
 */
template <hryky_template_param>
class hryky::shader::Statements :
	public Block<DerivedT>
{
public :

	typedef Statements<hryky_template_arg> this_type;
	typedef Block<DerivedT> base_type;

	/// writes out the code of statements.
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
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief writes out the code of statements.
 */
template <hryky_template_param>
hryky::shader::Coder &
hryky::shader::Statements<hryky_template_arg>::code_impl(
	Coder & coder) const
{
	this->nodes().foreach([&coder](node_type const & node) {
		coder << node << ";" << hryky::endl;
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
#endif // SHADER_STATEMENTS_H_20140824153232314
// end of file
