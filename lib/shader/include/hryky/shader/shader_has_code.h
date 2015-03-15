/**
  @file     shader_has_code.h
  @brief    confirms whether the class has the member function code().
  @author   HRYKY
  @version  $Id: shader_has_code.h 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#ifndef SHADER_HAS_CODE_H_20140823191228466
#define SHADER_HAS_CODE_H_20140823191228466
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT
#define hryky_template_arg \
	ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	class Coder;

namespace shader
{
namespace detail
{
	/// confirms whether the class has the member function code().
	template <typename ValueT>
	class HasCode;
} // namespace detail
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether the class has the member function code().
 */
template <hryky_template_param>
class hryky::shader::detail::HasCode
{
	template <typename TargetT, Coder & (TargetT::*)(Coder &) const>
	struct Test;

	template <typename TargetT>
	static uint16_t test(Test<TargetT, &TargetT::code> *);

	template <typename>
	static uint8_t test(...);
	
public :
	typedef IntegralConstant<
		bool, sizeof(uint16_t) == sizeof(test<ValueT>(0))> type;
	static typename type::value_type const value = type::value;
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
#endif // SHADER_HAS_CODE_H_20140823191228466
// end of file
