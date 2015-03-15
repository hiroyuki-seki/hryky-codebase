/**
  @file     symbolic_computation_reduce_power.h
  @brief    reduces a power.
  @author   HRYKY
  @version  $Id: symbolic_computation_reduce_power.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_SYMPLIFY_POWER_H_20131020085051035
#define SYMBOLIC_COMPUTATION_SYMPLIFY_POWER_H_20131020085051035
#include "hryky/symbolic_computation/symbolic_computation_simplify.h"
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
	template <typename BaseopT, int Exponent>
	class IntPower;
	
	template <hryky_template_param>
	class Power;
	
	template <hryky_template_param>
	class PowerImpl;
	
	template <typename LhsT, typename RhsT>
	class Mul;

	/// reduces a exponential operation.
	template <hryky_template_param>
	class ReducePower;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief reduces a exponential operation.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReducePower
{
private :
	typedef Reduce<BaseopT>         baseop;
	typedef Reduce<ExponentT>       exponent;
	typedef Power<baseop, exponent> power;
public :
	static bool const value = (
		baseop::value ||
		exponent::value ||
		IsAtom<power>::value ||
		IsInteger<exponent>::value);
	typedef typename ReduceIfC<value, power>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief reduces the base operation and the exponent.
 */
template <hryky_template_param>
class ReduceImpl<PowerImpl<hryky_template_arg> >
{
private :
	typedef ReducePower<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief multiplies the nested exponents.
 */
template <typename BaseopT, typename InternalT, typename ExternalT>
class ReducePower<PowerImpl<BaseopT, InternalT>, ExternalT>
{
private :
	typedef Reduce<BaseopT>   baseop;
	typedef Reduce<InternalT> internal;
	typedef Reduce<ExternalT> external;
public :
	typedef typename Reduce<Power<
		baseop, Mul<internal, external> > >::type type;
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
#endif // SYMBOLIC_COMPUTATION_SYMPLIFY_POWER_H_20131020085051035
// end of file
