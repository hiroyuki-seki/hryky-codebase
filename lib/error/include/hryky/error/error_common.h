/**
  @file         error_common.h
  @brief        common definitions for hryky::error module.
  @author       HRYKY
  @version      $Id: error_common.h 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#ifndef ERROR_COMMON_H_20120611170603379
#define ERROR_COMMON_H_20120611170603379
#include "hryky/error/error_holder.h"
//------------------------------------------------------------------------------
// define macross
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
	class Ptr;
} // namespace mempool
namespace error
{
	class Holder;

} // namespace error
typedef error::Holder error_type;
} // namespace hryky
//------------------------------------------------------------------------------
// struct declarations
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace error
{
	/// retrieves the instance which specifies that no error has occurred.
	error_type none();

	/// retrieves the mempool for hryky::error.
	mempool::Ptr const & mempool();

} // namespace error
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // ERROR_COMMON_H_20120611170603379
// end of file
