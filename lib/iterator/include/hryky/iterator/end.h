/**
  @file     end.h
  @brief    retrieves the end of container.
  @author   HRYKY
  @version  $Id: end.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef END_H_20131209095506079
#define END_H_20131209095506079
#include "hryky/type_traits/iterator_of.h"
#include "hryky/type_traits/add_pointer.h"
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
	/// retrieves the end of iterator for container.
	template <typename ContainerT>
	typename IteratorOf<ContainerT>::type end(ContainerT & src);

	/// retrieves the end of array.
	template <typename ValueT, size_t Size>
	typename AddPointer<ValueT>::type end(ValueT (&src)[Size]);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the end of iterator for container.
 */
template <typename ContainerT>
typename hryky::IteratorOf<ContainerT>::type
hryky::end(ContainerT & src)
{
	return src.end();
}
/**
  @brief retrieves the end of array.
 */
template <typename ValueT, size_t Size>
typename hryky::AddPointer<ValueT>::type
hryky::end(ValueT (&src)[Size])
{
	return &src[Size];
}
#endif // END_H_20131209095506079
// end of file
