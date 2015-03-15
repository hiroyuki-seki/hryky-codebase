/**
  @file     tmp_binary_logarithm.h
  @brief    retrieves a binary logarithm as an integral value.
  @author   HRYKY
  @version  $Id: tmp_binary_logarithm.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef TMP_BINARY_LOGARITHM_H_20140626164756366
#define TMP_BINARY_LOGARITHM_H_20140626164756366
#include "hryky/type_traits/integral_constant.h"
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
namespace tmp
{
	/// retrieves a binary logarithm as an integral value.
	template <typename ValueT>
	class BinaryLogarithm;

	/// retrieves a binary logarithm as an integral value from constant value.
	template <int Value>
	class BinaryLogarithmC;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves a binary logarithm as an integral value.
 */
template <hryky_template_param>
class hryky::tmp::BinaryLogarithm
{
	typedef BinaryLogarithmC<ValueT::type::value> impl;
public :
	typedef typename impl::type type;
	static typename type::value_type const value = type::value;
};
/**
  @brief retrieves a binary logarithm as an integral value from constant value.
 */
template <int Value>
class hryky::tmp::BinaryLogarithmC
{
	static_assert(0 != Value, "Value has to be more than zero.");
public :
	typedef IntegralConstant<
		int, BinaryLogarithmC<(Value >> 1)>::value + 1> type;
	static typename type::value_type const value = type::value;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  @brief retrieves a binary logarithm of 1.
 */
template <>
class BinaryLogarithmC<1>
{
public :
	typedef IntegralConstant<int, 0> type;
	static type::value_type const value = type::value;
};
} // namespace tmp
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
namespace tmp
{
} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // TMP_BINARY_LOGARITHM_H_20140626164756366
// end of file
