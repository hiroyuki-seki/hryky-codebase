/**
  @file         hamming_weight.cpp
  @brief        counts the number of non-zero values.
  @author       HRYKY
  @version      $Id: hamming_weight.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $

  @sa http://en.wikipedia.org/wiki/Hamming_weight
 */
#include "precompiled.h"
#include "hryky/hamming_weight.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace
{
} // namespace "anonymous"
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief counts the number of non-zero bit in 64 bits value.
 */
uint8_t hryky::hamming_weight(uint64_t const value)
{
	uint64_t const bitmask_2bit = 0x5555555555555555u;// 01010101...
	uint64_t const bitmask_4bit = 0x3333333333333333u;// 00110011...
	uint64_t const bitmask_8bit = 0x0F0F0F0F0F0F0F0Fu;// 00001111...
	uint64_t const accumulator  = 0x0101010101010101u;

	// counts the number of non-zero bit in each 2bits.
	uint64_t const count_2bit =
		value - ((value >> 1) & bitmask_2bit);
	
	// counts the number of non-zero bit in each 4bits.
	uint64_t const count_4bit =
		(count_2bit & bitmask_4bit) + ((count_2bit >> 2) & bitmask_4bit);
	
	// counts the number of non-zero bit in each 8bits.
	uint64_t const count_8bit =
		(count_4bit + (count_4bit >> 4)) & bitmask_8bit;
	
	return (count_8bit * accumulator) >> 56;
}
/**
  @brief counts the number of non-zero bit in 32 bits value.
 */
uint8_t hryky::hamming_weight(uint32_t const value)
{
	uint32_t const bitmask_2bit = 0x55555555u;// 01010101...
	uint32_t const bitmask_4bit = 0x33333333u;// 00110011...
	uint32_t const bitmask_8bit = 0x0F0F0F0Fu;// 00001111...
	uint32_t const accumulator  = 0x01010101u;

	// counts the number of non-zero bit in each 2bits.
	uint32_t const count_2bit =
		value - ((value >> 1) & bitmask_2bit);
	
	// counts the number of non-zero bit in each 4bits.
	uint32_t const count_4bit =
		(count_2bit & bitmask_4bit) + ((count_2bit >> 2) & bitmask_4bit);
	
	// counts the number of non-zero bit in each 8bits.
	uint32_t const count_8bit =
		(count_4bit + (count_4bit >> 4)) & bitmask_8bit;
	
	return (count_8bit * accumulator) >> 24;
}
/**
  @brief counts the number of non-zero bit in 16 bits value.
 */
uint8_t hryky::hamming_weight(uint16_t const value)
{
	uint16_t const bitmask_2bit = 0x5555u;// 01010101...
	uint16_t const bitmask_4bit = 0x3333u;// 00110011...
	uint16_t const bitmask_8bit = 0x0F0Fu;// 00001111...
	uint16_t const accumulator  = 0x0101u;

	// counts the number of non-zero bit in each 2bits.
	uint16_t const count_2bit = static_cast<uint16_t>(
		value - ((value >> 1) & bitmask_2bit));
	
	// counts the number of non-zero bit in each 4bits.
	uint16_t const count_4bit = static_cast<uint16_t>(
		(count_2bit & bitmask_4bit) + ((count_2bit >> 2) & bitmask_4bit));
	
	// counts the number of non-zero bit in each 8bits.
	uint16_t const count_8bit = static_cast<uint16_t>(
		(count_4bit + (count_4bit >> 4)) & bitmask_8bit);
	
	return static_cast<uint8_t>(
		static_cast<uint16_t>(count_8bit * accumulator) >> 8);
}
/**
  @brief counts the number of non-zero bit in 8 bits value.
 */
uint8_t hryky::hamming_weight(uint8_t const value)
{
	return (
		(value & 0x1u) +
		((value >> 1) & 0x1u) +
		((value >> 2) & 0x1u) +
		((value >> 3) & 0x1u) +
		((value >> 4) & 0x1u) +
		((value >> 5) & 0x1u) +
		((value >> 6) & 0x1u) +
		((value >> 7) & 0x1u));
}
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace
{
} // namespace "anonymous"
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
