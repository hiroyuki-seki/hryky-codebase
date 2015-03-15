/**
  @file     strnlen.h
  @brief    detects a null-terminator in a string.
  @author   HRYKY
  @version  $Id: strnlen.h 362 2014-07-07 09:43:31Z hryky.private@gmail.com $
 */
#ifndef STRNLEN_H_20131006115008159
#define STRNLEN_H_20131006115008159
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
	/// detects a null-terminator in a string.
	template <typename CharT>
	size_t strnlen(CharT const * const cstr, size_t const limit);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief detects a null-terminator in a string.
 */
template <typename CharT>
size_t hryky::strnlen(CharT const * const cstr, size_t const limit)
{
	size_t size pos = 0;
	for (; limit != pos; ++pos) {
		if ('\0' == cstr[pos]) {
			return pos;
		}
	}
	return pos;
}
#endif // STRNLEN_H_20131006115008159
// end of file
