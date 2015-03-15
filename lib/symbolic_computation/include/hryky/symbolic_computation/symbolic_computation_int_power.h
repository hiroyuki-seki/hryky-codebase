/**
  @file     symbolic_computation_int_power.h
  @brief    operates a power whose exponent is integer.
  @author   HRYKY
  @version  $Id: symbolic_computation_int_power.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_INT_POWER_H_20131010145300286
#define SYMBOLIC_COMPUTATION_INT_POWER_H_20131010145300286
#include "hryky/power.h"
#include "hryky/symbolic_computation/symbolic_computation_align.h"
#include "hryky/symbolic_computation/symbolic_computation_dividable.h"
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
	typename BaseopT, int Exponent
#define hryky_template_arg \
	BaseopT, Exponent
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// operates a power whose exponent is integer.
	template <hryky_template_param>
	class IntPower;

	/// specializes an integral exponentioal operation in regard to the base.
	template <hryky_template_param>
	class IntPowerBaseop;

	/// specializes an integral exponentioal operation in regard to the exponent.
	template <hryky_template_param>
	class IntPowerExponent;

	/// operates a power whose exponent is integer.
	template <hryky_template_param>
	class IntPowerImpl;

	/// evaluates IntPowerImpl
	template <
		hryky_template_param,
		bool Positive = (0 < Exponent)
	>
	class IntPowerSigned;

	template <typename LhsT, typename RhsT>
	class Mul;

	template <typename EvalT, int Value>
	class Integer;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief operates a power whose exponent is integer.
 */
template <hryky_template_param>
class hryky::symbolic_computation::IntPower :
	public WithStreamOut<IntPower<hryky_template_arg> >,
	public Evalable<
		IntPower<hryky_template_arg>, typename BaseopT::type::eval_type>
{
private :
	typedef IntPowerBaseop<typename BaseopT::type, Exponent> impl;
public :
	typedef typename impl::type type;
};
/**
  @brief specializes an integral exponentioal operation in regard to the base.
 */
template <hryky_template_param>
class hryky::symbolic_computation::IntPowerBaseop
{
public :
	typedef typename IntPowerExponent<hryky_template_arg>::type type;
};
/**
  @brief specializes an integral exponentioal operation in regard to the exponent.
 */
template <hryky_template_param>
class hryky::symbolic_computation::IntPowerExponent
{
public :
	typedef typename IntPowerImpl<hryky_template_arg>::type type;
};
/**
  @brief evaluates IntPowerImpl
 */
template <hryky_template_param, bool Positive>
class hryky::symbolic_computation::IntPowerSigned
{
public :
	typedef typename BaseopT::type                      baseop_type;
	typedef typename IntPowerImpl<BaseopT, Exponent>    type;

	typedef decltype(
		hryky::pow(typename BaseopT::eval_type(), size_t())) eval_type;

	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters)
	{
		return hryky::pow(
			baseop_type::eval(parameters),
			static_cast<size_t>(Exponent));
	}
};
/**
  @brief operates a power whose exponent is integer.
 */
