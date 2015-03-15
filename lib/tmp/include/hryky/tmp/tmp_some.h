/**
  @file     tmp_some.h
  @brief    iterates elements of container until the result of function is true.
  @author   HRYKY
  @version  $Id: tmp_some.h 355 2014-06-22 08:47:38Z hryky.private@gmail.com $
 */
#ifndef TMP_SOME_H_20131223120638171
#define TMP_SOME_H_20131223120638171
#include "hryky/tmp/tmp_eval.h"
#include "hryky/tmp/tmp_is_list.h"
#include "hryky/tmp/tmp_is_iterator.h"
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
	/// iterates elements of container until the result of function is true.
	template <
		typename ListT,
		hryky_op_param,
		typename AccumlatorT = null_type
	>
	class Some;

	/// iterates elements between two iterators until the function succeeds.
	template <
		typename BeginT,
		typename EndT,
		hryky_op_param,
		typename AccumlatorT = null_type
	>
	class SomeIn;

	/// applies each element to the functor with the previous operation.
	template <
		typename BeginT,
		typename EndT,
		typename ItrT,
		hryky_op_param,
		typename AccumlatorT
	>
	class SomeInImpl;

	/// evaluates the next element only if the previous operation failed.
	template <
		typename BooleanT,
		typename BeginT,
		typename EndT, 
		typename ItrT,
		hryky_op_param,
		typename AccumlatorT
	>
	class SomeNext;

	template <typename ListT>
	class Begin;

	template <typename ListT>
	class End;

	template <typename TermT>
	class Increment;

namespace some_detail
{
} // namespace some_detail
} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief iterates elements of container until the result of function is true.
 */
template <
	typename ListT,
	hryky_op_param,
	typename AccumlatorT
>
class hryky::tmp::Some
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
private :
	typedef SomeIn<
		Begin<ListT>,
		End<ListT>,
		OpT,
		AccumlatorT
	> impl;
public :
	typedef typename impl::type type;
	typedef typename impl::result result;
};
/**
  @brief iterates elements between two iterators until the function succeeds.
 */
template <
	typename BeginT,
	typename EndT,
	hryky_op_param,
	typename AccumlatorT
>
class hryky::tmp::SomeIn
{
	static_assert(
		IsIterator<BeginT>::type::value,
		"The first parameter has to be an iterator.");
	static_assert(
		IsIterator<EndT>::type::value,
		"The second parameter has to be an iterator.");
private :
	typedef SomeInImpl<
		typename BeginT::type,
		typename EndT::type,
		typename BeginT::type,
		OpT,
		AccumlatorT
	> impl;
public :
	typedef typename impl::type type;
	typedef typename impl::result result;
};
/**
  @brief applies each element to the functor with the previous operation.
 */
template <
	typename BeginT,
	typename EndT,
	typename ItrT,
	hryky_op_param,
	typename AccumlatorT
>
class hryky::tmp::SomeInImpl
{
private :
	typedef OpT<
		iteration::Arg<BeginT, EndT, ItrT, AccumlatorT>
	> op;
	
	typedef SomeNext<
		typename op::result,
		BeginT,
		EndT,
		typename Increment<ItrT>::type,
		OpT,
		typename iteration::GetAccumulator<op, AccumlatorT>::type
	> next;
public :
	typedef typename next::type type;
	typedef typename next::result result;
};
/**
  @brief evaluates the next element only if the previous operation failed.
 */
template <
	typename BooleanT,
	typename BeginT,
	typename EndT, 
	typename ItrT, 
	hryky_op_param,
	typename AccumlatorT
>
class hryky::tmp::SomeNext
{
private :
	typedef SomeInImpl<
		BeginT, EndT, ItrT, OpT, AccumlatorT> impl;
public :
	typedef typename impl::type type;
	typedef typename impl::result result;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  short-circuits the evaluations when the previous operation succeeded.
 */
template <
	typename BeginT,
	typename EndT,
	typename ItrT,
	hryky_op_param,
	typename AccumlatorT
>
class SomeNext<
	true_type, BeginT, EndT, ItrT, OpT, AccumlatorT>
{
public :
	typedef typename AccumlatorT::type type;
	typedef true_type result;
};
/**
  terminates iteration of SomeInImpl<> as all operations failed.
 */
template <
	typename BeginT,
	typename EndT,
	hryky_op_param,
	typename AccumlatorT
>
class SomeInImpl<BeginT, EndT, EndT, OpT, AccumlatorT>
{
public :
	typedef typename OpT<
		iteration::Arg<BeginT, EndT, EndT, AccumlatorT>
	>::type type;
	typedef false_type result;
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
#endif // TMP_SOME_H_20131223120638171
// end of file
