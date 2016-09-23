/**
  @file         stdint.h
  @brief        substitution for stdint.
  @author       HRYKY
  @version      $Id: stdint.h 366 2014-07-13 09:13:34Z hryky.private@gmail.com $
 */
#ifndef STDINT_H_20121230161004340
#define STDINT_H_20121230161004340
#include "hryky/definition.h"
#include "hryky/std/std_cstdint.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
#if hryky_cpp11
	typedef ::std::uint8_t          uint8_t;
	typedef ::std::int8_t           int8_t;
	typedef ::std::uint16_t         uint16_t;
	typedef ::std::int16_t          int16_t;
	typedef ::std::uint32_t         uint32_t;
	typedef ::std::int32_t          int32_t;
	typedef ::std::uint64_t         uint64_t;
	typedef ::std::int64_t          int64_t;
#else
	typedef unsigned char           uint8_t;
	typedef signed char             int8_t;
	typedef unsigned short int      uint16_t;
	typedef signed short int        int16_t;
	typedef unsigned long int       uint32_t;
	typedef signed long int         int32_t;
	typedef unsigned long long int  uint64_t;
	typedef signed long long int    int64_t;
#endif

	typedef unsigned int            uint_t;
	typedef signed int              int_t;

	typedef intmax_t                intmax_t;
	typedef uintmax_t               uintmax_t;

	/// alias for 8bit data.
	typedef uint8_t                 octet_type;

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
