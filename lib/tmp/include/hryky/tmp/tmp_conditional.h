/**
  @file     tmp_conditional.h
  @brief    selects a type in accordance with the condition.
  @author   HRYKY
  @version  $Id: tmp_conditional.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_CONDITIONAL_H_20140713153123313
#define TMP_CONDITIONAL_H_20140713153123313
#include "hryky/type_traits/conditional.h"
#include "hryky/tmp/tmp_eval.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename CondT, typename TrueT, typename FalseT
#define hryky_template_arg \
	CondT, TrueT, FalseT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// selects a type in accordance with the condition.
	template <typename CondT, typename TrueT, typename FalseT>
	class Conditional;

	/// selects a type if the condition can be evaluated.
	template <typename CondT, typename TrueT, typename FalseT>
	class ConditionalImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief selects a type in accordance with the condition.
 */
template <hryky_template_param>
class hryky::tmp::Conditional
{
public :
	typedef typename ConditionalImpl<
		typename CondT::type,
		TrueT,
		FalseT
	>::type::type type;
};
/**
  @brief selects a type if the condition can be evaluated.
 */
template <hryky_template_param>
class hryky::tmp::ConditionalImpl
{
public :
	typedef ConditionalImpl<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  @brief selects a type if the condition is integral constant.
 */
template <typename CondT, CondT Cond, typename TrueT, typename FalseT>
class ConditionalImpl<
	IntegralConstant<CondT, Cond>,
	TrueT,
	FalseT
>
{
public :
	typedef typename hryky::Conditional<
		IntegralConstant<CondT, Cond>, TrueT, FalseT>::type type;
};
/**
  @brief propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<ConditionalImpl<hryky_template_arg> >
{
public :
	typedef typename Conditional<
		Eval<CondT>, Eval<TrueT>, Eval<FalseT> >::type type;
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
#endif // TMP_CONDITIONAL_H_20140713153123313
// end of file
