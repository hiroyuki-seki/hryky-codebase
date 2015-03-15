/**
  @file     tmp_reverse_iterator.h
  @brief    A reversed iterator of container.
  @author   HRYKY
  @version  $Id: tmp_reverse_iterator.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef TMP_REVERSE_ITERATOR_H_20131221224831617
#define TMP_REVERSE_ITERATOR_H_20131221224831617
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
	/// A reversed iterator of container.
	template <hryky_template_param>
	class ReverseIterator;

	/// implements ReverseIterator<> for the actual types.
	template <hryky_template_param>
	class ReverseIteratorImpl;

	template <typename ListT, typename IndexT>
	class At;

	template <typename LhsT, typename RhsT>
	class Add;

	template <typename LhsT, typename RhsT>
	class Sub;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief A reversed iterator of container.
 */
template <hryky_template_param>
class hryky::tmp::ReverseIterator
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
public :
	typedef typename ReverseIteratorImpl<
		typename ListT::type, typename IndexT::type>::type type;
};
/**
  @brief implements ReverseIterator<> for the actual types.
 */
template <hryky_template_param>
class hryky::tmp::ReverseIteratorImpl
{
public :
	typedef ListT list_type;
	typedef IndexT index_type;
	typedef ReverseIteratorImpl<list_type, index_type> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  dereferences a reverse iterator.
 */
template <hryky_template_param>
class DereferenceImpl<ReverseIteratorImpl<hryky_template_arg> >
{
public :
	typedef typename At<
		ListT,
		Sub<
			Sub<Size<ListT>, IndexT>,
			IntegralConstant<int, 1>
		>
	>::type type;
};
/**
  increments a reverse iterator.
 */
template <hryky_template_param>
class IncrementImpl<ReverseIteratorImpl<hryky_template_arg> >
{
public :
	typedef typename ReverseIterator<ListT, Increment<IndexT> >::type type;
};
/**
  decrements a reverse iterator.
 */
template <hryky_template_param>
class DecrementImpl<ReverseIteratorImpl<hryky_template_arg> >
{
public :
	typedef typename ReverseIterator<ListT, Decrement<IndexT> >::type type;
};
/**
  adds an integral value to a reverse iterator from right.
 */
template <hryky_template_param, typename RhsT, RhsT Rhs>
class AddImpl<
	ReverseIteratorImpl<hryky_template_arg>,
	IntegralConstant<RhsT, Rhs>
>
{
public :
	typedef typename ReverseIterator<
		ListT, Add<IndexT, IntegralConstant<RhsT, Rhs> > >::type type;
};
/**
  adds an integral value to a reverse iterator from left.
 */
template <typename LhsT, LhsT Lhs, hryky_template_param>
class AddImpl<
	IntegralConstant<LhsT, Lhs>,
	ReverseIteratorImpl<hryky_template_arg>
>
{
public :
	typedef typename ReverseIterator<
		ListT, Add<IntegralConstant<LhsT, Lhs>, IndexT> >::type type;
};
/**
  subtract an integral value from a reverse iterator.
 */
template <hryky_template_param, typename RhsT, RhsT Rhs>
class SubtractImpl<
	ReverseIteratorImpl<hryky_template_arg>,
	IntegralConstant<RhsT, Rhs>
>
{
public :
	typedef typename ReverseIterator<
		ListT, Sub<IndexT, IntegralConstant<RhsT, Rhs> > >::type type;
};
/**
  calculates the distance between two iterators by the subtraction.
 */
template <hryky_template_param, typename RhsIndexT>
class SubtractImpl<
	ReverseIteratorImpl<hryky_template_arg>,
	ReverseIteratorImpl<ListT, RhsIndexT> >
{
public :
	typedef typename Sub<IndexT, RhsIndexT>::type type;
};
/**
  confirms the LHS iterator is equal to the RHS iterator.
 */
template <hryky_template_param, typename RhsIndexT>
class EqualImpl<
	ReverseIteratorImpl<hryky_template_arg>,
	ReverseIteratorImpl<ListT, RhsIndexT> >
{
public :
	typedef typename Equal<IndexT, RhsIndexT>::type type;
};
/**
  confirms the LHS iterator is not equal to the RHS iterator.
 */
template <hryky_template_param, typename RhsIndexT>
class NotEqualImpl<
	ReverseIteratorImpl<hryky_template_arg>,
	ReverseIteratorImpl<ListT, RhsIndexT> >
{
public :
	typedef typename NotEqual<IndexT, RhsIndexT>::type type;
};
/**
  confirms the LHS iterator is less than the RHS iterator.
 */
template <hryky_template_param, typename RhsIndexT>
class LessImpl<
	ReverseIteratorImpl<hryky_template_arg>,
	ReverseIteratorImpl<ListT, RhsIndexT> >
{
public :
	typedef typename Less<IndexT, RhsIndexT>::type type;
};
/**
  confirms the LHS iterator is less than or equal to the RHS iterator.
 */
template <hryky_template_param, typename RhsIndexT>
class LessEqualImpl<
	ReverseIteratorImpl<hryky_template_arg>,
	ReverseIteratorImpl<ListT, RhsIndexT> >
{
public :
	typedef typename LessEqual<IndexT, RhsIndexT>::type type;
};
/**
  confirms the LHS iterator is greater than the RHS iterator.
 */
template <hryky_template_param, typename RhsIndexT>
class GreaterImpl<
	ReverseIteratorImpl<hryky_template_arg>,
	ReverseIteratorImpl<ListT, RhsIndexT> >
{
public :
	typedef typename Greater<IndexT, RhsIndexT>::type type;
};
/**
  confirms the LHS iterator is greater than or equal to the RHS iterator.
 */
template <hryky_template_param, typename RhsIndexT>
class GreaterEqualImpl<
	ReverseIteratorImpl<hryky_template_arg>,
	ReverseIteratorImpl<ListT, RhsIndexT> >
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
#endif // TMP_REVERSE_ITERATOR_H_20131221224831617
// end of file
