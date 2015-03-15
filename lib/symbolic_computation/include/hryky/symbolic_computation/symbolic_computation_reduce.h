/**
  @file     symbolic_computation_reduce.h
  @brief    reduces the number of operations.
  @author   HRYKY
  @version  $Id: symbolic_computation_reduce.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_REDUCE_H_20131128104510114
#define SYMBOLIC_COMPUTATION_REDUCE_H_20131128104510114
#include "hryky/symbolic_computation/symbolic_computation_evalable.h"
#include "hryky/symbolic_computation/symbolic_computation_with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TargetT
#define hryky_template_arg \
	TargetT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// reduces the number of operations.
	template <hryky_template_param>
	class Reduce;

	/// applies Reduce<> to the actual type.
	template <hryky_template_param>
	class ReduceImpl;

	/// reduces if the CondT has true.
	template <
		typename CondT,
		typename TargetT,
		typename ElseT = TargetT
	>
	class ReduceIf;

	/// reduces if the condition is true.
	template <
		bool Cond,
		typename TargetT,
		typename ElseT = TargetT
	>
	class ReduceIfC;

	/// reduces a binary operation.
	template <
		typename LhsT,
		typename RhsT,
		template <typename,typename> class OpT
	>
	class ReduceBinary;

	/// reduces an unary operation.
	template <
		typename TermT,
		template <typename> class OpT
	>
	class ReduceUnary;

	template <typename TermT>
	class IsAtom;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief reduces the number of operations.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Reduce :
	public WithStreamOut<Reduce<hryky_template_arg> >,
	public Evalable<
		Reduce<hryky_template_arg>, typename TargetT::type::eval_type>
{
private :
	typedef ReduceImpl<typename TargetT::type> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief applies Reduce<> to the actual type.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ReduceImpl
{
public :
	typedef typename TargetT::type type;
	static bool const value = false;
};
/**
  @brief reduces if the CondT has true.
 */
template <typename CondT, typename TargetT, typename ElseT>
class hryky::symbolic_computation::ReduceIf
{
private :
	typedef ReduceIfC<CondT::value, TargetT, ElseT> impl;
public :
	typedef typename impl::type type;
};
/**
  @brief reduces if the condition is true.
 */
template <bool Cond, typename TargetT, typename ElseT>
class hryky::symbolic_computation::ReduceIfC
{
public :
	typedef typename ElseT::type type;
};
/**
  @brief reduces a binary operation.
 */
template <
	typename LhsT,
	typename RhsT,
	template <typename,typename> class OpT
>
class hryky::symbolic_computation::ReduceBinary
{
private :
	typedef Reduce<OpT<LhsT, RhsT> > impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value || IsAtom<type>::value;
};
/**
  @brief reduces an unary operation.
 */
template <
	typename TermT,
	template <typename> class OpT
>
class hryky::symbolic_computation::ReduceUnary
{
private :
	typedef Reduce<OpT<TermT> > impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value || IsNumeric<type>::value;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief reduces target.

   Conditional<> or EnableIf<> can not be used if the TargetT is not
  simplified. A template paramater is evaluated even if the condition is
  false. The evaluation of the type which is not simplified causes recusive
  evaluation.
 */
template <typename TargetT, typename ElseT>
class ReduceIfC<true, TargetT, ElseT>
{
public :
	typedef typename Reduce<TargetT>::type type;
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
#endif // SYMBOLIC_COMPUTATION_REDUCE_H_20131128104510114
// end of file
