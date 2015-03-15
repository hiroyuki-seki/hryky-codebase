/**
  @file     power.h
  @brief    exponentiates a value.
  @author   HRYKY
  @version  $Id: power.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef POWER_H_20131004232704643
#define POWER_H_20131004232704643
#include "hryky/std/std_cmath.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
	/// exponentiates a value with an integral exponent.
	template <typename ValueT>
	ValueT pow(ValueT src, size_t const exp);

	/// exponentiates a value with an arbitrary exponent.
	template <typename ValueT, typename ExponentT>
	auto pow(ValueT src, ExponentT exp) -> decltype(::std::pow(src, exp));

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief exponentiates a value with an integral exponent.
 */
template <typename ValueT>
ValueT hryky::pow(ValueT src, size_t const exp)
{
	return 0u == exp ? 1u : src * pow(src, exp - 1u);
}
/**
  @brief exponentiates a value with an arbitrary exponent.
 */
template <typename ValueT, typename ExponentT>
auto hryky::pow(ValueT src, ExponentT exp) -> decltype(::std::pow(src, exp))
{
	return ::std::pow(src, exp);
}
#endif // POWER_H_20131004232704643
// end of file
