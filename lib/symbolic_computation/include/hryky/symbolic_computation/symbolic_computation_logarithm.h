/**
  @file     symbolic_computation_logarithm.h
  @brief    operates a natural logarithm.
  @author   HRYKY
  @version  $Id: symbolic_computation_logarithm.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_LOGARITHM_H_20131019141736262
#define SYMBOLIC_COMPUTATION_LOGARITHM_H_20131019141736262
#include "hryky/logarithm.h"
#include "hryky/symbolic_computation/symbolic_computation_align.h"
#include "hryky/symbolic_computation/symbolic_computation_evalable.h"
#include "hryky/symbolic_computation/symbolic_computation_scatter.h"
#include "hryky/symbolic_computation/symbolic_computation_some.h"
#include "hryky/symbolic_computation/symbolic_computation_with_stream_out.h"
#include "hryky/symbolic_computation/symbolic_computation_substitute.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename AntiT
#define hryky_template_arg \
	AntiT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// The alias of Logarithm.
	template <hryky_template_param>
	class Ln;

	/// operates a natural logarithm.
	template <hryky_template_param>
	class Logarithm;

	/// implements an operation of natural logarithm.
	template <hryky_template_param>
	class LogarithmImpl;

	template <typename LhsT, typename RhsT>
	class Divide;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The alias of Logarithm.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Ln :
	public WithStreamOut<Ln<hryky_template_arg> >,
	public Evalable<Ln<hryky_template_arg>, typename AntiT::type::eval_type >
{
private :
	typedef Logarithm<typename AntiT::type> impl;
public :
	typedef typename impl::type type;
};
/**
  @brief operates a natural logarithm.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Logarithm :
	public WithStreamOut<Logarithm<hryky_template_arg> >,
	public Evalable<
		Logarithm<hryky_template_arg>, typename AntiT::eval_type >
{
private :
	typedef LogarithmImpl<typename AntiT::type> impl;
public :
	typedef typename impl::type type;
	typedef typename type::eval_type eval_type;
};
/**
  implements an operation of natural logarithm.
 */
template <hryky_template_param>
class hryky::symbolic_computation::LogarithmImpl :
	public hryky::WithStreamOut<LogarithmImpl<hryky_template_arg> >
{
public :
	typedef typename AntiT::type                    anti_type;
	typedef LogarithmImpl<hryky_template_arg>       type;
	
	typedef decltype(
		hryky::ln(typename anti_type::eval_type())) eval_type;

	/// evaluates an operation of natural logarithm.
	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters)
	{
		return hryky::ln(anti_type::eval(parameters));
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
  @brief evaluates function through natural logarithm.
 */
template <hryky_template_param, template <typename> class FunctionT>
class SomeImpl<LogarithmImpl<hryky_template_arg>, FunctionT>
{
public :
	typedef typename FunctionT<AntiT>::type type;
};
/**
  @brief substites operations in both terms.
 */
template <hryky_template_param, typename ForT, typename AlternativeT>
class SubstituteImpl<LogarithmImpl<hryky_template_arg>, ForT, AlternativeT>
{
private :
	typedef LogarithmImpl<hryky_template_arg> target;
public :
	typedef typename Ln<
		Substitute<typename target::anti_type, ForT, AlternativeT>
	>::type type;
};
/**
  differentiates a natural logarithm.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<LogarithmImpl<hryky_template_arg>, WrtT>
{
private :
	typedef LogarithmImpl<hryky_template_arg> target;
public :
	typedef typename Divide<
		D<typename target::anti_type, WrtT>,
		typename target::anti_type
	>::type type;
};
/**
  @brief distributes multiplications in the term.
 */
template <hryky_template_param>
class ScatterImpl<LogarithmImpl<hryky_template_arg> >
{
public :
	typedef typename Ln<Scatter<AntiT> >::type type;
};
/**
  @brief aligns operations in the term.
 */
template <hryky_template_param>
class AlignImpl<LogarithmImpl<hryky_template_arg> >
{
public :
	typedef typename Ln<Align<AntiT> >::type type;
};
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief prints the representation of natural logarithm.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::LogarithmImpl<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out << "ln(" << anti_type() << ")";
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
#endif // SYMBOLIC_COMPUTATION_LOGARITHM_H_20131019141736262
// end of file
