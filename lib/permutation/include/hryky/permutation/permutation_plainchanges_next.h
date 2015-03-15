/**
  @file     permutation_plainchanges_next.h
  @brief    generates the next permutation ordered by Plain Changes.
  @author   HRYKY
  @version  $Id: permutation_plainchanges_next.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef PERMUTATION_PLAINCHANGES_NEXT_H_20131209134010236
#define PERMUTATION_PLAINCHANGES_NEXT_H_20131209134010236
#include "hryky/permutation/permutation_plainchanges_direction.h"
#include "hryky/type_traits/const_reference_of.h"
#include "hryky/type_traits/iterator_of.h"
#include "hryky/type_traits/size_type_of.h"
#include "hryky/type_traits/is_same.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ListT
#define hryky_template_arg \
	ListT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	template <int Value>
	class Integer;
	
	template <typename ListT>
	class Begin;
	
	template <typename ListT>
	class End;

	template <typename TermT>
	class Increment;

	template <typename TermT>
	class Decrement;
	
	template <typename TermT>
	class Dereference;
	
	template <typename TermT>
	class DereferenceLazily;
	
	template <typename TermT>
	class Not;
	
	template <typename LhsT, typename RhsT>
	class Add;
	
	template <typename LhsT, typename RhsT>
	class Sub;
	
	template <typename LhsT, typename RhsT>
	class And;
	
	template <typename LhsT, typename RhsT>
	class NotEqual;
	
	template <typename LhsT, typename RhsT>
	class Equal;
	
	template <typename LhsT, typename RhsT>
	class Less;
	
	template <typename ListT, typename BeginIndexT, typename EndIndexT>
	class Slice;
	
	template <typename BeginT, typename EndT>
	class SliceIn;
	
	template <typename LhsT, typename RhsT>
	class Swap;
	
}
namespace permutation
{
namespace plainchanges
{
	/// generates the next permutation ordered by Plain Changes.
	template <hryky_template_param>
	class Next;

	/// generates the next permutation between two iterators.
	template <typename BeginT, typename EndT>
	class NextIn;

namespace detail
{
	/**
	  returns early if the length of list is short.
	  
	  if (2u > end - begin) {
		return false;
	  }
	 */
	template <
		typename BeginT,
		typename EndT,
		typename ConditionT
	>
	struct ShortIf;
	
	/**
	  examines the beginning of permutation.
	  
	  if (direction && *(itr + 1u) < *itr) {
		found = itr;
		found_direction = direction;
	  }
	 */
	template <
		typename BeginT,
		typename EndT,
		typename FirstDirectionT = DirectionIn<BeginT, EndT, BeginT>,
		typename ConditionT = typename tmp::And<
			FirstDirectionT,
			tmp::Less<
				tmp::Dereference<tmp::Increment<BeginT> >,
				tmp::Dereference<BeginT>
			>
		>::type
	>
	struct FirstPart;
	
	/**
	   examines the middle of permutation.
	   The middle range of iterator is [begin + 1, end - 2]. An ItrT
	  parameter starts as (begin + 2) so that the ItrT has to be
	  compared with the end of iterator.
	 */
	template <
		typename BeginT,
		typename EndT,
		typename FoundT,
		typename FoundDirectionT,
		typename ItrT = typename tmp::Add<
			BeginT, IntegralConstant<int, 2> >::type,
		bool at_end = tmp::Equal<ItrT, EndT>::type::value
	>
	struct MiddlePart;

	/**
	  if (*(itr + (direction ? 1 : -1)) < *itr) {
		found = itr;
		found_direction = direction
	  }
	 */
	template <
		typename BeginT,
		typename EndT,
		typename FoundT,
		typename FoundDirectionT,
		typename ItrT,
		typename DirectionT = DirectionIn<BeginT, EndT, ItrT>,
		typename ConditionT = typename tmp::Less<
			tmp::Dereference<
				tmp::Add<
					ItrT,
					typename Conditional<
						typename DirectionT::type,
						IntegralConstant<int, 1>,
						IntegralConstant<int, -1>
					>::type
				>
			>,
			tmp::Dereference<ItrT>
		>::type
	>
	struct MiddleFound;
	
	/**
	  continues early in the middle iteration.
	  
	  if (end != found && *itr < *found ) {
		continue;
	  }
	 */
	template <
		typename BeginT,
		typename EndT,
		typename FoundT,
		typename FoundDirectionT,
		typename ItrT,
		typename ConditionT = typename tmp::Eval<tmp::And<
			tmp::NotEqual<EndT, FoundT>,
			tmp::Less<
				tmp::Dereference<ItrT>,
				tmp::DereferenceLazily<FoundT>
			>
		> >::type
	>
	struct MiddleSkipIf;

	/**
	  examines the end of permutation.
	  
	  if (end == found || *found < *(end - 1))
	 */
	template <
		typename BeginT,
		typename EndT,
		typename FoundT,
		typename FoundDirectionT,
		typename ConditionT = typename tmp::Eval<tmp::Or<
			tmp::Equal<EndT, FoundT>,
			tmp::Less<
				tmp::DereferenceLazily<FoundT>,
				tmp::Dereference<tmp::Decrement<EndT> >
			>
		> >::type
	>
	struct LastPart;

	/**
	  The swapped target is found at the end of container.
	  
	  if (!direction && *(itr - 1u) < *itr) {
		found = itr;
		found_direction = direction;
	  }
	 */
	template <
		typename BeginT,
		typename EndT,
		typename FoundT,
		typename FoundDirectionT,
		typename ItrT,
		typename DirectionT = DirectionIn<BeginT, EndT, ItrT>,
		typename ConditionT = typename tmp::And<
			tmp::Not<DirectionT>,
			tmp::Less<
				tmp::Dereference<tmp::Decrement<ItrT> >,
				tmp::Dereference<ItrT>
			>
		>::type
	>
	struct LastFound;

	/**
	  fails if a swapped candicate is not found.
	 */
	template <
		typename BeginT,
		typename EndT,
		typename FoundT,
		typename FoundDirectionT,
		typename ConditionT = typename tmp::Equal<EndT, FoundT>::type
	>
	struct Result;

	/**
	  if (found_direction) {
		swap(*found, *(found + 1u));
	  } else {
		swap(*found, *(found - 1u));
	  }
	 */
	template <
		typename BeginT,
		typename EndT,
		typename ConditionT,
		typename FoundT
	>
	struct SwapRightIf;

} // namespace detail
} // namespace plainchanges
} // namespace permutation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief generates the next permutation ordered by Plain Changes.
 */
