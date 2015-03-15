/**
  @file     symbolic_computation_maclaurin_series.h
  @brief    approximates an operation by Maclaurin series.
  @author   HRYKY
  @version  $Id: symbolic_computation_maclaurin_series.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_MACLAURIN_SERIES_H_20131201212657560
#define SYMBOLIC_COMPUTATION_MACLAURIN_SERIES_H_20131201212657560
#include "hryky/symbolic_computation/symbolic_computation_taylor_series.h"
#include "hryky/symbolic_computation/symbolic_computation_with_stream_out.h"
#include "hryky/symbolic_computation/symbolic_computation_evalable.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename FunctionT, typename OrderT, typename WrtT
#define hryky_template_arg \
	FunctionT, OrderT, WrtT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	template <typename EvalT, int Value>
	class Integer;

	/// approximates an operation by Maclaurin series.
	template <hryky_template_param>
	class MaclaurinSeries;

	/// specifies the order of Maclaurin series by value.
	template <typename FunctionT, size_t Order, typename WrtT>
	class MaclaurinSeriesC;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief specifies the order of Maclaurin series by value.
 */
template <typename FunctionT, size_t Order, typename WrtT>
class hryky::symbolic_computation::MaclaurinSeriesC :
	public WithStreamOut<MaclaurinSeriesC<FunctionT, Order, WrtT> >,
	public Evalable<
		MaclaurinSeriesC<FunctionT, Order, WrtT>,
		typename FunctionT::type::eval_type>
{
public :
	typedef typename MaclaurinSeries<
		FunctionT, Integer<typename WrtT::eval_type, Order>, WrtT>::type type;
};
/**
  @brief approximates an operation by Maclaurin series.

   Maclaurin series is the special case of Taylor series. The center of Taylor
  series is zero.
 */
template <hryky_template_param>
class hryky::symbolic_computation::MaclaurinSeries :
	public WithStreamOut<MaclaurinSeries<hryky_template_arg> >,
	public Evalable<
		MaclaurinSeries<hryky_template_arg>,
		typename FunctionT::type::eval_type>
{
public :
	typedef typename TaylorSeries<
		FunctionT,
		OrderT,
		WrtT,
		Integer<typename WrtT::type::eval_type, 0>
	>::type type;
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
#endif // SYMBOLIC_COMPUTATION_MACLAURIN_SERIES_H_20131201212657560
// end of file
