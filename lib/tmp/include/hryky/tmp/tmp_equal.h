/**
  @file     tmp_equal.h
  @brief    confirms the LHS term is equal to the RHS term.
  @author   HRYKY
  @version  $Id: tmp_equal.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_EQUAL_H_20131222152347308
#define TMP_EQUAL_H_20131222152347308
#include "hryky/tmp/tmp_eval.h"
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename LhsT, typename RhsT
#define hryky_template_arg \
	LhsT, RhsT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// confirms the LHS term is equal to the RHS term.
	template <hryky_template_param>
	class Equal;

	/// implements Equal<> for the actual types.
	template <hryky_template_param>
	class EqualImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms the LHS term is equal to the RHS term.
 */
template <hryky_template_param>
class hryky::tmp::Equal
{
public :
	typedef typename EqualImpl<
		typename LhsT::type, typename RhsT::type>::type type;
};
/**
  @brief implements Equal<> for the actual types.
 */
template <hryky_template_param>
class hryky::tmp::EqualImpl
{
public :
	typedef EqualImpl<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  confirms the two integral values are equal.
 */
template <typename LhsT, LhsT Lhs, typename RhsT, RhsT Rhs>
class EqualImpl<
	IntegralConstant<LhsT, Lhs>,
	IntegralConstant<RhsT, Rhs>
>
{
public :
	typedef IntegralConstant<bool, (Lhs == Rhs)> type;
};
/**
  propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<EqualImpl<hryky_template_arg> >
{
public :
	typedef typename Equal<Eval<LhsT>, Eval<RhsT> >::type type;
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
#endif // TMP_EQUAL_H_20131222152347308
// end of file
