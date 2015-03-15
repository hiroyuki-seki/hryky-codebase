/**
  @file         scale_is_lower.h
  @brief        confirms whether LHS is on the lower scale than RHS.
  @author       HRYKY
  @version      $Id: scale_is_lower.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SCALE_IS_LOWER_H_20130101111540135
#define SCALE_IS_LOWER_H_20130101111540135
#include "hryky/scale/scale_is_lower_equal.h"
#include "hryky/scale/scale_has_higher.h"
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
	/// confirms whether LHS is on the lower scale than RHS.
	template <typename LhsT, typename RhsT>
	class IsLower;

} // namespace scale
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether LHS is on the lower scale than RHS.
 */
template <typename LhsT, typename RhsT>
class hryky::scale::IsLower
{
public :

	static bool const value =
		typename IsLowerEqual<typename LhsT::higher_type, RhsT>::value;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace scale
{
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
#endif // SCALE_IS_LOWER_H_20130101111540135
// end of file
