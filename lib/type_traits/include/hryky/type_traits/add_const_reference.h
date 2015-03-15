/**
  @file         add_const_reference.h
  @brief        retrieves the traits as const reference from any type.
  @author       HRYKY
  @version      $Id: add_const_reference.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
  @addtogroup   generic_programming
  @{
 */
#ifndef TYPE_ADD_CONST_REFERENCE_H_20120331181640428
#define TYPE_ADD_CONST_REFERENCE_H_20120331181640428
#include "hryky/type_traits/add_reference.h"
#include "hryky/type_traits/add_const.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the traits as const reference from any type.
	template < typename ValueT >
	class AddConstReference;
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the traits as const reference from any type.
 */
template < typename ValueT >
class hryky::AddConstReference
{
public :

	/// represents the type qualified by "const &"
	typedef typename AddReference<typename AddConst<ValueT>::type>::type type;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
}
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
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // TYPE_ADD_CONST_REFERENCE_H_20120331181640428
/// @}
// end of file
