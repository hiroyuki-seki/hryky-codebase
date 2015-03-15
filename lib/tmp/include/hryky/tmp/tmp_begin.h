/**
  @file     tmp_begin.h
  @brief    retrieves the beginning of list as the iterator.
  @author   HRYKY
  @version  $Id: tmp_begin.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef TMP_BEGIN_H_20131216224432614
#define TMP_BEGIN_H_20131216224432614
#include "hryky/type_traits/integral_constant.h"
#include "hryky/tmp/tmp_list.h"
#include "hryky/tmp/tmp_is_list.h"
#include "hryky/tmp/tmp_eval.h"
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
	/// retrieves the beginning of list as the iterator.
	template <hryky_template_param>
	class Begin;

	template <typename ListT, typename IndexT>
	class Iterator;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the beginning of list as the iterator.
 */
template <typename ListT>
class hryky::tmp::Begin
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
public :
	typedef typename Iterator<
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
#endif // TMP_BEGIN_H_20131216224432614
// end of file
