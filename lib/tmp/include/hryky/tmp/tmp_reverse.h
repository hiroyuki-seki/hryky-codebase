/**
  @file     tmp_reverse.h
  @brief    reverse the order of elements.
  @author   HRYKY
  @version  $Id: tmp_reverse.h 355 2014-06-22 08:47:38Z hryky.private@gmail.com $
 */
#ifndef TMP_REVERSE_H_20131223170240376
#define TMP_REVERSE_H_20131223170240376
#include "hryky/tmp/tmp_list.h"
#include "hryky/tmp/tmp_is_list.h"
#include "hryky/tmp/tmp_is_iterator.h"
#include "hryky/tmp/tmp_eval.h"
#include "hryky/tmp/tmp_foreach.h"
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
	/// reverse the order of elements.
	template <hryky_template_param>
	class Reverse;

	/// reverses the order of elements between two iterators.
	template <typename BeginT, typename EndT>
	class ReverseIn;

	template <typename ListT>
	class Begin;

	template <typename ListT>
	class End;

	template <typename LhsT, typename RhsT>
	class Concat;

	template <typename BeginT>
	class SliceAfter;

	template <typename EndT>
	class SliceBefore;

	template <typename TermT>
	class Dereference;

namespace reverse_detail
{
	/**
	  stacks an element in the reverse order.
	 */
	template <typename ArgT>
	struct Op;
	
	/**
	  bifurcates the operation if the list is empty.
	 */
	template <
		typename ArgT,
		typename Empty = typename ArgT::empty
	>
	struct OpEmpty;
	
	/**
	  bifurcates the operation at the end.
	 */
	template <
		typename ArgT,
		typename AtEnd = typename ArgT::at_end
	>
	struct OpEnd;
	
} // namespace reverse_detail
} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief reverse the order of elements.
 */
template <hryky_template_param>
class hryky::tmp::Reverse
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
public :
	typedef typename ReverseIn<
		Begin<ListT>,
		End<ListT>
	>::type::list_type type;
};
/**
  @brief reverses the order of elements between two iterators.
 */
template <typename BeginT, typename EndT>
class hryky::tmp::ReverseIn
{
	static_assert(
		IsIterator<BeginT>::type::value,
		"The first parameter has to be an iterator.");
	static_assert(
		IsIterator<EndT>::type::value,
		"The second parameter has to be an iterator.");
public :
	typedef typename Add<
		Begin<
			Concat<
				SliceBefore<BeginT>,
				ForeachIn<
					BeginT,
					EndT,
					reverse_detail::Op,
					null_list_type
				>
			>
		>,
		typename BeginT::type::index_type
	>::type type;
};
/**
  stacks an element in the reverse order.
 */
template <typename ArgT>
struct hryky::tmp::reverse_detail::Op
{
	typedef typename OpEmpty<ArgT>::type type;
	typedef type accumulator;
};
/**
  bifurcates the operation if the list is empty.
 */
template <typename ArgT, typename Empty>
struct hryky::tmp::reverse_detail::OpEmpty
{
	typedef typename OpEnd<ArgT>::type type;
	typedef type accumulator;
};
/**
  bifurcates the operation at the end.
 */
template <typename ArgT, typename AtEnd>
struct hryky::tmp::reverse_detail::OpEnd
{
	typedef typename PushFront<
		typename ArgT::accumulator,
		Dereference<typename ArgT::itr>
	>::type type;
	typedef type accumulator;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
namespace reverse_detail
{
/**
  The list is empty.
 */
template <typename ArgT>
struct OpEmpty<ArgT, true_type>
{
	typedef null_list_type type;
	typedef type accumulator;
};
/**
  At the end.
 */
template <typename ArgT>
struct OpEnd<ArgT, true_type>
{
	typedef typename Concat<
		typename ArgT::accumulator,
		SliceAfter<typename ArgT::end>
	>::type type;
	typedef type accumulator;
};
} // namespace reverse_detail
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
#endif // TMP_REVERSE_H_20131223170240376
// end of file
