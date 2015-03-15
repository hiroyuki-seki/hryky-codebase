/**
  @file     symbolic_computation_variable.h
  @brief    identifies the variable.
  @author   HRYKY
  @version  $Id: symbolic_computation_variable.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_VARIABLE_H_20130930231812637
#define SYMBOLIC_COMPUTATION_VARIABLE_H_20130930231812637
#include "hryky/symbolic_computation/symbolic_computation_with_stream_out.h"
#include "hryky/symbolic_computation/symbolic_computation_evalable.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_constant_condition
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename EvalT, size_t Index, char Symbol
#define hryky_template_arg \
	EvalT, Index, Symbol
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// identifies the variable.
	template <typename EvalT, size_t Index, char Symbol = '\0'>
	class Variable;

	/// identifies the variable.
	template <hryky_template_param>
	class VariableImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief identifies the variable.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Variable :
	public WithStreamOut<Variable<hryky_template_arg> >,
	public Evalable<Variable<hryky_template_arg>, EvalT>
{
public :
	typedef typename VariableImpl<hryky_template_arg>::type type;
};
/**
  @brief implements Variable.
 */
template <hryky_template_param>
class hryky::symbolic_computation::VariableImpl :
	public hryky::WithStreamOut<VariableImpl<hryky_template_arg> >
{
public :
	typedef EvalT eval_type;
	typedef VariableImpl<hryky_template_arg> type;

	static size_t const index = Index;
	static char const symbol = Symbol;

	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters)
	{
		return parameters[Index];
	}

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief differentiates a variable with respect to the same variable.
 */
template <hryky_template_param>
class DifferentiateImpl<
	VariableImpl<hryky_template_arg>,
	VariableImpl<hryky_template_arg> >
{
public :
	typedef Integer<EvalT, 1> type;
};
/**
  @brief differentiates a variable with respect to a different variable.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<VariableImpl<hryky_template_arg>, WrtT>
{
public :
	typedef Integer<EvalT, 0> type;
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
/**
  @brief prints a variable to an outout string-stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::VariableImpl<hryky_template_arg>::write_to(
	StreamT & out) const
{
	char const symbols[] = {
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	};
	size_t const symbols_size = sizeof(symbols) / sizeof(symbols[0]);

	if ('\0' != Symbol) {
		out << Symbol;
	}
	else if (Index < symbols_size) {
		out << symbols[Index];
	}
	else {
		out << "x_" << Index;
	}
	return out;
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // SYMBOLIC_COMPUTATION_VARIABLE_H_20130930231812637
// end of file