template <typename ListT>
class hryky::permutation::plainchanges::Next
{
private :
	typedef NextIn<
		typename tmp::Begin<ListT>::type,
		typename tmp::End<ListT>::type
	> impl;
public :
	typedef typename impl::type type;
	typedef typename impl::at_end at_end;
};
/**
  @brief generates the next permutation between two iterators.
 */
template <typename BeginT, typename EndT>
class hryky::permutation::plainchanges::NextIn
{
private :
	typedef typename BeginT::type   begin;
	typedef typename EndT::type     end;

	typedef detail::ShortIf<
		begin,
		end,
		typename tmp::Less<
			tmp::Sub<end, begin>,
			IntegralConstant<int, 2>
		>::type
	> impl;

public :
	typedef typename impl::type::type type;
	typedef typename impl::at_end::type at_end;
};
/**
  returns early if the length of list is short.
  
  if (2u > end - begin) {
	return false;
  }
 */
template <
	typename BeginT,
	typename EndT,
	typename ConditionT
>
struct hryky::permutation::plainchanges::detail::ShortIf
{
	typedef tmp::SliceIn<BeginT, EndT> type;
	typedef false_type at_end;
};
/**
  examines the beginning of permutation.
  
  if (direction && *(itr + 1u) < *itr) {
	found = itr;
	found_direction = direction;
  }
 */
template <
	typename BeginT,
	typename EndT,
	typename FirstDirectionT,
	typename ConditionT
>
struct hryky::permutation::plainchanges::detail::FirstPart
{
	typedef BeginT found;
	typedef FirstDirectionT found_direction;
};
/**
   examines the middle of permutation.
   The middle range of iterator is [begin + 1, end - 2]. An ItrT
  parameter starts as (begin + 2) so that the ItrT has to be
  compared with the end of iterator.
 */
template <
	typename BeginT,
	typename EndT,
	typename FoundT,
	typename FoundDirectionT,
	typename ItrT,
	bool at_end
