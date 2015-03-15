/**
  @file     tmp_decrement.h
  @brief    decrements a value.
  @author   HRYKY
  @version  $Id: tmp_decrement.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_DECREMENT_H_20131217230152626
#define TMP_DECREMENT_H_20131217230152626
#include "hryky/tmp/tmp_eval.h"
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TermT
#define hryky_template_arg \
	TermT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// decrements a value.
	template <hryky_template_param>
	class Decrement;

	/// implements Decrement with respect to the actual type.
	template <hryky_template_param>
	class DecrementImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief decrements a value.
 */
template <hryky_template_param>
class hryky::tmp::Decrement
{
public :
	typedef typename DecrementImpl<typename TermT::type>::type type;
};
/**
  @brief implements Decrement with respect to the actual type.
 */
template <hryky_template_param>
class hryky::tmp::DecrementImpl
{
public :
	typedef DecrementImpl<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  decrements an integral value.
 */
template <typename ValueT, ValueT Value>
class DecrementImpl<IntegralConstant<ValueT, Value> >
{
public :
	typedef IntegralConstant<ValueT, Value - 1> type;
};
/**
  propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<DecrementImpl<hryky_template_arg> >
{
public :
	typedef typename Decrement<Eval<TermT> >::type type;
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
#endif // TMP_DECREMENT_H_20131217230152626
// end of file
