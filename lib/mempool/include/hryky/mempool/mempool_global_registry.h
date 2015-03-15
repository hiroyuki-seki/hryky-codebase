/**
  @file     mempool_global_registry.h
  @brief    The registry of allocator used by multiple contexts.
  @author   HRYKY
  @version  $Id: mempool_global_registry.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef POOL_GLOBAL_H_20140204125858207
#define POOL_GLOBAL_H_20140204125858207
#include "hryky/definition.h"
#include "hryky/pragma.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/without_copy.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
/**
  @brief overloads global operator new and delete.
  
  - This macro defines the functions overloading global new/delete.
 */
#define HRYKY_DEFINE_GLOBAL_NEW_DELETE() \
	void * operator new(size_t size)\
	{\
		if (0u == size) { \
			return hryky_nullptr;\
		}\
		return hryky::mempool::global::Registry::instance()->allocate(size);\
	}\
	void operator delete(void *ptr)\
	{\
		if (hryky_is_null(ptr)) {\
			return;\
		}\
		hryky::mempool::global::Registry::instance()->deallocate(ptr);\
	}
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
	class Base;
	
namespace global
{
	/// The registry of allocator used by multiple contexts.
	class Registry;

} // namespace global
} // namespace mempool

typedef mempool::Base * mempool_type;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The registry of allocator used by multiple contexts.
 */
class hryky::mempool::global::Registry :
	private WithoutCopy,
	public WithStreamOut<Registry>,
	public WithSwap<Registry>
{
public :

	typedef Registry this_type;

	/// retrieves the mempool shared by multiple contexts.
	static mempool_type instance();

	/// default constructor.
	Registry();

	/// constructs with a memory pool used in the current scope.
	Registry(mempool_type const mempool);

	/// move constructor.
	Registry(this_type &&);

	/// destructor.
	~Registry();

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :

	hryky_delete_this_copy_constructor(Registry);
	hryky_delete_this_copy_assign_op(Registry);

	mempool_type prev_;
	bool valid_;

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
hryky::mempool::global::Registry::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(prev);
	hryky_write_member(valid);

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
namespace global
{
} // namespace global
} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // POOL_GLOBAL_H_20140204125858207
// end of file
