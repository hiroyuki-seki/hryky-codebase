/**
  @file     tmp_iteration_arg.h
  @brief    retains the arguments for iteration.
  @author   HRYKY
  @version  $Id: tmp_iteration.h 355 2014-06-22 08:47:38Z hryky.private@gmail.com $
 */
#ifndef TMP_ITERATION_H_20140621195215494
#define TMP_ITERATION_H_20140621195215494
#include "hryky/tmp/tmp_same.h"
#include "hryky/tmp/tmp_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename BeginT, typename EndT, typename ItrT, typename AccumlatorT
#define hryky_template_arg \
	BeginT, EndT, ItrT, AccumlatorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
namespace iteration
{
	/// retains the arguments for iteration.
	template <
		typename BeginT,
		typename EndT,
		typename ItrT,
		typename AccumlatorT = null_type
	>
	class Arg;

namespace detail
{
	/// confirms whether a class has the accumulator type.
	template <typename ValueT>
	class HasAccumulator;
	
} // namespace detail

	/// retrieves accumulator type if the value has it.
	template <
		typename ValueT,
		typename SubstitutionT = null_type,
		typename HasT = typename detail::HasAccumulator<ValueT>::type
	>
	class GetAccumulator;

} // namespace iteration
} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the arguments for iteration.
 */
template <hryky_template_param>
class hryky::tmp::iteration::Arg
{
public :
	typedef typename BeginT::type       begin;
	typedef typename EndT::type         end;
	typedef typename ItrT::type         itr;
	typedef typename AccumlatorT::type  accumulator;

	typedef typename Same<begin, end>::type empty;
	typedef typename Same<itr, begin>::type at_begin;
	typedef typename Same<itr, end>::type   at_end;
};
/**
  @brief confirms whether a class has the accumulator type.
 */
template <typename ValueT>
class hryky::tmp::iteration::detail::HasAccumulator
{
	template <typename TargetT>
	static uint16_t test(typename TargetT::accumulator *);

	template <typename>
	static uint8_t test(...);
public :
	typedef IntegralConstant<
		bool, sizeof(uint16_t) == sizeof(test<ValueT>(0))> type;
	
	static typename type::value_type const value = type::value;
};
/**
  @brief retrieves accumulator type if the value has it.
 */
template <
	typename ValueT,
	typename SubstitutionT,
	typename HasT
>
class hryky::tmp::iteration::GetAccumulator
{
public :
	typedef typename SubstitutionT::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
namespace iteration
{
/**
  @brief retrieves accumulator.
 */
template <
	typename ValueT,
	typename SubstitutionT
>
class GetAccumulator<ValueT, SubstitutionT, true_type>
{
public :
	typedef typename ValueT::accumulator type;
};
} // namespace iteration
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
namespace iteartion
{
} // namespace iteration
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
#endif // TMP_ITERATION_H_20140621195215494
// end of file
