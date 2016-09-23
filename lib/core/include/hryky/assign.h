/**
  @file     assign.h
  @brief    assigns to container.
  @author   HRYKY
  @version  $Id: assign.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef ASSIGN_H_20131209115714164
#define ASSIGN_H_20131209115714164
#include "hryky/range.h"
#include "hryky/std/std_type_traits.h"
#include "hryky/type_traits/is_array.h"
#include "hryky/type_traits/array_of.h"
#include "hryky/type_traits/enable_if.h"
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
	/// assigns array.
	template <typename ValueT>
	ValueT & assign(
		ValueT & dest,
		ValueT const & src,
		typename EnableIf<IsArray<ValueT> >::type * = hryky_nullptr);

	/// assigns non-array.
	template <typename ValueT>
	ValueT & assign(
		ValueT & dest,
		ValueT const & src,
		typename DisableIf<IsArray<ValueT> >::type * = hryky_nullptr);

	/// assigns to built-in array of POD elements.
	template <typename ValueT, size_t Size>
	typename ArrayOf<ValueT, Size>::reference assign_array(
		ValueT (&dest)[Size],
		ValueT const (&src)[Size],
		typename EnableIf< ::std::is_pod<ValueT> >::type * = hryky_nullptr);

	/// assigns to built-in array of non-POD elements.
	template <typename ValueT, size_t Size>
	typename ArrayOf<ValueT, Size>::reference assign_array(
		ValueT (&dest)[Size],
		ValueT const (&src)[Size],
		typename DisableIf< ::std::is_pod<ValueT> >::type * = hryky_nullptr);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief assigns array.
 */
template <typename ValueT>
ValueT &
hryky::assign(
	ValueT & dest,
	ValueT const & src,
	typename EnableIf<IsArray<ValueT> >::type *)
{
	return assign_array(dest, src);
}
/**
  @brief assigns non-array.
 */
template <typename ValueT>
ValueT &
hryky::assign(
	ValueT & dest,
	ValueT const & src,
	typename DisableIf<IsArray<ValueT> >::type *)
{
	return dest = src;
}
/**
  @brief assigns to built-in array of POD elements.
 */
template <typename ValueT, size_t Size>
typename hryky::ArrayOf<ValueT, Size>::reference
hryky::assign_array(
	ValueT (&dest)[Size],
	ValueT const (&src)[Size],
	typename EnableIf< ::std::is_pod<ValueT> >::type *)
{
	hryky::memcpy(dest, src, sizeof(ValueT) * Size);
	return dest;
}
/**
  @brief assigns to built-in array of non-POD elements.
 */
template <typename ValueT, size_t Size>
typename hryky::ArrayOf<ValueT, Size>::reference
hryky::assign_array(
	ValueT (&dest)[Size],
	ValueT const (&src)[Size],
	typename DisableIf< ::std::is_pod<ValueT> >::type *)
{
	hryky::range(src).foreach_at([&dest](
		ValueT const & element, size_t const index) {
		hryky::assign(dest[index], element);
	});
	return dest;
}
#endif // ASSIGN_H_20131209115714164
// end of file
