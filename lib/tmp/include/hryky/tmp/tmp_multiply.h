/**
  @file     tmp_multiply.h
  @brief    operates multiplication between two terms.
  @author   HRYKY
  @version  $Id: tmp_multiply.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_MULTIPLY_H_20131221223319606
#define TMP_MULTIPLY_H_20131221223319606
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
	/// The alias for Multiply.
	template <hryky_template_param>
	class Mul;

	/// operates multiplication between two terms.
	template <hryky_template_param>
	class Multiply;

	/// implements Multiply<> for the actual types.
	template <hryky_template_param>
	class MultiplyImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The alias for Multiply.
 */
template <hryky_template_param>
class hryky::tmp::Mul
{
public :
	typedef typename Multiply<hryky_template_arg>::type type;
};
/**
  @brief operates multiplication between two terms.
 */
template <hryky_template_param>
class hryky::tmp::Multiply
{
public :
	typedef typename MultiplyImpl<
		typename LhsT::type, typename RhsT::type>::type type;
};
/**
  @brief implements Multiply<> for the actual types.
 */
template <hryky_template_param>
class hryky::tmp::MultiplyImpl
{
public :
	typedef MultiplyImpl<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  multiply an integer by an other integer.
 */
template <typename LhsT, LhsT Lhs, typename RhsT, RhsT Rhs>
class MultiplyImpl<
	IntegralConstant<LhsT, Lhs>,
	IntegralConstant<RhsT, Rhs>
>
{
public :
	typedef IntegralConstant<
		decltype(Lhs * Rhs), (Lhs * Rhs)> type;
};
/**
  propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<MultiplyImpl<hryky_template_arg> >
{
public :
	typedef typename Multiply<Eval<LhsT>, Eval<RhsT> >::type type;
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
#endif // TMP_MULTIPLY_H_20131221223319606
// end of file
