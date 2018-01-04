/**
  @file     rtiow_has_verify.h
  @brief    confirms whether a class has the member function 'bool verify(A1T) const'.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_HAS_VERIFY_H_20160717115315161
#define RTIOW_HAS_VERIFY_H_20160717115315161
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ClsT, typename A1T
#define hryky_template_arg \
	ClsT, A1T
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
	/// confirms whether a class has the member function 'bool verify(A1T) const'.
	template <hryky_template_param>
	class HasVerify;

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether a class has the member function 'bool verify(A1T) const'.
 */
template <typename ClsT, typename A1T>
class hryky::rtiow::HasVerify
{
	template <typename TestedT, bool (TestedT::*)(A1T) const>
		struct Test;
	
	template <typename TestedT>
	static short test(Test<TestedT, &TestedT::verify> *);
	
	template <typename TestedT>
	static char test(...);
public :
	typedef IntegralConstant<bool, sizeof(short) == sizeof(test<ClsT>(0))>
		type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
} // namespace rtiow
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
namespace rtiow
{
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RTIOW_HAS_VERIFY_H_20160717115315161
// end of file
