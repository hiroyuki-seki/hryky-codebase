/**
  @file     symbolic_computation_power.h
  @brief    operates a power which has a base and a exponent typed arbitrarily.
  @author   HRYKY
  @version  $Id: symbolic_computation_power.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_POWER_H_20131019113754151
#define SYMBOLIC_COMPUTATION_POWER_H_20131019113754151
#include "hryky/exponential.h"
#include "hryky/power.h"
#include "hryky/symbolic_computation/symbolic_computation_align.h"
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
	typename BaseopT, typename ExponentT
#define hryky_template_arg \
	BaseopT, ExponentT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// operates a power which has a base and a exponent typed arbitrarily.
	template <hryky_template_param>
	class Power;

	/// receives reduced parameters.
	template <hryky_template_param>
	class PowerImpl;

	template <typename LhsT, typename RhsT>
	class Mul;

	template <typename AntiT>
	class Ln;

	template <typename EvalT>
	class Napier;

	/**
	  @brief achives the type of power operation.
	 */
	template <
		typename BaseopEvalT,
		typename ExponentEvalT,
		bool IsNull = IsSame<BaseopEvalT, hryky::Null>::type::value
	>
	struct PowEvalType;
	
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief operates a power which has a base and a exponent typed arbitrarily.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Power :
	public WithStreamOut<Power<hryky_template_arg> >,
	public Evalable<
		Power<hryky_template_arg>, typename BaseopT::type::eval_type >
{
private :
	typedef PowerImpl<
		typename BaseopT::type, typename ExponentT::type> impl;
public :
	typedef typename impl::type type;
	typedef typename type::eval_type eval_type;
};
/**
  @brief receives reduced parameters from Power.
 */
template <hryky_template_param>
class hryky::symbolic_computation::PowerImpl :
	public hryky::WithStreamOut<PowerImpl<hryky_template_arg> >
{
public :
	typedef typename BaseopT::type          baseop_type;
	typedef typename ExponentT::type        exponent_type;
	typedef PowerImpl<hryky_template_arg>   type;

	typedef typename PowEvalType<
		typename BaseopT::eval_type,
		typename ExponentT::eval_type
	>::type eval_type;
	
	/// evaluates the power.
	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters)
	{
		return hryky::pow(
			BaseopT::eval(parameters),
			ExponentT::eval(parameters));
	}

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;
};
/**
  @brief The type of power operation is null.
 */
template <typename BaseopEvalT, typename ExponentEvalT, bool IsNull>
struct hryky::symbolic_computation::PowEvalType
{
	typedef hryky::Null type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief exponentiates the Napier's Constant.
 */
template <typename EvalT, typename ExponentT>
class PowerImpl<Napier<EvalT>, ExponentT> :
	public hryky::WithStreamOut<PowerImpl<Napier<EvalT>, ExponentT> >
{
public :
	typedef typename Napier<EvalT>::type            baseop_type;
	typedef typename ExponentT::type                exponent_type;
	typedef PowerImpl<baseop_type, exponent_type>   type;
	typedef EvalT                                   eval_type;

	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters)
	{
		return eval_type(
			hryky::exp(exponent_type::eval(parameters)));
	}

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;
};
/**
  @brief prints a representation of power.
 */
template <typename EvalT, typename ExponentT>
template <typename StreamT>
StreamT &
PowerImpl<Napier<EvalT>, ExponentT>::write_to(StreamT & out) const
{
	return out << '(' << baseop_type() << '^' << exponent_type() <<')';
}
/**
  @brief simplifies the power whose exponent is integral.
 */
template <typename BaseopT, typename EvalT, int Value>
class PowerImpl<BaseopT, Integer<EvalT, Value> >
{
public :
	typedef typename IntPower<BaseopT, Value>::type type;
};
/**
  @brief achieves the type resulted by Power operation.
 */
template <typename BaseopEvalT, typename ExponentEvalT>
struct PowEvalType<BaseopEvalT, ExponentEvalT, false>
{
	typedef decltype(
		hryky::pow(BaseopEvalT(), ExponentEvalT())) type;
};
//------------------------------------------------------------------------------
// specializes other classes in respect to this class.
//------------------------------------------------------------------------------
/**
  @brief evaluates function through power.
 */
template <hryky_template_param, template <typename> class FunctionT>
class SomeImpl<PowerImpl<hryky_template_arg>, FunctionT>
{
public :
	typedef typename Some2<BaseopT, ExponentT, FunctionT>::type type;
};
/**
  @brief substites operations in both terms.
 */
template <hryky_template_param, typename ForT, typename AlternativeT>
class SubstituteImpl<PowerImpl<hryky_template_arg>, ForT, AlternativeT>
{
private :
	typedef PowerImpl<hryky_template_arg> target;
public :
	typedef typename Power<
		Substitute<typename target::baseop_type, ForT, AlternativeT>,
		Substitute<typename target::exponent_type, ForT, AlternativeT>
	>::type type;
};
/**
  @brief differentiates a power.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<PowerImpl<hryky_template_arg>, WrtT>
{
private :
	typedef PowerImpl<hryky_template_arg> target;
	typedef typename target::exponent_type exponent;
	typedef typename target::baseop_type baseop;
public :
	typedef typename Mul<
		D<Mul<exponent, Ln<baseop> >, WrtT>, target
	>::type type;
};
/**
  @brief distributes multiplications in the base and exponent.
 */
template <hryky_template_param>
class ScatterImpl<PowerImpl<hryky_template_arg> >
{
public :
	typedef typename Power<Scatter<BaseopT>, Scatter<ExponentT> >::type type;
};
/**
  @brief extracts multiplier in the base and exponent.
 */
template <hryky_template_param>
class GatherImpl<PowerImpl<hryky_template_arg> >
{
public :
	typedef typename Power<Gather<BaseopT>, Gather<ExponentT> >::type type;
};
/**
  @brief aligns operations in the base and exponent.
 */
template <hryky_template_param>
class AlignImpl<PowerImpl<hryky_template_arg> >
{
public :
	typedef typename Power<Align<BaseopT>, Align<ExponentT> >::type type;
};
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief prints a representation of power.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::PowerImpl<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out << '(' << baseop_type() << '^' << exponent_type() << ')';
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
#endif // SYMBOLIC_COMPUTATION_POWER_H_20131019113754151
// end of file
