/**
  @file     mempool_instantiate.h
  @brief    facilitates an intantiation of object.
  @author   HRYKY
  @version  $Id: mempool_instantiate.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef POOL_INSTANTIATE_H_20140201162636351
#define POOL_INSTANTIATE_H_20140201162636351
#include "hryky/mempool/mempool_base.h"
#include "hryky/mempool/mempool_deleter.h"
#include "hryky/mempool/mempool_ptr.h"
#include "hryky/unique_ptr.h"
#include "hryky/scoped_array.h"
#include "hryky/type/type_name.h"
#include "hryky/log/log_definition.h"
#include "hryky/is_null.h"
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
	/// The default array type using mempool.
	template <typename ValueT>
	class Array;

	/// The default smart pointer type using mempool.
	template <typename ValueT>
	class Instance;

} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The default array type using mempool.
 */
template <typename ValueT>
class hryky::mempool::Array
{
public :
	typedef ScopedArray<ValueT, Deleter<ValueT> > type;
};
/**
  @brief The default smart pointer type using mempool.
 */
template <typename ValueT>
class hryky::mempool::Instance
{
public :
	typedef UniquePtr<ValueT, Deleter<ValueT> > type;
};
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
	/// allocates memory by the specific mempool.
	template <typename ValueT>
	ValueT * allocate(mempool::Ptr const & mempool);

	/// creates an instance from the specific mempool.
	template <typename ValueT>
	typename Instance<ValueT>::type instantiate(
		mempool::Ptr const & mempool);

	/**
	  creates an instance as unique ptr with an argument.
	  The memory is allocated from the specific mempool.
	 */
	template <typename ValueT, typename Arg1T>
	typename Instance<ValueT>::type instantiate(
		mempool::Ptr const & mempool, Arg1T && arg1);

	/**
	  creates an instance as unique ptr with two arguments.
	  The memory is allocatoed from the specific mempool.
	 */
	template <typename ValueT, typename Arg1T, typename Arg2T>
	typename Instance<ValueT>::type instantiate(
		mempool::Ptr const & mempool, Arg1T && arg1, Arg2T && arg2);

	/**
	  creates an instance as unique ptr with three arguments.
	  The memory is allocated from the specific mempool.
	 */
	template <
		typename ValueT,
		typename Arg1T,
		typename Arg2T,
		typename Arg3T>
	typename Instance<ValueT>::type instantiate(
		mempool::Ptr const & mempool,
		Arg1T && arg1,
		Arg2T && arg2,
		Arg3T && arg3);

	/**
	  creates an array of instances as scoped array.
	  The memory is allocated from the specific mempool.
	  @todo remove this.
	 */
	template <typename ValueT>
	typename Array<ValueT>::type array(
		mempool::Ptr const & mempool, size_t const size);

} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief allocates memory by the specific mempool.
 */
template <typename ValueT>
ValueT * hryky::mempool::allocate(mempool::Ptr const & mempool)
{
	if (hryky_is_null(mempool)) {
		return hryky_nullptr;
	}

	return reinterpret_cast<ValueT *>(
		mempool->allocate(sizeof(ValueT)));
}
/**
  @brief creates an instance from the specific mempool.
 */
template <typename ValueT>
typename hryky::mempool::Instance<ValueT>::type
hryky::mempool::instantiate(mempool::Ptr const & mempool)
{
	typedef typename Instance<ValueT>::type instance_type;
	
	ValueT * const instance = allocate<ValueT>(mempool);
	if (hryky_is_null(instance)) {
		return instance_type();
	}

	return instance_type(new (instance) ValueT());
}
/**
  @brief creates an instance by the specific mempool with a argument.
 */
template <typename ValueT, typename Arg1T>
typename hryky::mempool::Instance<ValueT>::type 
hryky::mempool::instantiate(mempool::Ptr const & mempool, Arg1T && arg1)
{
	typedef typename Instance<ValueT>::type instance_type;
	
	ValueT * const instance = allocate<ValueT>(mempool);
	if (hryky_is_null(instance)) {
		return instance_type();
	}

	return instance_type(
		new (instance) ValueT(
			::std::forward<Arg1T>(arg1)));
}
/**
  @brief creates an instance by the specific mempool with two arguments.
 */
template <typename ValueT, typename Arg1T, typename Arg2T>
typename hryky::mempool::Instance<ValueT>::type 
hryky::mempool::instantiate(
	mempool::Ptr const & mempool, Arg1T && arg1, Arg2T && arg2)
{
	typedef typename Instance<ValueT>::type instance_type;
	
	ValueT * const instance = allocate<ValueT>(mempool);
	if (hryky_is_null(instance)) {
		return instance_type();
	}

	return instance_type(
		new (instance) ValueT(
			::std::forward<Arg1T>(arg1),
			::std::forward<Arg2T>(arg2)));
}
/**
  @brief creates an instance by the specific mempool with three arguments.
 */
template <
	typename ValueT, typename Arg1T, typename Arg2T, typename Arg3T
>
typename hryky::mempool::Instance<ValueT>::type 
hryky::mempool::instantiate(
	mempool::Ptr const & mempool,
	Arg1T && arg1,
	Arg2T && arg2,
	Arg3T && arg3)
{
	typedef typename Instance<ValueT>::type instance_type;
	
	ValueT * const instance = allocate<ValueT>(mempool);
	if (hryky_is_null(instance)) {
		return instance_type();
	}

	return instance_type(
		new (instance) ValueT(
			::std::forward<Arg1T>(arg1),
			::std::forward<Arg2T>(arg2),
			::std::forward<Arg3T>(arg3)));
}
/**
  @brief creates an array of instances by the specific mempool.
  @todo remove this.
 */
template <typename ValueT>
typename hryky::mempool::Array<ValueT>::type
hryky::mempool::array(
	mempool::Ptr const & mempool, size_t const size)
{
	typedef typename Array<ValueT>::type instance_type;
	
	if (hryky_is_null(mempool)) {
		return instance_type();
	}
	
	ValueT * const instance = reinterpret_cast<ValueT *>(
		mempool->allocate(sizeof(ValueT) * size));
	if (hryky_is_null(instance)) {
		return instance_type();
	}
	
	return instance_type(new (instance) ValueT[size], size);
}
#endif // POOL_INSTANTIATE_H_20140201162636351
// end of file
