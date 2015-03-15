/**
  @file         shared_ptr.h
  @brief        smart pointer which has a reference count.
  @author       HRYKY
  @version      $Id: shared_ptr.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef SHARED_PTR_H_20120611174032403
#define SHARED_PTR_H_20120611174032403
#include "hryky/allocator/allocator_instantiate.h"
#include "hryky/allocator/allocator_mempool.h"
#include "hryky/clear.h"
#include "hryky/exclusion/exclusion_variable.h"
#include "hryky/nullptr.h"
#include "hryky/type_traits/add_const_pointer.h"
#include "hryky/type_traits/add_const_reference.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/type_traits/add_reference.h"
#include "hryky/type_traits/integral_constant.h"
#include "hryky/type_traits/remove_const.h"
#include "hryky/type_traits/remove_pointer.h"
#include "hryky/with_is_null.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, typename LockableT, typename AllocatorT
#define hryky_template_arg \
	ValueT, LockableT, AllocatorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// smart pointer which has a reference count.
	template <
		typename ValueT,
		typename LockableT = exclusion::Mutex,
		typename AllocatorT = allocator::Mempool<ValueT>
	>
	class SharedPtr;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief smart pointer which has a reference count.
 */
template <hryky_template_param>
class hryky::SharedPtr :
	public WithStreamOut<SharedPtr<hryky_template_arg> >,
	public WithSwap<SharedPtr<hryky_template_arg> >,
	public WithIsNull<SharedPtr<hryky_template_arg> >
{
public :

	typedef SharedPtr<hryky_template_arg> this_type;
	typedef AllocatorT allocator_type;
	typedef typename RemoveConst<ValueT>::type value_type;
	typedef typename AddPointer<value_type>::type pointer;
	typedef typename AddReference<value_type>::type reference;
	typedef typename AddConstPointer<value_type>::type const_pointer;
	typedef typename AddConstReference<value_type>::type const_reference;

	typedef exclusion::Variable<size_t, LockableT> counter_type;

	/// default constructor.
	SharedPtr();

	/// copy constructor.
	SharedPtr(this_type const & rhs);

	/// move constructor.
	SharedPtr(this_type && rhs);

	/// constructor with same type or derived type.
	template <
		typename RhsValueT, typename RhsLockableT, typename RhsAllocatorT>
	explicit SharedPtr(
		SharedPtr<RhsValueT, RhsLockableT, RhsAllocatorT> const & rhs);

	/// constructor with an allocator.
	explicit SharedPtr(allocator_type const & allocator);

	/// constructor with a pointer and an allocator.
	template <typename OtherAllocatorT>
	explicit SharedPtr(pointer ptr, OtherAllocatorT const & allocator);

	/// destructor.
	~SharedPtr();

	/// assigns an arbitrary type.
	template <typename RhsT>
	this_type & operator=(RhsT const & rhs);

	/// retrieves the internal pointer.
	pointer operator->() const;

	/// dereferences the internal pointer.
	reference operator*() const;

	/// confirms whether this address is equal to an other address.
	bool operator==(this_type const & rhs) const;

	/// confirms whether this address is equal to an other raw pointer.
	bool operator==(const_pointer const rhs) const;

	/// confirms whether this address is not equal to an other address.
	bool operator!=(this_type const & rhs) const;

	/// confirms whether this address is not equal to an other raw pointer.
	bool operator!=(const_pointer const rhs) const;

	/// confirms whether this address is less than an other address.
	bool operator<(this_type const & rhs) const;

	/// confirms whether this address is less than an other raw pointer.
	bool operator<(const_pointer const rhs) const;

	/// confirms whether this address is greater than an other address.
	bool operator>(this_type const & rhs) const;

	/// confirms whether this address is greater than an other raw pointer.
	bool operator>(const_pointer const rhs) const;

	/**
	  confirms whether this address is less than or equal to an other
	  address.
	 */
	bool operator<=(this_type const & rhs) const;

	/**
	  confirms whether this address is less than or equal to an other
	  raw pointer.
	 */
	bool operator<=(const_pointer const rhs) const;

	/**
	  confirms whether this address is greater than or equal to an
	  other address.
	 */
	bool operator>=(this_type const & rhs) const;

	/**
	  confirms whether this address is greater than or equal to an
	  other raw pointer.
	 */
	bool operator>=(const_pointer const rhs) const;

	/// releases the internal resources.
	void clear();

	/// confirms whether the internal pointer is null.
	bool is_null() const;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges resources.
	void swap(this_type & src);

	/// retrieves the allocator.
	AllocatorT const & allocator() const;

protected :

private :

	friend class SharedPtr;

	typedef typename counter_type::value_type counter_value_type;

	/**
	  decrements the reference counter.
	  This functor is called in the critical section.
	 */
	class Decrement
	{
	public :
		typedef this_type   instance_type;
		typedef Decrement   this_type;
		
		Decrement(instance_type & instance)
			: instance_(instance)
		{
		}

		/**
		  If no other SharedPtr shares this the reference counter,
		  the instance is released.
		 */
		counter_value_type operator()(
			counter_value_type const count) const
		{
			if (1 == count) {
				allocator::release_by(
					this->instance_.allocator_,
					this->instance_.ptr_);
				hryky::clear(this->instance_.ptr_);
			}

			return count - 1;
		}

	private :
		hryky_delete_this_copy_constructor(Decrement);
		hryky_delete_this_copy_assign_op(Decrement);
		
		instance_type & instance_;
	};

	/**
	  swap two instances.
	  This functor is called in the critical section.
	 */
	class Swap
	{
	public :
		typedef this_type   instance_type;
		typedef Swap        this_type;

		Swap(instance_type & lhs, instance_type & rhs)
			: lhs_(lhs), rhs_(rhs)
		{
		}

		counter_value_type operator()(
			counter_value_type const count) const
		{
			hryky::swap(this->lhs_.counter_, this->rhs_.counter_);
			hryky::swap(this->lhs_.ptr_, this->rhs_.ptr_);

			return count;
		}

	private :
		hryky_delete_this_copy_constructor(Swap);
		hryky_delete_this_copy_assign_op(Swap);

		instance_type & lhs_;
		instance_type & rhs_;
	};

	/// increments the reference counter.
	void add_ref() const;

	/// retrieves the refernece counter.
	counter_type * counter() const;

	/// retrieves the raw pointer.
	pointer get() const;

	allocator_type  allocator_;
	counter_type *  counter_;
	pointer         ptr_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  specializes hryky::RemovePointer.
 */
template <hryky_template_param>
class RemovePointer<SharedPtr<hryky_template_arg> >
{
public :

	typedef ValueT                                      type;
	typedef SharedPtr<hryky_template_arg>    pointer;
	typedef typename pointer::reference                 result_type;

	RemovePointer(pointer ptr) : ptr_(ptr) {}

	result_type operator()() const {
		return *this->ptr_;
	}

private :
	pointer     ptr_;

};
/**
  specializes hryky::IsPointer.
 */
template <hryky_template_param>
class IsPointer<SharedPtr<hryky_template_arg> >
{
public :
	typedef true_type type;
};
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::SharedPtr<hryky_template_arg>::SharedPtr()
	: allocator_()
	  , counter_()
	  , ptr_()
{
	return;
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::SharedPtr<hryky_template_arg>::SharedPtr(this_type const & rhs)
	: allocator_(rhs.allocator())
	  , counter_(hryky_nullptr)
	  , ptr_(hryky_nullptr)
{
	rhs.add_ref();

	this->counter_ = rhs.counter();
	this->ptr_ = rhs.get();
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::SharedPtr<hryky_template_arg>::SharedPtr(this_type && rhs)
	: hryky_move_member(allocator)
	  , hryky_move_member(counter)
	  , hryky_move_member(ptr)
{
	rhs.counter_ = hryky_nullptr;
	rhs.ptr_ = hryky_nullptr;
}
/**
  @brief constructor with same type or derived type.
 */
template <hryky_template_param>
template <typename RhsValueT, typename RhsLockableT, typename RhsAllocatorT>
hryky::SharedPtr<hryky_template_arg>::SharedPtr(
	SharedPtr<RhsValueT, RhsLockableT, RhsAllocatorT> const & rhs)
	: allocator_(rhs.allocator())
	  , counter_(hryky_nullptr)
	  , ptr_(hryky_nullptr)
{
	rhs.add_ref();

	this->counter_ = rhs.counter();
	this->ptr_ = rhs.get();
}
/**
  @brief constructor with an allocator.
 */
template <hryky_template_param>
hryky::SharedPtr<hryky_template_arg>::SharedPtr(
	allocator_type const & allocator)
	: allocator_(allocator)
	  , counter_()
	  , ptr_()
{
}
/**
  @brief constructor with a pointer and an allocator.
 */
template <hryky_template_param>
template < typename OtherAllocatorT >
hryky::SharedPtr<hryky_template_arg>::SharedPtr(
	pointer ptr, OtherAllocatorT const & allocator)
	: allocator_(allocator)
	  , counter_()
	  , ptr_(ptr)
{
	if (!hryky_is_null(ptr)) {
		typename allocator_type::template rebind<counter_type>::other
			counter_allocator(this->allocator_);
		this->counter_ =
			allocator::instantiate_by(counter_allocator, 1u);
	}
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::SharedPtr<hryky_template_arg>::~SharedPtr()
{
	this->clear();
}
/**
  @brief assigns an arbitrary type.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::SharedPtr<hryky_template_arg> &
hryky::SharedPtr<hryky_template_arg>::operator=(
	RhsT const & rhs)
{
	if (reinterpret_cast<void *>(this)
		== reinterpret_cast<void const *>(&rhs)) {
		return *this;
	}

	this_type(rhs).swap(*this);
	
	return *this;
}
/**
  @brief retrieves the internal pointer.
 */
template <hryky_template_param>
typename hryky::SharedPtr<hryky_template_arg>::pointer
hryky::SharedPtr<hryky_template_arg>::operator->() const
{
	return this->ptr_;
}
/**
  @brief dereferences the internal pointer.
 */
template <hryky_template_param>
typename hryky::SharedPtr<hryky_template_arg>::reference
hryky::SharedPtr<hryky_template_arg>::operator*() const
{
	return *this->ptr_;
}
/**
  @brief confirms whether this address is equal to an other address.
 */
template <hryky_template_param>
bool hryky::SharedPtr<hryky_template_arg>::operator==(
	this_type const & rhs) const
{
	return this->ptr_ == rhs.ptr_;
}
/**
  @brief confirms whether this address is equal to
    an other raw pointer.
 */
template <hryky_template_param>
bool hryky::SharedPtr<hryky_template_arg>::operator==(
	const_pointer const rhs) const
{
	return this->ptr_ == rhs;
}
/**
  @brief confirms whether this address is not equal to
    an other address.
 */
template <hryky_template_param>
bool hryky::SharedPtr<hryky_template_arg>::operator!=(
	this_type const & rhs) const
{
	return this->ptr_ != rhs.ptr_;
}
/**
  @brief confirms whether this address is not equal to
    an other raw pointer.
 */
template <hryky_template_param>
bool hryky::SharedPtr<hryky_template_arg>::operator!=(
	const_pointer const rhs) const
{
	return this->ptr_ != rhs;
}
/**
  @brief confirms whether this address is less than
    an other address.
 */
template <hryky_template_param>
bool hryky::SharedPtr<hryky_template_arg>::operator<(
	this_type const & rhs) const
{
	return this->ptr_ < rhs.ptr_;
}
/**
  @brief confirms whether this address is less than
    an other raw pointer.
 */
template <hryky_template_param>
bool hryky::SharedPtr<hryky_template_arg>::operator<(
	const_pointer const rhs) const
{
	return this->ptr_ < rhs;
}
/**
  @brief confirms whether this address is greater than
    an other address.
 */
template <hryky_template_param>
bool hryky::SharedPtr<hryky_template_arg>::operator>(
	this_type const & rhs) const
{
	return this->ptr_ > rhs.ptr_;
}
/**
  @brief confirms whether this address is greater than
    an other raw pointer.
 */
template <hryky_template_param>
bool hryky::SharedPtr<hryky_template_arg>::operator>(
	const_pointer const rhs) const
{
	return this->ptr_ > rhs;
}
/**
  @brief confirms whether this address is less than or equal to
    an other address.
 */
template <hryky_template_param>
bool hryky::SharedPtr<hryky_template_arg>::operator<=(
	this_type const & rhs) const
{
	return this->ptr_ <= rhs.ptr_;
}
/**
  @brief confirms whether this address is less than or equal to
    an other raw pointer.
 */
template <hryky_template_param>
bool hryky::SharedPtr<hryky_template_arg>::operator<=(
	const_pointer const rhs) const
{
	return this->ptr_ <= rhs;
}
/**
  @brief confirms whether this address is greater than or equal to
    an other address.
 */
template <hryky_template_param>
bool hryky::SharedPtr<hryky_template_arg>::operator>=(
	this_type const & rhs) const
{
	return this->ptr_ >= rhs.ptr_;
}
/**
  @brief confirms whether this address is greater than or equal to
    an other raw pointer.
 */
template <hryky_template_param>
bool hryky::SharedPtr<hryky_template_arg>::operator>=(
	const_pointer const rhs) const
{
	return this->ptr_ >= rhs;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::SharedPtr<hryky_template_arg>::clear()
{
	if (hryky_is_null(this->counter_)) {
		return;
	}
	
	if (0 == this->counter_->update(Decrement(*this))) {
		typename allocator_type::template rebind<counter_type>::other 
			counter_allocator(this->allocator_);
		allocator::release_by(counter_allocator, this->counter_);
		hryky::clear(this->counter_);
	}
}
/**
  @brief confirms whether the internal pointer is null.
 */
template <hryky_template_param>
bool hryky::SharedPtr<hryky_template_arg>::is_null() const
{
	return hryky_nullptr == this->ptr_;
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::SharedPtr<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_pointer_member(counter);
	hryky_write_pointer_member(ptr);

	return out;
}
/**
  @brief interchanges resources.
 */
template <hryky_template_param>
void hryky::SharedPtr<hryky_template_arg>::swap(this_type & src)
{
	if (this->counter_ == src.counter_) {
		return;
	}

	if (!hryky_is_null(this->counter_)) {
		this->counter_->update(Swap(*this, src));
	}
	else if (!hryky_is_null(src.counter_)) {
		src.counter_->update(Swap(*this, src));
	}
}
/**
  @brief increments the reference counter.
 */
template <hryky_template_param>
void hryky::SharedPtr<hryky_template_arg>::add_ref() const
{
	if (hryky_is_null(this->counter_)) {
		return;
	}

	++(*this->counter_);
}
/**
  @brief retrieves the refernece counter.
 */
template <hryky_template_param>
typename hryky::SharedPtr<hryky_template_arg>::counter_type * 
hryky::SharedPtr<hryky_template_arg>::counter() const
{
	return this->counter_;
}
/**
  @brief retrieves the raw pointer.
 */
template <hryky_template_param>
typename hryky::SharedPtr<hryky_template_arg>::pointer 
hryky::SharedPtr<hryky_template_arg>::get() const
{
	return this->ptr_;
}
/**
  @brief retrieves the allocator.
 */
template <hryky_template_param>
AllocatorT const &
hryky::SharedPtr<hryky_template_arg>::allocator() const
{
	return this->allocator_;
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
	/// confirms whether a raw address is equal to an address of shared pointer.
	template <typename LhsT, typename RhsT, typename LockableT, typename AllocatorT>
	bool operator==(
		LhsT * const lhs, SharedPtr<RhsT, LockableT, AllocatorT> const & rhs);

	/// confirms whether a raw address is not equal to an address of shared pointer.
	template <typename LhsT, typename RhsT, typename LockableT, typename AllocatorT>
	bool operator!=(
		LhsT * const lhs, SharedPtr<RhsT, LockableT, AllocatorT> const & rhs);

	/// confirms whether a raw address is less than an address of shared pointer.
	template <typename LhsT, typename RhsT, typename LockableT, typename AllocatorT>
	bool operator<(
		LhsT * const lhs, SharedPtr<RhsT, LockableT, AllocatorT> const & rhs);

	/// confirms whether a raw address is greater than an address of shared pointer.
	template <typename LhsT, typename RhsT, typename LockableT, typename AllocatorT>
	bool operator>(
		LhsT * const lhs, SharedPtr<RhsT, LockableT, AllocatorT> const & rhs);

	/// confirms whether a raw address is less than or equal to an address of shared pointer.
	template <typename LhsT, typename RhsT, typename LockableT, typename AllocatorT>
	bool operator<=(
		LhsT * const lhs, SharedPtr<RhsT, LockableT, AllocatorT> const & rhs);

	/// confirms whether a raw address is greater than or equal to an address of shared pointer.
	template <typename LhsT, typename RhsT, typename LockableT, typename AllocatorT>
	bool operator>=(
		LhsT * const lhs, SharedPtr<RhsT, LockableT, AllocatorT> const & rhs);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief confirms whether a raw address is equal to an address of shared pointer.
 */
template <typename LhsT, typename RhsT, typename LockableT, typename AllocatorT>
bool hryky::operator==(
	LhsT * const lhs, SharedPtr<RhsT, LockableT, AllocatorT> const & rhs)
{
	return lhs == rhs.get();
}
/**
  @brief confirms whether a raw address is not equal to an address of shared pointer.
 */
template <typename LhsT, typename RhsT, typename LockableT, typename AllocatorT>
bool hryky::operator!=(
	LhsT * const lhs, SharedPtr<RhsT, LockableT, AllocatorT> const & rhs)
{
	return lhs != rhs.get();
}
/**
  @brief confirms whether a raw address is less than an address of shared pointer.
 */
template <typename LhsT, typename RhsT, typename LockableT, typename AllocatorT>
bool hryky::operator<(
	LhsT * const lhs, SharedPtr<RhsT, LockableT, AllocatorT> const & rhs)
{
	return lhs < rhs.get();
}
/**
  @brief confirms whether a raw address is greater than an address of shared pointer.
 */
template <typename LhsT, typename RhsT, typename LockableT, typename AllocatorT>
bool hryky::operator>(
	LhsT * const lhs, SharedPtr<RhsT, LockableT, AllocatorT> const & rhs)
{
	return lhs > rhs.get();
}
/**
  @brief confirms whether a raw address is less than or equal to an address of shared pointer.
 */
template <typename LhsT, typename RhsT, typename LockableT, typename AllocatorT>
bool hryky::operator<=(
	LhsT * const lhs, SharedPtr<RhsT, LockableT, AllocatorT> const & rhs)
{
	return lhs <= rhs.get();
}
/**
  @brief confirms whether a raw address is greater than or equal to an address of shared pointer.
 */
template <typename LhsT, typename RhsT, typename LockableT, typename AllocatorT>
bool hryky::operator>=(
	LhsT * const lhs, SharedPtr<RhsT, LockableT, AllocatorT> const & rhs)
{
	return lhs >= rhs.get();
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SHARED_PTR_H_20120611174032403
// end of file
