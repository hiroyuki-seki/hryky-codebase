/**
  @file         is_enum.h
  @brief        confirms whether the type is enum in compile time..
  @author       HRYKY
  @version      $Id: is_enum.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef IS_ENUM_H_20121230163951361
#define IS_ENUM_H_20121230163951361
#include "hryky/std/std_type_traits.h"
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// confirms whether the type is enum in compile time..
	template < typename ValueT >
	class IsEnum;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether the type is enum in compile time..
 */
template < typename ValueT >
class hryky::IsEnum
{
public :
	typedef IntegralConstant<
		bool, ::std::is_enum<ValueT>::value> type;
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
#endif // IS_ENUM_H_20121230163951361
// end of file
