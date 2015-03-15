/**
  @file     strlen.h
  @brief    measures the length of null-terminated string.
  @author   HRYKY
  @version  $Id: strlen.h 362 2014-07-07 09:43:31Z hryky.private@gmail.com $
 */
#ifndef STRLEN_H_20140707093124063
#define STRLEN_H_20140707093124063
#include "hryky/stdint.h"
#include "hryky/std/std_cstring.h"
#include "hryky/std/std_cwchar.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
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
	/// measures the length of null-terminated string.
	size_t strlen(char const * const c_str);

	/// measures the length of wide null-terminated string.
	size_t strlen(wchar_t const * const c_str);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief measures the length of null-terminated string.
 */
inline
hryky::size_t
hryky::strlen(char const * const c_str)
{
	return ::std::strlen(c_str);
}
/**
  @brief measures the length of wide null-terminated string.
 */
inline
hryky::size_t
hryky::strlen(wchar_t const * const c_str)
{
	return ::std::wcslen(c_str);
}
#endif // STRLEN_H_20140707093124063
// end of file
