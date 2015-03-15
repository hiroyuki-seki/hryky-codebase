/**
  @file     float_traits.h
  @brief    traits for floating point.
  @author   HRYKY
  @version  $Id: float_traits.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef FLOAT_TRAITS_H_20131005011945722
#define FLOAT_TRAITS_H_20131005011945722
#include "hryky/bitmask.h"
#include "hryky/stdint.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename FloatT
#define hryky_template_arg \
	FloatT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// traits for floating point.
	template <hryky_template_param>
	class FloatTraits;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief traits for floating point.
 */
template <typename FloatT>
class hryky::FloatTraits
{
public :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief specializes single-precision.
 */
template <>
class FloatTraits<float>
{
public :

	typedef uint32_t binary_type;

	static uint8_t const significant_width = 7u;
	
	static uint8_t const sign_offset = 31u;
	static uint8_t const sign_width = 1u;
	static binary_type const sign_mask =
		Bitmask<sign_width, sign_offset, binary_type>::value;
	
	static uint8_t const exponent_offset = 23u;
	static uint8_t const exponent_width = 8u;
	static binary_type const exponent_mask =
		Bitmask<exponent_width, exponent_offset, binary_type>::value;

	static uint8_t const fraction_offset = 0u;
	static uint8_t const fraction_width = 23u;
	static binary_type const fraction_mask =
		Bitmask<fraction_width, fraction_offset, binary_type>::value;

};
/**
  @brief specializes single-precision.
 */
template <>
class FloatTraits<double>
{
public :

	typedef uint64_t binary_type;

	static uint8_t const significant_width = 14u;
	
	static uint8_t const sign_offset = 63u;
	static uint8_t const sign_width = 1u;
	static binary_type const sign_mask =
		Bitmask<sign_width, sign_offset, binary_type>::value;
	
	static uint8_t const exponent_offset = 52u;
	static uint8_t const exponent_width = 11u;
	static binary_type const exponent_mask =
		Bitmask<exponent_width, exponent_offset, binary_type>::value;

	static uint8_t const fraction_offset = 0u;
	static uint8_t const fraction_width = 52u;
	static binary_type const fraction_mask =
		Bitmask<fraction_width, fraction_offset, binary_type>::value;

};
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
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
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // FLOAT_TRAITS_H_20131005011945722
// end of file
