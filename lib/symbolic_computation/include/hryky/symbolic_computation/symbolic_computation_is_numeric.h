/**
  @file     symbolic_computation_is_numeric.h
  @brief    confirmes whether the operation is numeric.
  @author   HRYKY
  @version  $Id: symbolic_computation_is_numeric.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_IS_NUMERIC_H_20131130185409454
#define SYMBOLIC_COMPUTATION_IS_NUMERIC_H_20131130185409454
#include "hryky/symbolic_computation/symbolic_computation_is_integer.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TargetT
#define hryky_template_arg \
	TargetT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// confirmes whether the operation is numeric.
	template <hryky_template_param>
	class IsNumeric;

	/// implements IsNumeric.
	template <hryky_template_param>
	class IsNumericImpl;

	template <typename EvalT, int Dividend, int Divisor>
	class FractionImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirmes whether the operation is numeric.
 */
template <typename TargetT>
class hryky::symbolic_computation::IsNumeric
{
private :
	typedef IsNumericImpl<typename TargetT::type> impl;
public :
	static bool const value = impl::value;
};
/**
  @brief implements IsNumeric.
 */
template <typename TargetT>
class hryky::symbolic_computation::IsNumericImpl
{
public :
	static bool const value = IsInteger<TargetT>::value;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief The fractional number is numeric.
 */
template <typename EvalT, int Dividend, int Divisor>
class IsNumericImpl<FractionImpl<EvalT, Dividend, Divisor> >
{
public :
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
#endif // SYMBOLIC_COMPUTATION_IS_NUMERIC_H_20131130185409454
// end of file
