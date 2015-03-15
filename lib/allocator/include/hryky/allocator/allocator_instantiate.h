/**
  @file     allocator_instantiate.h
  @brief    creates an instance by allocator.
  @author   HRYKY
  @version  $Id: allocator_instantiate.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef ALLOCATOR_INSTANTIATE_H_20140202083621025
#define ALLOCATOR_INSTANTIATE_H_20140202083621025
#include "hryky/nullptr.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace allocator
{
} // namespace allocator
} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace allocator
{
	/// allocates a memory and instantiates in the memory.
	template <typename AllocatorT>
	typename AllocatorT::pointer instantiate_by(AllocatorT & allocator);

	/// allocates a memory and instantiates in the memory with one argument.
	template <typename AllocatorT, typename Arg1T>
	typename AllocatorT::pointer instantiate_by(
		AllocatorT & allocator, Arg1T && arg1);

	/// allocates a memory and instantiates in the memory with two arguments.
	template <typename AllocatorT, typename Arg1T, typename Arg2T>
	typename AllocatorT::pointer instantiate_by(
		AllocatorT & allocator, Arg1T && arg1, Arg2T && arg2);

	/// allocates a memory and instantiates in the memory with three arguments.
	template <typename AllocatorT, typename Arg1T, typename Arg2T,
		typename Arg3T>
	typename AllocatorT::pointer instantiate_by(
		AllocatorT & allocator,
		Arg1T && arg1,
		Arg2T && arg2,
		Arg3T && arg3);

	/// destroys an instance and deallocates the memory which the instance is on.
	template <typename AllocatorT>
	void release_by(
		AllocatorT & allocator, typename AllocatorT::pointer instance);

	/// allocates the memory of an instance.
	template <typename AllocatorT>
	typename AllocatorT::pointer
		allocate_by(AllocatorT & allocator);

} // namespace allocator
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief allocates the memory of an instance.
 */
template <typename AllocatorT>
typename AllocatorT::pointer
hryky::allocator::allocate_by(AllocatorT & allocator)
{
	return allocator.allocate(1);
}
/**
  @brief allocates a memory and instantiates in the memory.
 */
template <typename AllocatorT>
typename AllocatorT::pointer
hryky::allocator::instantiate_by(AllocatorT & allocator)
{
	typename AllocatorT::pointer const instance = allocate_by(allocator);
	if (hryky_is_null(instance)) {
		return hryky_nullptr;
	}
	new (instance) typename AllocatorT::value_type;
	
	return instance;
}
/**
  @brief allocates a memory and instantiates in the memory by one argument.
 */
template <typename AllocatorT, typename Arg1T>
typename AllocatorT::pointer
hryky::allocator::instantiate_by(AllocatorT & allocator, Arg1T && arg1)
{
	typename AllocatorT::pointer const instance = allocate_by(allocator);
	if (hryky_is_null(instance)) {
		return hryky_nullptr;
	}

	allocator.construct(instance, ::std::forward<Arg1T>(arg1));
	
	return instance;
}
/**
  @brief allocates a memory and instantiates in the memory by two arguments.
 */
template <typename AllocatorT, typename Arg1T, typename Arg2T>
typename AllocatorT::pointer
hryky::allocator::instantiate_by(
	AllocatorT & allocator, Arg1T && arg1, Arg2T && arg2)
{
	typename AllocatorT::pointer const instance = allocate_by(allocator);
	if (hryky_is_null(instance)) {
		return hryky_nullptr;
	}

	allocator.construct(
		instance,
		::std::forward<Arg1T>(arg1),
		::std::forward<Arg2T>(arg2));
	
	return instance;
}
/**
  @brief allocates a memory and instantiates in the memory by three arguments.
 */
template <typename AllocatorT, typename Arg1T, typename Arg2T, typename Arg3T>
typename AllocatorT::pointer
hryky::allocator::instantiate_by(
	AllocatorT & allocator,
	Arg1T && arg1,
	Arg2T && arg2,
	Arg3T && arg3)
{
	typename AllocatorT::pointer const instance =
		reinterpret_cast<typename AllocatorT::pointer>(allocator.allocate(1));
	if (hryky_is_null(instance)) {
		return hryky_nullptr;
	}

	allocator.construct(
		instance,
		::std::forward<Arg1T>(arg1),
		::std::forward<Arg2T>(arg2),
		::std::forward<Arg3T>(arg3));
	
	return instance;
}
/**
  @brief destroys an instance and deallocates the memory which the instance is on.
 */
template <typename AllocatorT>
void hryky::allocator::release_by(
	AllocatorT & allocator, typename AllocatorT::pointer instance)
{
	allocator.destroy(instance);
	allocator.deallocate(instance, 1);
}
#endif // ALLOCATOR_INSTANTIATE_H_20140202083621025
// end of file
