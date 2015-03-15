/**
  @file     std_thread.h
  @brief    suppresses warnings in thread.
  @author   HRYKY
  @version  $Id: std_thread.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef STD_THREAD_H_20140322203448524
#define STD_THREAD_H_20140322203448524
#include "hryky/pragma.h"
#pragma hryky_pragma_push_warning
#   pragma hryky_pragma_disable_warning_padded
#   pragma hryky_pragma_disable_warning_catch_variadic
#   pragma hryky_pragma_disable_warning_base_copy_constructor
#   pragma hryky_pragma_disable_warning_base_assign_operator
#   pragma hryky_pragma_disable_warning_virtual_destructor
#   pragma hryky_pragma_disable_warning_changed_behavior
#   include <thread>
#pragma hryky_pragma_pop_warning
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
#endif // STD_THREAD_H_20140322203448524
// end of file
