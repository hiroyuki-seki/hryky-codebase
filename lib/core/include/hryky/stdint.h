/**
  @file         stdint.h
  @brief        substitution for stdint.
  @author       HRYKY
  @version      $Id: stdint.h 366 2014-07-13 09:13:34Z hryky.private@gmail.com $
 */
#ifndef STDINT_H_20121230161004340
#define STDINT_H_20121230161004340
#include "hryky/std/std_cstdint.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	typedef unsigned char           uint8_t;
	typedef signed char             int8_t;
	typedef unsigned short int      uint16_t;
	typedef signed short int        int16_t;
	typedef unsigned long int       uint32_t;
	typedef signed long int         int32_t;
	typedef unsigned long long int  uint64_t;
	typedef signed long long int    int64_t;

	typedef unsigned int            uint_t;
	typedef signed int              int_t;

	typedef intmax_t                intmax_t;
	typedef uintmax_t               uintmax_t;

	/// alias for 8bit data.
	typedef uint8_t                 octet_type;

	typedef char16_t                char16_t;
	typedef char32_t                char32_t;

	typedef size_t                  size_t;
	typedef intptr_t                intrptr_t;
	typedef uintptr_t               uintptr_t;

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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // STDINT_H_20121230161004340
// end of file
