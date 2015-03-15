/**
  @file     inner_product.h
  @brief    calculates an inner product.
  @author   HRYKY
  @version  $Id: inner_product.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef INNER_PRODUCT_H_20131109005333703
#define INNER_PRODUCT_H_20131109005333703
#include "hryky/type_traits/enable_if.h"
#include "hryky/type_traits/is_arithmetic.h"
#include "hryky/conjugate.h"
#include "hryky/nullptr.h"
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
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
	/// calcuates an inner product between built-in types.
	template <typename ValueT>
	ValueT inner_product(
		ValueT const lhs,
		ValueT const rhs,
		typename EnableIf<IsArithmetic<ValueT> >::type * const
		= hryky_nullptr);

	/// calculates an inner product as Hermitian form.
	template <typename LhsT, typename ValueT>
	auto inner_product(
		LhsT const & lhs, ::std::complex<ValueT> const & rhs)
		-> decltype(lhs * rhs);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief calcuates an inner product between built-in types.
 */
template <typename ValueT>
ValueT hryky::inner_product(
	ValueT const lhs,
	ValueT const rhs,
	typename EnableIf<IsArithmetic<ValueT> >::type * const)
{
	return lhs * rhs;
}
/**
  @brief calculates an inner product as Hermitian form.
 */
template <typename LhsT, typename ValueT>
auto hryky::inner_product(
	LhsT const & lhs, ::std::complex<ValueT> const & rhs) -> decltype(lhs * rhs)
{
	return lhs * hryky::conj(rhs);
}
#endif // INNER_PRODUCT_H_20131109005333703
// end of file
