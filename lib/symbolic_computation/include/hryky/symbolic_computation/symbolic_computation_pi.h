/**
  @file     symbolic_computation_pi.h
  @brief    represents the mathematical constant of PI.
  @author   HRYKY
  @version  $Id: symbolic_computation_pi.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_PI_H_20131119190951465
#define SYMBOLIC_COMPUTATION_PI_H_20131119190951465
#include "hryky/stream/ostream_string.h"
#include "hryky/symbolic_computation/symbolic_computation_differentiate.h"
#include "hryky/pi.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename EvalT
#define hryky_template_arg \
	EvalT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// represents the mathematical constant of PI.
	template <hryky_template_param>
	class Pi;

	template <typename EvalT, int Value>
	class Integer;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief represents the mathematical constant of PI.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Pi :
	public hryky::WithStreamOut<Pi<hryky_template_arg> >
{
public :
	typedef EvalT eval_type;
	typedef Pi<hryky_template_arg> type;

	template <typename ParametersT>
	static eval_type eval(ParametersT const &)
	{
		return hryky::Pi<eval_type>::value;
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
  @brief differentiates the PI.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<Pi<hryky_template_arg>, WrtT>
{
public :
	typedef typename Integer<EvalT, 0>::type type;
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
/**
  @brief prints the symbol of PI.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::Pi<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out << "pi";
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SYMBOLIC_COMPUTATION_PI_H_20131119190951465
// end of file
