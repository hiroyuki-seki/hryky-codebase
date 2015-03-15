/**
  @file         testing_log.h
  @brief        outputs the log of the unit test at the end of scope.
  @author       HRYKY
  @version      $Id: testing_log.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef TESTING_LOG_H_20120428183514441
#define TESTING_LOG_H_20120428183514441
#include "hryky/intrusive_ptr.h"
#include "hryky/json/json_writer.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace testing
{
	/// outputs the log of the unit test at the end of scope.
	class Log;

namespace unit
{
	class Base;
} // namespace unit
} // namespace testing
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief outputs the log of the unit test at the end of scope.
 */
class hryky::testing::Log
{
public :

	typedef Log                                 this_type;
	typedef unit::Base &                        unit_type;
	typedef json::Writer<>                      writer_type;
	typedef stream::map::Scope<writer_type>     map_type;
	typedef stream::array::Scope<writer_type>   array_type;

	/// constructor.
	explicit Log(unit_type unit);
	
	/// destructor.
	~Log();

	/// retrieves the collection of the log.
	writer_type & writer();

protected :

private :

	hryky_delete_default_constructor(Log);
	hryky_delete_this_copy_constructor(Log);
	hryky_delete_this_copy_assign_op(Log);

	writer_type writer_;
	String<>    name_;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace
{
} // namespace "anonymous"
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace
{
} // namespace "anonymous"
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // TESTING_LOG_H_20120428183514441
// end of file
