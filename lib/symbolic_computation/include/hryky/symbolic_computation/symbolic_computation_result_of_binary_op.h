/**
  @file     symbolic_computation_result_of_binary_op.h
  @brief    retrieves the result type of binary operation.
  @author   HRYKY
  @version  $Id: symbolic_computation_result_of_binary_op.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_RESULT_OF_BINARY_OP_H_20131113212702560
#define SYMBOLIC_COMPUTATION_RESULT_OF_BINARY_OP_H_20131113212702560
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename LhsT, typename RhsT, template <typename, typename> class OpT
#define hryky_template_arg \
	LhsT, RhsT, OpT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// retrieves the result type of binary operation.
	template <hryky_template_param>
	class ResultOfBinaryOp;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the result type of binary operation.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ResultOfBinaryOp
{
public :

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
#endif // SYMBOLIC_COMPUTATION_RESULT_OF_BINARY_OP_H_20131113212702560
// end of file
