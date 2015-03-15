/**
  @file     const_reference_of.h
  @brief    retrieves the immutable reference to each element of container.
  @author   HRYKY
  @version  $Id: const_reference_of.h 352 2014-06-08 08:48:59Z hryky.private@gmail.com $
 */
#ifndef CONST_REFERENCE_OF_H_20131209093250064
#define CONST_REFERENCE_OF_H_20131209093250064
#include "hryky/type_traits/add_const_reference.h"
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
	/// retrieves the immutable reference to each element of container.
	template <
		typename ValueT,
		bool has_reference = HasConstReference<ValueT>::type::value
	>
	class ConstReferenceOf;

	/// retrieves the immutable reference of each element of container.
	template <typename ContainerT>
	class ConstReferenceOfContainer;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the immutable reference to each element of container.
 */
template <hryky_template_param>
class hryky::ConstReferenceOf
{
public :
};
/**
  @brief retrieves the immutable reference of each element of container.
 */
template <typename ContainerT>
class hryky::ConstReferenceOfContainer
{
public :
	typedef typename ContainerT::const_reference type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief specializes the type retaining const reference.
 */
template <typename ValueT>
class ConstReferenceOf<ValueT, true>
{
public :
	typedef typename ConstReferenceOfContainer<ValueT>::type type;
};
/**
  @brief retrieves the immutable reference to an element of built-in array.
 */
template <typename ValueT, size_t Size>
class ConstReferenceOf<ValueT[Size], false>
{
public :
	typedef typename AddConstReference<ValueT>::type type;
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
#endif // CONST_REFERENCE_OF_H_20131209093250064
// end of file
