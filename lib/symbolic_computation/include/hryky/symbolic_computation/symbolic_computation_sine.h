/**
  @file     symbolic_computation_sine.h
  @brief    operates a trigonometric sine function.
  @author   HRYKY
  @version  $Id: symbolic_computation_sine.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_SINE_H_20131020182145431
#define SYMBOLIC_COMPUTATION_SINE_H_20131020182145431
#include "hryky/symbolic_computation/symbolic_computation_align.h"
#include "hryky/symbolic_computation/symbolic_computation_evalable.h"
#include "hryky/symbolic_computation/symbolic_computation_gather.h"
#include "hryky/symbolic_computation/symbolic_computation_scatter.h"
#include "hryky/symbolic_computation/symbolic_computation_some.h"
#include "hryky/symbolic_computation/symbolic_computation_with_stream_out.h"
#include "hryky/symbolic_computation/symbolic_computation_substitute.h"
#include "hryky/sine.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename AngleT, typename EvalT
#define hryky_template_arg \
	AngleT, EvalT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// The alias of Sine.
	template <hryky_template_param>
	class Sin;

	/// operates a trigonometric sine function.
	template <hryky_template_param>
	class Sine;

	/// implements to operate a trigonometric sine function.
	template <hryky_template_param>
	class SineImpl;

	template <hryky_template_param>
	class Cos;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The alias of Sine.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Sin :
	public WithStreamOut<Sine<hryky_template_arg> >,
	public Evalable<Sine<hryky_template_arg>, EvalT>
{
private :
	typedef Sine<typename AngleT::type, EvalT> impl;
public :
	typedef typename impl::type         type;
};
/**
  @brief operates a trigonometric sine function.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Sine :
	public WithStreamOut<Sine<hryky_template_arg> >,
	public Evalable<Sine<hryky_template_arg>, EvalT>
{
private :
	typedef SineImpl<typename AngleT::type, EvalT> impl;
public :
	typedef typename impl::type type;
};
/**
  @brief implements to operate a trigonometric sine function.
 */
template <hryky_template_param>
class hryky::symbolic_computation::SineImpl :
	public hryky::WithStreamOut<SineImpl<hryky_template_arg> >
{
public :
	typedef typename AngleT::type           angle_type;
	typedef SineImpl<hryky_template_arg>    type;
	typedef EvalT                           eval_type;

	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters)
	{
		return eval_type(hryky::sin(angle_type::eval(parameters)));
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
/**
  @brief sin(0) is zero.
 */
template <typename IntEvalT, typename EvalT>
class SineImpl<Integer<IntEvalT, 0>, EvalT>
{
public :
	typedef typename Integer<EvalT, 0>::type type;
};
//------------------------------------------------------------------------------
// specializes other classes in respect to this class.
//------------------------------------------------------------------------------
/**
  @brief evaluates function through sine.
 */
template <hryky_template_param, template <typename> class FunctionT>
class SomeImpl<SineImpl<hryky_template_arg>, FunctionT>
{
public :
	typedef typename FunctionT<AngleT>::type type;
};
/**
  @brief substites operations in the angular operation.
 */
template <hryky_template_param, typename ForT, typename AlternativeT>
class SubstituteImpl<SineImpl<hryky_template_arg>, ForT, AlternativeT>
{
private :
	typedef SineImpl<hryky_template_arg> target;
public :
	typedef typename Sin<
		Substitute<typename target::angle_type, ForT, AlternativeT>, EvalT
	>::type type;
};
/**
  @brief distributes multiplications in the angular operation.
 */
template <hryky_template_param>
class ScatterImpl<SineImpl<hryky_template_arg> >
{
public :
	typedef typename Sin<Scatter<AngleT>, EvalT>::type type;
};
/**
  @brief extracts multiplier in angular operation.
 */
template <hryky_template_param>
class GatherImpl<SineImpl<hryky_template_arg> >
{
public :
	typedef typename Sin<Gather<AngleT>, EvalT>::type type;
};
/**
  @brief aligns operations in the angular operation.
 */
template <hryky_template_param>
class AlignImpl<SineImpl<hryky_template_arg> >
{
public :
	typedef typename Sin<Align<AngleT>, EvalT>::type type;
};
/**
  @brief differentiates a trigonometric sine function.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<SineImpl<hryky_template_arg>, WrtT>
{
public :
	typedef typename Cos<hryky_template_arg>::type type;
};
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief prints a trigonometric sine function.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::SineImpl<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out << "sin(" << angle_type() << ')';
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
#endif // SYMBOLIC_COMPUTATION_SINE_H_20131020182145431
// end of file
