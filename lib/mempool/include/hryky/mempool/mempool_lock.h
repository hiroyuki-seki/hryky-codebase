/**
  @file         mempool_lock.h
  @brief        performs the exclusion control at the allocation and deallocation of mempool.
  @author       HRYKY
  @version      $Id: mempool_lock.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef POOL_LOCK_H_20120317184727449
#define POOL_LOCK_H_20120317184727449
#include "hryky/exclusion/exclusion_lock.h"
#include "hryky/exclusion/exclusion_mutex.h"
#include "hryky/retention/retention_value.h"
#include "hryky/mempool/mempool_global_registry.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename LockedT, typename LockableT, template <typename> class RetainT
#define hryky_template_arg \
	LockedT, LockableT, RetainT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
	/// performs the exclusion control at the allocation and deallocation of mempool.
	template <
		typename LockedT,
		typename LockableT = exclusion::Mutex,
		template <typename> class RetainT = retention::Value
	>
	class Lock;
} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief performs the exclusion control at the allocation and deallocation of mempool.
 */
template <hryky_template_param>
class hryky::mempool::Lock :
	public RetainT<LockedT>,
	public WithStreamOut<Lock<hryky_template_arg> >,
	private WithoutCopy
{
public :

	typedef Lock<hryky_template_arg>    this_type;
	typedef LockedT                     locked_type;
	typedef RetainT<LockedT>            retain_type;
	
	typedef typename retain_type::initializer_type  initializer_type;
	typedef typename retain_type::reference         reference;
	typedef typename retain_type::const_reference   const_reference;

	/// default constructor.
	Lock();

	/// constructor with the locked instance.
	Lock(initializer_type locked);

	/// calls the LockedT::allocate() with the exclusion control.
	void * allocate(size_t const size);

	/// calls the LockedT::deallocate() with the exclusion control.
	bool deallocate(void * const address);

	/// calls the LockedT::allocatable_size() with the exclusion control.
	size_t allocatable_size() const;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

private :

	typedef LockableT                       lockable_type;
	typedef exclusion::Lock<lockable_type>  lock_type;

	hryky_delete_this_copy_constructor(Lock);
	hryky_delete_this_copy_assign_op(Lock);

	mutable lockable_type   lockable_;
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
  @brief default constructor.
 */
template <hryky_template_param>
hryky::mempool::Lock<hryky_template_arg>::Lock()
	: retain_type()
	  , lockable_()
{
}
/**
  @brief constructor with the locked instance.
 */
template <hryky_template_param>
hryky::mempool::Lock<hryky_template_arg>::Lock(
	initializer_type locked)
	: retain_type(locked)
	  , lockable_()
{
	return;
}
/**
  @brief calls the LockedT::allocate() with the exclusion control.
 */
template <hryky_template_param>
void *
hryky::mempool::Lock<hryky_template_arg>::allocate(
	size_t const size)
{
	lock_type const lock(this->lockable_);

	return this->get()->allocate(size);
}
/**
  @brief calls the LockedT::deallocate() with the exclusion control.
 */
template <hryky_template_param>
bool
hryky::mempool::Lock<hryky_template_arg>::deallocate(
	void * const address)
{
	lock_type const lock(this->lockable_);

	return this->get()->deallocate(address);
}
/**
  @brief calls the LockedT::allocatable_size() with the exclusion control.
 */
template <hryky_template_param>
hryky::size_t
hryky::mempool::Lock<hryky_template_arg>::allocatable_size(
	) const
{
	lock_type const lock(this->lockable_);

	return this->get()->allocatable_size();
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::mempool::Lock<hryky_template_arg>::write_to(
	StreamT & out) const
{
	lock_type const lock(this->lockable_);

	return this->get()->write_to(out);
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
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // POOL_LOCK_H_20120317184727449
// end of file
