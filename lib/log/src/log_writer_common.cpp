/**
  @file         log_writer_common.cpp
  @brief        functions for log writer.
  @author       HRYKY
  @version      $Id: log_writer_common.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include <precompiled.h>
#include "hryky/exclusion/exclusion_lock.h"
#include "hryky/exclusion/exclusion_recursive_mutex.h"
#include "hryky/log/log_level_entity.h"
#include "hryky/log/log_writer_common.h"
#include "hryky/log/log_writer_stream.h"
#include "hryky/scoped_registry.h"
#include "hryky/std/std_iostream.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace log
{
namespace writer
{
namespace
{
	typedef ScopedRegistry<writer_type> registry_type;
	
	Stream< ::std::ostream>     g_default_writer(::std::clog);
	registry_type const         g_default_registry(&g_default_writer);
	exclusion::RecursiveMutex   g_mutex;
	
} // namespace *anonymous*
} // namespace writer
} // namespace log
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief logs a message.
 */
void hryky::log::write(
	level::Kind::Raw const level,
	char const * const str,
	size_t const str_size)
{
	exclusion::Lock<exclusion::RecursiveMutex> const
		lock(writer::g_mutex);
	
	writer_type * const writer = writer::registry_type::instance();
	if (hryky_is_null(writer)) {
		return;
	}
	writer::registry_type const
		prevent_recursive_write(&writer::g_default_writer);

	if (!writer->available(level_type(level))) {
		return;
	}

	(*writer)(str, str_size);
}
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace
{
}
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
