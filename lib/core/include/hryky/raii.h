/**
  @file         raii.h
  @brief        collection of the module relevant to RAII.
  @author       HRYKY
  @version      $Id: raii.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef RAII_H_20130105172753394
#define RAII_H_20130105172753394
#include "hryky/nullptr.h"
#include "hryky/raii/auto_assign.h"
#include "hryky/raii/auto_call.h"
#include "hryky/raii/auto_decrement.h"
#include "hryky/raii/autofunc.h"
#include "hryky/raii/automemfunc.h"
#include "hryky/raii/scoped_increment.h"
#include "hryky/std/std_cstdlib.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/**
	  @brief deallocates a pointer when the current scope exits.
	 */
	class AutoFree;

	/// delete an instance when the current scope exits.
	template < typename InstanceT >
	class AutoDelete;
	
	/**
	  @brief    releases a resource when the current scope exits.
	  @param    ResourceT is the type of released resouce.
	 */
	template < class ResourceT >
	struct AutoRelease;

// utilities for using RAII.
namespace raii
{
} // namespace raii
} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
/**
  @brief deallocate a pointer when the current scope exits.
 */
class hryky::AutoFree : WithoutCopy
{
public :
	typedef AutoFree this_type;
	
	/**
	  @brief    constructor with a deallocated pointer.
	  @param    ptr is the pointer of the instance to be freed.
	 */
	AutoFree(void * ptr)
		: ptr_(ptr)
	{
	}

	/// destructor
	~AutoFree()
	{
		if (!hryky_is_null(this->ptr_)) {
			::std::free(this->ptr_);
		}
	}

	/**
	  @brief cancels the deallocation.
	 */
	void disable()
	{
		this->ptr_ = hryky_nullptr;
	}

private :
	hryky_delete_this_copy_constructor(AutoFree);
	hryky_delete_this_copy_assign_op(AutoFree);
	
	void * ptr_;
};
/**
  @brief delete an instance when the current scope exits.

  - The method of deleting is 'delete' operator.
 */
template < typename InstanceT >
class hryky::AutoDelete : WithoutCopy
{
public :
	typedef WithoutCopy base_type;
	typedef AutoDelete  this_type;

	/**
	  @brief    constructor with a deleted instance.
	  @param    instance is the pointer of the instance to be deleted.
	 */
	AutoDelete(InstanceT * const instance)
		: instance_(instance)
	{
	}

	/// destructor
	~AutoDelete()
	{
		if (!hryky_is_null(this->instance_))
		{
			delete this->instance_;
		}
	}

	/// cancels the deletion.
	void disable()
	{
		this->instance_ = hryky_nullptr;
	}

private :
	InstanceT * instance_;

};
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace raii
{
} // namespace raii
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // RAII_H_20130105172753394
// end of file
