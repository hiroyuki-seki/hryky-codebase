/**
  @file         log.h
  @brief        collection of the log modules.
  @author       HRYKY
  @version      $Id: log.h 375 2014-07-29 04:27:53Z hryky.private@gmail.com $
 */
#ifndef LOG_H_20111228003402690
#define LOG_H_20111228003402690

/**
  @page hryky::log logging

  This module is intended to output the runtime information.
  The destinations to which the information will be saved can be file or memory.
  The elements in the information can be hierarchical structures.

  @section writer_File hryky::log::writer::File

  hryky::log::writer::File writes messages out to a file.
  hryky::log::writer::File::operator() can be called thread safely.

  @dontinclude  common/test_main.cpp

  @subsection   Initialization instantiating writer
  @skip         // instantiates writer
  @until        log_writer;

  But in many case, the instance of this class can be registered to
  be used from all threads.

  @subsection   registration assignment of common writer
  @skip         // enregisters the writer
  @until        AutoRestore

  @subsection   logging output of the message with log-level

  to write simple message
  @skip         // output the information
  @until        hryky_log_

  @skip         // output the information
  @until        hryky_log_

  The difference between the log levels is documented with hryky::log::Level in log_level.h.

  @dontinclude  test_log.cpp

  manipulators can be passed to the logging macro.
  @skip         hryky_log_debug(
  @until        ::std::hex

  @example      test_main.cpp
  @example      test_log.cpp
  
 */
#include "hryky/log/log_common.h"
#include "hryky/log/log_definition.h"
#include "hryky/log/log_level_entity.h"
#include "hryky/log/log_level_common.h"
#include "hryky/log/log_writer_base.h"
#include "hryky/log/log_writer_common.h"
#include "hryky/log/log_writer_file.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
/// modules for logging progress.
namespace log
{
}
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
#endif // LOG_H_20111228003402690
// end of file
