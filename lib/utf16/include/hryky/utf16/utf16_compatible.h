/**
  @file     utf16_compatible.h
  @brief    confirms whether the type can be converted to utf16.
  @author   HRYKY
  @version  $Id: utf16_compatible.h 352 2014-06-08 08:48:59Z hryky.private@gmail.com $
 */
#ifndef UTF16_COMPATIBLE_H_20140325173721400
#define UTF16_COMPATIBLE_H_20140325173721400
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
namespace utf16
{
	/// confirms whether the type can be converted to utf16.
	template <typename ValueT>
	class Compatible;

} // namespace utf16
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether the type can be converted to utf16.
 */
template <hryky_template_param>
class hryky::utf16::Compatible
{
public :
	typedef false_type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace utf16
{
/**
  specializes char16_t
 */
template <>
class Compatible<char16_t>
{
public :
	typedef true_type type;
};
/**
  specializes wchar_t
 */
template <>
class Compatible<wchar_t>
{
public :
	typedef IntegralConstant<
		bool,
		sizeof(wchar_t) == sizeof(char16_t)> type;
};
} // namespace utf16
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
namespace utf16
{
} // namespace utf16
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // UTF16_COMPATIBLE_H_20140325173721400
// end of file
