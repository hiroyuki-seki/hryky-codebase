/**
  @file     exponential.h
  @brief    exponentiates the Napier's Constant.
  @author   HRYKY
  @version  $Id: exponential.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef EXPONENTIAL_H_20131020173433398
#define EXPONENTIAL_H_20131020173433398
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
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
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
	/// calculates the power of the Napier's Constant.
	template <typename ValueT>
	auto exp(ValueT exponent) -> decltype(::std::exp(exponent));

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief calculates the power of the Napier's Constant.
 */
template <typename ValueT>
auto hryky::exp(ValueT exponent) -> decltype(::std::exp(exponent))
{
	return ::std::exp(exponent);
}
#endif // EXPONENTIAL_H_20131020173433398
// end of file
