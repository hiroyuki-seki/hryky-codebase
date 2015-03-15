/**
  @file     is_boolean.h
  @brief    confirms whether the type is boolean.
  @author   HRYKY
  @version  $Id: is_boolean.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef IS_BOOLEAN_H_20140209171431385
#define IS_BOOLEAN_H_20140209171431385
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
	/// confirms whether the type is boolean.
	template <hryky_template_param>
	class IsBoolean;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether the type is boolean.
 */
template <typename ValueT>
class hryky::IsBoolean
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
  The type is boolean.
 */
template <>
class hryky::IsBoolean<bool>
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
#endif // IS_BOOLEAN_H_20140209171431385
// end of file
