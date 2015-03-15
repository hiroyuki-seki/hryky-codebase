/**
  @file     at.h
  @brief    refers to the specified position of container.
  @author   HRYKY
  @version  $Id: at.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef AT_H_20131123231753637
#define AT_H_20131123231753637
#include "hryky/type_traits/reference_of.h"
#include "hryky/type_traits/size_type_of.h"
#include "hryky/type_traits/difference_type_of.h"
#include "hryky/iterator/begin.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	size_t Pos
#define hryky_template_arg \
	Pos
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// refers to the specified position of container.
	template <hryky_template_param>
	class At;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief refers to the specified position of container.
 */
template <size_t Pos>
class hryky::At
{
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
	/// retrieves the reference at the constant position of built-in array.
	template <typename ContainerT, size_t Index>
	typename ReferenceOf<ContainerT>::type
	at(ContainerT & dest);

	/// retrieves the reference at the specified potion of container.
	template <typename ContainerT>
	typename ReferenceOf<ContainerT>::type
		at(
			ContainerT & src,
			typename SizeTypeOf<ContainerT>::type const index);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the reference at the constant position of built-in array.
 */
template <typename ContainerT, size_t Index>
typename hryky::ReferenceOf<ContainerT>::type
hryky::at(ContainerT & dest)
{
	return array[Index];
}
/**
  @brief retrieves the reference at the specified potion of container.
 */
template <typename ContainerT>
typename hryky::ReferenceOf<ContainerT>::type
hryky::at(
	ContainerT & src,
	typename SizeTypeOf<ContainerT>::type const index)
{
	return *::std::next(
		hryky::begin(src),
		static_cast<DifferenceTypeOf<ContainerT>::type>(index));
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // AT_H_20131123231753637
// end of file
