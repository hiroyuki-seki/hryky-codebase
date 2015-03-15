/**
  @file     tmp_assign.h
  @brief    assigns a value at the position.
  @author   HRYKY
  @version  $Id: tmp_assign.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_ASSIGN_H_20131222174255404
#define TMP_ASSIGN_H_20131222174255404
#include "hryky/tmp/tmp_list.h"
#include "hryky/tmp/tmp_is_list.h"
#include "hryky/tmp/tmp_eval.h"
#include "hryky/type_traits/integral_constant.h"
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
	/// assigns a value at the position specified by the iterator.
	template <hryky_template_param>
	class Assign;

	/// assigns a value at the position specified by the index.
	template <typename ListT, typename IndexT, typename ValueT>
	class AssignAt;

	/// implements AssignAt<> for the actual types.
	template <typename ListT, typename IndexT, typename ValueT>
	class AssignAtImpl;

	template <typename TermT>
	class Decrement;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief assigns a value at the position specified by the iterator.
 */
template <hryky_template_param>
class hryky::tmp::Assign
{
public :
	typedef typename AssignAt<
		typename IteratorT::type::list_type,
		typename IteratorT::type::index_type,
		typename ValueT::type
	>::type type;
};
/**
  @brief assigns a value at the position specified by the index.
 */
template <typename ListT, typename IndexT, typename ValueT>
class hryky::tmp::AssignAt
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
public :
	typedef typename AssignAtImpl<
		typename ListT::type,
		typename IndexT::type,
		typename ValueT::type
	>::type type;
};
/**
  @brief implements AssignAt<> for the actual types.
 */
template <typename ListT, typename IndexT, typename ValueT>
class hryky::tmp::AssignAtImpl
{
public :
	typedef typename List<
		typename ListT::first_type,
		typename AssignAtImpl<
			typename ListT::rest_type,
			typename Decrement<IndexT>::type,
			ValueT
		>::type
	>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  assigns the value at the position specified by the integral value.
 */
template <
	typename ListT,
	typename IndexT,
	IndexT Index,
	typename ValueT
>
class AssignAtImpl<ListT, IntegralConstant<IndexT, Index>, ValueT>
{
public :
	typedef typename List<
		typename ListT::first_type,
		AssignAt<
			typename ListT::rest_type,
			Decrement<IntegralConstant<IndexT, Index> >,
			ValueT
		>
	>::type type;
};
/**
  determins the position when the index becomes to zero.
 */
template <typename ListT, typename IndexT, typename ValueT>
class AssignAtImpl<ListT, IntegralConstant<IndexT, 0>, ValueT>
{
public :
	typedef typename List<
		ValueT, typename ListT::rest_type>::type type;
};
/**
  propagates the lazy evaluation.
 */
template <typename ListT, typename IndexT, typename ValueT>
class EvalImpl<AssignAtImpl<ListT, IndexT, ValueT> >
{
public :
	typedef typename AssignAt<
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
#endif // TMP_ASSIGN_H_20131222174255404
// end of file
