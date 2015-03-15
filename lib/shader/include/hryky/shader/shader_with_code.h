/**
  @file     shader_with_code.h
  @brief    appends the feature to write code.
  @author   HRYKY
  @version  $Id: shader_with_code.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_WITH_CODE_H_20140830192207473
#define SHADER_WITH_CODE_H_20140830192207473
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
	/// appends the feature to write code.
	template <typename DerivedT>
	class WithCode;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief appends the feature to write code.
 */
template <hryky_template_param>
class hryky::shader::WithCode
{
public :

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
#endif // SHADER_WITH_CODE_H_20140830192207473
// end of file
