/**
  @file     strstr.h
  @brief    wraps strstr of C Standard Library.
  @author   HRYKY
  @version  $Id: strstr.h 348 2014-04-19 03:28:11Z hryky.private@gmail.com $
 */
#ifndef STRSTR_H_20140419072401975
#define STRSTR_H_20140419072401975
#include "hryky/std/std_cstring.h"
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
	/// uses strstr as it is.
	char const * strstr(
		char const * const str, char const * const target);

	/// uses strstr as it is.
	char * strstr(
		char * const str, char * const target);

	/// uses wcsstr through overloading.
	wchar_t const * strstr(
		wchar_t const * const str, wchar_t const * const target);

	/// uses wcsstr through overloading.
	wchar_t * strstr(
		wchar_t * const str, wchar_t * const target);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief uses strstr as it is.
 */
inline
char const * hryky::strstr(
	char const * const str, char const * const target)
{
	return ::std::strstr(str, target);
}
/**
  @brief uses strstr as it is.
 */
inline
char * hryky::strstr(char * const str, char * const target)
{
	return ::std::strstr(str, target);
}
/**
  @brief uses wcsstr through overloading.
 */
inline
wchar_t const * hryky::strstr(
	wchar_t const * const str, wchar_t const * const target)
{
	return ::std::wcsstr(str, target);
}
/**
  @brief uses wcsstr through overloading.
 */
inline
wchar_t * hryky::strstr(
	wchar_t * const str, wchar_t * const target)
{
	return ::std::wcsstr(str, target);
}
#endif // STRSTR_H_20140419072401975
// end of file
