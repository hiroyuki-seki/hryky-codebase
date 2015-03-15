/**
  @file         align.h
  @brief        rounds an integer value along the specified boundary.
  @author       HRYKY
  @version      $Id: align.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef ALIGN_H_20130105173617400
#define ALIGN_H_20130105173617400
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
	/// represents an alignment in bits.
	typedef uint8_t alignment_type;

	/**
	  @brief    rounds down an integer value to the nearest value aligned in bit.
	  @param    value is the value to be rounded down.
	  @param    alignment is the number of alignment in bits.
	  @return   rounded value
	 */
	template < typename T >
	T align_floor(T value, alignment_type alignment);

	/**
	  @brief    rounds up an integer value to the nearest value aligned in bit.
	  @param    value is the value to be rounded up.
	  @param    alignment is the number of alignment in bits.
	  @return   rounded value
	 */
	template < typename T >
	T align_ceil(T value, alignment_type alignment);
	
	/**
	  @brief    confirms whether an integer value is aligned in bit
	  @param    value is the value to be confirmed.
	  @param    alignment is the number of alignment in bits.
	  @return   aligned or not aligned
	 */
	template < typename T >
	bool is_aligned(T value, alignment_type alignment);

	/**
	  @internal
	  @brief    rounds down an integer value to the nearest value aligned in bit.
	  @param    value is the value to be rounded down.
	  @param    alignment is the number of alignment in bits.
	  @return   rounded value
	  @endinternal
	 */
	template < typename T >
	T * align_floor(T * value, alignment_type alignment);

	/**
	  @internal
	  @brief    rounds up an integer value to the nearest value aligned in bit.
	  @param    value is the value to be rounded up.
	  @param    alignment is the number of alignment in bits.
	  @return   rounded value
	  @endinternal
	 */
	template < typename T >
	T * align_ceil(T * value, alignment_type alignment);

	/**
	  @internal
	  @brief    confirms whether an integer value is aligned in bit
	  @param    value is the value to be confirmed.
	  @param    alignment is the number of alignment in bits.
	  @return   aligned or not aligned
	  @endinternal
	 */
	template < typename T >
	bool is_aligned(T * value, alignment_type alignment);

	/**
	  @brief    rounds down an integer value to the nearest value aligned
	            in the unit of the value.
	  @param    value is the value to be rounded down.
	  @param    alignment is the number of alignment in units.
	  @return   rounded value
	 */
	template < typename T >
	T align_floor_unit(T value, T alignment);

	/**
	  @brief    rounds up an integer value to the nearest value aligned
	            in the unit of the value.
	  @param    value is the value to be rounded up.
	  @param    alignment is the number of alignment in units.
	  @return   rounded value
	 */
	template < typename T >
	T align_ceil_unit(T value, T alignment);
	
	/**
	  @brief    confirms whether an integer value is aligned in the unit
	            of the value.
	  @param    value is the value to be confirmed.
	  @param    alignment is the number of alignment in units.
	  @return   aligned or not aligned
	 */
	template < typename T >
	bool is_aligned_unit(T value, T alignment);

	/**
	  @internal
	  @brief    rounds down an integer value to the nearest value aligned
	            in the unit of the value.
	  @param    value is the value to be rounded down.
	  @param    alignment is the number of alignment in units.
	  @return   rounded value
	  @endinternal
	 */
	template < typename T >
	T * align_floor_unit(T * value, size_t const alignment);

	/**
	  @internal
	  @brief    rounds up an integer value to the nearest value aligned in
	            the unit of the value.
	  @param    value is the value to be rounded up.
	  @param    alignment is the number of alignment in units.
	  @return   rounded value
	  @endinternal
	 */
	template < typename T >
	T * align_ceil_unit(T * value, size_t const alignment);

	/**
	  @internal
	  @brief    confirms whether an integer value is aligned in the
	            unit of the value.
	  @param    value is the value to be confirmed.
	  @param    alignment is the number of alignment in units.
	  @return   aligned or not aligned
	  @endinternal
	 */
	template < typename T >
	bool is_aligned_unit(T * value, size_t const alignment);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief    rounds down an integer value to the nearest value aligned in bit.
  @param    value is the value to be rounded down.
  @param    alignment is the number of alignment in bits.
  @return   rounded value
 */
template < typename T >
T hryky::align_floor(T value, alignment_type alignment)
{ 
	return static_cast<T>(
		static_cast<size_t>(value)
		& ~static_cast<size_t>((1 << (alignment)) - 1));
}
/**
  @brief    rounds up an integer value to the nearest value aligned in bit.
  @param    value is the value to be rounded up.
  @param    alignment is the number of alignment in bits.
  @return   rounded value
 */
