/**
  @file         exclusion_lock.h
  @brief        obtains the ownership of an exclusion object during the existance of this instance.
  @author       HRYKY
  @version      $Id: exclusion_lock.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
  @addtogroup   exclusion_control
  @{
 */
#ifndef EXCLUSION_LOCK_H_20120417231208633
#define EXCLUSION_LOCK_H_20120417231208633
#include "hryky/std/std_thread.h"
#include "hryky/tmp/null.h"
#include "hryky/exclusion/exclusion_mutex.h"
#include "hryky/without_copy.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename LockableT
#define hryky_template_arg \
	LockableT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace exclusion
{
	/// obtains the ownership of an exclusion object during the existance of this instance.
	template <
		typename LockableT = Mutex
	>
	class Lock;
}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief obtains the ownership of an exclusion object during the existance of this instance.
 */
template <hryky_template_param>
class hryky::exclusion::Lock :
	private WithoutCopy
{
public :

	typedef Lock<LockableT>     this_type;
	typedef LockableT           lockable_type;

#if HRYKY_USE_BOOST_EXCLUSION
	typedef boost::unique_lock<typename lockable_type::raw_type> raw_type;
#else
	typedef ::std::unique_lock<typename lockable_type::raw_type> raw_type;
#endif

	/// instantiates with an exclusion object.
	explicit Lock(lockable_type & lockable);

	/// move constructor.
	Lock(this_type && rhs);
	
	/// destructor.
	~Lock();

	/// move assignment operator.
	hryky_move_assign_op;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the mutable raw object.
	raw_type & raw();

protected :

private :

	hryky_delete_default_constructor(Lock);
	hryky_delete_this_copy_constructor(Lock);
	hryky_delete_this_copy_assign_op(Lock);

	raw_type    raw_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace exclusion
{
/**
  @brief specializes with hryky::Null.
 */
template <>
class Lock<Null> :
	private WithoutCopy
{
public :

	typedef Lock<Null>  this_type;
	typedef Null        lockable_type;

	/// constructor with an exclusion object.
	explicit Lock(lockable_type &)
	{
	}

	/// destructor.
	~Lock()
	{
	}

protected :

private :

	hryky_delete_this_copy_constructor(Lock);
	hryky_delete_this_copy_assign_op(Lock);

};
} // namespace exclusion
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief instantiates with the lockable object.
 */
template <hryky_template_param>
hryky::exclusion::Lock<hryky_template_arg>::Lock(
	lockable_type & lockable)
	: raw_(lockable.raw())
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::exclusion::Lock<hryky_template_arg>::Lock(
	this_type && rhs)
	: hryky_move_member(raw)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::exclusion::Lock<hryky_template_arg>::~Lock()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::exclusion::Lock<hryky_template_arg>::swap(
	this_type & src)
{
	this->raw_.swap(src.raw_);
}
/**
  @brief retrieves the mutable raw object.
 */
template <hryky_template_param>
typename hryky::exclusion::Lock<hryky_template_arg>::raw_type & 
hryky::exclusion::Lock<hryky_template_arg>::raw()
{
	return this->raw_;
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
namespace exclusion
{
}
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // EXCLUSION_LOCK_H_20120417231208633
/// @}
// end of file
