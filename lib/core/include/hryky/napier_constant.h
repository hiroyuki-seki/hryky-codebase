/**
  @file     napier_constant.h
  @brief    Napier's Constant (also known as Euler's number).
  @author   HRYKY
  @version  $Id: napier_constant.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef NAPIER_CONSTANT_H_20131020153512316
#define NAPIER_CONSTANT_H_20131020153512316
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
	/// Napier's Constant.
	template <hryky_template_param>
	class NapierConstant;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief Napier's Constant.
 */
template <typename ValueT>
class hryky::NapierConstant
{
public :
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  The Napier's Constant by single-precision floating-point.
 */
template <>
class NapierConstant<float>
{
public :
	static float const value;
};
float const NapierConstant<float>::value = 2.7182818284f;

/**
  The Napier's Constant by double-precision floating-point.
 */
template <>
class NapierConstant<double>
{
public :
	static double const value;
};
double const NapierConstant<double>::value = 2.71828182845904523536;
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
#endif // NAPIER_CONSTANT_H_20131020153512316
// end of file
