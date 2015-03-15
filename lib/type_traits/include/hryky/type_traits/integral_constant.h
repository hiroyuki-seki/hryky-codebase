/**
  @file     integral_constant.h
  @brief    retains a constant value.
  @author   HRYKY
  @version  $Id: integral_constant.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef INTEGRAL_CONSTANT_H_20140527062419933
#define INTEGRAL_CONSTANT_H_20140527062419933
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, ValueT Value
#define hryky_template_arg \
	ValueT, Value
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retains a constant value.
	template <hryky_template_param>
	class IntegralConstant;

	/// extracts the constant value from class.
	template <typename ValueT>
	class IntegralConstantOf;

	typedef IntegralConstant<bool, true> true_type;
	typedef IntegralConstant<bool, false> false_type;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief extracts the constant value from class.
 */
template <typename ValueT>
class hryky::IntegralConstantOf
{
public :
	typedef IntegralConstant<
		typename ValueT::type::value_type,
		ValueT::type::value
	> type;
};
/**
  @brief retains a constant value.
 */
template <hryky_template_param>
class hryky::IntegralConstant
{
public :
	typedef IntegralConstant<ValueT, Value> type;
	typedef ValueT                          value_type;
	
	static ValueT const value = Value;
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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // INTEGRAL_CONSTANT_H_20140527062419933
// end of file
