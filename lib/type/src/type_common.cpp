/**
  @file         type_common.cpp
  @brief        common definitions for hryky::type.
  @author       HRYKY
  @version      $Id: type_common.cpp 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/type/type_common.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace type
{
namespace
{
	/// the incremental id for all types.
	id_type g_id_ = 0;
	
} // namespace "anonymous"
} // namespace type
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief increments the id of type.
 */
hryky::type::id_type hryky::type::issue_id()
{
	return g_id_++;
}
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace type
{
namespace
{
} // namespace "anonymous"
} // namespace type
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
