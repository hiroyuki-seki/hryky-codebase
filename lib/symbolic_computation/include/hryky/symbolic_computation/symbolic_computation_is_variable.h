/**
  @file     symbolic_computation_is_variable.h
  @brief    confirms whether the term is a variable.
  @author   HRYKY
  @version  $Id: symbolic_computation_is_variable.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_IS_VARIABLE_H_20131130201144508
#define SYMBOLIC_COMPUTATION_IS_VARIABLE_H_20131130201144508
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
	template <typename EvalT, size_t Index, char Symbol>
	class VariableImpl;

	/// confirms whether the term is a variable.
	template <hryky_template_param>
	class IsVariable;

	/// implements IsVariable.
	template <hryky_template_param>
	class IsVariableImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether the term is a variable.
 */
template <typename TermT>
class hryky::symbolic_computation::IsVariable
{
public :
	static bool const value = IsVariableImpl<typename TermT::type>::value;
};
/**
  @brief implements IsVariable.
 */
template <typename TermT>
class hryky::symbolic_computation::IsVariableImpl
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
  @brief The term is variable.
 */
template <typename EvalT, size_t Index, char Symbol>
class IsVariableImpl<VariableImpl<EvalT, Index, Symbol> >
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
#endif // SYMBOLIC_COMPUTATION_IS_VARIABLE_H_20131130201144508
// end of file
