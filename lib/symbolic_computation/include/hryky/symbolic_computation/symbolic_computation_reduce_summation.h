/**
  @file     symbolic_computation_reduce_summation.h
  @brief    reduces a summation.
  @author   HRYKY
  @version  $Id: symbolic_computation_reduce_summation.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_REDUCE_SUMMATION_H_20131123235810665
#define SYMBOLIC_COMPUTATION_REDUCE_SUMMATION_H_20131123235810665
#include "hryky/symbolic_computation/symbolic_computation_simplify.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename OpT, typename IndexT, typename FirstT, typename LastT
#define hryky_template_arg \
	OpT, IndexT, FirstT, LastT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	template <hryky_template_param>
	class Sum;
	
	template <hryky_template_param>
	class SummationImpl;

	template <typename TargetT, typename ForT, typename AlternativeT>
	class Substitute;

	template <typename OpT, typename IndexT, int First, int Last>
	class ExpandSum;

	template <typename LhsT, typename RhsT>
	class Add;

	template <typename EvalT, int Value>
	class Integer;
	
	template <hryky_template_param>
	class ReduceSum;
	
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief constrains the simplification for summation.
  */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceSum
{
private :
	typedef Reduce<OpT>       target;
	typedef Reduce<FirstT>    first;
	typedef Reduce<LastT>     last;
public :
	static bool const value = target::value || first::value || last::value;
	typedef typename ReduceIfC<
		value, Sum<target, IndexT, first, last> >::type type;
};
/**
  @brief creates summation as the sequence of addition.
 */
template <typename OpT, typename IndexT, int First, int Last>
class hryky::symbolic_computation::ExpandSum
{
	static_assert(
		First < Last,
		"variable of summation is over the maximum value.");
	
public :
	typedef typename Add<
		Substitute<OpT, IndexT, Integer<typename IndexT::eval_type, First> >,
		ExpandSum<OpT, IndexT, First + 1, Last>
	>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief constrains the simplification for summation.
 */
template <hryky_template_param>
class ReduceImpl<SummationImpl<hryky_template_arg> >
{
private :
	typedef ReduceSum<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief expands to additional operation if both first and last are constant.
 */
template <typename OpT, typename IndexT, typename EvalT, int First, int Last>
class ReduceSum<
	OpT, IndexT, Integer<EvalT, First>, Integer<EvalT, Last> >
{
private :
	typedef ExpandSum<OpT, IndexT, First, Last> impl;
public :
	typedef typename Reduce<impl>::type type;
	static bool const value = true;
};
/**
  @brief terminates the recursion of ExpandSum at the upper bound.
 */
template <typename OpT, typename IndexT, int Last>
class symbolic_computation::ExpandSum<OpT, IndexT, Last, Last>
{
public :
	typedef typename Substitute<
		OpT, IndexT, Integer<typename IndexT::eval_type, Last> >::type type;
};
} // namespace symbolic_computation
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
namespace symbolic_computation
{
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SYMBOLIC_COMPUTATION_REDUCE_SUMMATION_H_20131123235810665
// end of file
