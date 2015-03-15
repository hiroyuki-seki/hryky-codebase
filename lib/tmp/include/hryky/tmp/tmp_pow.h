/**
  @file     tmp_pow.h
  @brief    calculates exponentation.
  @author   HRYKY
  @version  $Id: tmp_pow.h 355 2014-06-22 08:47:38Z hryky.private@gmail.com $
 */
#ifndef TMP_POW_H_20140621161303342
#define TMP_POW_H_20140621161303342
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename BaseT, typename ExponentT
#define hryky_template_arg \
	BaseT, ExponentT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// calculates exponentation.
	template <typename BaseT, typename ExponentT>
	class Pow;

	/// calculates exponentation from integral values.
	template <int Base, size_t Exponent>
	class PowC;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief calculates exponentation.
 */
template <hryky_template_param>
class hryky::tmp::Pow
{
	typedef PowC<BaseT::type::value, ExponentT::type::value> impl;
public :
	typedef typename impl::type type;

	static typename type::value_type const value = type::value;
};
/**
  @brief calculates exponentation from integral values.
 */
template <int Base, size_t Exponent>
class hryky::tmp::PowC
{
public :
	typedef IntegralConstant<
		int, (Base * PowC<Base, Exponent - 1>::value)>
			type;

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
  The 0th power is one.
 */
template <int Base>
class PowC<Base, 0>
{
public :
	typedef IntegralConstant<int, 1> type;

	static typename type::value_type const value = type::value;
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
#endif // TMP_POW_H_20140621161303342
// end of file
