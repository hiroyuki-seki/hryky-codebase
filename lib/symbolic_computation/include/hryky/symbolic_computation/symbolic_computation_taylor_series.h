/**
  @file     symbolic_computation_taylor_series.h
  @brief    approximates an operation by Taylor series.
  @author   HRYKY
  @version  $Id: symbolic_computation_taylor_series.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_TAYLOR_SERIES_H_20131201132716227
#define SYMBOLIC_COMPUTATION_TAYLOR_SERIES_H_20131201132716227
#include "hryky/symbolic_computation/symbolic_computation_with_stream_out.h"
#include "hryky/symbolic_computation/symbolic_computation_evalable.h"
#include "hryky/symbolic_computation/symbolic_computation_issue_variable.h"
#include "hryky/bitsize_of.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename FunctionT, typename OrderT, typename WrtT, typename CenterT
#define hryky_template_arg \
	FunctionT, OrderT, WrtT, CenterT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// approximates an operation by Taylor series.
	template <hryky_template_param>
	class TaylorSeries;

	template <hryky_template_param>
	class TaylorSeriesImpl;

	template <typename OpT, typename IndexT, typename FirstT, typename LastT>
	class Sum;

	template <typename WrtT>
	class Differentiator;

	template <typename BaseopT, typename ExponentT>
	class Power;

	template <typename FactorT>
	class Factorial;

	template <typename LhsT, typename RhsT>
	class Divide;

	template <typename LhsT, typename RhsT>
	class Mul;

	template <typename LhsT, typename RhsT>
	class Sub;

	template <typename TargetT, typename ForT, typename AlternativeT>
	class Substitute;

	template <typename TargetT>
	class Simplify;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief approximates an operation by Taylor series.
 */
template <hryky_template_param>
class hryky::symbolic_computation::TaylorSeries :
	public WithStreamOut<TaylorSeries<hryky_template_arg> >,
	public Evalable<
		TaylorSeries<hryky_template_arg>,
		typename FunctionT::type::eval_type>
{
public :
	typedef typename TaylorSeriesImpl<
		typename FunctionT::type,
		typename OrderT::type,
		typename WrtT::type,
		typename CenterT::type
	>::type type;
};
/**
  @brief implements TaylorSeries.
 */
template <hryky_template_param>
class hryky::symbolic_computation::TaylorSeriesImpl
{
private :
	static size_t const index = 1u << (BitsizeOf<uint32_t>::value - 1);
	
	// issues a new variable for the index of summation.
	typedef typename IssueVariable<
		FunctionT,
		Variable<typename WrtT::eval_type, index, 'k'>
	>::type k;

	// issues a new variable for assigned value to derivatives.
	typedef typename IssueVariable<
		FunctionT,
		Variable<typename WrtT::eval_type, k::index + 1u, k::symbol + 1>
	>::type l;

	// replaces the differenciated variable.
	typedef Substitute<FunctionT, WrtT, l> differentiated;

	// creates a differential operator.
	typedef Power<Differentiator<l>, k> differentiator;
	
	// creates a higher derivative in summation.
	typedef Mul<differentiator, differentiated> derivative;
	
	typedef Power<Sub<WrtT, CenterT>, k>                    power;
	typedef Divide<Mul<derivative, power>, Factorial<k> >   summed;
	typedef Integer<typename k::eval_type, 0>               first;
public :

	// @todo delay substitution.

	typedef typename Substitute<
		Simplify<Sum<summed, k, first, OrderT> >, l, CenterT>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
} // namespace symbolic_computation
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
namespace symbolic_computation
{
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SYMBOLIC_COMPUTATION_TAYLOR_SERIES_H_20131201132716227
// end of file
