/**
  @file     tmp_is_zero.h
  @brief    confirms whether the value is zero.
  @author   HRYKY
  @version  $Id: tmp_is_zero.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_IS_ZERO_H_20140713142500267
#define TMP_IS_ZERO_H_20140713142500267
#include "hryky/type_traits/integral_constant.h"
#include "hryky/tmp/tmp_equal.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TermT
#define hryky_template_arg \
	TermT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// confirms whether the value is zero.
	template <typename TermT>
	class IsZero;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether the value is zero.
 */
template <hryky_template_param>
class hryky::tmp::IsZero
{
public :
	typedef typename Equal<
		TermT,
		IntegralConstant<typename TermT::type::value_type, 0>
	>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
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
#endif // TMP_IS_ZERO_H_20140713142500267
// end of file
