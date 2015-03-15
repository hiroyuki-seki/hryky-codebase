/**
  @file     tmp_same.h
  @brief    confirms whether both actual types are same .
  @author   HRYKY
  @version  $Id: tmp_same.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef TMP_SAME_H_20131221152557309
#define TMP_SAME_H_20131221152557309
#include "hryky/type_traits/is_same.h"
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename LhsT, typename RhsT
#define hryky_template_arg \
	LhsT, RhsT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// confirms whether both actual types are same .
	template <hryky_template_param>
	class Same;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether both actual types are same .
 */
template <hryky_template_param>
class hryky::tmp::Same
{
public :
	typedef typename IntegralConstantOf<hryky::IsSame<
		typename LhsT::type,
		typename RhsT::type
	> >::type type;
	static bool const value = type::value;
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
#endif // TMP_SAME_H_20131221152557309
// end of file
