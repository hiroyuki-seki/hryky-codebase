/**
  @file     permutation_parity.h
  @brief    retrieves the parity of permutation.
  @author   HRYKY
  @version  $Id: permutation_parity.h 355 2014-06-22 08:47:38Z hryky.private@gmail.com $
 */
#ifndef PERMUTATION_PARITY_H_20131207141958263
#define PERMUTATION_PARITY_H_20131207141958263
#include "hryky/range.h"
#include "hryky/iterator/end.h"
#include "hryky/iterator/begin.h"
#include "hryky/type_traits/iterator_of.h"
#include "hryky/type_traits/conditional.h"
#include "hryky/type_traits/integral_constant.h"
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
	template <typename BooleanT, typename TrueT, typename FalseT>
	class Conditional;
	
namespace tmp
{
	template <typename ListT>
	class Begin;
	
	template <typename ListT>
	class End;

	template <bool Value>
	class Boolean;

	template <typename LhsT, typename RhsT>
	class Less;

	template <typename TermT>
	class Eval;

	template <typename TermT>
	class Dereference;

	template <typename TermT>
	class Increment;

	template <typename TermT>
	class Not;
}
namespace permutation
{
	/// retrieves the parity of permutation.
	template <hryky_template_param>
	class Parity;

	/// retrieves the parity of permutation between two iterator.
	template <typename BeginT, typename EndT>
	class ParityIn;

	typedef bool parity_type;

namespace parity_detail
{
	/**
	  1st iteration up to end.
	 */
	template <
		typename BeginT,
		typename EndT,
		typename Itr1stT,
		typename ResultT
	>
	struct Iterate1st;
	
	/**
	  2nd iteration.
	 */
	template <
		typename Itr1stT,
		typename Itr2ndT,
		typename ResultT
	>
	struct Iterate2nd;

} // namespace parity_detail
} // namespace permutation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the parity of permutation.
 */
template <typename ListT>
class hryky::permutation::Parity
{
public :
	typedef typename ParityIn<
		tmp::Begin<ListT>,
		tmp::End<ListT>
	>::type type;
};
/**
  @brief retrieves the parity of permutation between two iterator.
 */
template <typename BeginT, typename EndT>
class hryky::permutation::ParityIn
{
private :
	template <typename BeginT, typename EndT>
	struct Impl
	{
		// 1st iteration up to end.
		typedef typename parity_detail::Iterate1st<
			BeginT,
			EndT,
			BeginT,
			false_type
		>::type type;
	};
public :
	typedef typename Impl<
		typename BeginT::type,
		typename EndT::type
	>::type type;
};
/**
  1st iteration up to end.
 */
template <
	typename BeginT,
	typename EndT,
	typename Itr1stT,
	typename ResultT
>
struct hryky::permutation::parity_detail::Iterate1st
{
	typedef typename Iterate1st<
		BeginT,
		EndT,
		// ++itr1st
		typename tmp::Increment<Itr1stT>::type,
		// 2nd iteration up to itr1st
		typename Iterate2nd<
			Itr1stT, typename BeginT::type, ResultT>
	>::type type;
};
/**
  2nd iteration.
 */
template <typename Itr1stT, typename Itr2ndT, typename ResultT>
struct hryky::permutation::parity_detail::Iterate2nd
{
	typedef typename Iterate2nd<
		Itr1stT,
		// ++itr2nd
		typename tmp::Increment<Itr2ndT>::type,
		// (*itr1st < *itr2nd ? !result : result)
		typename Conditional<
			typename tmp::Less<
				tmp::Dereference<Itr1stT>,
				tmp::Dereference<Itr2ndT>
			>::type,
			tmp::Not<ResultT>,
			ResultT
		>::type
	>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace permutation
{
namespace parity_detail
{
/**
  terminates the 1st iteration.
 */
template <typename BeginT, typename EndT, typename ResultT>
struct Iterate1st<BeginT, EndT, EndT, ResultT>
{
	typedef typename ResultT::type type;
};
/**
  terminates the 2nd iteration.
 */
template <typename Itr1stT, typename ResultT>
struct Iterate2nd<Itr1stT, Itr1stT, ResultT>
{
	typedef typename ResultT::type type;
};
} // namespace parity_detail
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
	/// retrieves the parity of permutation.
	template <typename PermutationT>
	parity_type parity(PermutationT & src);

} // namespace permutation
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the parity of permutation.
 */
template <typename PermutationT>
hryky::permutation::parity_type hryky::permutation::parity(
	PermutationT & src)
{
	typedef typename IteratorOf<PermutationT>::type iterator;
	
	parity_type result = false;

	iterator const begin = hryky::begin(src);
	iterator const end = hryky::end(src);

	if (2u > end - begin) {
		return result;
	}

	iterator itr1st = begin + 1;

	for (; end != itr1st; ++itr1st) {
		iterator itr2nd = begin;
		for (; itr1st != itr2nd; ++itr2nd) {
			result = (*itr1st < *itr2nd) ? !result : result;
		}
	}
	
	return result;
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // PERMUTATION_PARITY_H_20131207141958263
// end of file
