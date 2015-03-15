/**
  @file         memory_common.h
  @brief        common definition for hryky::memory module.
  @author       HRYKY
  @version      $Id: memory_common.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef MEMORY_COMMON_H_20130105172032389
#define MEMORY_COMMON_H_20130105172032389
#include "hryky/std/std_cstddef.h"
#include "hryky/std/std_cstring.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace memory
{
} // namespace memory
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
	/// fills memory with a octet.
	void * memset(
		void * const dest,
		int const octet,
		::std::size_t const count);

	/// copies the two separated regions of memory.
	void * memcpy(
		void * const dest,
		void const * const src,
		::std::size_t const count);

	/// copies the two regions of memory.
	void * memmove(
		void * const dest,
		void const * const src,
		::std::size_t const count);

	/// compares the two regions of memory.
	int memcmp(
		void const * const lhs,
		void const * const rhs,
		::std::size_t const count);

namespace memory
{
} // namespace memory
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief fills memory with a octet.
 */
inline void * hryky::memset(
	void * const dest, int const octet, ::std::size_t const count)
{
	return ::std::memset(dest, octet, count);
}
/**
  @brief copies the two separated regions of memory.
 */
inline void * hryky::memcpy(
	void * const dest, void const * const src, ::std::size_t const count)
{
	return ::std::memcpy(dest, src, count);
}
/**
  @brief copies the two regions of memory.
 */
inline void * hryky::memmove(
	void * const dest, void const * const src, ::std::size_t const count)
{
	return ::std::memmove(dest, src, count);
}
/**
  @brief compares the two regions of memory.
 */
inline int hryky::memcmp(
	void const * const lhs, void const * const rhs, ::std::size_t const count)
{
	return ::std::memcmp(lhs, rhs, count);
}
#endif // MEMORY_COMMON_H_20130105172032389
// end of file
