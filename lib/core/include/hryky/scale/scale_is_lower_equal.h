/**
  @file         scale_is_lower_equal.h
  @brief        confirms whether LHS is on the scale lower than or equal to the one of RHS.
  @author       HRYKY
  @version      $Id: scale_is_lower_equal.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SCALE_IS_LOWER_EQUAL_H_20130101114526156
#define SCALE_IS_LOWER_EQUAL_H_20130101114526156
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
	/// confirms whether LHS is on the scale lower than or equal to the one of RHS.
	template <typename LhsT, typename RhsT>
	class IsLowerEqual;

} // namespace scale
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether LHS is on the scale lower than or equal to the one of RHS.
 */
template <typename LhsT, typename RhsT>
class hryky::scale::IsLowerEqual
{
public :

	static bool const value = typename IsSame<LhsT, RhsT>::value
		|| typename IsLowerEqual<typename LhsT::higher_type, RhsT>::value;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace scale
{
/**
  @brief specializes when the LHS has no more higher type.
 */
template <typename RhsT>
class IsLowerEqual<hryky::Null, RhsT>
{
public :

	static bool const value = false;
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
#endif // SCALE_IS_LOWER_EQUAL_H_20130101114526156
// end of file