>
struct hryky::permutation::plainchanges::detail::MiddlePart
{
	static_assert(
		!IsSame<typename ItrT::type, EndT>::value, "at end");
	static_assert(
		tmp::Less<ItrT, EndT>::type::value, "at end");

	typedef MiddleSkipIf<
		BeginT,
		EndT,
		FoundT,
		FoundDirectionT,
		tmp::Decrement<ItrT>
	> skip_type;

	// The next iteration.
	typedef MiddlePart<
		BeginT,
		EndT,
		typename skip_type::found,
		typename skip_type::found_direction,
		typename tmp::Increment<ItrT>::type
	> next;

	typedef typename next::found found;
	typedef typename next::found_direction found_direction;
};
/**
  if (*(itr + (direction ? 1 : -1)) < *itr) {
	found = itr;
	found_direction = direction
  }
 */
template <
	typename BeginT,
	typename EndT,
	typename FoundT,
	typename FoundDirectionT,
	typename ItrT,
	typename DirectionT,
	typename ConditionT
>
struct hryky::permutation::plainchanges::detail::MiddleFound
{
	typedef ItrT found;
	typedef DirectionT found_direction;
};
/**
  continues early in the middle iteration.
  
  if (end != found && *itr < *found ) {
	continue;
  }
 */
template <
	typename BeginT,
	typename EndT,
	typename FoundT,
	typename FoundDirectionT,
	typename ItrT,
	typename ConditionT
>
struct hryky::permutation::plainchanges::detail::MiddleSkipIf
{
	typedef FoundT found;
	typedef FoundDirectionT found_direction;
};
/**
  examines the end of permutation.
  
  if (end == found || *found < *(end - 1))
 */
template <
	typename BeginT,
	typename EndT,
	typename FoundT,
	typename FoundDirectionT,
	typename ConditionT
>
struct hryky::permutation::plainchanges::detail::LastPart
{
	// The middle iteration ended before the last element.
	typedef tmp::Decrement<EndT> itr;

	typedef LastFound<
		BeginT, EndT, FoundT, FoundDirectionT, itr> last_found;

	typedef typename last_found::found found;
	typedef typename last_found::found_direction found_direction;
};
/**
  The swapped target is found at the end of container.
  
  if (!direction && *(itr - 1u) < *itr) {
	found = itr;
	found_direction = direction;
  }
 */
template <
	typename BeginT,
	typename EndT,
	typename FoundT,
	typename FoundDirectionT,
	typename ItrT,
	typename DirectionT,
	typename ConditionT
>
struct hryky::permutation::plainchanges::detail::LastFound
{
	typedef ItrT found;
	typedef DirectionT found_direction;
};
/**
  fails if a swapped candicate is not found.
 */
template <
	typename BeginT,
	typename EndT,
	typename FoundT,
	typename FoundDirectionT,
	typename ConditionT
>
struct hryky::permutation::plainchanges::detail::Result
{
	typedef tmp::SliceIn<BeginT, EndT> type;
	typedef false_type at_end;
};
/**
  if (found_direction) {
	swap(*found, *(found + 1u));
  } else {
	swap(*found, *(found - 1u));
  }
 */
template <
	typename BeginT,
	typename EndT,
	typename ConditionT,
	typename FoundT
