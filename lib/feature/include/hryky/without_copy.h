/**
  @file         without_copy.h
  @brief        forbids to copy an instance.
  @author       HRYKY
  @version      $Id: without_copy.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef WITHOUT_COPY_H_20111021154734324
#define WITHOUT_COPY_H_20111021154734324
#include "hryky/definition.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// forbids to copy an instance
	class WithoutCopy;
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief forbids to copy an instance.
 */
class hryky::WithoutCopy
{
protected :

	/// default constructor
	WithoutCopy()
	{
	};

	/// destrunctor
	~WithoutCopy()
	{
	};

private :
	typedef WithoutCopy this_type;
	
	hryky_delete_this_copy_constructor(WithoutCopy);
	hryky_delete_this_copy_assign_op(WithoutCopy);
};
//------------------------------------------------------------------------------
// inline functions
//------------------------------------------------------------------------------
#endif // WITHOUT_COPY_H_20111021154734324
// end of file
