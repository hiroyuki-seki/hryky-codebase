/**
  @file     symbolic_computation_reduce_factorial.h
  @brief    reduces Factorial.
  @author   HRYKY
  @version  $Id: symbolic_computation_reduce_factorial.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_REDUCE_FACTORIAL_H_20131123023323773
#define SYMBOLIC_COMPUTATION_REDUCE_FACTORIAL_H_20131123023323773
#include "hryky/symbolic_computation/symbolic_computation_simplify.h"
#include "hryky/factorial.h"
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
	template <hryky_template_param>
	class Factorial;
	
	template <hryky_template_param>
	class FactorialImpl;
	
	/// reduces factorial.
	template <hryky_template_param>
	class ReduceFactorial;
	
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief reduces factorial.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceFactorial
{
private :
	typedef Reduce<FactorT> factor;
public :
	static bool const value = factor::value;
	typedef typename ReduceIf<
		factor, Factorial<typename factor::type> >::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief constrains simplification to factorial.
 */
template <hryky_template_param>
class ReduceImpl<FactorialImpl<hryky_template_arg> >
{
private :
	typedef ReduceFactorial<typename Reduce<FactorT>::type> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
//------------------------------------------------------------------------------
// specializes classes for ReduceFactorial
//------------------------------------------------------------------------------
/**
  @brief calculates the factorial at compile time.
 */
template <typename EvalT, int Value>
class ReduceFactorial<Integer<EvalT, Value> >
{
	static_assert(
		0 <= Value,
		"The factorial of negative number is not supported.");
public :
	typedef typename Integer<EvalT, hryky::Factorial<Value>::value>::type type;
	static bool const value = true;
};
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
#endif // SYMBOLIC_COMPUTATION_REDUCE_FACTORIAL_H_20131123023323773
// end of file
