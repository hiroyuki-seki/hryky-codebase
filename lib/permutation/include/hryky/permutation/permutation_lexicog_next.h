/**
  @file     permutation_lexicog_next.h
  @brief    generates the next permutation lexicographically.
  @author   HRYKY
  @version  $Id: permutation_lexicog_next.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef PERMUTATION_LEXICOG_NEXT_H_20131209110517128
#define PERMUTATION_LEXICOG_NEXT_H_20131209110517128
#include "hryky/assign.h"
#include "hryky/iterator/begin.h"
#include "hryky/iterator/end.h"
#include "hryky/std/std_algorithm.h"
#include "hryky/swap.h"
#include "hryky/type_traits/iterator_of.h"
#include "hryky/type_traits/size_type_of.h"
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
namespace permutation
{
namespace lexicog
{
	/// generates the next permutation lexicographically.
	template <hryky_template_param>
	class Next;

} // namespace lexicog
} // namespace permutation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief generates the next permutation lexicographically.
 */
template <typename ValueT>
class hryky::permutation::lexicog::Next
{
public :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace permutation
{
namespace lexicog
{
} // namespace lexicog
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
namespace lexicog
{
	/**
	  generates the next permutation lexicographically.
	  @retval true The next permutation is found.
	  @retval false The src is the last permutation.
	 */
	template <typename ContainerT>
	bool next(ContainerT & dest, ContainerT const & src);

} // namespace lexicog
} // namespace permutation
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief generates the next permutation lexicographically.
 */
template <typename ContainerT>
bool hryky::permutation::lexicog::next(
	ContainerT & dest, ContainerT const & src)
{
	typedef typename IteratorOf<ContainerT>::type iterator;
	typedef typename SizeTypeOf<ContainerT>::type size_type;

	hryky::assign(dest, src);

	iterator const begin = hryky::begin(dest);
	iterator const end = hryky::end(dest);

	if (2u > end - begin) {
		return false;
	}

	iterator found = end;
	{
		iterator itr = begin + 1u;
		for (; end != itr; ++itr) {
			iterator const prev = itr - 1u;
			if (*prev < *itr) {
				found = prev;
			}
		}
	}
	
	if (end == found) {
		// The src is the end of permutations lexicographically.
		return false;
	}

	// The next of the found is greater in obvious.
	iterator target = found + 1u;
	{
		iterator itr = target + 1u;
		for (; end != itr; ++itr) {
			if (*found < *itr) {
				target = itr;
			}
		}
	}
	swap(*found, *target);

	::std::reverse(found + 1u, end);

	return true;
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // PERMUTATION_LEXICOG_NEXT_H_20131209110517128
// end of file
