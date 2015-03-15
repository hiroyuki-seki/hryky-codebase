/**
  @file         error_common.cpp
  @brief        common definitions for hryky::error module.
  @author       HRYKY
  @version      $Id: error_common.cpp 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/error/error_common.h"
#include "hryky/mempool/mempool_standard.h"
#include "hryky/mempool/mempool_adapter.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace error
{
namespace
{
	mempool::Adapter<mempool::Standard> g_mempool;
	mempool::Ptr const g_mempool_ptr(&g_mempool);
	
} // namespace "anonymous"
} // namespace error
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the instance which specifies that no error has occurred.
 */
hryky::error_type
hryky::error::none()
{
	return error_type();
}
/**
  @brief retrieves the mempool for hryky::error.
 */
hryky::mempool::Ptr const &
hryky::error::mempool()
{
	return g_mempool_ptr;
}
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace error
{
namespace
{
} // namespace "anonymous"
} // namespace error
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
