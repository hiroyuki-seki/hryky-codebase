/**
  @file     tmp_has_type.h
  @brief    confirms whether a ValueT has type.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef TMP_HAS_TYPE_H_20161210150726296
#define TMP_HAS_TYPE_H_20161210150726296
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
	/// confirms whether a ValueT has type.
	template <hryky_template_param>
	class HasType;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether a ValueT has type.
 */
template <typename ValueT>
class hryky::tmp::HasType
{
	template <typename TestT>
	static short test(typename TestT::type *);

	static char test(...);
public :
	typedef IntegralConstant<
		bool, sizeof(short) == sizeof(test<ValueT>(0)) > type;
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
#endif // TMP_HAS_TYPE_H_20161210150726296
// end of file
