/**
  @file         precompiled.h
  @brief        precompiled header for hryky::exclusion.
  @author       HRYKY
  @version      $Id: precompiled.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef PRECOMPILED_H_20120911133727234
#define PRECOMPILED_H_20120911133727234
#include "hryky/config.h"
#if HRYKY_USE_BOOST_EXCLUSION
#   include "hryky/boost.h"
#else
#   include "hryky/std/std_mutex.h"
#   include "hryky/std/std_condition_variable.h"
#endif
#include "hryky/clear.h"
#include "hryky/definition.h"
#include "hryky/log.h"
#include "hryky/std/std_thread.h"
#include "hryky/stream.h"
#include "hryky/tmp.h"
#include "hryky/with_stream_out.h"
#include "hryky/without_copy.h"
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
#endif // PRECOMPILED_H_20120911133727234
// end of file
