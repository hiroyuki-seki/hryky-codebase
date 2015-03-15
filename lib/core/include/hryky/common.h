/**
  @file         common.h
  @brief        common definition.
  @author       HRYKY
  @version      $Id: common.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef COMMON_H_20111021154357322
#define COMMON_H_20111021154357322
#include "hryky/nullptr.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// function declaration
//------------------------------------------------------------------------------
namespace hryky
{
	/**
	  @brief    release the instance that has release() method.
	  @param    ptr is the instance
	 */
	template < typename T >
	void release(T * & ptr);

} // namespace hryky
//------------------------------------------------------------------------------
// function definitions
//------------------------------------------------------------------------------
//--------------------------------
// address management
//--------------------------------
/**
  @brief    release the instance that has release() method.
  @param    ptr is the instance

  - If ptr is null-pointer, this function does nothing.
 */
template < typename T >
void hryky::release(T * & ptr)
{
	if (hryky_is_null(ptr)) {
		return;
	}
	
	ptr->release();
	ptr = hryky_nullptr;
}
#endif // COMMON_H_20111021154357322
// end of file