>
struct hryky::permutation::plainchanges::detail::SwapRightIf
{
	// There is the target to be interchanged at the right side.
	typedef tmp::Swap<FoundT, tmp::Increment<FoundT> > swapped;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace permutation
{
namespace plainchanges
{
namespace detail
{
/**
  if (2u > end - begin) {
	return false;
  }
 */
template <
	typename BeginT,
	typename EndT
>
struct ShortIf<BeginT, EndT, false_type>
{
	typedef FirstPart<BeginT, EndT> first_part;

	typedef MiddlePart<
		BeginT,
		EndT,
		typename first_part::found,
		typename first_part::found_direction
	> middle_part;

	typedef LastPart<
		BeginT,
		EndT,
		typename middle_part::found,
		typename middle_part::found_direction
	> last_part;

	typedef Result<
		BeginT,
		EndT,
		typename last_part::found,
		typename last_part::found_direction
	> result;

	typedef typename result::type type;
	typedef typename result::at_end at_end;
};
/**
  if (direction && *(itr + 1u) < *itr) {
	found = itr;
	found_direction = direction;
  }
 */
template <
	typename BeginT,
	typename EndT,
	typename FirstDirectionT
>
struct FirstPart<
	BeginT, EndT, FirstDirectionT, false_type>
{
	typedef EndT found;
	typedef false_type found_direction;
};
/**
   examines the middle of permutation.
   The middle range of iterator is [begin + 1, end - 2]. An ItrT
  parameter starts as (begin + 2) so that the ItrT has to be
  compared with the end of iterator.
 */
template <
	typename BeginT,
	typename EndT,
	typename FoundT,
	typename FoundDirectionT,
	typename ItrT
>
struct MiddlePart<
	BeginT, EndT, FoundT, FoundDirectionT, ItrT, true>
{
	typedef FoundT found;
	typedef FoundDirectionT found_direction;
};
/**
  continues early in the middle iteration.
  
  if (end != found && *itr < *found ) {
	continue;
  }
 */
template <
	typename BeginT,
	typename EndT,
	typename FoundT,
	typename FoundDirectionT,
	typename ItrT
>
struct MiddleSkipIf<
	BeginT, EndT, FoundT, FoundDirectionT, ItrT, false_type>
{
	typedef MiddleFound<
		BeginT, EndT, FoundT, FoundDirectionT, ItrT> middle_found;

	typedef typename middle_found::found found;
	typedef typename middle_found::found_direction found_direction;
};
/**
  if (*(itr + (direction ? 1 : -1)) < *itr) {
	found = itr;
	found_direction = direction
  }
 */
template <
	typename BeginT,
	typename EndT,
	typename FoundT,
	typename FoundDirectionT,
	typename ItrT,
	typename DirectionT
>
struct MiddleFound<
	BeginT,
	EndT,
	FoundT,
	FoundDirectionT,
	ItrT,
	DirectionT,
	false_type
>
{
	typedef FoundT found;
	typedef FoundDirectionT found_direction;
};
/**
  examines the end of permutation.
  
  if (end == found || *found < *(end - 1))
 */
template <
	typename BeginT,
	typename EndT,
	typename FoundT,
	typename FoundDirectionT
>
struct LastPart<
	BeginT, EndT, FoundT, FoundDirectionT, false_type>
{
	typedef FoundT found;
	typedef FoundDirectionT found_direction;
};
/**
  The swapped target is found at the end of container.
  
  if (!direction && *(itr - 1u) < *itr) {
	found = itr;
	found_direction = direction;
  }
 */
template <
	typename BeginT,
	typename EndT,
	typename FoundT,
	typename FoundDirectionT,
	typename ItrT,
	typename DirectionT
>
struct LastFound<
	BeginT, EndT, FoundT, FoundDirectionT, ItrT, DirectionT, false_type>
{
	typedef FoundT found;
	typedef FoundDirectionT found_direction;
};
/**
  fails if a swapped candicate is not found.
 */
template <
	typename BeginT,
	typename EndT,
	typename FoundT,
	typename FoundDirectionT
>
struct Result<BeginT, EndT, FoundT, FoundDirectionT, false_type>
{
	typedef typename SwapRightIf<
		BeginT,
		EndT,
		typename FoundDirectionT::type,
		FoundT
	>::swapped swapped;

	typedef tmp::Slice<
		swapped,
		typename BeginT::index_type,
		typename EndT::index_type
	> type;
	typedef true_type at_end;
};
/**
  if (found_direction) {
	swap(*found, *(found + 1u));
  } else {
	swap(*found, *(found - 1u));
  }
 */
template <
	typename BeginT,
	typename EndT,
	typename FoundT
>
struct SwapRightIf<BeginT, EndT, false_type, FoundT>
{
	// There is the target to be interchanged at the left side.
	typedef tmp::Swap<FoundT, tmp::Decrement<FoundT> > swapped;
};
} // namespace detail
} // namespace plainchanges
} // namespace permutation
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
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
namespace permutation
{
namespace plainchanges
{
	/// generates the next permutation ordered by Plain Changes.
	template <typename PermutationT>
	bool next(PermutationT & dest, PermutationT const & src);

