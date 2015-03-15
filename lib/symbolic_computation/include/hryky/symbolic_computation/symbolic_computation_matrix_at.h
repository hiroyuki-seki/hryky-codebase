/**
  @file     symbolic_computation_matrix_at.h
  @brief    retrives the element at the specified row and column.
  @author   HRYKY
  @version  $Id: symbolic_computation_matrix_at.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_MATRIX_AT_H_20131112224736616
#define SYMBOLIC_COMPUTATION_MATRIX_AT_H_20131112224736616
#include "hryky/symbolic_computation/symbolic_computation_vector_at.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename MatrixT, size_t Row, size_t Column
#define hryky_template_arg \
	MatrixT, Row, Column
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// retrives the element at the specified row and column.
	template <hryky_template_param>
	class MatrixAt;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrives the element at the specified row and column.
 */
template <typename MatrixT, size_t Row, size_t Column>
class hryky::symbolic_computation::MatrixAt
{
private :
	typedef typename MatrixT::type target;
public :
	typedef VectorAt<typename VectorAt<target, Column>::type, Row>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
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
#endif // SYMBOLIC_COMPUTATION_MATRIX_AT_H_20131112224736616
// end of file
