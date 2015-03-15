/**
  @file         add_const_pointer.h
  @brief        retrieves the traits as const pointer from any type.
  @author       HRYKY
  @version      $Id: add_const_pointer.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
  @addtogroup   generic_programming
  @{
 */
#ifndef TYPE_ADD_CONST_POINTER_H_20120805225113618
#define TYPE_ADD_CONST_POINTER_H_20120805225113618
#include "hryky/type_traits/add_const.h"
#include "hryky/type_traits/add_pointer.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the traits as const pointer from any type.
	template < typename ValueT >
	class AddConstPointer;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the traits as const pointer from any type.
 */
template < typename ValueT >
class hryky::AddConstPointer
{
public :

	/// represents the type qualified by "const *"
	typedef typename AddPointer<typename AddConst<ValueT>::type>::type type;

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
#endif // TYPE_ADD_CONST_POINTER_H_20120805225113618
/// @}
// end of file
