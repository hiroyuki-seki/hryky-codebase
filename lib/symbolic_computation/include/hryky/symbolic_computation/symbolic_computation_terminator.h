/**
  @file     symbolic_computation_terminator.h
  @brief    The terminal of recursive definition.
  @author   HRYKY
  @version  $Id: symbolic_computation_terminator.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_TERMINATOR_H_20131130120251168
#define SYMBOLIC_COMPUTATION_TERMINATOR_H_20131130120251168
#include "hryky/tmp/null.h"
#include "hryky/symbolic_computation/symbolic_computation_dividable.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// The terminal of recursive definition.
	class Terminator;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The terminal of recursive definition.
 */
class hryky::symbolic_computation::Terminator :
	public hryky::WithStreamOut<Terminator>
{
public :
	typedef Terminator type;
	typedef hryky::Null eval_type;

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
  @brief terminates the recursion.
 */
template <typename WrtT>
class DividableImpl<Terminator, WrtT>
{
public :
	typedef Terminator type;
	static bool const value = true;
};
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief prints no representation.
 */
template <typename StreamT>
StreamT &
hryky::symbolic_computation::Terminator::write_to(
	StreamT & out) const
{
	return out;
}
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
#endif // SYMBOLIC_COMPUTATION_TERMINATOR_H_20131130120251168
// end of file