template <hryky_template_param>
class hryky::symbolic_computation::IntPowerImpl :
	public IntPowerSigned<hryky_template_arg>,
	public hryky::WithStreamOut<IntPowerImpl<hryky_template_arg> >
{
public :
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
/**
  @brief reduces to zero if the base is zero.
 */
template <typename EvalT, int Exponent>
class IntPowerBaseop<Integer<EvalT, 0>, Exponent>
{
public :
	typedef typename Integer<EvalT, 0>::type type;
};
/**
  @brief reduces to one if the base is one.
 */
template <typename EvalT, int Exponent>
class IntPowerBaseop<Integer<EvalT, 1>, Exponent>
{
public :
	typedef typename Integer<EvalT, 1>::type type;
};
/**
  @brief reduces to one if the exponent is zero.
 */
template <typename BaseopT>
class IntPowerExponent<BaseopT, 0>
{
public :
	typedef typename Integer<
		typename BaseopT::eval_type, 1>::type type;
};
/**
  @brief reduces to the base operation if the exponent is one.
 */
template <typename BaseopT>
class IntPowerExponent<BaseopT, 1>
{
public :
	typedef typename BaseopT::type type;
};
/**
  @brief creates higher differentiation.
 */
template <typename TargetT, typename WrtT, int Exponent>
class IntPowerImpl<DifferentiateImpl<TargetT, WrtT>, Exponent>
{
private :
	static_assert(
		1 < Exponent,
		"The exponent of higher differential operator has to "
		"be more than one.");
public :
	typedef typename D<
		IntPower<D<TargetT, WrtT>, Exponent - 1>, WrtT>::type type;
};
/**
  @brief specializes if the exponent is negative.
 */
template <hryky_template_param>
class IntPowerSigned<hryky_template_arg, false>
{
public :
	typedef typename BaseopT::type                      baseop_type;
	typedef typename IntPowerImpl<BaseopT, Exponent>    type;

	typedef decltype(
		typename BaseopT::eval_type() /
		hryky::pow(typename BaseopT::eval_type(), size_t())) eval_type;
	

	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters)
	{
		return eval_type(1) / hryky::pow(
			baseop_type::eval(parameters),
			static_cast<size_t>(-Exponent));
	}
};
//------------------------------------------------------------------------------
// specializes other classes in respect to this class.
//------------------------------------------------------------------------------
/**
  @brief evaluates function through integral exponent.
 */
template <hryky_template_param, template <typename> class FunctionT>
class SomeImpl<IntPowerImpl<hryky_template_arg>, FunctionT>
{
public :
	typedef typename FunctionT<BaseopT>::type type;
};
/**
  @brief divides the exponential operation.
 */
template <hryky_template_param, int WrtExponent>
class DividableImpl<
	IntPowerImpl<hryky_template_arg>,
	IntPowerImpl<BaseopT, WrtExponent>
>
{
public :
	typedef typename IntPower<BaseopT, Exponent - WrtExponent>::type
		type;
	static const bool value = true;
};
/**
  @brief substites operations in the base operation.
 */
template <hryky_template_param, typename ForT, typename AlternativeT>
class SubstituteImpl<IntPowerImpl<hryky_template_arg>, ForT, AlternativeT>
{
private :
	typedef IntPowerImpl<hryky_template_arg> target;
public :
	typedef typename IntPower<
		Substitute<typename target::baseop_type, ForT, AlternativeT>,
		Exponent
	>::type type;
};
/**
  @brief differentiates an exponential operation.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<IntPowerImpl<hryky_template_arg>, WrtT>
{
private :
	typedef IntPowerImpl<hryky_template_arg> target;
public :
	typedef typename Mul<
		Mul<
			Integer<typename target::eval_type, Exponent>,
			IntPower<BaseopT, Exponent - 1>
		>,
		D<typename target::baseop_type, WrtT>
	>::type type;
};
/**
  @brief distributes multiplications in the term.
 */
template <hryky_template_param>
class ScatterImpl<IntPowerImpl<hryky_template_arg> >
{
public :
	typedef typename IntPower<Scatter<BaseopT>, Exponent>::type type;
};
/**
  @brief extracts multiplifer in the term.
 */
template <hryky_template_param>
class GatherImpl<IntPowerImpl<hryky_template_arg> >
{
public :
	typedef typename IntPower<Gather<BaseopT>, Exponent>::type type;
};
/**
  @brief aligns operations in the term.
 */
template <hryky_template_param>
class AlignImpl<IntPowerImpl<hryky_template_arg> >
{
public :
	typedef typename IntPower<Align<BaseopT>, Exponent>::type type;
};
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief prints a power.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::IntPowerImpl<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out << '(' << baseop_type() << '^' << Exponent << ')';
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
#endif // SYMBOLIC_COMPUTATION_INT_POWER_H_20131010145300286
// end of file
