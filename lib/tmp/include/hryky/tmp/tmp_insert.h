/**
  @file     tmp_insert.h
  @brief    inserts a value at the front of the iterator.
  @author   HRYKY
  @version  $Id: tmp_insert.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_INSERT_H_20131219234338655
#define TMP_INSERT_H_20131219234338655
#include "hryky/tmp/tmp_list.h"
#include "hryky/tmp/tmp_is_list.h"
#include "hryky/tmp/tmp_eval.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename IteratorT, typename ValueT
#define hryky_template_arg \
	IteratorT, ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// inserts a value at the front of the iterator.
	template <hryky_template_param>
	class Insert;

	/// inserts a value at the position specified by the index.
	template <typename ListT, typename IndexT, typename ValueT>
	class InsertAt;

	/// implements InsertAt<> for the actual type.
	template <typename ListT, typename IndexT, typename ValueT>
	class InsertAtImpl;

	template <typename TermT>
	class Decrement;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief inserts a value at the front of the iterator.
 */
template <hryky_template_param>
class hryky::tmp::Insert
{
public :
	typedef typename InsertAt<
		typename IteratorT::type::list_type,
		typename IteratorT::type::index_type,
		ValueT
	>::type type;
};
/**
  @brief inserts a value at the position specified by the index.
 */
template <typename ListT, typename IndexT, typename ValueT>
class hryky::tmp::InsertAt
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
public :
	typedef typename InsertAtImpl<
		typename ListT::type,
		typename IndexT::type,
		typename ValueT::type
	>::type type;
};
/**
  @brief implements InsertAt<> for the actual type.
 */
template <typename ListT, typename IndexT, typename ValueT>
class hryky::tmp::InsertAtImpl
{
public :
	typedef InsertAtImpl<ListT, IndexT, ValueT> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  inserts the value at the position specified by the integral index.
 */
template <
	typename ListT,
	typename IndexT,
	IndexT Index,
	typename ValueT
>
class InsertAtImpl<ListT, IntegralConstant<IndexT, Index>, ValueT>
{
public :
	typedef typename List<
		typename ListT::first_type,
		InsertAt<
			typename ListT::rest_type,
			Decrement<IntegralConstant<IndexT, Index> >,
			ValueT
		>
	>::type type;
};
/**
  @brief terminates InsertAtImpl<>
 */
template <typename ListT, typename IndexT, typename ValueT>
class InsertAtImpl<ListT, IntegralConstant<IndexT, 0>, ValueT>
{
public :
	typedef typename List<ValueT, ListT>::type type;
};
/**
  propagates the lazy evaluation.
 */
template <typename ListT, typename IndexT, typename ValueT>
class EvalImpl<InsertAtImpl<ListT, IndexT, ValueT> >
{
public :
	typedef typename InsertAt<
		Eval<ListT>, Eval<IndexT>, Eval<ValueT> >::type type;
};
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
#endif // TMP_INSERT_H_20131219234338655
// end of file
