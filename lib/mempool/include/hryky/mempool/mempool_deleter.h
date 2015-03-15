/**
  @file     mempool_deleter.h
  @brief    deletes an instance.
  @author   HRYKY
  @version  $Id: mempool_deleter.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef POOL_DELETER_H_20140121174134403
#define POOL_DELETER_H_20140121174134403
#include "hryky/definition.h"
#include "hryky/mempool/mempool_base.h"
#include "hryky/mempool/mempool_ptr.h"
#include "hryky/range.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/is_null.h"
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
	template <typename ElementT, typename DeleterT>
	class UniquePtr;
	
namespace mempool
{
	/// deletes an instance.
	template <hryky_template_param>
	class Deleter;

} // namespace mempool

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief deletes an instance.
 */
template <hryky_template_param>
class hryky::mempool::Deleter :
	public WithStreamOut<Deleter<hryky_template_arg> >,
	public WithSwap<Deleter<hryky_template_arg> >
{
public :

	typedef Deleter<hryky_template_arg>         this_type;
	typedef ValueT                              value_type;
	typedef typename AddPointer<ValueT>::type   pointer;

	/// default constructor.
	Deleter();

	/// constructs with memory pool.
	Deleter(mempool::Ptr const & mempool);

	/// copy constructor.
	Deleter(this_type const &);

	/// move constructor.
	Deleter(this_type &&);

	/// destructor.
	~Deleter();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// deletes an instance.
	void operator()(pointer const ptr) const;

	/// deletes an array of instances.
	void operator()(pointer const ptr, size_t const size) const;

protected :

private :

	mempool::Ptr const mempool_;

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
hryky::mempool::Deleter<hryky_template_arg>::Deleter()
	: mempool_()
{
}
/**
  @brief constructs with memory pool.
 */
template <hryky_template_param>
hryky::mempool::Deleter<hryky_template_arg>::Deleter(
	mempool::Ptr const & mempool)
	: mempool_(mempool)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::mempool::Deleter<ValueT>::Deleter(this_type const & rhs)
	: hryky_copy_member(mempool)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::mempool::Deleter<ValueT>::Deleter(this_type && rhs)
	: hryky_move_member(mempool)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::mempool::Deleter<ValueT>::~Deleter()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::mempool::Deleter<ValueT>::clear()
{
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::mempool::Deleter<ValueT>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(mempool);

	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::mempool::Deleter<ValueT>::swap(this_type & src)
{
	hryky_swap_member(mempool);
}
/**
  @brief deletes an instance.
 */
template <hryky_template_param>
void hryky::mempool::Deleter<hryky_template_arg>::operator()(
	pointer const ptr) const
{
	if (hryky_is_null(this->mempool_)) {
		return;
	}

	if (hryky_is_null(ptr)) {
		return;
	}
	
	ptr->~ValueT();
	this->mempool_->deallocate(ptr);
}
/**
  @brief deletes an array of instances.
 */
template <hryky_template_param>
void hryky::mempool::Deleter<hryky_template_arg>::operator()(
	pointer const ptr, size_t const size) const
{
	if (hryky_is_null(this->mempool_)) {
		return;
	}

	if (hryky_is_null(ptr)) {
		return;
	}
	
	hryky::range(ptr, ptr + size).foreach([](ValueT & element) {
		element.~ValueT();
	});

	this->mempool_->deallocate(ptr);
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
#endif // POOL_DELETER_H_20140121174134403
// end of file
