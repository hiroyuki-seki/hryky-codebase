/**
  @file         log_writer_base.h
  @brief        The interface to output log message [interface].
  @author       HRYKY
  @version      $Id: log_writer_base.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef LOG_WRITER_BASE_H_20111105103115105
#define LOG_WRITER_BASE_H_20111105103115105
#include "hryky/log/log_level_entity.h"
#include "hryky/literal_string.h"
#include "hryky/without_copy.h"
#include "hryky/without_new.h"
#include "hryky/pragma.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_virtual_destructor
#pragma hryky_pragma_disable_warning_padded
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace debug
{
	class Source;
}
namespace log
{
namespace writer
{
	/// The interface to output log message
	class Base;
	
} // namespace writer
typedef writer::Base writer_type;

} // namespace log
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The interface to output log message.
 */
class hryky::log::writer::Base :
	private WithoutCopy,
	private WithoutNew
{
public :

	typedef Base this_type;///< self

	/**
	  @brief outputs a string.

	  The derived classes have to implement this function as
	  write_impl(char const * const, size_t const);
	 */
	bool operator()(char const * const str, size_t const size);
	
	/**
	  @brief write out bufferred messages.
	 */
	void flush()
	{
		this->flush_impl();
	};

	/// assigns the level than which the output of log is ignored less than.
	Base & lower(level_type const & level);

	/// assigns the level than which the output of log is ignored more than.
	Base & upper(level_type const & level);

	/// confirms whether the log level is in the available range.
	bool available(level_type const & level) const;

protected :

	/// default constructor
	Base();

	/// destrunctor
	~Base();

private :

	hryky_delete_this_copy_constructor(Base);
	hryky_delete_this_copy_assign_op(Base);

	/**
	  @brief outputs a string.
	 */
	virtual bool write_impl(
		char const * const str, size_t const size) = 0;

	/**
	  @brief write out bufferred messages.
	 */
	virtual void flush_impl()
	{
	};

	level_type  lower_;///< minimum limit
	level_type  upper_;///< maximum limit

};
//------------------------------------------------------------------------------
// inline functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// public function
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // LOG_WRITER_BASE_H_20111105103115105
// end of file
