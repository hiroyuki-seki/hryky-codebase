/**
  @file     tmp_every.h
  @brief    iterates elements of container until the result of function is false.
  @author   HRYKY
  @version  $Id: tmp_every.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef TMP_EVERY_H_20131223093200063
#define TMP_EVERY_H_20131223093200063
#include "hryky/tmp/tmp_list.h"
#include "hryky/tmp/tmp_is_list.h"
#include "hryky/tmp/tmp_is_iterator.h"
#include "hryky/tmp/tmp_eval.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	template <typename, typename, typename> class FunctorT
#define hryky_template_arg \
	FunctorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// iterates elements of container until the result of function is false.
	template <typename ListT, hryky_template_param>
	class Every;

	/// iterates elements between two iterators until the function fails.
	template <typename BeginT, typename EndT, hryky_template_param>
	class EveryIn;

	/// applies each element to the functor with the previous operation.
	template <
		typename BeginT, typename EndT, hryky_template_param, typename PrevT
	>
	class EveryInImpl;

	/// evaluates the next element only if the previous operation succeeded.
	template <
		typename BooleanT,
		typename BeginT,
		typename EndT,
		hryky_template_param,
		typename PrevT
	>
	class EveryNext;

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
  @brief iterates elements of container until the result of function is false.
 */
template <typename ListT, hryky_template_param>
class hryky::tmp::Every
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
private :
	typedef EveryIn<
		Begin<ListT>,
		End<ListT>,
		FunctorT
	> impl;
public :
	typedef typename impl::type type;
	typedef typename impl::result result;
};
/**
  @brief iterates elements between two iterators until the function fails.
 */
template <typename BeginT, typename EndT, hryky_template_param>
class hryky::tmp::EveryIn
{
	static_assert(
		IsIterator<BeginT>::type::value,
		"The first parameter has to be an iterator.");
	static_assert(
		IsIterator<EndT>::type::value,
		"The second parameter has to be an iterator.");
private :
	typedef EveryInImpl<
		typename BeginT::type,
		typename EndT::type,
		FunctorT,
		null_type
	> impl;
public :
	typedef typename impl::type type;
	typedef typename impl::result result;
};
/**
  @brief applies each element to the functor with the previous operation.
 */
template <
	typename BeginT, typename EndT, hryky_template_param, typename PrevT
>
class hryky::tmp::EveryInImpl
{
private :
	typedef FunctorT<BeginT, EndT, PrevT> applied;
	typedef EveryNext<
		typename applied::result,
		typename Increment<BeginT>::type,
		EndT,
		FunctorT,
		applied
	> next;
public :
	typedef typename next::type type;
	typedef typename next::result result;
};
/**
  @brief evaluates the next element only if the previous operation succeeded.
 */
template <
	typename BooleanT,
	typename BeginT,
	typename EndT,
	hryky_template_param,
	typename PrevT
>
class hryky::tmp::EveryNext
{
private :
	typedef EveryInImpl<BeginT, EndT, FunctorT, PrevT> impl;
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
  short-circuits the evaluations when the previous operation fails.
 */
template <typename BeginT, typename EndT, hryky_template_param, typename PrevT>
class EveryNext<false_type, BeginT, EndT, hryky_template_arg, PrevT>
{
public :
	typedef typename PrevT::type type;
	typedef false_type result;
};
/**
  terminates iteration of EveryInImpl<> as all operations succeeded.
 */
template <typename EndT, hryky_template_param, typename PrevT>
class EveryInImpl<EndT, EndT, hryky_template_arg, PrevT>
{
public :
	typedef typename FunctorT<EndT, EndT, PrevT>::type type;
	typedef true_type result;
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
#undef hryky_template_param
#undef hryky_template_arg
#endif // TMP_EVERY_H_20131223093200063
// end of file
