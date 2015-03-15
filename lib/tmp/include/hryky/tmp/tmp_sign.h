/**
  @file     tmp_sign.h
  @brief    retrieves the sign of value.
  @author   HRYKY
  @version  $Id: tmp_sign.h 366 2014-07-13 09:13:34Z hryky.private@gmail.com $
 */
#ifndef TMP_SIGN_H_20140713170746380
#define TMP_SIGN_H_20140713170746380
#include "hryky/tmp/tmp_conditional.h"
#include "hryky/tmp/tmp_is_zero.h"
#include "hryky/tmp/tmp_is_negative.h"
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
	/// retrieves the sign of value.
	template <typename TermT>
	class Sign;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the sign of value.
 */
template <hryky_template_param>
class hryky::tmp::Sign
{
public :
	typedef typename Conditional<
		IsZero<TermT>,
		IntegralConstant<typename TermT::type::value_type, 0>,
		typename Conditional<
			IsNegative<TermT>,
			IntegralConstant<typename TermT::type::value_type, -1>,
			IntegralConstant<typename TermT::type::value_type, 1>
		>::type
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
#endif // TMP_SIGN_H_20140713170746380
// end of file
