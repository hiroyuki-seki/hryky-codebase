/**
  @file     symbolic_computation_is_zero_vector.h
  @brief    confirms whether all elements of vector are zero.
  @author   HRYKY
  @version  $Id: symbolic_computation_is_zero_vector.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_IS_ZERO_VECTOR_H_20131110173114396
#define SYMBOLIC_COMPUTATION_IS_ZERO_VECTOR_H_20131110173114396
#include "hryky/tmp/tmp_and.h"
#include "hryky/type_traits/integral_constant.h"
#include "hryky/symbolic_computation/symbolic_computation_is_zero.h"
#include "hryky/symbolic_computation/symbolic_computation_terminator.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename VectorT
#define hryky_template_arg \
	VectorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// confirms whether all elements of vector are zero.
	template <hryky_template_param>
	class IsZeroVector;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether all elements of vector are zero.
 */
template <hryky_template_param>
class hryky::symbolic_computation::IsZeroVector
{
private :
	typedef typename VectorT::type target;
public :
	typedef typename IntegralConstantOf<tmp::And<
		IsZero<typename target::element_type>,
		IsZeroVector<typename target::rest_type>
	> >::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief confirms whether all elements of terminal vector are zero.
 */
template <>
class IsZeroVector<Terminator>
{
public :
	typedef true_type type;
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
#endif // SYMBOLIC_COMPUTATION_IS_ZERO_VECTOR_H_20131110173114396
// end of file
