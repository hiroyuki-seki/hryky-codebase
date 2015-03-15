/**
  @file     is_size.h
  @brief    confirms whether a type can be converted to the corresponding address.
  @author   HRYKY
  @version  $Id: is_size.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef IS_SIZE_H_20140330125919207
#define IS_SIZE_H_20140330125919207
#include "hryky/stdint.h"
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
	/// confirms whether a type can be converted to the corresponding address.
	template <typename ValueT>
	class IsSize;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether a type can be converted to the corresponding address.
 */
template <hryky_template_param>
class hryky::IsSize
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
  allows size_t
 */
template <>
class hryky::IsSize<size_t>
{
public :
	typedef true_type type;
};
/**
  allows intptr_t
 */
template <>
class hryky::IsSize<intptr_t>
{
public :
	typedef true_type type;
};
#if !HRYKY_PLATFORM_WINDOWS
/**
  allows uintptr_t
 */
template <>
class hryky::IsSize<uintptr_t>
{
public :
	typedef true_type type;
};
#endif // !HRYKY_PLATFORM_WINDOWS
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
#endif // IS_SIZE_H_20140330125919207
// end of file
