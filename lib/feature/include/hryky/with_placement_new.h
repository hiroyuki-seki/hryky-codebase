/**
  @file         with_placement_new.h
  @brief        enable class to use placement-new.
  @author       HRYKY
  @version      $Id: with_placement_new.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef WITH_PLACEMENT_NEW_H_20111021190856464
#define WITH_PLACEMENT_NEW_H_20111021190856464
#include "hryky/nullptr.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// enable class to use placement-new
	class WithPlacementNew;
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief enable class to use placement-new.
 */
class hryky::WithPlacementNew
{
public :
	static void * operator new(::std::size_t, void *buf) {
		return buf;
	}
	
	static void operator delete(void *, void *) {
	}

private :
	static void * operator new[](::std::size_t, void *) {
		// The placement new for array is not practical.
		return hryky_nullptr;
	}
	
	static void operator delete[](void *, void *) {
	}
};
//------------------------------------------------------------------------------
// inline functions
//------------------------------------------------------------------------------
#endif // WITH_PLACEMENT_NEW_H_20111021190856464
// end of file
