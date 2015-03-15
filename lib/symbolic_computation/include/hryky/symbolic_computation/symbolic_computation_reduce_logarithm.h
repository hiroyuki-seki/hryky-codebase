/**
  @file     symbolic_computation_reduce_logarithm.h
  @brief    reduces an operation of natural logarithm.
  @author   HRYKY
  @version  $Id: symbolic_computation_reduce_logarithm.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_SYMPLIFY_LOGARITHM_H_20131019175852415
#define SYMBOLIC_COMPUTATION_SYMPLIFY_LOGARITHM_H_20131019175852415
#include "hryky/symbolic_computation/symbolic_computation_simplify.h"
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
	template <hryky_template_param>
	class Ln;

	template <hryky_template_param>
	class LogarithmImpl;

	template <typename EvalT, int Value>
	class Integer;

	template <typename LhsT, typename RhsT>
	class Mul;

	template <typename BaseopT, typename ExponentT>
	class PowerImpl;

	template <typename EvalT>
	class Napier;

	/// simplifies a natural logarithm.
	template <hryky_template_param>
	class ReduceLn;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief simplifies a natural logarithm.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceLn
{
private :
	typedef Reduce<AntiT> anti;
	typedef Ln<anti> ln;
public :
	static bool const value = anti::value || IsAtom<ln>::value;
	typedef typename ReduceIfC<value, anti>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief restricts the specilization to a natural logarithm.
 */
template <hryky_template_param>
class ReduceImpl<LogarithmImpl<hryky_template_arg> >
{
private :
	typedef ReduceLn<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::type;
};
/**
  @brief reduces to zero.
 */
template <typename EvalT>
class ReduceLn<Integer<EvalT, 1> >
{
public :
	typedef typename Integer<EvalT, 0>::type type;
	static bool const value = true;
};
/**
  @brief reduces to one.
 */
template <typename EvalT>
class ReduceLn<Napier<EvalT> >
{
public :
	typedef typename Integer<EvalT, 1>::type type;
	static bool const value = true;
};
/**
  @brief extracts the exponent of anti-logarithm.
 */
template <typename BaseopT, typename ExponentT>
class ReduceLn<PowerImpl<BaseopT, ExponentT> >
{
private :
	typedef Reduce<BaseopT>   baseop;
	typedef Reduce<ExponentT> exponent;
public :
	typedef typename Reduce<Mul<exponent, Ln<baseop> > >::type type;
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
#endif // SYMBOLIC_COMPUTATION_SYMPLIFY_LOGARITHM_H_20131019175852415
// end of file
