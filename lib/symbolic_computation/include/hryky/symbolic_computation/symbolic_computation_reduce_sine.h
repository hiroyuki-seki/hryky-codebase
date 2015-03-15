/**
  @file     symbolic_computation_reduce_sine.h
  @brief    reduces operations in the trigonometric sine function.
  @author   HRYKY
  @version  $Id: symbolic_computation_reduce_sine.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_REDUCE_SINE_H_20131128152119306
#define SYMBOLIC_COMPUTATION_REDUCE_SINE_H_20131128152119306
#include "hryky/symbolic_computation/symbolic_computation_reduce.h"
#include "hryky/symbolic_computation/symbolic_computation_is_integer.h"
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
	template <typename EvalT, int Value>
	class Integer;

	template <hryky_template_param>
	class Sin;

	template <hryky_template_param>
	class SineImpl;

	template <typename EvalT>
	class Pi;

	/// reduces operations in the trigonometric sine function.
	template <hryky_template_param>
	class ReduceSin;

	template <hryky_template_param>
	class ReduceSinHalfPi;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief reduces to constant value if the angle is multiple of PI/2.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceSinHalfPi
{
	typedef ReduceSin<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief reduces operations in the trigonometric sine function.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceSin
{
private :
	typedef Reduce<AngleT>      angle;
	typedef Sin<angle, EvalT>   sin;
public :
	static bool const value = angle::value || IsAtom<sin>::value;
	typedef typename ReduceIfC<value, sin>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief restricts the specializations for sine function.
 */
template <hryky_template_param>
class ReduceImpl<SineImpl<hryky_template_arg> >
{
private :
	typedef ReduceSinHalfPi<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
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
#endif // SYMBOLIC_COMPUTATION_REDUCE_SINE_H_20131128152119306
// end of file
