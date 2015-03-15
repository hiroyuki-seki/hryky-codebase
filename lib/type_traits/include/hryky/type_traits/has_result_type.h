/**
  @file     has_result_type.h
  @brief    confirms whether a type has result_type.
  @author   HRYKY
  @version  $Id: has_result_type.h 353 2014-06-17 04:55:19Z hryky.private@gmail.com $
 */
#ifndef HAS_RESULT_TYPE_H_20140617050927881
#define HAS_RESULT_TYPE_H_20140617050927881
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
	/// confirms whether a type has result_type.
	template <typename ValueT>
	class HasResultType;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether a type has result_type.
 */
template <hryky_template_param>
class hryky::HasResultType
{
	template <typename TargetT>
	static uint16_t test(typename TargetT::result_type *);

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
#endif // HAS_RESULT_TYPE_H_20140617050927881
// end of file
