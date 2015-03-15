/**
  @file     symbolic_computation_evalable.h
  @brief    appends the feature to evaluate an operation.
  @author   HRYKY
  @version  $Id: symbolic_computation_evalable.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_EVALABLE_H_20131010180006416
#define SYMBOLIC_COMPUTATION_EVALABLE_H_20131010180006416
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename DerivedT, typename EvalT
#define hryky_template_arg \
	DerivedT, EvalT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// appends the feature to evaluate an operation.
	template <hryky_template_param>
	class Evalable;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief appends the feature to evaluate an operation.
 */
template <typename DerivedT, typename EvalT>
class hryky::symbolic_computation::Evalable
{
public :
	typedef EvalT eval_type;
	
	template <typename ParametersT>
	static eval_type eval(
		ParametersT const & parameters)
	{
		return DerivedT::type::eval(parameters);
	}
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
#endif // SYMBOLIC_COMPUTATION_EVALABLE_H_20131010180006416
// end of file
