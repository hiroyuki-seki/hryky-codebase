/**
  @file     bitmask.h
  @brief    retrieves the value which all of the bits are enabled.
  @author   HRYKY
  @version  $Id: bitmask.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef BITMASK_H_20130525211119549
#define BITMASK_H_20130525211119549
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	size_t Bits, size_t Offset, typename ResultT
#define hryky_template_arg \
	ValueT, ResultT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the value which all of the bits are enabled.
	template <hryky_template_param>
	class Bitmask;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the value which all of the bits are enabled.
 */
template <
	size_t Bits,
	size_t Offset = 0u,
	typename ResultT = size_t>
class hryky::Bitmask
{
public :
	typedef IntegralConstant<
		ResultT,
		(((static_cast<ResultT>(1) << Bits) - 1) << Offset)
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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // BITMASK_H_20130525211119549
// end of file
