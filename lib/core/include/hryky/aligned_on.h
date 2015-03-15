/**
  @file     aligned_on.h
  @brief    selects the aligned type from exponent of Power of 2.
  @author   HRYKY
  @version  $Id: aligned_on.h 355 2014-06-22 08:47:38Z hryky.private@gmail.com $
 */
#ifndef ALIGNED_ON_H_20140621160841339
#define ALIGNED_ON_H_20140621160841339
#include "hryky/tmp/tmp_pow.h"
#include "hryky/stdint.h"
#include "hryky/definition.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	size_t Exponent
#define hryky_template_arg \
	Exponent
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// selects the aligned type from exponent of Power of 2.
	template <hryky_template_param>
	class AlignedOn;

	/// selects the aligned type from the byte of alignment.
	template <size_t Bytes>
	class AlignedOnBytes;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief selects the aligned type from exponent of Power of 2.
 */
template <hryky_template_param>
class hryky::AlignedOn
{
public :
	typedef typename AlignedOnBytes<
		tmp::PowC<2, Exponent>::value>::type type;
};
/**
  @brief selects the aligned type from the byte of alignment.
 */
template <size_t>
class hryky::AlignedOnBytes
{
public :
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief aligned on 1.
 */
template <>
class AlignedOnBytes<1>
{
public :
	union type
	{
		uint8_t uint8_;
	};
};
/**
  @brief aligned on 2.
 */
template <>
class AlignedOnBytes<2>
{
public :
	union type
	{
		hryky_aligned(2, uint8_t uint8_);
	};
};
/**
  @brief aligned on 4.
 */
template <>
class AlignedOnBytes<4>
{
public :
	union type
	{
		hryky_aligned(4, uint8_t uint8_);
	};
};
/**
  @brief aligned on 8.
 */
template <>
class AlignedOnBytes<8>
{
public :
	union type
	{
		hryky_aligned(8, uint8_t uint8_);
	};
};
/**
  @brief aligned on 16.
 */
template <>
class AlignedOnBytes<16>
{
public :
	union type
	{
		hryky_aligned(16, uint8_t uint8_);
	};
};
/**
  @brief aligned on 32.
 */
template <>
class AlignedOnBytes<32>
{
public :
	union type
	{
		hryky_aligned(32, uint8_t uint8_);
	};
};
/**
  @brief aligned on 64.
 */
template <>
class AlignedOnBytes<64>
{
public :
	union type
	{
		hryky_aligned(64, uint8_t uint8_);
	};
};
/**
  @brief aligned on 128.
 */
template <>
class AlignedOnBytes<128>
{
public :
	union type
	{
		hryky_aligned(128, uint8_t uint8_);
	};
};
/**
  @brief aligned on 256.
 */
template <>
class AlignedOnBytes<256>
{
public :
	union type
	{
		hryky_aligned(256, uint8_t uint8_);
	};
};
/**
  @brief aligned on 512.
 */
template <>
class AlignedOnBytes<512>
{
public :
	union type
	{
		hryky_aligned(512, uint8_t uint8_);
	};
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
#endif // ALIGNED_ON_H_20140621160841339
// end of file
