/**
  @file     symbolic_computation_is_integer.h
  @brief    confirms whether the type is integral.
  @author   HRYKY
  @version  $Id: symbolic_computation_is_integer.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_IS_INTEGER_H_20131010222021597
#define SYMBOLIC_COMPUTATION_IS_INTEGER_H_20131010222021597
#include "hryky/symbolic_computation/symbolic_computation_integer.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TermT
#define hryky_template_arg \
	TermT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// confirms whether the type is integral.
	template <hryky_template_param>
	class IsInteger;

	/// implements IsInteger.
	template <hryky_template_param>
	class IsIntegerImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether the type is integral.
 */
template <hryky_template_param>
class hryky::symbolic_computation::IsInteger
{
public :
	static bool const value = IsIntegerImpl<typename TermT::type>::value;

};
/**
  @brief implements IsInteger.
 */
template <hryky_template_param>
class hryky::symbolic_computation::IsIntegerImpl
{
public :
	static bool const value = false;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief specializes if the type is integral.
 */
template <typename EvalT, int Value>
class IsIntegerImpl<Integer<EvalT, Value> >
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
#endif // SYMBOLIC_COMPUTATION_IS_INTEGER_H_20131010222021597
// end of file
