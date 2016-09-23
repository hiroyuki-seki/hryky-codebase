/**
  @file     is_array.h
  @brief    confirms whether the type is built-in array.
  @author   HRYKY
  @version  $Id: is_array.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef IS_ARRAY_H_20140126083801026
#define IS_ARRAY_H_20140126083801026
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
	/// confirms whether the type is built-in array.
	template <hryky_template_param>
	class IsArray;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether the type is built-in array.
 */
template <typename ValueT>
class hryky::IsArray
{
public :
	typedef false_type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  ValueT is array.
 */
template <typename ValueT, size_t Size>
class IsArray<ValueT[Size]>
{
public :
	typedef true_type type;
};
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
#endif // IS_ARRAY_H_20140126083801026
// end of file
