/**
  @file     remove_const_reference.h
  @brief    removes the const and reference qualifier from a type.
  @author   HRYKY
  @version  $Id: remove_const_reference.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef REMOVE_CONST_REFERENCE_H_20140626094749074
#define REMOVE_CONST_REFERENCE_H_20140626094749074
#include "hryky/type_traits/remove_const.h"
#include "hryky/type_traits/remove_reference.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT
#define hryky_template_arg \
	ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// removes the const and reference qualifier from a type.
	template <typename ValueT>
	class RemoveConstReference;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief removes the const and reference qualifier from a type.
 */
template <hryky_template_param>
class hryky::RemoveConstReference
{
public :
	typedef typename RemoveConst<
		typename RemoveReference<ValueT>::type>::type type;
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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // REMOVE_CONST_REFERENCE_H_20140626094749074
// end of file
