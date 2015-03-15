/**
  @file         exclusion_common.h
  @brief        common definitions of exclusion module.
  @author       HRYKY
  @version      $Id: exclusion_common.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
  @addtogroup   exclusion_control
  @{
 */
#ifndef EXCLUSION_COMMON_H_20120218180013416
#define EXCLUSION_COMMON_H_20120218180013416
#include "hryky/chrono.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace exclusion
{
	/// represents waiting time to join
	typedef chrono::nanoseconds duration_type;

	duration_type const g_default_duration(chrono::seconds(5));

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
#endif // EXCLUSION_COMMON_H_20120218180013416
/// @}
// end of file
