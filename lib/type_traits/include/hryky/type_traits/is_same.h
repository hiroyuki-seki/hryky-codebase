/**
  @file         is_same.h
  @brief        confirms whether two types are same.
  @author       HRYKY
  @version      $Id: is_same.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef IS_SAME_H_20130101112621143
#define IS_SAME_H_20130101112621143
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// confirms whether two types are same.
	template <typename LhsT, typename RhsT >
	class IsSame;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether two types are same.
 */
template <typename LhsT, typename RhsT >
class hryky::IsSame
{
public :
	typedef false_type type;
	static bool const value = type::value;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief specializes IsSame of which arguments are same.
 */
template <typename ValueT>
class IsSame<ValueT, ValueT>
{
public :
	typedef true_type type;
	static bool const value = type::value;
};
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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // IS_SAME_H_20130101112621143
// end of file
