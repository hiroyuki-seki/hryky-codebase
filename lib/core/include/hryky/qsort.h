/**
  @file         qsort.h
  @brief        common definition for quick sort.
  @author       HRYKY
  @version      $Id: qsort.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef QSORT_H_20120911113935152
#define QSORT_H_20120911113935152
#include "hryky/foreach.h"
#include "hryky/range.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
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
	/**
	  @brief  quick sort.
	  @param  begin specifies the beginning of the sorted range.
	  @param  end specifies just after the last element in the sorted range.
	 */
	template < typename InputIteratorT >
	void qsort(InputIteratorT const begin, InputIteratorT const end);

	/// internal use of qsort()
	namespace qsort_internal
	{
		/**
		  @brief  gets the position of pivot to partition values.
		  @param  begin specifies the beginning of the sorted range.
		  @param  end specifies just after the last element in the sorted range.
		  @retval -1 represents that all elements in the range are same value.
		  @retval !=-1 represents the position of the element selected as the target of
		          comparison (known as pivot).
		 */
		template < typename InputIteratorT >
		size_t pivot_position(
			InputIteratorT const begin, InputIteratorT const end);
		/**
		  @brief  divides into two groups. 
		  @param  begin specifies the beginning of the sorted range.
		  @param  end specifies just after the last element in the sorted range.
		  @return The beginning of the last half gruop.

		   divides into two groups. The values in one group are less than a pivot.
		  The values in the other  is equal to or greater than the pivot.
		 */
		template < typename InputIteratorT >
		InputIteratorT partition(InputIteratorT const begin, InputIteratorT const end);
	}

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief quick sort.
 */
template < typename InputIteratorT >
void hryky::qsort(InputIteratorT const begin, InputIteratorT const end)
{
#if 0
	::std::ostringstream os;
	os << "[" << begin << "," << end << ") => {";
	for (ValueT & value : ::std::make_pair(begin, end)) {
		os << ::std::hex << ::std::showbase << value << ",";
	}
	os << "}";
	hryky_log_debug(os.str());
#endif

	InputIteratorT const boundary = qsort_internal::partition(begin, end);

	if (end == boundary) {
		return;
	}

	hryky::qsort(begin, boundary);
	hryky::qsort(boundary, end);
};
/**
  @brief gets the position of pivot to partition values.
 */
template < typename InputIteratorT >
hryky::size_t hryky::qsort_internal::pivot_position(
	InputIteratorT const begin, InputIteratorT const end)
{
	typedef typename ::std::iterator_traits<InputIteratorT>::reference
		reference;
	
	reference begin_ref = *begin;

	Range<InputIteratorT> range(begin + 1, end);
	Foreach<Range<InputIteratorT> > foreach(range);
	for (; foreach.valid(); ++foreach) {
		reference ref = *foreach;
		if (begin_ref > ref) {
			return 0;
		}
		else if (begin_ref < ref) {
			return foreach.offset() + 1;
		}
	}
	
	return static_cast<size_t>(-1);
};
/**
  @brief divides into two groups.
 */
template < typename InputIteratorT >
InputIteratorT hryky::qsort_internal::partition(
	InputIteratorT const begin, InputIteratorT const end)
{
	typedef ::std::iterator_traits<InputIteratorT>    iterator_traits;
	typedef iterator_traits::difference_type        difference_type;
	
	typename difference_type const size = ::std::distance(begin, end);
	
	if (0 == size || 1 == size) {
		return end;
	}

	size_t const pivot_pos = pivot_position(begin, end);

	if (static_cast<size_t>(-1) == pivot_pos) {
		return end;
	}

	typedef iterator_traits::value_type value_type;

	value_type const pivot = *::std::next(
		begin, static_cast<difference_type>(pivot_pos));
	
	InputIteratorT forward = begin;
	InputIteratorT backward = end - 1;
	
	size_t forward_index = 0u;
	size_t backward_index = static_cast<size_t>(size - 1u);

	while (forward <= backward) {
		while (*forward < pivot) {
			++forward;
			++forward_index;
		}

		while (backward_index > 0u && *backward >= pivot) {
			--backward;
			--backward_index;
		}

		if (backward_index <= forward_index) {
			return forward;
		}

		hryky::swap(*forward, *backward);
		++forward;
		++forward_index;
		--backward;
		--backward_index;
	}
	
	return forward;
};
#endif // QSORT_H_20120911113935152
// end of file
