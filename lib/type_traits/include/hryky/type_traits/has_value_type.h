/**
  @file     has_value_type.h
  @brief    confirms whether a class has a type named "value_type".
  @author   HRYKY
  @version  $Id: has_value_type.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef HAS_VALUE_TYPE_H_20140527062743935
#define HAS_VALUE_TYPE_H_20140527062743935
#include "hryky/type_traits/integral_constant.h"
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
	/// confirms whether a class has a type named "value_type".
	template <typename ValueT>
	class HasValueType;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether a class has a type named "value_type".
 */
template <hryky_template_param>
class hryky::HasValueType
{
	template <typename TargetT>
	static uint16_t test(typename TargetT::value_type const * const);

	template <typename>
	static uint8_t test(...);
public :
	typedef IntegralConstant<
		bool, sizeof(uint16_t) == sizeof(test<ValueT>(0))> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // HAS_VALUE_TYPE_H_20140527062743935
// end of file
