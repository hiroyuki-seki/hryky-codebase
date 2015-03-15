/**
  @file         scale_lower_of.h
  @brief        retrieves the lower type from two scales.
  @author       HRYKY
  @version      $Id: scale_lower_of.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SCALE_LOWER_OF_H_20130101173449399
#define SCALE_LOWER_OF_H_20130101173449399
#include "hryky/scale/scale_is_lower.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace scale
{
	/// retrieves the lower type from two scales.
	template <typename LhsT, typename RhsT, bool IsLower>
	class LowerOf;

} // namespace scale
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the lower type from two scales.
 */
template <
	typename LhsT,
	typename RhsT,
	bool IsLower = scale::IsLowerEqual<typename LhsT::higher_type, RhsT>::value >
class hryky::scale::LowerOf
{
public :

	typedef RhsT type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace scale
{
/**
  @brief specializes LowerOf of which LHS is on the lower scale.
 */
template <typename LhsT, typename RhsT>
class LowerOf<LhsT, RhsT, true>
{
public :

	typedef LhsT type;
};
} // namespace scale
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
namespace scale
{
} // namespace scale
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SCALE_LOWER_OF_H_20130101173449399
// end of file
