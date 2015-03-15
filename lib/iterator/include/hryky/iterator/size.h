/**
  @file     size.h
  @brief    retrieves the size of container.
  @author   HRYKY
  @version  $Id: size.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef SIZE_H_20131209111112132
#define SIZE_H_20131209111112132
#include "hryky/type_traits/size_type_of.h"
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
	/// retrieves the size of container.
	template <typename ContainerT>
	typename SizeTypeOf<ContainerT>::type
		size(ContainerT & src);

	/// retrieves the size of built-in array.
	template <typename ValueT, size_t Size>
	typename SizeTypeOf<ValueT[Size]>::type
		size(ValueT (&src)[Size]);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the size of container.
 */
template <typename ContainerT>
typename hryky::SizeTypeOf<ContainerT>::type
hryky::size(ContainerT & src)
{
	return src.size();
}
/**
  @brief retrieves the size of built-in array.
 */
template <typename ValueT, size_t Size>
typename hryky::SizeTypeOf<ValueT[Size]>::type
hryky::size(ValueT (&)[Size])
{
	return Size;
}
#endif // SIZE_H_20131209111112132
// end of file
