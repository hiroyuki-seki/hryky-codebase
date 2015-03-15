/**
  @file     tmp_swap.h
  @brief    interchanges the values at the each position.
  @author   HRYKY
  @version  $Id: tmp_swap.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef TMP_SWAP_H_20131222175816415
#define TMP_SWAP_H_20131222175816415
#include "hryky/tmp/tmp_same.h"
#include "hryky/tmp/tmp_eval.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename LhsIteratorT, typename RhsIteratorT
#define hryky_template_arg \
	LhsIteratorT, RhsIteratorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// interchanges the values at the each position.
	template <hryky_template_param>
	class Swap;

	/// interchanges the values at the each position specified by the indices.
	template <typename ListT, typename LhsIndexT, typename RhsIndexT>
	class SwapAt;

	template <typename ListT, typename IndexT, typename ValueT>
	class AssignAt;

	template <typename ListT, typename IndexT>
	class At;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief interchanges the values at the each position.
 */
template <hryky_template_param>
class hryky::tmp::Swap
{
	static_assert(
		Same<
			typename LhsIteratorT::type::list_type,
			typename RhsIteratorT::type::list_type
		>::value,
		"interchanged iterators must have the same list.");
public :
	typedef typename SwapAt<
		typename LhsIteratorT::type::list_type,
		typename LhsIteratorT::type::index_type,
		typename RhsIteratorT::type::index_type
	>::type type;
};
/**
  @brief interchanges the values at the each position specified by the indices.
 */
template <typename ListT, typename LhsIndexT, typename RhsIndexT>
class hryky::tmp::SwapAt
{
public :
	typedef typename AssignAt<
		AssignAt<
			ListT,
			LhsIndexT,
			At<ListT, RhsIndexT> >,
		RhsIndexT,
		At<ListT, LhsIndexT>
	>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
} // namespace tmp
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
namespace tmp
{
} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // TMP_SWAP_H_20131222175816415
// end of file
