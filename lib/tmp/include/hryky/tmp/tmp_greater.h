/**
  @file     tmp_greater.h
  @brief    confirms the LHS term is greater than the RHS term.
  @author   HRYKY
  @version  $Id: tmp_greater.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_GREATER_H_20131222151016298
#define TMP_GREATER_H_20131222151016298
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
	/// confirms the LHS term is greater than the RHS term.
	template <hryky_template_param>
	class Greater;

	/// implements Greater<> for the actual types.
	template <hryky_template_param>
	class GreaterImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms the LHS term is greater than the RHS term.
 */
template <hryky_template_param>
class hryky::tmp::Greater
{
public :
	typedef typename GreaterImpl<
		typename LhsT::type, typename RhsT::type>::type type;
};
/**
  @brief implements Greater<> for the actual types.
 */
template <hryky_template_param>
class hryky::tmp::GreaterImpl
{
public :
	typedef GreaterImpl<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  confirms the LHS term is greater than the RHS term.
 */
template <typename LhsT, LhsT Lhs, typename RhsT, RhsT Rhs>
class GreaterImpl<
	IntegralConstant<LhsT, Lhs>,
	IntegralConstant<RhsT, Rhs>
>
{
public :
	typedef IntegralConstant<bool, (Lhs > Rhs)> type;
};
/**
  propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<GreaterImpl<hryky_template_arg> >
{
public :
	typedef typename Greater<Eval<LhsT>, Eval<RhsT> >::type type;
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
#endif // TMP_GREATER_H_20131222151016298
// end of file
