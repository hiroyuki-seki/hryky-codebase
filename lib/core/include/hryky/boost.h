/**
  @file     boost.h
  @brief    aggregates the use of Boost C++ Library.
  @author   HRYKY
  @version  $Id: boost.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef BOOST_H_20140125132407225
#define BOOST_H_20140125132407225
#include "hryky/config.h"
#include "hryky/pragma.h"
#if HRYKY_USE_BOOST
#   pragma hryky_pragma_push_warning
#       pragma hryky_pragma_disable_warning_padded
#       pragma hryky_pragma_disable_warning_undef
#       pragma hryky_pragma_disable_warning_unknown_warning
#       pragma hryky_pragma_disable_warning_invalid_macro
#       pragma hryky_pragma_disable_warning_sign_conversion
#       pragma hryky_pragma_disable_warning_base_copy_constructor
#       pragma hryky_pragma_disable_warning_base_assign_operator
#       pragma hryky_pragma_disable_warning_catch_variadic
#       pragma hryky_pragma_disable_warning_unthreadsafe_instance
#       pragma hryky_pragma_disable_warning_change_layout
#       pragma hryky_pragma_disable_warning_unused_value
#       pragma hryky_pragma_disable_warning_conversion
#       pragma hryky_pragma_disable_warning_bad_function_cast
#       pragma hryky_pragma_disable_warning_switch_enum
#       pragma hryky_pragma_disable_warning_overload_binary_op
#       pragma hryky_pragma_disable_warning_changed_behavior
#       pragma hryky_pragma_disable_warning_codepage
#       pragma hryky_pragma_disable_warning_trancated_name
#       pragma hryky_pragma_disable_warning_deprecated_api
#       if HRYKY_USE_BOOST_ASIO
#           include <boost/asio.hpp>
#       endif
#       include <boost/scoped_array.hpp>
#       include <boost/integer_traits.hpp>
#       include <boost/exception/all.hpp>
#       include <boost/assert.hpp>
#       include <boost/call_traits.hpp>

#       if HRYKY_USE_BOOST_FILESYSTEM
#           include <boost/filesystem.hpp>
#           include <boost/filesystem/fstream.hpp>
#       endif

#       if HRYKY_USE_BOOST_EXCLUSION
#           include <boost/thread.hpp>
#       endif
#   pragma hryky_pragma_pop_warning
#endif // HRYKY_USE_BOOSt
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
// struct declaration
//------------------------------------------------------------------------------
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
#endif // BOOST_H_20140125132407225
// end of file
