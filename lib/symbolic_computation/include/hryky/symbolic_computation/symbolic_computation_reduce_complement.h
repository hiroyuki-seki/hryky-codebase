/**
  @file     symbolic_computation_reduce_complement.h
  @brief    reduces operation of complement.
  @author   HRYKY
  @version  $Id: symbolic_computation_reduce_complement.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_REDUCE_COMPLEMENT_H_20131116010716713
#define SYMBOLIC_COMPUTATION_REDUCE_COMPLEMENT_H_20131116010716713
#include "hryky/symbolic_computation/symbolic_computation_simplify.h"
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
	template <hryky_template_param>
	class Complement;

	template <hryky_template_param>
	class ComplementImpl;

	template <typename EvalT, int Value>
	class Integer;
	
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
//------------------------------------------------------------------------------
// reduces internal operation.
//------------------------------------------------------------------------------
/**
  @brief reduces the internal term.
 */
template <hryky_template_param>
class ReduceImpl<ComplementImpl<hryky_template_arg> >
{
private :
	typedef Reduce<TermT>       term;
	typedef Complement<term>    complement;
public :
	static bool const value =
		term::value || IsAtom<complement>::value;
	typedef typename ReduceIfC<value, complement>::type type;
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
#endif // SYMBOLIC_COMPUTATION_REDUCE_COMPLEMENT_H_20131116010716713
// end of file
