/**
  @file     container_constructor_normal.h
  @brief    defines the behavior for constructing elements in Vector.
  @author   HRYKY
  @version  $Id: container_constructor_normal.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef CONTAINER_CONSTRUCTOR_NORMAL_H_20140302171308384
#define CONTAINER_CONSTRUCTOR_NORMAL_H_20140302171308384
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace container
{
namespace constructor
{
	/// defines the behavior for constructing elements in Vector.
	class Normal;

} // namespace constructor
} // namespace container
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief defines the behavior for constructing elements in Vector.
 */
class hryky::container::constructor::Normal
{
public :

	/// constructs between two iterators.
	template <typename AllocatorT, typename InputIteratorT>
	static void construct(
		AllocatorT & allocator,
		InputIteratorT begin,
		InputIteratorT end);

	/// constructs between two iterators with an argument.
	template <typename AllocatorT, typename InputIteratorT, typename Arg1T>
	static void construct(
		AllocatorT & allocator,
		InputIteratorT begin,
		InputIteratorT end,
		Arg1T && arg1);

	/// constructs between two iterators with two arguments.
	template <
		typename AllocatorT,
		typename InputIteratorT,
		typename Arg1T,
		typename Arg2T
	>
	static void construct(
		AllocatorT & allocator,
		InputIteratorT begin,
		InputIteratorT end,
		Arg1T && arg1,
		Arg2T && arg2);

	/// destroies the elements between two iterators.
	template <typename AllocatorT, typename InputIteratorT>
	static void destroy(
		AllocatorT & allocator, InputIteratorT begin, InputIteratorT end);

	/// destroies the element.
	template <typename AllocatorT, typename InputIteratorT>
	static void destroy(AllocatorT & allocator, InputIteratorT itr);

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace container
{
namespace constructor
{
} // namespace constructor
} // namespace container
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructs between two iterators.
 */
template <typename AllocatorT, typename InputIteratorT>
void 
hryky::container::constructor::Normal::construct(
	AllocatorT & allocator, InputIteratorT begin, InputIteratorT end)
{
	InputIteratorT itr = begin;
	for (; end != itr; ++itr) {
		allocator.construct(&*itr);
	}
}
/**
  @brief constructs between two iterators with an argument.
 */
template <typename AllocatorT, typename InputIteratorT, typename Arg1T>
void 
hryky::container::constructor::Normal::construct(
	AllocatorT & allocator,
	InputIteratorT begin,
	InputIteratorT end,
	Arg1T && arg1)
{
	InputIteratorT itr = begin;
	for (; end != itr; ++itr) {
		allocator.construct(&*itr, ::std::forward<Arg1T>(arg1));
	}
}
/**
  @brief constructs between two iterators with two arguments.
 */
template <
	typename AllocatorT,
	typename InputIteratorT,
	typename Arg1T,
	typename Arg2T
>
void 
hryky::container::constructor::Normal::construct(
	AllocatorT & allocator,
	InputIteratorT begin,
	InputIteratorT end,
	Arg1T && arg1,
	Arg2T && arg2)
{
	InputIteratorT itr = begin;
	for (; end != itr; ++itr) {
		allocator.construct(
			&*itr,
			::std::forward<Arg1T>(arg1),
			::std::forward<Arg2T>(arg2));
	}
}
/**
  @brief destroies the elements between two iterators.
 */
template <typename AllocatorT, typename InputIteratorT>
void hryky::container::constructor::Normal::destroy(
	AllocatorT & allocator, InputIteratorT begin, InputIteratorT end)
{
	InputIteratorT itr = begin;
	for (; end != itr; ++itr) {
		allocator.destroy(&*itr);
	}
	return;
}
/**
  @brief destroies the element.
 */
template <typename AllocatorT, typename InputIteratorT>
void hryky::container::constructor::Normal::destroy(
	AllocatorT & allocator, InputIteratorT itr)
{
	allocator.destroy(&*itr);
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
namespace container
{
namespace constructor
{
} // namespace constructor
} // namespace container
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // CONTAINER_CONSTRUCTOR_NORMAL_H_20140302171308384
// end of file
