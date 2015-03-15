/**
  @file     with_at.h
  @brief    provides the access to an element in container.
  @author   HRYKY
  @version  $Id: with_at.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef WITH_AT_H_20130518162653352
#define WITH_AT_H_20130518162653352
#include "hryky/debug/debug_common.h"
#include "hryky/type_traits/add_const.h"
#include "hryky/type_traits/add_const_reference.h"
#include "hryky/type_traits/add_reference.h"
#include "hryky/type_traits/remove_reference.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ContainerT, \
	typename ValueT, \
	typename ReferenceT, \
	typename ConstReferenceT, \
	typename SizeT
#define hryky_template_arg \
	ContainerT, ValueT, ReferenceT, ConstReferenceT, SizeT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// provides the access to an element in container.
	template <hryky_template_param>
	class WithAt;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief provides the access to an element in container.
 */
template <
	typename ContainerT,
	typename ValueT,
	typename ReferenceT = typename AddReference<ValueT>::type,
	typename ConstReferenceT = typename AddConstReference<ValueT>::type,
	typename SizeT = ::std::size_t
>
class hryky::WithAt
{
public :

	/// retrieves the mutable element with offset.
	ReferenceT at(SizeT const index);

	/// retrieves the immutable element with offset.
	ConstReferenceT at(SizeT const index) const;

	/// retrieves the mutable first element.
	ReferenceT front();

	/// retrieves the immutable first element.
	ConstReferenceT front() const;

	/// retrieves the mutable last element.
	ReferenceT back();

	/// retrieves the immutable last element.
	ConstReferenceT back() const;

protected :

private :

	static typename AddConst<
		typename RemoveReference<ReferenceT>::type>::type dummy_value_;

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
  @brief retrieves the mutable element with offset.
 */
template <hryky_template_param>
ReferenceT
hryky::WithAt<hryky_template_arg>::at(SizeT const index)
{
	if (static_cast<ContainerT *>(this)->size() <= index) {
		hryky_throw(
			::std::out_of_range,
			"the specified index is out of range"
			<< " : size " << static_cast<ContainerT *>(this)->size()
			<< " : index " << index,
			return dummy_value_);
	}
	
	return static_cast<ContainerT *>(this)->operator[](index);
}
/**
  @brief retrieves the immutable element with offset.
 */
template <hryky_template_param>
ConstReferenceT 
hryky::WithAt<hryky_template_arg>::at(SizeT const index) const
{
	if (static_cast<ContainerT const *>(this)->size() <= index) {
		hryky_throw(
			::std::out_of_range,
			"the specified index is out of range"
			<< " : size " << static_cast<ContainerT const *>(this)->size()
			<< " : index " << index,
			return dummy_value_);
	}
	
	return static_cast<ContainerT const *>(this)->operator[](index);
}
/**
  @brief retrieves the mutable first element.
 */
template <hryky_template_param>
ReferenceT
hryky::WithAt<hryky_template_arg>::front()
{
	return static_cast<ContainerT *>(this)->operator[](0);
}
/**
  @brief retrieves the immutable first element.
 */
template <hryky_template_param>
ConstReferenceT
hryky::WithAt<hryky_template_arg>::front() const
{
	return static_cast<ContainerT const *>(this)->operator[](0);
}
/**
  @brief retrieves the mutable last element.
 */
template <hryky_template_param>
ReferenceT
hryky::WithAt<hryky_template_arg>::back()
{
	return static_cast<ContainerT *>(this)->operator[](
		static_cast<ContainerT *>(this)->size() - 1);
}
/**
  @brief retrieves the immutable last element.
 */
template <hryky_template_param>
ConstReferenceT
hryky::WithAt<hryky_template_arg>::back() const
{
	return static_cast<ContainerT const *>(this)->operator[](
		static_cast<ContainerT const *>(this)->size() - 1);
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
#endif // WITH_AT_H_20130518162653352
// end of file
