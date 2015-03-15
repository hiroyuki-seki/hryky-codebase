/**
  @file     symbolic_computation_napier.h
  @brief    represents the Napier's Constant.
  @author   HRYKY
  @version  $Id: symbolic_computation_napier.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_NAPIER_H_20131020171445385
#define SYMBOLIC_COMPUTATION_NAPIER_H_20131020171445385
#include "hryky/stream/ostream_string.h"
#include "hryky/symbolic_computation/symbolic_computation_differentiate.h"
#include "hryky/napier_constant.h"
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
	/// represents the Napier's Constant.
	template <hryky_template_param>
	class Napier;

	template <typename EvalT, int Value>
	class Integer;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief represents the Napier's Constant.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Napier :
	public hryky::WithStreamOut<Napier<hryky_template_arg> >
{
public :
	typedef EvalT eval_type;
	typedef Napier<hryky_template_arg> type;

	template <typename ParametersT>
	static eval_type eval(ParametersT const &)
	{
		return NapierConstant<eval_type>::value;
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
  @brief differentiates the Napier's Constant.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<Napier<hryky_template_arg>, WrtT>
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
  @brief prints the symbol of Napier's Constant.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::Napier<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out << "e";
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SYMBOLIC_COMPUTATION_NAPIER_H_20131020171445385
// end of file
