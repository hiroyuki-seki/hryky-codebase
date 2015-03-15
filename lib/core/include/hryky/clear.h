/**
  @file         clear.h
  @brief        clears an arbitrary instance.
  @author       HRYKY
  @version      $Id: clear.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef CLEAR_H_20130209162740352
#define CLEAR_H_20130209162740352
#include "hryky/type_traits/enable_if.h"
#include "hryky/type_traits/integral_constant.h"
#include "hryky/type_traits/remove_const_reference.h"
#include "hryky/nullptr.h"
#include "hryky/stdint.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// confirms whether the class has 'clear' function.
	template <typename ValueT>
	class HasClear;

} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether the class has 'clear' function.
 */
template <typename ValueT>
class hryky::HasClear
{
	typedef uint8_t no;
	typedef uint16_t yes;

	template <typename TargetT, void (TargetT::*)()>
	struct TestClear;

	template <typename TargetT>
	static yes test(TestClear<TargetT, &TargetT::clear> *);

	template <typename TargetT>
	static no test(...);

public :
	typedef IntegralConstant<
		bool,
		sizeof(yes) == sizeof(
			test<typename RemoveConstReference<ValueT>::type>(0))
	> type;
};
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
	/// clears an arbitrary instance which has 'clear' function.
	template <typename ValueT>
	void clear(
		ValueT & value,
		typename EnableIf<HasClear<ValueT> >::type * = hryky_nullptr);

	/// clears an arbitrary instance which doesn't have 'clear' function.
	template <typename ValueT>
	void clear(
		ValueT & value,
		typename DisableIf<HasClear<ValueT> >::type * = hryky_nullptr);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief clears an arbitrary instance which has 'clear' function.
 */
template <typename ValueT>
void hryky::clear(
	ValueT & value,
	typename EnableIf<HasClear<ValueT> >::type *)
{
	value.clear();
}
/**
  @brief clears an arbitrary instance which doesn't have 'clear' function.
 */
template <typename ValueT>
void hryky::clear(
	ValueT & value,
	typename DisableIf<HasClear<ValueT> >::type *)
{
	value = ValueT();
}
#endif // CLEAR_H_20130209162740352
// end of file
