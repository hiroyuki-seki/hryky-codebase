/**
  @file     symbolic_computation_reduce_vector.h
  @brief    reduces the calculation about vector at compile-time.
  @author   HRYKY
  @version  $Id: symbolic_computation_reduce_vector.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_REDUCE_VECTOR_H_20131113191824471
#define SYMBOLIC_COMPUTATION_REDUCE_VECTOR_H_20131113191824471
#include "hryky/symbolic_computation/symbolic_computation_vector_binary_op.h"
#include "hryky/symbolic_computation/symbolic_computation_vector_unary_op.h"
#include "hryky/symbolic_computation/symbolic_computation_terminator.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	template <typename LhsT, typename RhsT>
	class Add;

	template <typename LhsT, typename RhsT>
	class AddImpl;

	template <typename LhsT, typename RhsT>
	class Sub;

	template <typename LhsT, typename RhsT>
	class SubtractImpl;

	template <typename ElementT, typename RestT, typename EvalT>
	class ReduceVector;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief reduces each element of vector.
 */
template <typename ElementT, typename RestT, typename EvalT>
class hryky::symbolic_computation::ReduceVector
{
private :
	typedef Reduce<ElementT> element;
	typedef Reduce<RestT> rest;
public :
	typedef typename ReduceIfC<
		element::value || rest::value,
		V<element, rest, EvalT> >::type type;
	static bool const value = element::value || rest::value;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief reduces each element of vector.
 */
template <typename ElementT, typename RestT, typename EvalT>
class ReduceImpl<VectorImpl<ElementT, RestT, EvalT> >
{
private :
	typedef ReduceVector<ElementT, RestT, EvalT> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief terminates the simplification of vector.
 */
template <>
class ReduceImpl<Terminator>
{
public :
	typedef Terminator type;
	static bool const value = false;
};
//------------------------------------------------------------------------------
// specializes the binary operation between two vectors.
//------------------------------------------------------------------------------
/**
  @brief calculates addition between two vectors.
 */
template <
	typename LhsElementT,
	typename LhsRestT,
	typename RhsElementT,
	typename RhsRestT,
	typename EvalT>
class ReduceImpl<
	AddImpl<
		VectorImpl<LhsElementT, LhsRestT, EvalT>,
		VectorImpl<RhsElementT, RhsRestT, EvalT>
	>
>
{
private :
	typedef Reduce<VectorImpl<LhsElementT, LhsRestT, EvalT> > lhs;
	typedef Reduce<VectorImpl<RhsElementT, RhsRestT, EvalT> > rhs;
public :
	typedef typename Reduce<VectorBinaryOp<
		lhs, rhs, Add, EvalT> >::type type;
	static bool const value = true;
};
/**
  @brief calculates subtraction between two vectors.
 */
template <
	typename LhsElementT,
	typename LhsRestT,
	typename RhsElementT,
	typename RhsRestT,
	typename EvalT>
class ReduceImpl<
	SubtractImpl<
		VectorImpl<LhsElementT, LhsRestT, EvalT>,
		VectorImpl<RhsElementT, RhsRestT, EvalT>
	>
>
{
private :
	typedef Reduce<VectorImpl<LhsElementT, LhsRestT, EvalT> > lhs;
	typedef Reduce<VectorImpl<RhsElementT, RhsRestT, EvalT> > rhs;
public :
	typedef typename Reduce<VectorBinaryOp<
		lhs, rhs, Sub, EvalT> >::type type;
	static bool const value = true;
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
#endif // SYMBOLIC_COMPUTATION_REDUCE_VECTOR_H_20131113191824471
// end of file
