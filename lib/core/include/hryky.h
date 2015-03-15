/**
  @file         hryky.h
  @brief        include the entire headers of hryky-codebase.
  @since        2011-11-23T10:48:45+0900
  @author       HRYKY
  @version      $Id: hryky.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $

  @mainpage hryky-codebase

  - @subpage hryky::log outputs runtime information with log-level.
  
  - @subpage hryky::memory allocates memory dynamically.
  
  - @subpage hryky::task dispatches tasks concurrentlly.
 */
#ifndef HRYKY_H_20111123104845117
#define HRYKY_H_20111123104845117

#include "hryky/config.h"
#include "hryky/common.h"
#include "hryky/log.h"
#include "hryky/memory.h"
#include "hryky/task.h"
#include "hryky/exclusion.h"

//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
/// the root of all namespaces in hryky-codebase.
namespace hryky
{
	uint32_t const g_version = HRYKY_CODEBASE_VERSION;
}
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// define global functions
//------------------------------------------------------------------------------
#endif // HRYKY_H_20111123104845117
// end of file
