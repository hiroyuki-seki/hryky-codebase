/**
  @file     tmp_greater_equal.h
  @brief    confirms the LHS term is greater than or equal to the RHS term.
  @author   HRYKY
  @version  $Id: tmp_greater_equal.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_GREATER_EQUAL_H_20131222151424301
#define TMP_GREATER_EQUAL_H_20131222151424301
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
	/// confirms the LHS term is greater than or equal to the RHS term.
	template <hryky_template_param>
	class GreaterEqual;

	/// implements GreaterEqual<> for the actual types.
	template <hryky_template_param>
	class GreaterEqualImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms the LHS term is greater than or equal to the RHS term.
 */
template <hryky_template_param>
class hryky::tmp::GreaterEqual
{
public :
	typedef typename GreaterEqualImpl<
		typename LhsT::type, typename RhsT::type>::type type;
};
/**
  @brief implements GreaterEqual<> for the actual types.
 */
template <hryky_template_param>
class hryky::tmp::GreaterEqualImpl
{
public :
	typedef GreaterEqualImpl<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  confirms the LHS term is greater than or equal to the RHS term.
 */
template <typename LhsT, LhsT Lhs, typename RhsT, RhsT Rhs>
class GreaterEqualImpl<
	IntegralConstant<LhsT, Lhs>,
	IntegralConstant<RhsT, Rhs>
>
{
public :
	typedef IntegralConstant<bool, (Lhs >= Rhs)> type;
};
/**
  propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<GreaterEqualImpl<hryky_template_arg> >
{
public :
	typedef typename GreaterEqual<Eval<LhsT>, Eval<RhsT> >::type type;
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
#endif // TMP_GREATER_EQUAL_H_20131222151424301
// end of file
