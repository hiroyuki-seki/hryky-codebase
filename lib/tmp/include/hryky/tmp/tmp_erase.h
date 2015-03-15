/**
  @file     tmp_erase.h
  @brief    removes the value at the position.
  @author   HRYKY
  @version  $Id: tmp_erase.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_ERASE_H_20131222164506364
#define TMP_ERASE_H_20131222164506364
#include "hryky/type_traits/integral_constant.h"
#include "hryky/tmp/tmp_list.h"
#include "hryky/tmp/tmp_is_list.h"
#include "hryky/tmp/tmp_eval.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename IteratorT
#define hryky_template_arg \
	IteratorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// removes the value at the position specified by iterator.
	template <hryky_template_param>
	class Erase;

	/// removes the value at the position specified by index.
	template <typename ListT, typename IndexT>
	class EraseAt;

	/// implements EraseAt<> for the actual type.
	template <typename ListT, typename IndexT>
	class EraseAtImpl;

	template <typename TermT>
	class Decrement;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief removes the value at the position specified by iterator.
 */
template <hryky_template_param>
class hryky::tmp::Erase
{
public :
	typedef typename EraseAt<
		typename IteratorT::type::list_type,
		typename IteratorT::type::index_type
	>::type type;
};
/**
  @brief removes the value at the position specified by index.
 */
template <typename ListT, typename IndexT>
class hryky::tmp::EraseAt
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
public :
	typedef typename EraseAtImpl<
		typename ListT::type,
		typename IndexT::type
	>::type type;
};
/**
  @brief implements EraseAt<> for the actual type.
 */
template <typename ListT, typename IndexT>
class hryky::tmp::EraseAtImpl
{
public :
	typedef EraseAtImpl<ListT, IndexT> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  removes the value from the position specified by the integral index.
 */
template <typename ListT, typename IndexT, IndexT Index>
class EraseAtImpl<ListT, IntegralConstant<IndexT, Index> >
{
public :
	typedef typename List<
		typename ListT::first_type,
		typename EraseAt<
			typename ListT::rest_type,
			Decrement<IntegralConstant<IndexT, Index> >
		>::type
	>::type type;
};
/**
  removes the value where the index becomes to zero.
 */
template <typename ListT, typename IndexT>
class EraseAtImpl<ListT, IntegralConstant<IndexT, 0> >
{
public :
	typedef typename ListT::rest_type type;
};
/**
  propagates the lazy evaluation.
 */
template <typename ListT, typename IndexT>
class EvalImpl<EraseAtImpl<ListT, IndexT> >
{
public :
	typedef typename EraseAt<Eval<ListT>, Eval<IndexT> >::type type;
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
#endif // TMP_ERASE_H_20131222164506364
// end of file
