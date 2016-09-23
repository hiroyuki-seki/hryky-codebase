/**
  @file     log_definition.h
  @brief    defines the common macro to utilize log module.
  @author   HRYKY
  @version  $Id: log_definition.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef LOG_DEFINITION_H_20140213072936978
#define LOG_DEFINITION_H_20140213072936978
#include "hryky/log/log_level_common.h"
#include "hryky/log/log_level_entity.h"
#include "hryky/stream/stream_endl.h"
#include "hryky/stream/ostream_string.h"
#include "hryky/debug/debug_source.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
/**
  @brief writes log message as hryky::log::level::Kind::emerg level.
 */
#define hryky_log_emerg(message) \
	hryky_log(hryky::log::level::Kind::emerg, message)
/**
  @brief writes log message as hryky::log::level::Kind::alert level.
 */
#define hryky_log_alert(message) \
	hryky_log(hryky::log::level::Kind::alert, message)
/**
  @brief writes log message as hryky::log::level::Kind::crit level.
 */
#define hryky_log_crit(message) \
	hryky_log(hryky::log::level::Kind::crit, message)
/**
  @brief writes log message as hryky::log::level::Kind::err level.
 */
#define hryky_log_err(message) \
	hryky_log(hryky::log::level::Kind::err, message)
/**
  @brief writes log message as hryky::log::level::Kind::warning level.
 */
#define hryky_log_warning(message) \
	hryky_log(hryky::log::level::Kind::warning, message)
/**
  @brief writes log message as hryky::log::level::Kind::notice level.
 */
#define hryky_log_notice(message) \
	hryky_log(hryky::log::level::Kind::notice, message)
/**
  @brief writes log message as hryky::log::level::Kind::info level.
 */
#define hryky_log_info(message) \
	hryky_log(hryky::log::level::Kind::info, message)
/**
  @brief writes log message as hryky::log::level::Kind::debug level.

  hryky_log_debug is compiled at only debug build.
 */
#if defined(NDEBUG)
#   define hryky_log_debug(message)
#else // defined(NDEBUG)
#   define hryky_log_debug(message) \
	hryky_log(hryky::log::level::Kind::debug, message)
#endif // defined(NDEBUG)

/**
  writes a log message with the arbitrary log-level.
 */
#define hryky_log(level, message) \
{ \
	hryky::mempool::Adapter<hryky::mempool::Standard> \
		_standard_mempool;\
	hryky::ostream::String<hryky::String<> > hryky_log_os(&_standard_mempool);\
	hryky_log_os << message; \
	hryky::log::write(hryky_source_position, (level), hryky_log_os); \
}
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace log
{
} // namespace log
} // namespace hryky
//------------------------------------------------------------------------------
// declares structs
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace log
{
	/// writes a arbitrary message out to the writer.
	template <typename SourceT, typename MessageT>
	void write(
		SourceT const & source,
		level::Kind::Raw const level,
		MessageT const & message);

	/// logs characters.
	void write(
		level::Kind::Raw const level,
		char const * const str,
		size_t const str_size);
	
} // namespace log
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief writes a arbitrary message out to the writer.
 */
template <typename SourceT, typename MessageT>
void hryky::log::write(
	SourceT const & source,
	level::Kind::Raw const level,
	MessageT const & message)
{
	mempool::Adapter<mempool::Standard> mempool;
	ostream::String<String<> > os(&mempool);
	os << source << level_type(level) << message << hryky::endl;

	write(level, os.str().data(), os.str().size());
}
#endif // LOG_DEFINITION_H_20140213072936978
// end of file
