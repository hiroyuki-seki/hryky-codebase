/**
  @file         date_month_common.h
  @brief        common definition for month.
  @author       HRYKY
  @version      $Id: date_month_common.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef DATE_MONTH_COMMON_H_20121229222914603
#define DATE_MONTH_COMMON_H_20121229222914603
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
namespace month
{
	struct Kind {
		enum Raw {
			january,
			february,
			march,
			april,
			may,
			june,
			july,
			august,
			september,
			october,
			november,
			december,
			num,
			invalid = -1,
		};
	};
	typedef hryky::Kind<Kind, Kind::invalid> kind_type;

} // namespace month

	typedef month::kind_type month_type;

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
namespace month
{
} // namespace month
} // namespace date
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // DATE_MONTH_COMMON_H_20121229222914603
// end of file
