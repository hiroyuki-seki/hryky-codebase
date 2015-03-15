/**
  @file     begin.h
  @brief    retrieves the beginning of iterator.
  @author   HRYKY
  @version  $Id: begin.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef BEGIN_H_20131209094644074
#define BEGIN_H_20131209094644074
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
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
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
	/// retrieves the beginning of iterator for container.
	template <typename ContainerT>
	typename IteratorOf<ContainerT>::type begin(ContainerT & src);

	/// retrieves the beginning of array.
	template <typename ValueT, size_t Size>
	typename AddPointer<ValueT>::type begin(ValueT (&src)[Size]);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the beginning of iterator for container.
 */
template <typename ContainerT>
typename hryky::IteratorOf<ContainerT>::type
hryky::begin(ContainerT & src)
{
	return src.begin();
}
/**
  @brief retrieves the beginning of array.
 */
template <typename ValueT, size_t Size>
typename hryky::AddPointer<ValueT>::type
hryky::begin(ValueT (&src)[Size])
{
	return &src[0u];
}
#endif // BEGIN_H_20131209094644074
// end of file
