/**
  @file     permutation_plainchanges_direction.h
  @brief    retrieves the direction of the element in permutation ordered by Plain Chages.
  @author   HRYKY
  @version  $Id: permutation_plainchanges_direction.h 355 2014-06-22 08:47:38Z hryky.private@gmail.com $
 */
#ifndef PERMUTATION_PLAINCHANGES_DIRECTION_H_20131209144810283
#define PERMUTATION_PLAINCHANGES_DIRECTION_H_20131209144810283
#include "hryky/type_traits/size_type_of.h"
#include "hryky/type_traits/const_reference_of.h"
#include "hryky/range.h"
#include "hryky/iterator/at.h"
#include "hryky/iterator/size.h"
#include "hryky/tmp/tmp_list.h"
#include "hryky/tmp/tmp_equal.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ListT, typename IndexT
#define hryky_template_arg \
	ValueT, IndexT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	template <typename ListT>
	class Begin;

	template <typename ListT>
	class End;

	template <typename TermT>
	class Dereference;

	template <typename TermT>
	class Eval;

	template <typename TermT>
	class Increment;

	template <typename LhsT, typename RhsT>
	class Less;

	template <typename LhsT, typename RhsT>
	class Add;

	template <typename LhsT, typename RhsT>
	class And;

}
namespace permutation
{
namespace plainchanges
{
	/**
	  retrieves the direction of the element in permutation in terms of
	  Plain Chages.
	 */
	template <hryky_template_param>
	class Direction;

	/**
	  retrieves the direction of an element in permutation between two
	  iterators in terms of Plain Changes.
	 */
	template <typename BeginT, typename EndT, typename TargetItrT>
	class DirectionIn;

	/**
	  generates each direction of element in permutation in terms of
	  Plain Changes.
	 */
	template <typename ListT>
	class Directions;

	/**
	  generates each direction of element in permutation between two
	  iteratiors in terms of Plain Changes.
	 */
	template <typename BeginT, typename EndT>
	class DirectionsIn;

	/**
	  false is LEFT.
	  true is RIGHT.
	 */
	typedef bool direction_type;

namespace direction_detail
{
	/**
	  The first iteration.
	 */
	template <
		typename BeginT,
		typename EndT,
		typename TargetT,
		typename Itr1stT,
		typename ResultT
	>
	struct FirstFor;
	
	/**
	  if (true == (ref < target))
	 */
	template <
		typename BeginT,
		typename EndT,
		typename RefT,
		typename RefIndexT,
		typename CondT,
		typename ResultT
	>
	struct If;

	/**
	  The second iteration.
	 */
	template <
		typename EndT,
		typename RefT,
		typename RefIndexT,
		typename Itr2ndT,
		typename ResultT
	>
	struct SecondFor;

	/**
	  implements DirectionsIn.
	 */
	template <
		typename BeginT,
		typename EndT,
		typename ItrT,
		bool at_end = tmp::Equal<ItrT, EndT>::type::value
	>
	struct DirectionsInImpl;
	
} // namespace direction_detail
} // namespace plainchanges
} // namespace permutation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the direction of the element in permutation ordered by Plain Chages.
 */
template <hryky_template_param>
class hryky::permutation::plainchanges::Direction
{
private :
	typedef tmp::Begin<ListT> begin;
	typedef tmp::End<ListT> end;
public :
	typedef typename DirectionIn<
		begin,
		end,
		tmp::Add<begin, IndexT>
	>::type type;
};
/**
  @brief retrieves the direction of an element in permutation between two iterators.
 */
template <typename BeginT, typename EndT, typename TargetItrT>
class hryky::permutation::plainchanges::DirectionIn
{
private :
	typedef typename BeginT::type           begin;
	typedef typename EndT::type             end;
	typedef tmp::Dereference<TargetItrT>    target;

public :

	// starts the first iteration.
	typedef typename direction_detail::FirstFor<
		begin,
		end,
		target,
		begin,
		false_type
	>::type type;
};
/**
  @brief generates each direction of element in permutation in terms of
    Plain Changes.
 */
template <typename ListT>
class hryky::permutation::plainchanges::Directions
{
public :
	typedef typename DirectionsIn<
		tmp::Begin<ListT>,
		tmp::End<ListT>
	>::type type;
};
/**
  @brief generates each direction of element in permutation between
    two iteratiors in terms of Plain Changes.
 */
template <typename BeginT, typename EndT>
class hryky::permutation::plainchanges::DirectionsIn
{
private :
	typedef typename BeginT::type   begin;
	typedef typename EndT::type     end;
	
public :
	typedef typename direction_detail::DirectionsInImpl<
		begin, end, begin>::type type;
};
/**
  The first iteration.
 */
template <
	typename BeginT,
	typename EndT,
	typename TargetT,
	typename Itr1stT,
	typename ResultT
>
struct hryky::permutation::plainchanges::direction_detail::FirstFor
{
	typedef Itr1stT                     ref_index;
	typedef tmp::Dereference<Itr1stT>   ref;

	typedef typename FirstFor<
		BeginT,
		EndT,
		TargetT,
		// ++itr1st
		typename tmp::Increment<Itr1stT>::type,
		// ref < target
		typename If<
			BeginT,
			EndT,
			ref,
			ref_index,
			typename tmp::Less<ref, TargetT>::type,
			ResultT
		>::type
	>::type type;
};
/**
  if (true == (ref < target))
 */
