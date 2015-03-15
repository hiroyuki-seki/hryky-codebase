/**
  @file     symbolic_computation_factorial.h
  @brief    represents a factorial.
  @author   HRYKY
  @version  $Id: symbolic_computation_factorial.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_FACTORIAL_H_20131123020625754
#define SYMBOLIC_COMPUTATION_FACTORIAL_H_20131123020625754
#include "hryky/factorial.h"
#include "hryky/symbolic_computation/symbolic_computation_differentiate.h"
#include "hryky/symbolic_computation/symbolic_computation_evalable.h"
#include "hryky/symbolic_computation/symbolic_computation_some.h"
#include "hryky/symbolic_computation/symbolic_computation_with_stream_out.h"
#include "hryky/symbolic_computation/symbolic_computation_substitute.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename FactorT
#define hryky_template_arg \
	FactorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// represents a factorial.
	template <hryky_template_param>
	class Factorial;

	/// implements Factorial.
	template <hryky_template_param>
	class FactorialImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief represents a factorial.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Factorial :
	public WithStreamOut<Factorial<hryky_template_arg> >,
	public Evalable<
		Factorial<hryky_template_arg>, typename FactorT::eval_type>
{
private :
	typedef FactorialImpl<typename FactorT::type> impl;
public :
	typedef typename impl::type type;
};
/**
  @brief implements Factorial.
 */
template <hryky_template_param>
class hryky::symbolic_computation::FactorialImpl :
	public hryky::WithStreamOut<FactorialImpl<hryky_template_arg> >
{
public :
	typedef FactorialImpl<hryky_template_arg> type;
	typedef typename FactorT::type factor_type;
	typedef typename factor_type::eval_type eval_type;

	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters)
	{
		return eval_type(
			hryky::factorial(factor_type::eval(parameters)));
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
  @brief evaluates function through factorial.
 */
template <hryky_template_param, template <typename> class FunctionT>
class SomeImpl<FactorialImpl<hryky_template_arg>, FunctionT>
{
public :
	typedef typename FunctionT<FactorT>::type type;
};
/**
  @brief substites operations in both terms.
 */
template <hryky_template_param, typename ForT, typename AlternativeT>
class SubstituteImpl<FactorialImpl<hryky_template_arg>, ForT, AlternativeT>
{
private :
	typedef FactorialImpl<hryky_template_arg> target;
public :
	typedef typename Factorial<
		Substitute<typename target::factor_type, ForT, AlternativeT>
	>::type type;
};
/**
  @brief A factorial seem to be constant in differentiation.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<FactorialImpl<hryky_template_arg>, WrtT>
{
private :
	typedef FactorialImpl<hryky_template_arg> target;
public :
	typedef typename Integer<typename target::eval_type, 0>::type type;
};
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief prints the expression of factorial.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::FactorialImpl<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out << factor_type() << '!';
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
#endif // SYMBOLIC_COMPUTATION_FACTORIAL_H_20131123020625754
// end of file
