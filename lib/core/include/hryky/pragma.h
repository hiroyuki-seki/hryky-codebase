/**
  @file     pragma.h
  @brief    defines the macro to utilize the compiler specific pragmas.
  @author   HRYKY
  @version  $Id: pragma.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef PRAGMA_H_20140322160522337
#define PRAGMA_H_20140322160522337
#include "hryky/config.h"

#if HRYKY_PLATFORM_WINDOWS
#   define hryky_pragma_push_warning                    warning(push)
#   define hryky_pragma_pop_warning                     warning(pop)
#   define hryky_pragma_disable_warning_padded          warning(disable:4820)
#   define hryky_pragma_disable_warning_undef           warning(disable:4668)
#   define hryky_pragma_disable_warning_unknown_pragmas warning(disable:4068)
#   define hryky_pragma_disable_warning_unknown_warning warning(disable:4619)
#   define hryky_pragma_disable_warning_invalid_macro   warning(disable:4574)
#   define hryky_pragma_disable_warning_sign_conversion warning(disable:4365)
#   define hryky_pragma_disable_warning_user_constructor \
	warning(disable:4610)
#   define hryky_pragma_disable_warning_base_default_constructor \
	warning(disable:4623)
#   define hryky_pragma_disable_warning_base_copy_constructor \
	warning(disable:4625)
#   define hryky_pragma_disable_warning_base_assign_operator warning(disable:4626)
#   define hryky_pragma_disable_warning_catch_variadic  warning(disable:4571)
#   define hryky_pragma_disable_warning_unthreadsafe_instance \
	warning(disable:4640)
#   define hryky_pragma_disable_warning_change_layout   warning(disable:4371)
#   define hryky_pragma_disable_warning_unused_value    warning(disable:4548)
#   define hryky_pragma_disable_warning_unused_variable warning(disable:4100)
#   define hryky_pragma_disable_warning_conversion      warning(disable:4242)
#   define hryky_pragma_disable_warning_bad_function_cast \
	warning(disable:4191)
#   define hryky_pragma_disable_warning_switch_enum     warning(disable:4061)
#   define hryky_pragma_disable_warning_overload_binary_op \
	warning(disable:4913)
#   define hryky_pragma_disable_warning_virtual_destructor \
	warning(disable:4265)
#   define hryky_pragma_disable_warning_virtual_functions \
	warning(disable:4263)
#   define hryky_pragma_disable_warning_changed_behavior \
	warning(disable:4350)
#   define hryky_pragma_disable_warning_inline          warning(disable:4710)
#   define hryky_pragma_disable_warning_codepage        warning(disable:4819)
#   define hryky_pragma_disable_warning_constant_condition \
	warning(disable:4127)
#   define hryky_pragma_disable_warning_create_default_constructor \
	warning(disable:4510)
#   define hryky_pragma_disable_warning_create_assign_operator \
	warning(disable:4512)
#   define hryky_pragma_disable_warning_trancated_name  warning(disable:4503)
#   define hryky_pragma_disable_warning_aligned_padded  warning(disable:4324)
#   define hryky_pragma_disable_warning_unreferenced_local_function \
	warning(disable:4505)
#   define hryky_pragma_disable_warning_deprecated_api warning(disable:4996)

#else
#   define hryky_pragma_push_warning
#   define hryky_pragma_pop_warning
#   define hryky_pragma_disable_warning_padded
#   define hryky_pragma_disable_warning_undef
#   define hryky_pragma_disable_warning_unknown_pragmas
#   define hryky_pragma_disable_warning_unknown_warning
#   define hryky_pragma_disable_warning_invalid_macro
#   define hryky_pragma_disable_warning_sign_conversion
#   define hryky_pragma_disable_warning_user_constructor
#   define hryky_pragma_disable_warning_base_default_constructor
#   define hryky_pragma_disable_warning_base_copy_constructor
#   define hryky_pragma_disable_warning_base_assign_operator
#   define hryky_pragma_disable_warning_catch_variadic
#   define hryky_pragma_disable_warning_unthreadsafe_instance
#   define hryky_pragma_disable_warning_change_layout
#   define hryky_pragma_disable_warning_unused_value
#   define hryky_pragma_disable_warning_unused_variable
#   define hryky_pragma_disable_warning_conversion
#   define hryky_pragma_disable_warning_bad_function_cast
#   define hryky_pragma_disable_warning_switch_enum
#   define hryky_pragma_disable_warning_overload_binary_op
#   define hryky_pragma_disable_warning_virtual_destructor
#   define hryky_pragma_disable_warning_virtual_functions
#   define hryky_pragma_disable_warning_changed_behavior
#   define hryky_pragma_disable_warning_inline
#   define hryky_pragma_disable_warning_codepage
#   define hryky_pragma_disable_warning_constant_condition
#   define hryky_pragma_disable_warning_create_default_constructor
#   define hryky_pragma_disable_warning_create_assign_operator
#   define hryky_pragma_disable_warning_trancated_name
#   define hryky_pragma_disable_warning_aligned_padded
#   define hryky_pragma_disable_warning_unreferenced_local_function
#   define hryky_pragma_disable_warning_deprecated_api
#endif
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
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
#endif // PRAGMA_H_20140322160522337
// end of file