	/**
	  generates the next permutation ordered by Plain Changes with the
	  pre-calculated directions.
	 */
	template <typename PermutationT, typename DirectionsT>
	bool next(
		PermutationT & dest,
		PermutationT const & src,
		DirectionsT & directions);

} // namespace plainchanges
} // namespace permutation
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief generates the next permutation ordered by Plain Changes.
 */
template <typename PermutationT>
bool hryky::permutation::plainchanges::next(
	PermutationT & dest, PermutationT const & src)
{
	typedef typename IteratorOf<PermutationT>::type iterator;
	typedef typename SizeTypeOf<PermutationT>::type size_type;

	hryky::assign(dest, src);

	iterator const begin = hryky::begin(dest);
	iterator const end = hryky::end(dest);

	if (2u > end - begin) {
		return false;
	}

	iterator found = end;
	direction_type found_direction = direction_type();
	
	iterator itr = begin;
	size_type index = 0u;

	// examines beginning of permutation.
	{
		direction_type const direction =
			plainchanges::direction(dest, index);
		if (direction && *(itr + 1u) < *itr) {
			found = itr;
			found_direction = direction;
		}
		++itr;
		++index;
	}

	// examines the middle of permutation.
	for (; end != itr + 1u; ++itr, ++index) {
		if (end != found && *itr < *found ) {
			continue;
		}
		direction_type const direction =
			plainchanges::direction(dest, index);
		if (*(itr + (direction ? 1 : -1)) < *itr) {
			found = itr;
			found_direction = direction;
		}
	}

	// examines the end of permutation
	if (end == found || *found < *itr) {
		direction_type const direction =
			plainchanges::direction(dest, index);
		if (!direction && *(itr - 1u) < *itr) {
			found = itr;
			found_direction = direction;
		}
	}

	// The src is the last permutation ordred by Plain Changes.
	if (end == found) {
		return false;
	}

	if (found_direction) {
		swap(*found, *(found + 1u));
	}
	else {
		swap(*found, *(found - 1u));
	}

	return true;
}
/**
  @brief generates the next permutation ordered by Plain Changes with the
    pre-calculated directions.
 */
template <typename PermutationT, typename DirectionsT>
bool hryky::permutation::plainchanges::next(
	PermutationT & dest, PermutationT const & src, DirectionsT & directions)
{
	typedef typename ConstReferenceOf<PermutationT>::type const_reference;
	typedef typename IteratorOf<PermutationT>::type iterator;
	typedef typename SizeTypeOf<PermutationT>::type size_type;
	typedef typename SizeTypeOf<DirectionsT>::type directions_size_type;

	hryky::assign(dest, src);

	iterator const begin = hryky::begin(dest);
	iterator const end = hryky::end(dest);

	if (2u > end - begin) {
		return false;
	}

	iterator found = end;
	direction_type found_direction = direction_type();
	directions_size_type found_index = 0u;
	
	iterator itr = begin;
	directions_size_type index = 0u;

	// examines beginning of permutation.
	{
		direction_type const direction = directions[index];
		if (direction && *(itr + 1u) < *itr) {
			found = itr;
			found_direction = direction;
			found_index = index;
		}
		++itr;
		++index;
	}

	// examines the middle of permutation.
	for (; end != itr + 1; ++itr, ++index) {
		if (end != found && *itr < *found ) {
			continue;
		}
		direction_type const direction = directions[index];
		if (*(itr + (direction ? 1 : -1)) < *itr) {
			found = itr;
			found_direction = direction;
			found_index = index;
		}
	}

	// examines the end of permutation
	if (end == found || *found < *itr) {
		direction_type const direction = directions[index];
		if (!direction && *(itr - 1) < *itr) {
			found = itr;
			found_direction = direction;
			found_index = index;
		}
	}

	// The src is the last permutation ordred by Plain Changes.
	if (end == found) {
		return false;
	}

	int8_t const adjacent = found_direction ? 1 : -1;

	iterator const target = found + adjacent;
	directions_size_type const target_index =
		static_cast<directions_size_type>(found_index + adjacent);

	swap(*found, *target);

	// interchanges directions
	{
		bool const tmp = directions[found_index];
		directions[found_index] = directions[target_index];
		directions[target_index] = tmp;
	}

	// The value at the target indicates the found value after swap.

	// updates directions
	hryky::range(dest).foreach_at([&directions, &target, target_index](
		const_reference element, size_type const index) {
		if (*target < element) {
			directions.set(
				static_cast<directions_size_type>(index),
				index < target_index);
		}
	});

	return true;
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // PERMUTATION_PLAINCHANGES_NEXT_H_20131209134010236
// end of file
