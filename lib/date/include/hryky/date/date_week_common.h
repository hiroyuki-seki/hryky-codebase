/**
  @file         date_week_common.h
  @brief        common definition for weekday.
  @author       HRYKY
  @version      $Id: date_week_common.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef DATE_WEEK_COMMON_H_20121229222634601
#define DATE_WEEK_COMMON_H_20121229222634601
#include "hryky/kind.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace date
{
namespace week
{
	struct Kind {
		enum Raw {
			sunday,
			monday,
			tuesday,
			wednesday,
			thursday,
			friday,
			saturday,
			num,
			invalid = -1,
		};
	};
	typedef hryky::Kind<Kind, Kind::invalid> kind_type;
	
} // namespace week

	typedef week::kind_type week_type;

} // namespace date
} // namespace hryky
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
namespace date
{
namespace week
{
} // namespace week
} // namespace date
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // DATE_WEEK_COMMON_H_20121229222634601
// end of file
