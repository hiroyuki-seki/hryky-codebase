/**
  @file     symbolic_computation_summation.h
  @brief    represents the sum of an operation.
  @author   HRYKY
  @version  $Id: symbolic_computation_summation.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_SUMMATION_H_20131123185924457
#define SYMBOLIC_COMPUTATION_SUMMATION_H_20131123185924457
#include "hryky/iterator/at.h"
#include "hryky/symbolic_computation/symbolic_computation_align.h"
#include "hryky/symbolic_computation/symbolic_computation_integer.h"
#include "hryky/symbolic_computation/symbolic_computation_dividable.h"
#include "hryky/symbolic_computation/symbolic_computation_differentiate.h"
#include "hryky/symbolic_computation/symbolic_computation_evalable.h"
#include "hryky/symbolic_computation/symbolic_computation_gather.h"
#include "hryky/symbolic_computation/symbolic_computation_scatter.h"
#include "hryky/symbolic_computation/symbolic_computation_some.h"
#include "hryky/symbolic_computation/symbolic_computation_with_stream_out.h"
#include "hryky/symbolic_computation/symbolic_computation_substitute.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename OpT, typename IndexT, typename FirstT, typename LastT
#define hryky_template_arg \
	OpT, IndexT, FirstT, LastT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// The alias of Summation.
	template <hryky_template_param>
	class Sum;

	/// binds the range of summation to constant values.
	template <typename OpT, typename IndexT, int First, int Last>
	class SumC;
	
	/// represents the sum of an operation.
	template <hryky_template_param>
	class Summation;

	/// implements Summation.
	template <hryky_template_param>
	class SummationImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The alias of summation.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Sum :
	public WithStreamOut<Sum<hryky_template_arg> >,
	public Evalable<
		Sum<hryky_template_arg>, typename OpT::type::eval_type>
{
private :
	typedef Summation<hryky_template_arg> impl;
public :
	typedef typename impl::type         type;
	typedef typename type::eval_type    eval_type;
};
/**
  @brief binds the range of summation to constant values.
 */
template <typename OpT, typename IndexT, int First, int Last>
class hryky::symbolic_computation::SumC :
	public WithStreamOut<SumC<OpT, IndexT, First, Last> >,
	public Evalable<
		SumC<OpT, IndexT, First, Last>, typename OpT::type::eval_type>
{
private :
	typedef Integer<typename IndexT::eval_type, First> first;
	typedef Integer<typename IndexT::eval_type, Last> last;
	typedef Sum<OpT, IndexT, first, last> impl;
public :
	typedef typename impl::type         type;
	typedef typename type::eval_type    eval_type;
};
/**
  @brief represents the sum of an operation.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Summation :
	public WithStreamOut<Summation<hryky_template_arg> >,
	public Evalable<
		Summation<hryky_template_arg>, typename OpT::type::eval_type>
{
private :
	typedef SummationImpl<
		typename OpT::type,
		typename IndexT::type,
		typename FirstT::type,
		typename LastT::type
	> impl;
public :
	typedef typename impl::type         type;
	typedef typename type::eval_type    eval_type;
};
/**
  @brief implements Summation.
 */
template <hryky_template_param>
class hryky::symbolic_computation::SummationImpl :
	public hryky::WithStreamOut<SummationImpl<hryky_template_arg> >
{
public :
	typedef typename OpT::type                  op_type;
	typedef typename op_type::eval_type         eval_type;
	typedef typename FirstT::type               first_type;
	typedef typename LastT::type                last_type;
	typedef typename IndexT::type               index_type;
	typedef SummationImpl<hryky_template_arg>   type;

	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters)
	{
		typedef int index_value_type;
		index_value_type const last =
			static_cast<index_value_type>(last_type::eval(parameters));
		index_value_type const first =
			static_cast<index_value_type>(first_type::eval(parameters));
		
		if (last < first) {
			return eval_type();
		}

		index_value_type index = first;
		eval_type result = eval_type();
		ParametersT serial_params(parameters);
		
		for (; last != index; ++index) {
			hryky::at<ParametersT, index_type::index>(serial_params) = index;
			result += op_type::eval(serial_params);
		}

		return result;
	}

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
//------------------------------------------------------------------------------
// specializes other classes in respect to this class.
//------------------------------------------------------------------------------
/**
  @brief evaluates function through summation.
 */
template <hryky_template_param, template <typename> class FunctionT>
class SomeImpl<SummationImpl<hryky_template_arg>, FunctionT>
{
public :
	typedef typename Some4<
		OpT, IndexT, FirstT, LastT, FunctionT>::type type;
};
/**
  @brief A summation can be divided if the kernel operation can be divided.
 */
template <hryky_template_param, typename WrtT>
class DividableImpl<SummationImpl<hryky_template_arg>, WrtT>
{
private :
	typedef Dividable<OpT, WrtT> op;
public :
	typedef typename Sum<
		op,
		IndexT,
		FirstT,
		LastT
	>::type type;
	static bool const value = op::value;
};
/**
  @brief substitutes operations in the kernel operation and boundaries.
 */
template <hryky_template_param, typename ForT, typename AlternativeT>
class SubstituteImpl<SummationImpl<hryky_template_arg>, ForT, AlternativeT>
{
public :
	typedef typename Sum<
		Substitute<OpT, ForT, AlternativeT>,
		IndexT,
		Substitute<FirstT, ForT, AlternativeT>,
		Substitute<LastT, ForT, AlternativeT>
	>::type type;
};
/**
  @brief differentiates operations in the kernel operation.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<SummationImpl<hryky_template_arg>, WrtT>
{
public :
	typedef typename Sum<D<OpT, WrtT>, IndexT, FirstT, LastT>::type type;
};
/**
  @brief distributes multiplications in this operation.
 */
template <hryky_template_param>
class ScatterImpl<SummationImpl<hryky_template_arg> >
{
public :
	typedef typename Sum<
		Scatter<OpT>,
		IndexT,
		Scatter<FirstT>,
		Scatter<LastT>
	>::type type;
};
/**
  @brief extracts multiplier in this operation.
 */
template <hryky_template_param>
class GatherImpl<SummationImpl<hryky_template_arg> >
{
public :
	typedef typename Sum<
		Gather<OpT>,
		IndexT,
		Gather<FirstT>,
		Gather<LastT>
	>::type type;
};
/**
  @brief aligns operations in this kernel operation.
 */
template <hryky_template_param>
class AlignImpl<SummationImpl<hryky_template_arg> >
{
public :
	typedef typename Sum<
		Align<OpT>,
		IndexT,
		Align<FirstT>,
		Align<LastT>
	>::type type;
};
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief prints the expression of summation.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::SummationImpl<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return (
		out << "sum{" << index_type() << ':' << first_type() <<
		"->" << last_type() << "}(" << op_type() << ")");
}
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
#endif // SYMBOLIC_COMPUTATION_SUMMATION_H_20131123185924457
// end of file
