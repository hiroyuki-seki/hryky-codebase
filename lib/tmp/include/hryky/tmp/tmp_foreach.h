/**
  @file     tmp_foreach.h
  @brief    applies a function to each element of container.
  @author   HRYKY
  @version  $Id: tmp_foreach.h 355 2014-06-22 08:47:38Z hryky.private@gmail.com $
 */
#ifndef TMP_FOREACH_H_20131223090201043
#define TMP_FOREACH_H_20131223090201043
#include "hryky/tmp/tmp_list.h"
#include "hryky/tmp/tmp_is_list.h"
#include "hryky/tmp/tmp_is_iterator.h"
#include "hryky/tmp/tmp_eval.h"
#include "hryky/tmp/tmp_iteration.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_op_param \
	template <typename> class OpT
#define hryky_op_arg \
	OpT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// applies a function to each element of container.
	template <
		typename ListT,
		hryky_op_param,
		typename AccumulatorT = null_type
	>
	class Foreach;

	/// applies a function to each element between two iterators.
	template <
		typename BeginT,
		typename EndT,
		hryky_op_param,
		typename AccumulatorT = null_type
	>
	class ForeachIn;

	/// implements Foreach<> with the previous result.
	template <
		typename BeginT,
		typename EndT,
		typename ItrT,
		hryky_op_param,
		typename AccumulatorT
	>
	class ForeachInImpl;

	template <typename ListT>
	class Begin;

	template <typename ListT>
	class End;

	template <typename TermT>
	class Increment;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief applies a function to each element of container.
 */
template <typename ListT, hryky_op_param, typename AccumulatorT>
class hryky::tmp::Foreach
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
public :
	typedef typename ForeachIn<
		Begin<ListT>,
		End<ListT>,
		OpT,
		AccumulatorT
	>::type type;
};
/**
  @brief applies a function to each element between two iterators.
 */
template <
	typename BeginT,
	typename EndT,
	hryky_op_param,
	typename AccumulatorT
>
class hryky::tmp::ForeachIn
{
	static_assert(
		IsIterator<BeginT>::type::value,
		"The first parameter has to be an iterator.");
	static_assert(
		IsIterator<EndT>::type::value,
		"The second parameter has to be an iterator.");
public :
	typedef typename ForeachInImpl<
		typename BeginT::type,
		typename EndT::type,
		typename BeginT::type,
		OpT,
		AccumulatorT
	>::type type;
};
/**
  @brief implements ForeachIn<> with the previous result.
 */
template <
	typename BeginT,
	typename EndT,
	typename ItrT,
	hryky_op_param,
	typename AccumulatorT
>
class hryky::tmp::ForeachInImpl
{
	typedef OpT<
		iteration::Arg<
			BeginT, EndT, ItrT, AccumulatorT
		>
	> op;
public :
	typedef typename ForeachInImpl<
		BeginT,
		EndT,
		typename Increment<ItrT>::type,
		OpT,
		typename iteration::GetAccumulator<op, AccumulatorT>::type
	>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  terminates iteration of ForeachInImpl<>.
 */
template <
	typename BeginT,
	typename EndT,
	hryky_op_param,
	typename AccumulatorT
>
class ForeachInImpl<
	BeginT, EndT, EndT, hryky_op_arg, AccumulatorT>
{
public :
	typedef typename OpT<
		iteration::Arg<
			BeginT, EndT, EndT, AccumulatorT
		>
	>::type type;
};
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
#undef hryky_op_param
#undef hryky_op_arg
#endif // TMP_FOREACH_H_20131223090201043
// end of file
