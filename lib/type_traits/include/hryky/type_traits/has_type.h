/**
  @file     has_type.h
  @brief    confirms whether a class has a type named "type".
  @author   HRYKY
  @version  $Id: has_type.h 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#ifndef HAS_TYPE_H_20140527062027930
#define HAS_TYPE_H_20140527062027930
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
	/// confirms whether a class has a type named "type".
	template <typename ValueT>
	class HasType;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether a class has a type named "type".
 */
template <hryky_template_param>
class hryky::HasType
{
	template <typename TargetT>
	static uint16_t test(typename TargetT::type const * const);
	
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
#endif // HAS_TYPE_H_20140527062027930
// end of file
