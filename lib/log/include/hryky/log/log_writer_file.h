/**
  @file         log_writer_file.h
  @brief        output log message.
  @author       HRYKY
  @version      $Id: log_writer_file.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef LOG_WRITER_H_20111105101354092
#define LOG_WRITER_H_20111105101354092
#include "hryky/common.h"
#include "hryky/exclusion/exclusion_mutex.h"
#include "hryky/log/log_writer_base.h"
#include "hryky/mempool/mempool_adapter.h"
#include "hryky/mempool/mempool_standard.h"
#include "hryky/pragma.h"
#include "hryky/string.h"
#include "hryky/without_copy.h"
#include "hryky/path.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
#pragma hryky_pragma_disable_warning_virtual_destructor
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
	/// output log message to a file
	class File;
	
} // namespace writer
} // namespace log
namespace exclusion
{
	template < typename LockableT >
	class Lock;
}
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief output log message.
 */
class hryky::log::writer::File :
	public Base
{
public :

	typedef File    this_type;
	typedef Base    base_type;

	/// default constructor
	File();

	/// creates an instance with the path to the logged file.
	File(path_type const & path);

	/// destrunctor
	~File();

	/// assign a new path.
	void path(path_type const & src);

protected :

private :

	typedef exclusion::Mutex                lockable_type;
	typedef exclusion::Lock<lockable_type>  lock_type;

	typedef mempool::Adapter<mempool::Standard> mempool_type;

	hryky_delete_this_copy_constructor(File);
	hryky_delete_this_copy_assign_op(File);

	/// writes out the bufferred messages
	virtual void flush_impl();

	/// writes out a string.
	virtual bool write_impl(
		char const * const str, size_t const size);

	mempool_type            mempool_;
	String<>                log_;       ///< log(UTF-8)
	path_type               path_;      ///< log-file path
	lockable_type           lockable_;  ///< mutex for logging

};
//------------------------------------------------------------------------------
// inline functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // LOG_WRITER_H_20111105101354092
// end of file
