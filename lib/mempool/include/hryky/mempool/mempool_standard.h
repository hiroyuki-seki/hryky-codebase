/**
  @file         mempool_standard.h
  @brief        allocates memory by ::std::malloc and deallocates it by ::std::free.
  @author       HRYKY
  @version      $Id: mempool_standard.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef POOL_STANDARD_H_20120417224749616
#define POOL_STANDARD_H_20120417224749616
#include "hryky/definition.h"
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
	/// allocates memory by ::std::malloc and deallocates it by ::std::free.
	class Standard;
	
} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief allocates memory by ::std::malloc and deallocates it by ::std::free.
 */
class hryky::mempool::Standard
{
public :

	typedef Standard this_type;

	/// default constructor.
	Standard();

	/// allocates memory.
	void * allocate(size_t size);

	/// deallocates the allocated memory.
	bool deallocate(void * ptr);

	/// retrieves the maximum size of allocation can be successful.
	size_t allocatable_size() const;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

	hryky_delete_this_copy_constructor(Standard);
	hryky_delete_this_copy_assign_op(Standard);

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
hryky::mempool::Standard::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
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
#endif // POOL_STANDARD_H_20120417224749616
// end of file