template < typename T >
T hryky::align_ceil(T value, alignment_type alignment)
{
	return align_floor(
		static_cast<T>(
			static_cast<size_t>(value) + ((1 << (alignment)) - 1)),
		alignment);
}
/**
  @brief    confirms whether an integer value is aligned in bit
  @param    value is the value to be confirmed.
  @param    alignment is the number of alignment in bits.
  @return   aligned or not aligned
 */
template < typename T >
bool hryky::is_aligned(T value, alignment_type alignment)
{
	return (0 == (
		static_cast<size_t>(value)
		& static_cast<size_t>((1 << (alignment)) - 1)));
}
/**
  @internal
  @brief    rounds down a value to the nearest value aligned in bit.
  @param    value is the value to be rounded down.
  @param    alignment is the number of alignment in bits.
  @return   rounded value
  @endinternal
 */
template < typename T >
T * hryky::align_floor(T * value, alignment_type alignment)
{ 
	return reinterpret_cast<T *>(
		reinterpret_cast<size_t>(value)
		& ~static_cast<size_t>((1 << (alignment)) - 1));
}
/**
  @internal
  @brief    rounds up an integer value to the nearest value aligned in bit.
  @param    value is the value to be rounded up.
  @param    alignment is the number of alignment in bits.
  @return   rounded value
  @endinternal
 */
template < typename T >
T * hryky::align_ceil(T * value, alignment_type alignment)
{
	return align_floor(
		reinterpret_cast<T *>(
			reinterpret_cast<size_t>(value) + ((1 << (alignment)) - 1)),
		alignment);
}
/**
  @internal
  @brief    confirms whether an integer value is aligned in bit
  @param    value is the value to be confirmed.
  @param    alignment is the number of alignment in bits.
  @return   aligned or not aligned
  @endinternal
 */
template < typename T >
bool hryky::is_aligned(T * value, alignment_type alignment)
{
	return (0 == (
		reinterpret_cast<size_t>(value)
		& static_cast<size_t>((1 << (alignment)) - 1)));
}
/**
  @brief    rounds down an integer value to the nearest value aligned
            in the unit of the value.
  @param    value is the value to be rounded down.
  @param    alignment is the number of alignment in the unit of value.
  @return   rounded value
 */
template < typename T >
T hryky::align_floor_unit(T value, T alignment)
{ 
	return (value / alignment) * alignment;
}
/**
  @brief    rounds up an integer value to the nearest value aligned in
            the unit of the value.
  @param    value is the value to be rounded up.
  @param    alignment is the number of alignment in the unit of value.
  @return   rounded value
 */
template < typename T >
T hryky::align_ceil_unit(T value, T alignment)
{
	return align_floor_unit(value + alignment - 1, alignment);
}
/**
  @brief    confirms whether an integer value is aligned in the unit
            of the value.
  @param    value is the value to be confirmed.
  @param    alignment is the number of alignment in the unit of value.
  @return   aligned or not aligned
 */
template < typename T >
bool hryky::is_aligned_unit(T value, T alignment)
{
	return 0 == (value % alignment);
}
/**
  @internal
  @brief    rounds down a value to the nearest value aligned in the
            unit of the value.
  @param    value is the value to be rounded down.
  @param    alignment is the number of alignment in the unit of value.
  @return   rounded value
  @endinternal
 */
template < typename T >
T * hryky::align_floor_unit(T * value, size_t const alignment)
{ 
	return reinterpret_cast<T *>(
		reinterpret_cast<size_t>(value) / alignment * alignment);
}
/**
  @internal
  @brief    rounds up an integer value to the nearest value aligned in
            the unit of the value.
  @param    value is the value to be rounded up.
  @param    alignment is the number of alignment in bits.
  @return   rounded value
  @endinternal
 */
template < typename T >
T * hryky::align_ceil_unit(T * value, size_t const alignment)
{
	return align_floor_unit(
		reinterpret_cast<T *>(
			reinterpret_cast<size_t>(value) + alignment - 1),
		alignment);
}
/**
  @internal
  @brief    confirms whether an integer value is aligned in the unit
            of the value.
  @param    value is the value to be confirmed.
  @param    alignment is the number of alignment in bits.
  @return   aligned or not aligned
  @endinternal
 */
template < typename T >
bool hryky::is_aligned_unit(T * value, size_t const alignment)
{
	return 0 == (
		reinterpret_cast<size_t>(value) % alignment);
}
#endif // ALIGN_H_20130105173617400
// end of file
