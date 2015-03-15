/**
  @file     tmp_iterator.h
  @brief    An iterator of container.
  @author   HRYKY
  @version  $Id: tmp_iterator.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef TMP_ITERATOR_H_20131216223652608
#define TMP_ITERATOR_H_20131216223652608
#include "hryky/tmp/tmp_decrement.h"
#include "hryky/tmp/tmp_dereference.h"
#include "hryky/tmp/tmp_equal.h"
#include "hryky/tmp/tmp_eval.h"
#include "hryky/tmp/tmp_greater.h"
#include "hryky/tmp/tmp_greater_equal.h"
#include "hryky/tmp/tmp_increment.h"
#include "hryky/tmp/tmp_is_list.h"
#include "hryky/tmp/tmp_less.h"
#include "hryky/tmp/tmp_less_equal.h"
#include "hryky/tmp/tmp_list.h"
#include "hryky/tmp/tmp_not_equal.h"
#include "hryky/tmp/tmp_add.h"
#include "hryky/tmp/tmp_subtract.h"
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ListT, typename IndexT
#define hryky_template_arg \
	ListT, IndexT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// An iterator of container.
	template <hryky_template_param>
	class Iterator;

	/// implements Iterator<> for the actual types.
	template <hryky_template_param>
	class IteratorImpl;

	template <typename ListT, typename IndexT>
	class At;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief An iterator of container.
 */
template <hryky_template_param>
class hryky::tmp::Iterator
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
public :
	typedef typename IteratorImpl<
		typename ListT::type, typename IndexT::type>::type type;
};
/**
  @brief implements Iterator<> for the actual types.
 */
template <hryky_template_param>
class hryky::tmp::IteratorImpl
{
public :
	typedef ListT list_type;
	typedef IndexT index_type;
	typedef IteratorImpl<list_type, index_type> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  dereferences a normal iterator.
 */
template <hryky_template_param>
class DereferenceImpl<IteratorImpl<hryky_template_arg> >
{
public :
	typedef typename At<ListT, IndexT>::type type;
};
/**
  increments an iterator.
 */
template <hryky_template_param>
class IncrementImpl<IteratorImpl<hryky_template_arg> >
{
public :
	typedef typename Iterator<ListT, Increment<IndexT> >::type type;
};
/**
  decrements an iterator.
 */
template <hryky_template_param>
class DecrementImpl<IteratorImpl<hryky_template_arg> >
{
public :
	typedef typename Iterator<ListT, Decrement<IndexT> >::type type;
};
/**
  adds an integral value to an iterator from right.
 */
template <hryky_template_param, typename RhsT, RhsT Rhs>
class AddImpl<
	IteratorImpl<hryky_template_arg>,
	IntegralConstant<RhsT, Rhs>
>
{
public :
	typedef typename Iterator<
		ListT, Add<IndexT, IntegralConstant<RhsT, Rhs> > >::type type;
};
/**
  adds an integral value to an iterator from left.
 */
template <typename LhsT, LhsT Lhs, hryky_template_param>
class AddImpl<
	IntegralConstant<LhsT, Lhs>,
	IteratorImpl<hryky_template_arg>
>
{
public :
	typedef typename Iterator<
		ListT, Add<IntegralConstant<LhsT, Lhs>, IndexT> >::type type;
};
/**
  subtract an integral value from an iterator.
 */
template <hryky_template_param, typename RhsT, RhsT Rhs>
class SubtractImpl<
	IteratorImpl<hryky_template_arg>,
	IntegralConstant<RhsT, Rhs>
>
{
public :
	typedef typename Iterator<
		ListT, Sub<IndexT, IntegralConstant<RhsT, Rhs> > >::type type;
};
/**
  calculates the distance between two iterators by the subtraction.
 */
template <hryky_template_param, typename RhsIndexT>
class SubtractImpl<
	IteratorImpl<hryky_template_arg>, IteratorImpl<ListT, RhsIndexT> >
{
public :
	typedef typename Sub<IndexT, RhsIndexT>::type type;
};
/**
  confirms the LHS iterator is equal to the RHS iterator.
 */
template <hryky_template_param, typename RhsIndexT>
class EqualImpl<
	IteratorImpl<hryky_template_arg>, IteratorImpl<ListT, RhsIndexT> >
{
public :
	typedef typename Equal<IndexT, RhsIndexT>::type type;
};
/**
  confirms the LHS iterator is not equal to the RHS iterator.
 */
template <hryky_template_param, typename RhsIndexT>
class NotEqualImpl<
	IteratorImpl<hryky_template_arg>, IteratorImpl<ListT, RhsIndexT> >
{
public :
	typedef typename NotEqual<IndexT, RhsIndexT>::type type;
};
/**
  confirms the LHS iterator is less than the RHS iterator.
 */
template <hryky_template_param, typename RhsIndexT>
class LessImpl<
	IteratorImpl<hryky_template_arg>, IteratorImpl<ListT, RhsIndexT> >
{
public :
	typedef typename Less<IndexT, RhsIndexT>::type type;
};
/**
  confirms the LHS iterator is less than or equal to the RHS iterator.
 */
template <hryky_template_param, typename RhsIndexT>
class LessEqualImpl<
	IteratorImpl<hryky_template_arg>, IteratorImpl<ListT, RhsIndexT> >
{
public :
	typedef typename LessEqual<IndexT, RhsIndexT>::type type;
};
/**
  confirms the LHS iterator is greater than the RHS iterator.
 */
template <hryky_template_param, typename RhsIndexT>
class GreaterImpl<
	IteratorImpl<hryky_template_arg>, IteratorImpl<ListT, RhsIndexT> >
{
public :
	typedef typename Greater<IndexT, RhsIndexT>::type type;
};
/**
  confirms the LHS iterator is greater than or equal to the RHS iterator.
 */
template <hryky_template_param, typename RhsIndexT>
class GreaterEqualImpl<
	IteratorImpl<hryky_template_arg>, IteratorImpl<ListT, RhsIndexT> >
{
public :
	typedef typename GreaterEqual<IndexT, RhsIndexT>::type type;
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
#endif // TMP_ITERATOR_H_20131216223652608
// end of file
