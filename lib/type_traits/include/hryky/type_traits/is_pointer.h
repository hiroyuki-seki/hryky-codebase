/**
  @file         is_pointer.h
  @brief        confirms whether the type can behave as pointer.
  @author       HRYKY
  @version      $Id: is_pointer.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef IS_POINTER_H_20130325222822603
#define IS_POINTER_H_20130325222822603
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// confirms whether the type can behave as pointer.
	template <typename ValueT>
	class IsPointer;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether the type can behave as pointer.
 */
template <typename ValueT>
class hryky::IsPointer
{
public :
	typedef false_type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief specializes a built-in pointer.
 */
template <typename ValueT>
class IsPointer<ValueT *>
{
public :
	typedef true_type type;
};
/**
  @brief specializes a built-in pointer.
 */
template <typename ValueT>
class IsPointer<ValueT * const>
{
public :
	typedef true_type type;
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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // IS_POINTER_H_20130325222822603
// end of file
