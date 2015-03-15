/**
  @file         intrusive_ptr_trait.h
  @brief        appends the ability to use the reference counter for IntrusivePtr.
  @author       HRYKY
  @version      $Id: intrusive_ptr_trait.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef INTRUSIVE_PTR_TRAIT_H_20130307122218182
#define INTRUSIVE_PTR_TRAIT_H_20130307122218182
#include "hryky/allocator/allocator_instantiate.h"
#include "hryky/allocator/allocator_mempool.h"
#include "hryky/exclusion/exclusion_variable.h"
#include "hryky/exclusion/exclusion_mutex.h"
#include "hryky/log/log_definition.h"
#include "hryky/type_traits/add_const_pointer.h"
#include "hryky/type_traits/add_const_reference.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/type_traits/add_reference.h"
#include "hryky/type_traits/remove_const.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename LockableT, typename AllocatorT
#define hryky_template_arg \
	LockableT, AllocatorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// appends the ability to use the reference counter for IntrusivePtr.
	template <
		typename LockableT = exclusion::Mutex,
		typename AllocatorT = allocator::Mempool<int>
	>
	class IntrusivePtrTrait;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief appends the ability to use the reference counter for IntrusivePtr.

   The default LockableT is Null. To append thread-safety, the appropriate type
  has to be assigned to LockableT.
 */
template <hryky_template_param>
class hryky::IntrusivePtrTrait
{
public :

	typedef IntrusivePtrTrait<hryky_template_arg>   this_type;
	typedef exclusion::Variable<size_t, LockableT>  counter_type;
	typedef AllocatorT                              allocator_type;
	
	/// default constructor.
	IntrusivePtrTrait();

	/// copy constructor.
	IntrusivePtrTrait(this_type const &);

	/// move constructor.
	IntrusivePtrTrait(this_type &&);

	/// constructor with an allocator.
	IntrusivePtrTrait(allocator_type const & allocator);

	/// destructor.
	virtual ~IntrusivePtrTrait();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// increments the reference counter.
	void add_ref();

	/// decrements the reference counter.
	void release();

	/// retrieves the allocator.
	allocator_type const & allocator() const;

protected :

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// releases the internal resources.
	void clear();

private :

	struct Decrement
	{
		Decrement()
			: value_()
		{}

		size_t operator()(size_t value) {
			this->value_ = --value;
			return value;
		}

		size_t value_;
	};

	allocator_type  allocator_;
	counter_type    counter_;

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
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::IntrusivePtrTrait<hryky_template_arg>::IntrusivePtrTrait()
	: allocator_()
	  , counter_()
{
}
/**
  @brief copy constructor.

  The reference counter is not copied.
 */
template <hryky_template_param>
hryky::IntrusivePtrTrait<hryky_template_arg>::IntrusivePtrTrait(
	this_type const & rhs)
	: hryky_copy_member(allocator)
	  , counter_()
{
}
/**
  @brief move constructor.
  
  The reference counter is not copied.
 */
template <hryky_template_param>
hryky::IntrusivePtrTrait<hryky_template_arg>::IntrusivePtrTrait(
	this_type && rhs)
	: hryky_move_member(allocator)
	  , counter_()
{
}
/**
  @brief constructor with an allocator.
 */
template <hryky_template_param>
hryky::IntrusivePtrTrait<hryky_template_arg>::IntrusivePtrTrait(
	allocator_type const & allocator)
	: allocator_(allocator)
	  , counter_()
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::IntrusivePtrTrait<hryky_template_arg>::~IntrusivePtrTrait()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::IntrusivePtrTrait<hryky_template_arg>::clear()
{
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::IntrusivePtrTrait<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(allocator);
	hryky_write_member(counter);
	return out;
}
/**
  @brief increments the reference counter.
 */
template <hryky_template_param>
void hryky::IntrusivePtrTrait<hryky_template_arg>::add_ref()
{
	++this->counter_;
}
/**
  @brief decrements the reference counter.
 */
template <hryky_template_param>
void hryky::IntrusivePtrTrait<hryky_template_arg>::release()
{
	if (0 == this->counter_) {
		hryky_log_crit(
			"The reference counter is invalid. "
			"The releasing operation is unexpected.");
		return;
	}
	
	if (0 == --this->counter_) {
		typename allocator_type::template rebind<this_type>::other
			instance_allocator(this->allocator_);
		allocator::release_by(instance_allocator, this);
	}
}
/**
  @brief retrieves the allocator.
 */
template <hryky_template_param>
typename hryky::IntrusivePtrTrait<hryky_template_arg>::allocator_type const & 
hryky::IntrusivePtrTrait<hryky_template_arg>::allocator() const
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
	/// increments the reference counter as an intrusive pointer.
	template <hryky_template_param>
	void intrusive_ptr_add_ref(
		IntrusivePtrTrait<hryky_template_arg> * ptr);

	/// decrements the reference counter as an intrusive pointer.
	template <hryky_template_param>
	void intrusive_ptr_release(
		IntrusivePtrTrait<hryky_template_arg> * ptr);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief increments the reference counter as an intrusive pointer.
 */
template <hryky_template_param>
void hryky::intrusive_ptr_add_ref(
	IntrusivePtrTrait<hryky_template_arg> * const ptr)
{
	if (hryky_is_null(ptr)) {
		return;
	}
	ptr->add_ref();
}
/**
  @brief decrements the reference counter as an intrusive pointer.
 */
template <hryky_template_param>
void hryky::intrusive_ptr_release(
	IntrusivePtrTrait<hryky_template_arg> * const ptr)
{
	if (hryky_is_null(ptr)) {
		return;
	}
	ptr->release();
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // INTRUSIVE_PTR_TRAIT_H_20130307122218182
// end of file
