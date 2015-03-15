/**
  @file     tmp_at.h
  @brief    retrieves the element in list.
  @author   HRYKY
  @version  $Id: tmp_at.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_AT_H_20131216223825610
#define TMP_AT_H_20131216223825610
#include "hryky/type_traits/integral_constant.h"
#include "hryky/tmp/tmp_list.h"
#include "hryky/tmp/tmp_is_list.h"
#include "hryky/tmp/tmp_eval.h"
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
	/// retrieves the element in list.
	template <hryky_template_param>
	class At;

	/// implements At<> for detailed type.
	template <hryky_template_param>
	class AtImpl;

	template <typename IndexT>
	class Decrement;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the element in list.
 */
template <hryky_template_param>
class hryky::tmp::At
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
public :
	typedef typename AtImpl<
		typename ListT::type, typename IndexT::type>::type type;
};
/**
  @brief implements At<> for detailed type.
 */
template <hryky_template_param>
class hryky::tmp::AtImpl
{
public :
	typedef AtImpl<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  refers the position specified by the integral value.
 */
template <typename ListT, typename IndexT, IndexT Index>
class AtImpl<ListT, IntegralConstant<IndexT, Index> >
{
public :
	typedef typename At<
		typename ListT::type::rest_type,
		Decrement<IntegralConstant<IndexT, Index> >
	>::type type;
};
/**
  terminates AtImpl.
 */
template <typename ListT, typename IndexT>
class AtImpl<ListT, IntegralConstant<IndexT, 0> >
{
public :
	typedef typename ListT::type::first_type type;
};
/**
  propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<AtImpl<hryky_template_arg> >
{
public :
	typedef typename At<Eval<ListT>, Eval<IndexT> >::type type;
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
#endif // TMP_AT_H_20131216223825610
// end of file
