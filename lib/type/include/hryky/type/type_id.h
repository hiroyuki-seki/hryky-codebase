/**
  @file         type_id.h
  @brief        instantiates the unique id of each type.
  @author       HRYKY
  @version      $Id: type_id.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef TYPE_ID_H_20121217234926659
#define TYPE_ID_H_20121217234926659
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
	/// instantiates the unique id of each type.
	template <typename ValueT>
	class Id;

} // namespace type
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief instantiates the unique id of each type.
 */
template <typename ValueT>
class hryky::type::Id
{
public :
	static id_type const value;
};
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
template <typename ValueT>
hryky::type::id_type const
hryky::type::Id<ValueT>::value = hryky::type::issue_id();
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
#endif // TYPE_ID_H_20121217234926659
// end of file
