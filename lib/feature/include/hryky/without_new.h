/**
  @file     without_new.h
  @brief    prevents a user from using operator new.
  @author   HRYKY
  @version  $Id: without_new.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef WITHOUT_NEW_H_20140310082306016
#define WITHOUT_NEW_H_20140310082306016
#include "hryky/definition.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// prevents a user from using operator new.
	class WithoutNew;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief prevents a user from using operator new.
 */
class hryky::WithoutNew
{
protected :
	/// default constructor.
	WithoutNew();

	/// destructor.
	~WithoutNew();

private :
	typedef WithoutNew this_type;
	
	hryky_delete_this_copy_constructor(WithoutNew);
	hryky_delete_this_copy_assign_op(WithoutNew);
	
	static void * operator new(::std::size_t);
	static void * operator new[](::std::size_t);
	static void operator delete(void *);
	static void operator delete[](void *);
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
/**
  @brief default constructor.
 */
inline
hryky::WithoutNew::WithoutNew()
{
}
/**
  @brief destructor.
 */
inline
hryky::WithoutNew::~WithoutNew()
{
}
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
#endif // WITHOUT_NEW_H_20140310082306016
// end of file
