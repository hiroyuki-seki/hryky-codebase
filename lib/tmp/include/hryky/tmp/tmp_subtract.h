/**
  @file     tmp_subtract.h
  @brief    calculates subtractions between two terms.
  @author   HRYKY
  @version  $Id: tmp_subtract.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_SUBTRACT_H_20131221222315599
#define TMP_SUBTRACT_H_20131221222315599
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
	/// The alias for Subtract.
	template <hryky_template_param>
	class Sub;

	/// calculates subtractions between two terms.
	template <hryky_template_param>
	class Subtract;

	/// implements Subtract<> for the actual types.
	template <hryky_template_param>
	class SubtractImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The alias for Subtract.
 */
template <hryky_template_param>
class hryky::tmp::Sub
{
public :
	typedef typename Subtract<hryky_template_arg>::type type;
};
/**
  @brief calculates subtractions between two terms.
 */
template <hryky_template_param>
class hryky::tmp::Subtract
{
public :
	typedef typename SubtractImpl<
		typename LhsT::type, typename RhsT::type>::type type;
};
/**
  @brief implements Subtract<> for the actual types.
 */
template <hryky_template_param>
class hryky::tmp::SubtractImpl
{
public :
	typedef SubtractImpl<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  subtracts an integer from an other integer.
 */
template <typename LhsT, LhsT Lhs, typename RhsT, RhsT Rhs>
class SubtractImpl<
	IntegralConstant<LhsT, Lhs>,
	IntegralConstant<RhsT, Rhs>
>
{
public :
	typedef IntegralConstant<
		decltype(Lhs - Rhs), (Lhs - Rhs)> type;
};
/**
  propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<SubtractImpl<hryky_template_arg> >
{
public :
	typedef typename Subtract<Eval<LhsT>, Eval<RhsT> >::type type;
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
#endif // TMP_SUBTRACT_H_20131221222315599
// end of file
