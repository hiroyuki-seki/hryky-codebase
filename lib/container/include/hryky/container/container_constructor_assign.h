/**
  @file     container_constructor_assign.h
  @brief    constructs and destroies elements by assignment operation.
  @author   HRYKY
  @version  $Id: container_constructor_assign.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef CONTAINER_CONSTRUCTOR_ASSIGN_H_20140302184904450
#define CONTAINER_CONSTRUCTOR_ASSIGN_H_20140302184904450
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
	/// constructs and destroies elements by assignment operation.
	class Assign;

} // namespace constructor
} // namespace container
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief constructs and destroies elements by assignment operation.
 */
class hryky::container::constructor::Assign
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
hryky::container::constructor::Assign::construct(
	AllocatorT &, InputIteratorT begin, InputIteratorT end)
{
	typedef ::std::iterator_traits<InputIteratorT>::value_type value_type;

	InputIteratorT itr = begin;
	for (; end != itr; ++itr) {
		*itr = value_type();
	}
}
/**
  @brief constructs between two iterators with an argument.
 */
template <typename AllocatorT, typename InputIteratorT, typename Arg1T>
void 
hryky::container::constructor::Assign::construct(
	AllocatorT & allocator,
	InputIteratorT begin,
	InputIteratorT end,
	Arg1T && arg1)
{
	typedef ::std::iterator_traits<InputIteratorT>::value_type value_type;
	
	InputIteratorT itr = begin;
	for (; end != itr; ++itr) {
		*itr = value_type(::std::forward<Arg1T>(arg1));
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
hryky::container::constructor::Assign::construct(
	AllocatorT & allocator,
	InputIteratorT begin,
	InputIteratorT end,
	Arg1T && arg1,
	Arg2T && arg2)
{
	typedef ::std::iterator_traits<InputIteratorT>::value_type value_type;
	
	InputIteratorT itr = begin;
	for (; end != itr; ++itr) {
		*itr = value_type(
			::std::forward<Arg1T>(arg1),
			::std::forward<Arg2T>(arg2));
	}
}
/**
  @brief destroies the elements between two iterators.
 */
template <typename AllocatorT, typename InputIteratorT>
void hryky::container::constructor::Assign::destroy(
	AllocatorT &, InputIteratorT begin, InputIteratorT end)
{
	typedef ::std::iterator_traits<InputIteratorT>::value_type value_type;
	
	InputIteratorT itr = begin;
	for (; end != itr; ++itr) {
		*itr = value_type();
	}
}
/**
  @brief destroies the element.
 */
template <typename AllocatorT, typename InputIteratorT>
void hryky::container::constructor::Assign::destroy(
	AllocatorT & allocator, InputIteratorT itr)
{
	typedef ::std::iterator_traits<InputIteratorT>::value_type value_type;
	*itr = value_type();
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
#endif // CONTAINER_CONSTRUCTOR_ASSIGN_H_20140302184904450
// end of file
