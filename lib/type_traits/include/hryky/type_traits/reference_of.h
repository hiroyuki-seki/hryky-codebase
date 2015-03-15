/**
  @file     reference_of.h
  @brief    retrieves the reference of each element.
  @author   HRYKY
  @version  $Id: reference_of.h 352 2014-06-08 08:48:59Z hryky.private@gmail.com $
 */
#ifndef REFERENCE_OF_H_20131209092930062
#define REFERENCE_OF_H_20131209092930062
#include "hryky/type_traits/add_reference.h"
#include "hryky/type_traits/has_reference.h"
#include "hryky/type_traits/has_const_reference.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, bool has_reference
#define hryky_template_arg \
	ValueT, has_reference
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the reference of each element.
	template <
		typename ValueT,
		bool has_reference =
			HasReference<ValueT>::value
				|| HasConstReference<ValueT>::value
	>
	class ReferenceOf;

	/// retrieves the reference of each element of container.
	template <typename ContainerT>
	class ReferenceOfContainer;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the reference of each element.
 */
template <hryky_template_param>
class hryky::ReferenceOf
{
public :
};
/**
  @brief retrieves the reference of each element of container.
 */
template <typename ContainerT>
class hryky::ReferenceOfContainer
{
public :
	typedef typename ContainerT::reference type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief specializes the type having reference.
 */
template <typename ValueT>
class ReferenceOf<ValueT, true>
{
	static_assert(
		HasReference<ValueT>::type::value
		|| HasConstReference<ValueT>::type::value, "error");
public :
	typedef typename ReferenceOfContainer<ValueT>::type type;
};
/**
  @brief retrieves the reference to an element of built-in array.
 */
template <typename ValueT, size_t Size>
class ReferenceOf<ValueT[Size], false>
{
public :
	typedef typename AddReference<ValueT>::type type;
};
/**
  @brief retrieves the immutable reference of each element of container.
 */
template <typename ContainerT>
class ReferenceOfContainer<ContainerT const>
{
public :
	typedef typename ContainerT::const_reference type;
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
#endif // REFERENCE_OF_H_20131209092930062
// end of file
