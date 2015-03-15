/**
  @file         hamming_weight.h
  @brief        counts the number of non-zero values.
  @author       HRYKY
  @version      $Id: hamming_weight.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef HAMMING_WEIGHT_H_20130120175847415
#define HAMMING_WEIGHT_H_20130120175847415
#include "hryky/stdint.h"
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
	/// counts the number of non-zero bits in 64-bits value.
	uint8_t hamming_weight(uint64_t const value);

	/// counts the number of non-zero bits in 32-bits value.
	uint8_t hamming_weight(uint32_t const value);

	/// counts the number of non-zero bits in 16-bits value.
	uint8_t hamming_weight(uint16_t const value);

	/// counts the number of non-zero bits in 8-bits value.
	uint8_t hamming_weight(uint8_t const value);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HAMMING_WEIGHT_H_20130120175847415
// end of file
