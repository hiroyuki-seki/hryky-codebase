/**
  @file         swap.h
  @brief        interchanges the values of two instances.
  @author       HRYKY
  @version      $Id: swap.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef SWAP_H_20130105173839401
#define SWAP_H_20130105173839401
#include "hryky/type_traits/enable_if.h"
#include "hryky/type_traits/is_arithmetic.h"
#include "hryky/type_traits/is_enum.h"
#include "hryky/type_traits/is_size.h"
#include "hryky/tmp/tmp_or.h"
#include "hryky/nullptr.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_swap_member(name) \
	hryky::swap(this->##name##_, src.##name##_);
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// confirms whether the type has swap() function.
	template <typename ValueT>
	class HasSwap;

} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
/**
  @brief confirms whether the type has swap() function.
 */
template <typename ValueT>
class hryky::HasSwap
{
	template <typename TargetT, void (TargetT::*)(TargetT &)>
	struct Test;

	template <typename TargetT>
	static short test(Test<TargetT, &TargetT::swap> *);

	template <typename>
	static char test(...);
public :
	typedef IntegralConstant<
		bool, sizeof(short) == sizeof(test<ValueT>(0))> type;
	static typename type::value_type const value = type::value;
};
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
	/**
	  interchanges instances with swap() function.
	 */
	template <typename ValueT>
	void swap(
		ValueT & lhs,
		ValueT & rhs,
		typename DisableIf<HasSwap<ValueT> >::type * = hryky_nullptr)
	{
		::std::swap(lhs, rhs);
	}

#if 0
	/**
	  interchanges standard types.
	 */
	template <typename ValueT>
	void swap(
		ValueT & lhs,
		ValueT & rhs,
		typename EnableIf<tmp::Or<
			tmp::Or<
				IsArithmetic<ValueT>,
				IsEnum<ValueT>
			>,
			IsSize<ValueT>
		> >::type * = hryky_nullptr)
	{
		::std::swap(lhs, rhs);
	}
#endif

	
	/// interchanges pointers.
	template <typename ValueT>
	void swap(ValueT * & lhs, ValueT * & rhs);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief interchanges pointers.
 */
template <typename ValueT>
void hryky::swap(ValueT * & lhs, ValueT * & rhs)
{
	::std::swap(lhs, rhs);
}
#endif // SWAP_H_20130105173839401
// end of file
