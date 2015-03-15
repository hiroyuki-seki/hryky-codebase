/**
  @file     tmp_find.h
  @brief    finds the value in container.
  @author   HRYKY
  @version  $Id: tmp_find.h 355 2014-06-22 08:47:38Z hryky.private@gmail.com $
 */
#ifndef TMP_FIND_H_20131223125935208
#define TMP_FIND_H_20131223125935208
#include "hryky/tmp/tmp_null.h"
#include "hryky/tmp/tmp_list.h"
#include "hryky/tmp/tmp_is_list.h"
#include "hryky/tmp/tmp_is_iterator.h"
#include "hryky/tmp/tmp_eval.h"
#include "hryky/tmp/tmp_some.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ListT, typename ValueT
#define hryky_template_arg \
	ListT, ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// finds the value in container.
	template <hryky_template_param>
	class Find;

	/// finds the value between two iterators.
	template <typename BeginT, typename EndT, typename ValueT>
	class FindIn;

	template <typename ListT>
	class Begin;

	template <typename ListT>
	class End;

	template <typename LhsT, typename RhsT>
	class Same;

	template <typename TermT>
	class Dereference;

namespace find_detail
{
	/**
	  finds the value.
	 */
	template <typename ArgT>
	struct Op;
	
	/**
	  confirms whether the iteration is at the end.
	 */
	template <typename ArgT, typename AtEnd = typename ArgT::at_end>
	struct OpEnd;
	
} // namespace find_detail
} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief finds the value in container.
 */
template <hryky_template_param>
class hryky::tmp::Find
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
private :
	typedef FindIn<
		Begin<ListT>,
		End<ListT>,
		ValueT
	> impl;
public :
	typedef typename impl::type type;
	typedef typename impl::result result;
};
/**
  @brief finds the value between two iterators.
 */
template <typename BeginT, typename EndT, typename ValueT>
class hryky::tmp::FindIn
{
	static_assert(
		IsIterator<BeginT>::type::value,
		"The first parameter has to be an iterator.");
	static_assert(
		IsIterator<EndT>::type::value,
		"The second parameter has to be an iterator.");
public :

	typedef SomeIn<BeginT, EndT, find_detail::Op, ValueT> impl;

	typedef typename impl::type type;
	typedef typename impl::result result;
};
/**
  finds the value.
 */
template <typename ArgT>
struct hryky::tmp::find_detail::Op
{
	typedef OpEnd<ArgT> impl;
	typedef typename impl::result result;
	typedef typename impl::type type;
};
/**
  confirms whether the iteration is at the end.
 */
template <typename ArgT, typename AtEnd>
struct hryky::tmp::find_detail::OpEnd
{
	typedef typename Same<
		Dereference<typename ArgT::itr>,
		typename ArgT::accumulator
	>::type result;
	typedef typename ArgT::itr type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
namespace find_detail
{
/**
  The value is not found.
 */
template <typename ArgT>
struct OpEnd<ArgT, true_type>
{
	typedef false_type result;
	typedef typename ArgT::itr type;
};
} // namespace find_detail
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
#endif // TMP_FIND_H_20131223125935208
// end of file
