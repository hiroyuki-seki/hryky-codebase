/**
  @file         mempool_base.h
  @brief        interface of dynamic memory allocation.
  @author       HRYKY
  @version      $Id: mempool_base.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef POOL_BASE_H_20120311185039451
#define POOL_BASE_H_20120311185039451
#include "hryky/pragma.h"
#include "hryky/without_new.h"
#include "hryky/without_copy.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
#pragma hryky_pragma_disable_warning_virtual_destructor
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
	/// interface of dynamic memory allocation.
	class Base;

} // namespace mempool
	typedef mempool::Base * mempool_type;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief interface of dynamic memory allocation.
 */
class hryky::mempool::Base :
	private WithoutNew,
	private WithoutCopy
{
public :

	typedef Base this_type;

	/**
	  @brief    allocates memory
	  @param    size is the minimum size of allocated memory.
	  @retval   hryky_nullptr is failure.
	  @retval   !hryky_nullptr is the address of the head of
	            an allocated memory.
	  @note
	  - the data alignment depends on the inplementation of the derived class.
	 */
	void * allocate(size_t const size);

	/**
	  @brief deallocates the allocated memory.
	  @param address        is the address of the head of the allocated memory.
	  @return               success and failure.
	 */
	bool deallocate(void * const address);

	/**
	  @brief retrieves the maximum size of allocate() can be successful.
	  @return the maximim size of allocate() can be successful.
	 */
	size_t allocatable_size() const;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :
	
	/// default constructor.
	Base();

	/// move constructor.
	Base(this_type && rhs);

	/// destructor.
	~Base();

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

private :
	hryky_delete_this_copy_constructor(Base);
	hryky_delete_this_copy_assign_op(Base);

	/**
	  @brief implements the memory allocation.
	 */
	virtual void * allocate_impl(size_t const size) = 0;

	/**
	  @brief implements the memory deallocation.
	 */
	virtual bool deallocate_impl(void * const address) = 0;

	/**
	  @brief implementation of allocatable_size().
	 */
	virtual size_t allocatable_size_impl() const = 0;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::mempool::Base::write_to(StreamT & out) const
{
	return out;
}
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
namespace mempool
{
} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // POOL_BASE_H_20120311185039451
// end of file
