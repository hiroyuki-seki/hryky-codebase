/**
  @file     tmp_divide.h
  @brief    operates division between two terms.
  @author   HRYKY
  @version  $Id: tmp_divide.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_DIVIDE_H_20131221223711609
#define TMP_DIVIDE_H_20131221223711609
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
	/// operates division between two terms.
	template <hryky_template_param>
	class Divide;

	/// implements Divide<> for the actual type.
	template <hryky_template_param>
	class DivideImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief operates division between two terms.
 */
template <hryky_template_param>
class hryky::tmp::Divide
{
public :
	typedef typename DivideImpl<
		typename LhsT::type, typename RhsT::type>::type type;
};
/**
  @brief implements Divide<> for the actual type.
 */
template <hryky_template_param>
class hryky::tmp::DivideImpl
{
public :
	typedef DivideImpl<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  divide an integer by an other integer.
 */
template <typename LhsT, LhsT Lhs, typename RhsT, RhsT Rhs>
class DivideImpl<
	IntegralConstant<LhsT, Lhs>,
	IntegralConstant<RhsT, Rhs>
>
{
public :
	typedef IntegralConstant<
		decltype(Lhs / Rhs), (Lhs / Rhs)> type;
};
/**
  propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<DivideImpl<hryky_template_arg> >
{
public :
	typedef typename Divide<Eval<LhsT>, Eval<RhsT> >::type type;
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
#endif // TMP_DIVIDE_H_20131221223711609
// end of file
