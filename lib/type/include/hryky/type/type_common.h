/**
  @file         type_common.h
  @brief        common definitions for hryky::type.
  @author       HRYKY
  @version      $Id: type_common.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef TYPE_COMMON_H_20121216182949437
#define TYPE_COMMON_H_20121216182949437
#include "hryky/stdint.h"
#include "hryky/literal_string.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace type
{
	/// unique id between each type.
	typedef uint32_t id_type;

	/// the invalid id of id_type.
	id_type const g_invalid_id = static_cast<id_type>(-1);

	typedef LiteralString<> name_type;
	
} // namespace type
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
namespace type
{
	/// retrieves the incremental id of type.
	id_type issue_id();

} // namespace type
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // TYPE_COMMON_H_20121216182949437
// end of file
