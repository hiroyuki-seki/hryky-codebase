/**
  @file     tmp_rbegin.h
  @brief    retrieves the beginning of list in the reversed order.
  @author   HRYKY
  @version  $Id: tmp_rbegin.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef TMP_RBEGIN_H_20131223122313182
#define TMP_RBEGIN_H_20131223122313182
#include "hryky/tmp/tmp_eval.h"
#include "hryky/tmp/tmp_is_list.h"
#include "hryky/tmp/tmp_list.h"
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ListT
#define hryky_template_arg \
	ListT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// retrieves the beginning of list in the reversed order.
	template <hryky_template_param>
	class Rbegin;

	template <typename ListT, typename IndexT>
	class ReverseIterator;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the beginning of list in the reversed order.
 */
template <hryky_template_param>
class hryky::tmp::Rbegin
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
public :
	typedef typename ReverseIteratorT<
		ListT, IntegralConstant<int, 0> >::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
} // namespace tmp
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
namespace tmp
{
} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // TMP_RBEGIN_H_20131223122313182
// end of file
