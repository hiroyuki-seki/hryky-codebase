/**
  @file     symbolic_computation_vector_length.h
  @brief    retrieves the length of vector.
  @author   HRYKY
  @version  $Id: symbolic_computation_vector_length.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_VECTOR_LENGTH_H_20131110182548434
#define SYMBOLIC_COMPUTATION_VECTOR_LENGTH_H_20131110182548434
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
	/// retrieves the length of vector.
	template <hryky_template_param>
	class VectorLength;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the length of vector.
 */
template <typename VectorT>
class hryky::symbolic_computation::VectorLength
{
public :

	static size_t const value = 1 +
		VectorLength<typename VectorT::type::rest_type>::value;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief terminates to increment the length of vector.
 */
template <>
class VectorLength<Terminator>
{
public :

	static size_t const value = 0;

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
#endif // SYMBOLIC_COMPUTATION_VECTOR_LENGTH_H_20131110182548434
// end of file
