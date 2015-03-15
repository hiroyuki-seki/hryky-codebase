/**
  @file     std_mutex.h
  @brief    suppresses warnings in mutex.
  @author   HRYKY
  @version  $Id: std_mutex.h 347 2014-04-13 07:49:18Z hryky.private@gmail.com $
 */
#ifndef STD_MUTEX_H_20140322203621525
#define STD_MUTEX_H_20140322203621525
#include "hryky/pragma.h"
#pragma hryky_pragma_push_warning
#   pragma hryky_pragma_disable_warning_virtual_destructor
#   pragma hryky_pragma_disable_warning_unused_value
#   include <mutex>
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
#endif // STD_MUTEX_H_20140322203621525
// end of file
