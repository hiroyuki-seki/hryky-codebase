/**
  @file     symbolic_computation_sequence.h
  @brief    lines up the evaluated terms.
  @author   HRYKY
  @version  $Id: symbolic_computation_sequence.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_SEQUENCE_H_20131201151613302
#define SYMBOLIC_COMPUTATION_SEQUENCE_H_20131201151613302
#include "hryky/symbolic_computation/symbolic_computation_terminator.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename FirstT, typename RestT
#define hryky_template_arg \
	FirstT, RestT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// lines up the evaluated terms.
	template <typename FirstT, typename RestT = Terminator>
	class Sequence;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief lines up the evaluated terms.
 */
template <typename FirstT, typename RestT>
class hryky::symbolic_computation::Sequence
{
public :
	typedef Sequence<FirstT, RestT> type;
	typedef FirstT first;
	typedef RestT rest;
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
#endif // SYMBOLIC_COMPUTATION_SEQUENCE_H_20131201151613302
// end of file