template <
	typename BeginT,
	typename EndT,
	typename RefT,
	typename RefIndexT,
	typename CondT,
	typename ResultT
>
struct hryky::permutation::plainchanges::direction_detail::If
{
	// starts the second iteration.
	typedef typename SecondFor<
		EndT, RefT, RefIndexT, BeginT, ResultT>::type type;
};
/**
  The second iteration.
 */
template <
	typename EndT,
	typename RefT,
	typename RefIndexT,
	typename Itr2ndT,
	typename ResultT
>
struct hryky::permutation::plainchanges::direction_detail::SecondFor
{
	typedef Itr2ndT                     parity_index;
	typedef tmp::Dereference<Itr2ndT>   parity_ref;
	
	typedef typename SecondFor<
		EndT,
		RefT,
		RefIndexT,
		// ++itr2nd
		typename tmp::Increment<Itr2ndT>::type,
		/**
		  result = parity_ref < ref && ref_index < parity_ref ?
			!result : result;
		 */
		typename Conditional<
			typename tmp::And<
				tmp::Less<parity_ref, RefT>,
				tmp::Less<RefIndexT, parity_index>
			>::type,
			tmp::Not<ResultT>,
			ResultT
		>::type
	>::type type;
};
/**
  implements DirectionsIn.
 */
template <
	typename BeginT,
	typename EndT,
	typename ItrT,
	bool at_end
>
struct hryky::permutation::plainchanges::direction_detail::DirectionsInImpl
{
	typedef typename tmp::List<
		DirectionIn<BeginT, EndT, ItrT>,
		DirectionsInImpl<
			BeginT,
			EndT,
			typename tmp::Increment<ItrT>::type
		>
	>::type type;
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
namespace direction_detail
{
/**
  terminates the first iteration.
 */
template <
	typename BeginT,
	typename EndT,
	typename TargetT,
	typename ResultT
>
struct FirstFor<BeginT, EndT, TargetT, EndT, ResultT>
{
	typedef typename ResultT::type type;
};
/**
  if (false == (ref < target))
 */
template <
	typename BeginT,
	typename EndT,
	typename RefT,
	typename RefIndexT,
	typename ResultT
>
struct If<BeginT, EndT, RefT, RefIndexT, false_type, ResultT>
{
	typedef typename ResultT::type type;
};
/**
  termintes the second iteration
 */
template <
	typename EndT,
	typename RefT,
	typename RefIndexT,
	typename ResultT
>
struct SecondFor<EndT, RefT, RefIndexT, EndT, ResultT>
{
	typedef typename ResultT::type type;
};
/**
  terminates DirectionsInImpl.
 */
template <
	typename BeginT,
	typename EndT,
	typename ItrT
>
struct DirectionsInImpl<BeginT, EndT, ItrT, true>
{
	typedef tmp::null_list_type type;
};
} // namespace direction_detail
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
	/**
	  retrieves the direction of the element in permutation
	  ordered by Plain Chages.
	 */
	template <typename PermutationT>
	direction_type direction(
		PermutationT const & src,
		typename SizeTypeOf<PermutationT>::type const index);

	/**
	  generates directions of elements in permutation in accordance with
	  Plain Changes.
	 */
	template <typename DirectionsT, typename PermutationT>
	bool directions(DirectionsT & directions, PermutationT const & src);

} // namespace plainchanges
} // namespace permutation
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the direction of the element in permutation
    ordered by Plain Chages.
 */
template <typename PermutationT>
hryky::permutation::plainchanges::direction_type 
hryky::permutation::plainchanges::direction(
	PermutationT const & src,
	typename SizeTypeOf<PermutationT>::type const index)
{
	typedef typename ConstReferenceOf<PermutationT>::type const_reference;
	typedef typename SizeTypeOf<PermutationT>::type size_type;

	direction_type result = false;

	const_reference target = hryky::at(src, index);

	hryky::range(src).foreach_at([&result, &target, &src, index](
		const_reference ref, size_type const ref_index) {
		if (ref < target) {
			hryky::range(src).foreach_at([&result, &ref, ref_index](
				const_reference parity_ref, size_type const parity_index) {
				result = parity_ref < ref && ref_index < parity_index ?
					!result : result;
			});
		}
	});

	return result;
}
/**
  @brief generates directions of elements in permutation in accordance with
    Plain Changes.
 */
template <typename DirectionsT, typename PermutationT>
bool hryky::permutation::plainchanges::directions(
	DirectionsT & directions, PermutationT const & src)
{
	typedef typename SizeTypeOf<PermutationT>::type size_type;
	typedef typename SizeTypeOf<DirectionsT>::type directions_size_type;

	size_type const src_size = hryky::size(src);
	
	if (hryky::size(directions) < src_size) {
		return false;
	}

	hryky::repeat(src_size).foreach_at([&directions, &src](
		size_type const index) {
		directions.set(
			static_cast<directions_size_type>(index),
			plainchanges::direction(src, index));
	});
	
	return true;
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // PERMUTATION_PLAINCHANGES_DIRECTION_H_20131209144810283
// end of file
