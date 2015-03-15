/**
  @file         type_name.h
  @brief        retains the name of type.
  @author       HRYKY
  @version      $Id: type_name.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef TYPE_NAME_H_20121216181514427
#define TYPE_NAME_H_20121216181514427
#include "hryky/type/type_common.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace type
{
	/// retains the name of type.
	template <typename ValueT>
	class Name;

} // namespace type
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the name of type.
 */
template <typename ValueT>
class hryky::type::Name
{
public :
	static name_type const value;

};
template <typename ValueT>
hryky::type::name_type const
hryky::type::Name<ValueT>::value("");
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace type
{
} // namespace type
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
namespace type
{
} // namespace type
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // TYPE_NAME_H_20121216181514427
// end of file
