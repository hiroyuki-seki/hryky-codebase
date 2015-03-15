/**
  @file     tmp_rend.h
  @brief    retrieves the end of list in the reversed order.
  @author   HRYKY
  @version  $Id: tmp_rend.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef TMP_REND_H_20131223122506184
#define TMP_REND_H_20131223122506184
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
	/// retrieves the end of list in the reversed order.
	template <hryky_template_param>
	class Rend;

	template <typename ListT, typename IndexT>
	class ReverseIterator;

	template <typename ListT>
	class Size;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the end of list in the reversed order.
 */
template <hryky_template_param>
class hryky::tmp::Rend
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
public :
	typedef typename ReverseIterator<ListT, Size<ListT> >::type type;
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
#endif // TMP_REND_H_20131223122506184
// end of file
