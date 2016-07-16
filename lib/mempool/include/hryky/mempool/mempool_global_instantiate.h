/**
  @file     mempool_global_instantiate.h
  @brief    creates an instance by the shared memory pool.
  @author   HRYKY
  @version  $Id: mempool_global_instantiate.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef MEMPOOL_GLOBAL_INSTANTIATE_H_20140301141157258
#define MEMPOOL_GLOBAL_INSTANTIATE_H_20140301141157258
#include "hryky/mempool/mempool_instantiate.h"
#include "hryky/mempool/mempool_global_registry.h"
#include "hryky/mempool/mempool_ptr.h"
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
namespace global
{
} // namespace global
} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
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
	/// allocates memory from the default mempool.
	template <typename ValueT>
	ValueT * allocate();

	/**
	  creates an instance as unique ptr without an argument.
	  The memory is allocated from the default mempool.
	 */
	template <typename ValueT>
	typename Instance<ValueT>::type instantiate();

	/**
	  creates an instance as unique ptr with an argument.
	  The memory is allocated from the default mempool.
	 */
	template <typename ValueT, typename Arg1T>
	typename Instance<ValueT>::type
		instantiate(Arg1T && arg1);

	/**
	  creates an instance as unique ptr with two arguments.
	  The memory is allocated from the default mempool.
	 */
	template <typename ValueT, typename Arg1T, typename Arg2T>
	typename Instance<ValueT>::type
		instantiate(Arg1T && arg1, Arg2T && arg2);

	/**
	  creates an array of instances as scoped array.
	  The memory is allocated from the default mempool.
	  @todo remove this.
	 */
	template <typename ValueT>
	typename Array<ValueT>::type array(size_t const size);

} // namespace global
} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief allocates memory from the default mempool.
 */
template <typename ValueT>
ValueT * hryky::mempool::global::allocate()
{
	return mempool::allocate<ValueT>(mempool::Ptr());
}
/**
  @brief creates an instance as unique ptr without a argument.
 */
template <typename ValueT>
typename hryky::mempool::Instance<ValueT>::type 
hryky::mempool::global::instantiate()
{
	return mempool::instantiate<ValueT>(mempool::Ptr());
}
/**
  @brief creates an instance with a argument.
 */
template <typename ValueT, typename Arg1T>
typename hryky::mempool::Instance<ValueT>::type 
hryky::mempool::global::instantiate(Arg1T && arg1)
{
	return mempool::instantiate<ValueT>(
		mempool::Ptr(), ::std::forward<Arg1T>(arg1));
}
/**
  @brief creates an instance with two arguments.
 */
template <typename ValueT, typename Arg1T, typename Arg2T>
typename hryky::mempool::Instance<ValueT>::type 
hryky::mempool::global::instantiate(Arg1T && arg1, Arg2T && arg2)
{
	return mempool::instantiate<ValueT>(
		mempool::Ptr(),
		::std::forward<Arg1T>(arg1),
		::std::forward<Arg2T>(arg2));
}
/**
  @brief creates an array of instances by unique ptr.
  @todo remove this.
 */
template <typename ValueT>
typename hryky::mempool::Array<ValueT>::type
hryky::mempool::global::array(size_t const size)
{
	return mempool::array<ValueT>(mempool::Ptr(), size);
}
#endif // MEMPOOL_GLOBAL_INSTANTIATE_H_20140301141157258
// end of file
