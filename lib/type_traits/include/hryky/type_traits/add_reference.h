/**
  @file         add_reference.h
  @brief        retrieves the traits as reference from any type.
  @author       HRYKY
  @version      $Id: add_reference.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
  @addtogroup   generic_programming
  @{
 */
#ifndef TYPE_ADD_REFERENCE_H_20120226152634310
#define TYPE_ADD_REFERENCE_H_20120226152634310
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the traits as reference from any type.
	template < typename ValueT >
	class AddReference;
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the traits as reference from any type.
 */
template < typename ValueT >
class hryky::AddReference
{
public :

	/// represents the reference type of ValueT.
	typedef ValueT &       type;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @internal
  @brief        retrieves the traits as reference from any type.
  @note
  - specializes AddReference for traditional reference
  @endinternal
 */
template < typename ValueT >
class AddReference<ValueT &>
{
public :
	typedef ValueT &       type;

};
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
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // TYPE_ADD_REFERENCE_H_20120226152634310
/// @}
// end of file
