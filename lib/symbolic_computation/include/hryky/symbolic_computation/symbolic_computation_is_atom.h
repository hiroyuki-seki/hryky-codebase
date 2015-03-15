/**
  @file     symbolic_computation_is_atom.h
  @brief    confirms whether the term is not docomposed anymore.
  @author   HRYKY
  @version  $Id: symbolic_computation_is_atom.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_IS_ATOM_H_20131130200904506
#define SYMBOLIC_COMPUTATION_IS_ATOM_H_20131130200904506
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
	/// confirms whether the term is not docomposed anymore.
	template <hryky_template_param>
	class IsAtom;

	template <hryky_template_param>
	class IsNumeric;
	
	template <hryky_template_param>
	class IsVariable;
	

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether the term is not docomposed anymore.
 */
template <typename TermT>
class hryky::symbolic_computation::IsAtom
{
public :
	static bool const value =
		IsNumeric<TermT>::value || IsVariable<TermT>::value;
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
#endif // SYMBOLIC_COMPUTATION_IS_ATOM_H_20131130200904506
// end of file
