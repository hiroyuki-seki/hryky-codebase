/**
  @file     tmp_less.h
  @brief    confirmes the LHS term is less than the RHS term.
  @author   HRYKY
  @version  $Id: tmp_less.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_LESS_H_20131222150810297
#define TMP_LESS_H_20131222150810297
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
	/// confirmes the LHS term is less than the RHS term.
	template <hryky_template_param>
	class Less;

	/// implements Less<> for the actual types.
	template <hryky_template_param>
	class LessImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirmes the LHS term is less than the RHS term.
 */
template <hryky_template_param>
class hryky::tmp::Less
{
public :
	typedef typename LessImpl<
		typename LhsT::type, typename RhsT::type>::type type;
};
/**
  @brief implements Less<> for the actual types.
 */
template <hryky_template_param>
class hryky::tmp::LessImpl
{
public :
	typedef LessImpl<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  confirms the LHS term is less than the RHS term.
 */
template <typename LhsT, LhsT Lhs, typename RhsT, RhsT Rhs>
class LessImpl<
	IntegralConstant<LhsT, Lhs>,
	IntegralConstant<RhsT, Rhs>
>
{
public :
	typedef IntegralConstant<bool, (Lhs < Rhs)> type;
};
/**
  propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<LessImpl<hryky_template_arg> >
{
public :
	typedef typename Less<Eval<LhsT>, Eval<RhsT> >::type type;
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
#endif // TMP_LESS_H_20131222150810297
// end of file
