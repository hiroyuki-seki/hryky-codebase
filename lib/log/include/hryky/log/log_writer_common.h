/**
  @file         log_writer_common.h
  @brief        functions for log writer.
  @author       HRYKY
  @version      $Id: log_writer_common.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef LOG_WRITER_COMMON_H_20111105105026118
#define LOG_WRITER_COMMON_H_20111105105026118
#include "hryky/scoped_registry.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace log
{
namespace writer
{
	class Base;
	typedef ScopedRegistry<Base> registry_type;
} // namespace writer
} // namespace log
} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// global function definition
//------------------------------------------------------------------------------
#endif // LOG_WRITER_COMMON_H_20111105105026118
// end of file
