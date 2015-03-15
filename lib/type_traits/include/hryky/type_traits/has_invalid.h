/**
  @file     has_invalid.h
  @brief    confirms whether a type has the member function 'invalid'.
  @author   HRYKY
  @version  $Id: has_invalid.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef HAS_INVALID_H_20140626093527066
#define HAS_INVALID_H_20140626093527066
#include "hryky/type_traits/integral_constant.h"
#include "hryky/type_traits/enable_if.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT
#define hryky_template_arg \
	ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// confirms whether a type has the member function 'invalid'.
	template <typename ValueT>
	class HasInvalid;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether a type has the member function 'invalid'.
 */
template <hryky_template_param>
class hryky::HasInvalid
{
	template <
		typename TargetT,
		bool (TargetT::*Invalid)() const = &TargetT::invalid
	>
	struct Test;
	
	template <typename TargetT>
	static short test(Test<TargetT> *);

	template <typename>
	static char test(...);
public :
	typedef IntegralConstant<
		bool,
		(sizeof(short) == (sizeof(test<ValueT>(0))))
	> type;

	static typename type::value_type const value = type::value;
};
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
	/// confirms whether the value is invalid.
	template <typename ValueT>
	bool invaild(
		ValueT const & src,
		typename EnableIf<HasInvalid<ValueT> >::type * = hryky_nullptr);

	/// confirms whether the value is invalid.
	template <typename ValueT>
	bool invaild(
		ValueT const & src,
		typename DisableIf<HasInvalid<ValueT> >::type * = hryky_nullptr);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief confirms whether the value is invalid.
 */
template <typename ValueT>
bool hryky::invaild(
	ValueT const & src,
	typename EnableIf<HasInvalid<ValueT> >::type *)
{
	return src.is_null();
}
/**
  @brief confirms whether the value is invalid.
 */
template <typename ValueT>
bool hryky::invaild(
	ValueT const & src,
	typename DisableIf<HasInvalid<ValueT> >::type *)
{
	return false;
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // HAS_INVALID_H_20140626093527066
// end of file
