/**
  @file     tmp_add.h
  @brief    operates addition between two terms.
  @author   HRYKY
  @version  $Id: tmp_add.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_ADD_H_20131221223151605
#define TMP_ADD_H_20131221223151605
#include "hryky/tmp/tmp_eval.h"
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
	/// operates addition between two terms.
	template <hryky_template_param>
	class Add;

	/// implements Add<> for the actual types.
	template <hryky_template_param>
	class AddImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief operates addition between two terms.
 */
template <hryky_template_param>
class hryky::tmp::Add
{
public :
	typedef typename AddImpl<
		typename LhsT::type, typename RhsT::type>::type type;
};
/**
  @brief implements Add<> for the actual types.
 */
template <hryky_template_param>
class hryky::tmp::AddImpl
{
public :
	typedef IntegralConstant<
		decltype(LhsT::value + RhsT::value),
		(LhsT::value + RhsT::value)> type;
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
#endif // TMP_ADD_H_20131221223151605
// end of file
