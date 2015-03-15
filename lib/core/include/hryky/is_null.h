/**
  @file     is_null.h
  @brief    confirms whether the value is regarded as null.
  @author   HRYKY
  @version  $Id: is_null.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef IS_NULL_H_20140626094101070
#define IS_NULL_H_20140626094101070
#include "hryky/nullptr.h"
#include "hryky/type_traits/has_invalid.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_is_null(value) hryky_is_null::adl(value)
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
	/// confirms whether the pointer is null.
	bool is_null(void const * const ptr);

} // namespace hryky
namespace hryky_is_null
{
	/// confirms whether the value is regarded as null.
	template <typename ValueT>
	bool adl(ValueT const & src);

} // namespace _hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief confirms whether the pointer is null.
 */
inline
bool hryky::is_null(void const * const ptr)
{
	return hryky_nullptr == ptr;
}
/**
  @brief confirms whether the value is regarded as null.
 */
template <typename ValueT>
bool hryky_is_null::adl(ValueT const & src)
{
	using namespace hryky;
	
	return is_null(src);
}
#endif // IS_NULL_H_20140626094101070
// end of file
