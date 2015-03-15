/**
  @file     with_iterator.h
  @brief    features functions to retrieve the iterators.
  @author   HRYKY
  @version  $Id: with_iterator.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef WITH_ITERATABLE_H_20130517213351565
#define WITH_ITERATABLE_H_20130517213351565
#include "hryky/std/std_iterator.h"
#include "hryky/type_traits/add_const_pointer.h"
#include "hryky/type_traits/add_const_reference.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/type_traits/add_reference.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ContainerT, \
	typename IteratorT, \
	typename ConstIteratorT
#define hryky_template_arg \
	ContainerT, \
	IteratorT, \
	ConstIteratorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// features functions to retrieve the iterators.
	template <hryky_template_param>
	class WithIterator;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief features functions to retrieve the iterators.
 */
template <hryky_template_param>
class hryky::WithIterator
{
public :

	typedef IteratorT iterator;
	typedef ConstIteratorT const_iterator;
	typedef ::std::reverse_iterator<iterator> reverse_iterator;
	typedef ::std::reverse_iterator<const_iterator> const_reverse_iterator;

	/// retrieves a forward iterator referring to the first mutable element.
	iterator begin();

	/// retrieves a forward iterator referring to the first immutable element.
	const_iterator begin() const;

	/// retrieves a forward iterator referring to the last mutable element.
	iterator end();

	/// retrieves a forward iterator referring to the last immutable element.
	const_iterator end() const;

	/// retrieves a backward iterator referring to the first mutable element.
	reverse_iterator rbegin();

	/// retrieves a backward iterator referring to the first immutable element.
	const_reverse_iterator rbegin() const;

	/// retrieves a backward iterator referring to the last mutable element.
	reverse_iterator rend();

	/// retrieves a backward iterator referring to the last immutable element.
	const_reverse_iterator rend() const;

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief retrieves a forward iterator referring to the first mutable element.
 */
template <hryky_template_param>
typename hryky::WithIterator<hryky_template_arg>::iterator
hryky::WithIterator<hryky_template_arg>::begin()
{
	return iterator(static_cast<ContainerT *>(this), 0);
}
/**
  @brief retrieves a forward iterator referring to the first immutable element.
 */
template <hryky_template_param>
typename hryky::WithIterator<hryky_template_arg>::const_iterator
hryky::WithIterator<hryky_template_arg>::begin() const
{
	return const_iterator(static_cast<ContainerT const *>(this), 0);
}
/**
  @brief retrieves a forward iterator referring to the last mutable element.
 */
template <hryky_template_param>
typename hryky::WithIterator<hryky_template_arg>::iterator
hryky::WithIterator<hryky_template_arg>::end()
{
	return iterator(
		static_cast<ContainerT *>(this),
		static_cast<ContainerT *>(this)->size());
}
/**
  @brief retrieves a forward iterator referring to the last immutable element.
 */
template <hryky_template_param>
typename hryky::WithIterator<hryky_template_arg>::const_iterator
hryky::WithIterator<hryky_template_arg>::end() const
{
	return const_iterator(
		static_cast<ContainerT const *>(this),
		static_cast<ContainerT const *>(this)->size());
}
/**
  @brief retrieves a backward iterator referring to the first mutable element.
 */
template <hryky_template_param>
typename hryky::WithIterator<hryky_template_arg>::reverse_iterator
hryky::WithIterator<hryky_template_arg>::rbegin()
{
	return reverse_iterator(this->end());
}
/**
  @brief retrieves a backward iterator referring to the first immutable element.
 */
template <hryky_template_param>
typename hryky::WithIterator<hryky_template_arg>::const_reverse_iterator
hryky::WithIterator<hryky_template_arg>::rbegin() const
{
	return const_reverse_iterator(this->end());
}
/**
  @brief retrieves a backward iterator referring to the last mutable element.
 */
template <hryky_template_param>
typename hryky::WithIterator<hryky_template_arg>::reverse_iterator
hryky::WithIterator<hryky_template_arg>::rend()
{
	return reverse_iterator(this->begin());
}
/**
  @brief retrieves a backward iterator referring to the last immutable element.
 */
template <hryky_template_param>
typename hryky::WithIterator<hryky_template_arg>::const_reverse_iterator
hryky::WithIterator<hryky_template_arg>::rend() const
{
	return const_reverse_iterator(this->begin());
}
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
#endif // WITH_ITERATABLE_H_20130517213351565
// end of file
