/**
  @file         allocator_mempool.h
  @brief        allocator using mempool::Base.
  @author       HRYKY
  @version      $Id: allocator_mempool.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef ALLOCATOR_HEAP_H_20120225184209445
#define ALLOCATOR_HEAP_H_20120225184209445
#include "hryky/allocator/allocator_base.h"
#include "hryky/definition.h"
#include "hryky/mempool/mempool_ptr.h"
#include "hryky/mempool/mempool_base.h"
#include "hryky/nullptr.h"
#include "hryky/pragma.h"
#include "hryky/swap.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/stream/stream_definition.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT
#define hryky_template_arg \
	ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace allocator
{
	/// allocator using mempool::Base.
	template <hryky_template_param>
	class Mempool;
} // namespace allocator
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief allocator using mempool::Base.
 */
template <hryky_template_param>
class hryky::allocator::Mempool :
	public allocator::Base<ValueT>,
	public WithStreamOut<Mempool<hryky_template_arg> >,
	public WithSwap<Mempool<hryky_template_arg> >
{
public :

	typedef Mempool<hryky_template_arg> this_type;

	template <typename OtherT>
	struct rebind
	{
		typedef Mempool<OtherT> other;
	};

	/// default constructor
	Mempool();

	/// copy constructor
	Mempool(this_type const & rhs);

	/// move constructor.
	Mempool(this_type && rhs);

	/// constructor with the memory pool.
	Mempool(mempool::Ptr const & mempool);

	/// constructor with the raw pointer of memory pool.
	Mempool(mempool::Base * const mempool);

	/// constructor with an allocator for other type.
	template < typename OtherT >
	Mempool(Mempool<OtherT> const & rhs);

	/// destructor
	~Mempool();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// allocates memory by the memory pool.
	pointer allocate(size_type count, void const * = hryky_nullptr);

	/// deallocates memory by the memory pool.
	void deallocate(pointer ptr, size_type);

	/// retrieves the maximum size by which an allocation can be successful.
	size_type max_size() const;

	/// retrieves the internal representation.
	mempool_type mempool() const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

private :
	mempool::Ptr mempool_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::allocator::Mempool<hryky_template_arg>::Mempool()
	: mempool_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::allocator::Mempool<hryky_template_arg>::Mempool(this_type const & rhs)
	: hryky_copy_member(mempool)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::allocator::Mempool<hryky_template_arg>::Mempool(this_type && rhs)
	: hryky_move_member(mempool)
{
}
/**
  @brief constructor with the memory pool.
 */
template <hryky_template_param>
hryky::allocator::Mempool<hryky_template_arg>::Mempool(
	mempool::Ptr const & mempool)
	: mempool_(mempool)
{
}
/**
  @brief constructor with the raw pointer of memory pool.
 */
template <hryky_template_param>
hryky::allocator::Mempool<hryky_template_arg>::Mempool(
	mempool::Base * const mempool)
	: mempool_(mempool)
{
}
/**
  @brief constructor with an allocator for other type.
 */
template <hryky_template_param>
template < typename OtherT >
hryky::allocator::Mempool<hryky_template_arg>::Mempool(
	Mempool<OtherT> const & rhs)
	: mempool_(rhs.mempool())
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::allocator::Mempool<hryky_template_arg>::~Mempool()
{
}
/**
  @brief allocates memory by the memory pool.
 */
template <hryky_template_param>
typename hryky::allocator::Mempool<hryky_template_arg>::pointer
hryky::allocator::Mempool<hryky_template_arg>::allocate(
	size_type count, void const *)
{
	if (hryky_is_null(this->mempool_)) {
		return hryky_nullptr;
	}

	return reinterpret_cast<pointer>(
		this->mempool_->allocate(count * sizeof(ValueT)));
}
/**
  @brief deallocates memory by the memory pool.
 */
template <hryky_template_param>
void hryky::allocator::Mempool<hryky_template_arg>::deallocate(
	pointer ptr, size_type)
{
	if (hryky_is_null(this->mempool_)) {
		return;
	}

	this->mempool_->deallocate(ptr);
}
/**
  @brief retrieves the maximum size by which an allocation can be successful.
 */
template <hryky_template_param>
typename hryky::allocator::Mempool<hryky_template_arg>::size_type
hryky::allocator::Mempool<hryky_template_arg>::max_size() const
{
	if (hryky_is_null(this->mempool_)) {
		return 0;
	}

	return this->mempool_->allocatable_size() / sizeof(value_type);
}
/**
  @brief retrieves the internal representation.
 */
template <hryky_template_param>
hryky::mempool_type
hryky::allocator::Mempool<hryky_template_arg>::mempool() const
{
	return this->mempool_.get();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::allocator::Mempool<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(mempool);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::allocator::Mempool<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->mempool_.write_to(out);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// prototypes of global function
//------------------------------------------------------------------------------
namespace hryky
{
namespace allocator
{
}
}
//------------------------------------------------------------------------------
// definitions of global function
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // ALLOCATOR_HEAP_H_20120225184209445
// end of file
