/**
  @file         iterator_of.h
  @brief        retrieves the type of iterator.
  @author       HRYKY
  @version      $Id: iterator_of.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef TYPE_ITERATOR_OF_H_20120909000702671
#define TYPE_ITERATOR_OF_H_20120909000702671
#include "hryky/type_traits/has_const_iterator.h"
#include "hryky/type_traits/has_iterator.h"
#include "hryky/type_traits/add_pointer.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the type of iterator.
	template <
		typename ContainerT,
		bool has_iterator =
			HasIterator<ContainerT>::value ||
				HasConstIterator<ContainerT>::value
	>
	class IteratorOf;

	/// retrieves the iterator of container.
	template <typename ContainerT>
	class IteratorOfContainer;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the type of iterator.
 */
template <typename ContainerT, bool has_iterator>
class hryky::IteratorOf
{
public :
};
/**
  @brief retrieves the iterator of container.
 */
template <typename ContainerT>
class hryky::IteratorOfContainer
{
public :
	typedef typename ContainerT::iterator type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief specializes type which has iterator.
 */
template <typename ContainerT>
class IteratorOf<ContainerT, true>
{
public :
	typedef typename IteratorOfContainer<ContainerT>::type type;
};
/**
  @brief specializes built-in array.
 */
template <typename ValueT, size_t Size>
class IteratorOf<ValueT[Size], false>
{
public :
	typedef typename AddPointer<ValueT>::type type;
};
/**
  @brief specializes type which is qualified const and has const_iterator.
 */
template <typename ContainerT>
class IteratorOfContainer<ContainerT const>
{
public :
	typedef typename ContainerT::const_iterator type;
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
#endif // TYPE_ITERATOR_OF_H_20120909000702671
// end of file
