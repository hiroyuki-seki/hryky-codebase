/**
  @file     symbolic_computation_some.h
  @brief    ends the traverse if the value of function is true.
  @author   HRYKY
  @version  $Id: symbolic_computation_some.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_SOME_H_20131201140718255
#define SYMBOLIC_COMPUTATION_SOME_H_20131201140718255
#include "hryky/symbolic_computation/symbolic_computation_sequence.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	template <typename> class OpT
#define hryky_template_arg \
	OpT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	template <typename T1, hryky_template_param>
	class Some;

	/// ends the traverse if the value of function is true.
	template <typename T1, typename T2, hryky_template_param>
	class Some2;

	template <
		typename T1, typename T2, typename T3, typename T4,
		hryky_template_param
	>
	class Some4;

	/// implements Some.
	template <typename TargetT, hryky_template_param>
	class SomeImpl;

	/**
	  @brief evaluate if condition is true.
	 */
	template <
		typename ConditionT,
		typename TargetT,
		hryky_template_param,
		bool Condition = ConditionT::value
	>
	class SomeIf;

	/// evaluate an unary operation if constant is true.
	template <
		typename ConditionT,
		typename FirstT,
		typename RestT,
		hryky_template_param,
		bool Condition = ConditionT::value
	>
	class SomeFirst;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief ends the traverse if the value of function is true.
 */
template <typename T1, hryky_template_param>
class hryky::symbolic_computation::Some
{
public :
	typedef typename SomeImpl<T1, OpT>::type type;
};
/**
  @brief ends the traverse if the value of function is true.
 */
template <typename T1, typename T2, hryky_template_param>
class hryky::symbolic_computation::Some2
{
public :
	typedef typename Some<Sequence<T1, T2>, OpT>::type type;
};
/**
  @brief ends the traverse if the value of function is true.
 */
template <
	typename T1, typename T2, typename T3, typename T4,
	hryky_template_param
>
class hryky::symbolic_computation::Some4
{
public :
	typedef typename Some<
		Sequence<T1, Sequence<T2, Sequence<T3, T4> > >, OpT>::type type;
};
/**
  @brief implements Some.
 */
template <typename TargetT, hryky_template_param>
class hryky::symbolic_computation::SomeImpl
{
public :
	typedef typename OpT<TargetT>::type type;
};
/**
  @brief evaluate if condition is true.
 */
template <
	typename ConditionT,
	typename TargetT,
	hryky_template_param,
	bool Condition
>
class hryky::symbolic_computation::SomeIf
{
public :
	typedef typename Some<TargetT, OpT>::type type;
};
/**
  @brief evaluate an unary operation if constant is true.
 */
template <
	typename ConditionT,
	typename FirstT,
	typename RestT,
	hryky_template_param,
	bool Condition
>
class hryky::symbolic_computation::SomeFirst
{
private :
	typedef typename Some<FirstT, OpT>::type first;
public :
	typedef typename SomeIf<first, RestT, OpT>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief evaluates terms until the result is true.
 */
template <
	typename FirstT,
	typename RestT,
	template <typename> class OpT
>
class SomeImpl<Sequence<FirstT, RestT>, OpT>
{
private :
	typedef typename OpT<FirstT>::type first;
public :
	typedef typename SomeFirst<first, FirstT, RestT, OpT>::type type;
	static bool const value = type::value;
};
/**
  @brief cuts the following evaluations.
 */
template <
	typename ConditionT,
	typename FirstT,
	typename RestT,
	hryky_template_param
>
class SomeFirst<ConditionT, FirstT, RestT, OpT, true>
{
public :
	typedef typename ConditionT::type type;
};
/**
  @brief cuts the following evaluations.
 */
template <
	typename ConditionT,
	typename TargetT,
	hryky_template_param
>
class SomeIf<ConditionT, TargetT, OpT, true>
{
public :
	typedef typename ConditionT::type type;
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
#endif // SYMBOLIC_COMPUTATION_SOME_H_20131201140718255
// end of file
