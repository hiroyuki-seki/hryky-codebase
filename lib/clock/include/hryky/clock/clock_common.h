/**
  @file         clock_common.h
  @brief        common definitions of clock module.
  @author       HRYKY
  @version      $Id: clock_common.h 374 2014-07-27 11:54:24Z hryky.private@gmail.com $
 */
#ifndef CLOCK_COMMON_H_20120218192544476
#define CLOCK_COMMON_H_20120218192544476
#include "hryky/without_copy.h"
#include "hryky/chrono.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace clock
{
	typedef ::std::chrono::high_resolution_clock    clock_type;
	typedef clock_type::time_point                  time_point;
	typedef chrono::Duration<
		clock_type::duration::rep,
		Ratio<
			clock_type::period::num,
			clock_type::period::den> > duration_type;
}
}
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
namespace clock
{
	/// retrieves the current clock.
	time_point now();

} // namespace clock
} // namespace hryky
#endif // CLOCK_COMMON_H_20120218192544476
// end of file
