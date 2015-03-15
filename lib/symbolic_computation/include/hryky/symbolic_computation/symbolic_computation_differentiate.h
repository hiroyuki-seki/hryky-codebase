/**
  @file     symbolic_computation_differentiate.h
  @brief    differentiates an operation.
  @author   HRYKY
  @version  $Id: symbolic_computation_differentiate.h 326 2014-02-11 06:30:44Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_DIFFERENTIATE_H_20131008220037583
#define SYMBOLIC_COMPUTATION_DIFFERENTIATE_H_20131008220037583
#include "hryky/symbolic_computation/symbolic_computation_with_stream_out.h"
#include "hryky/symbolic_computation/symbolic_computation_evalable.h"
#include "hryky/symbolic_computation/symbolic_computation_terminator.h"
#include "hryky/symbolic_computation/symbolic_computation_some.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TargetT, typename WrtT
#define hryky_template_arg \
	TargetT, WrtT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// The alias of Differentiate.
	template <hryky_template_param>
	class D;

	/// differentiates an operation.
	template <hryky_template_param>
	class Differentiate;

	/// differentiates an operation with specialization.
	template <hryky_template_param>
	class DifferentiateImpl;

	/// applies higher differentiation recursively.
	template <typename TargetT, typename DifferentiateT>
	class ApplyDifferentiate;

	/// represents a differential operator.
	template <typename WrtT>
	class Differentiator;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The alias of Differentiate.
 */
template <hryky_template_param>
class hryky::symbolic_computation::D :
	public WithStreamOut<D<hryky_template_arg> >,
	public Evalable<D<hryky_template_arg>, typename TargetT::type::eval_type>
{
private :
	typedef Differentiate<typename TargetT::type, typename WrtT::type> impl;
public :
	typedef typename impl::type type;
};
/**
  @brief differentiates an operation.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Differentiate :
	public WithStreamOut<Differentiate<hryky_template_arg> >,
	public Evalable<
		Differentiate<hryky_template_arg>, typename TargetT::type::eval_type>
{
private :
	typedef DifferentiateImpl<typename TargetT::type, typename WrtT::type> impl;
public :
	typedef typename impl::type type;
};
/**
  @brief differentiates an operation with specialization.
 */
template <hryky_template_param>
class hryky::symbolic_computation::DifferentiateImpl :
	public hryky::WithStreamOut<DifferentiateImpl<hryky_template_arg> >
{
public :
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const
	{
		return out << "d/d" << WrtT() << '(' << TargetT() << ')';
	}
};
/**
  @brief applies higher differentiation recursively.
 */
template <typename TargetT, typename DifferentiateT>
class hryky::symbolic_computation::ApplyDifferentiate
{
private :
	typedef typename DifferentiateT::wrt_type wrt;
	typedef typename DifferentiateT::target_type prev;
public :
	typedef typename D<
		typename ApplyDifferentiate<TargetT, prev>::type, wrt>::type type;
};
/**
  @brief represents a differential operator.
 */
template <typename WrtT>
class hryky::symbolic_computation::Differentiator :
	public WithStreamOut<Differentiator<WrtT> >,
	public Evalable<Differentiator<WrtT>, hryky::Null>
{
private :
	typedef D<Terminator, WrtT> impl;
public :
	typedef typename impl::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief creates a differential operator.
 */
template <typename WrtT>
class DifferentiateImpl<Terminator, WrtT> :
	public hryky::WithStreamOut<DifferentiateImpl<Terminator, WrtT> >
{
public :
	typedef DifferentiateImpl<Terminator, WrtT> type;
	typedef WrtT                                wrt_type;
	typedef Terminator                          target_type;
	typedef typename Terminator::eval_type      eval_type;

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const
	{
		return out << "d/d" << wrt_type();
	}
};
/**
  @brief applies higher differentiation.
 */
template <hryky_template_param, typename NextWrtT>
class DifferentiateImpl<DifferentiateImpl<hryky_template_arg>, NextWrtT> :
	public hryky::WithStreamOut<
		DifferentiateImpl<DifferentiateImpl<hryky_template_arg>, NextWrtT>
	>
{
private :
public :
	typedef DifferentiateImpl<hryky_template_arg>       target_type;
	typedef NextWrtT                                    wrt_type;
	typedef DifferentiateImpl<target_type, NextWrtT>    type;
	typedef typename target_type::eval_type             eval_type;

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const
	{
		return out << "d/d" << wrt_type() << '(' << target_type() << ')';
	}
};
/**
  @brief terminates higher differentiation.
 */
template <hryky_template_param>
class ApplyDifferentiate<TargetT, DifferentiateImpl<Terminator, WrtT> >
{
public :
	typedef typename D<TargetT, WrtT>::type type;
};
//------------------------------------------------------------------------------
// specializes other classes in respect to this class.
//------------------------------------------------------------------------------
/**
  @brief evaluates function through differentiation.
 */
template <hryky_template_param, template <typename> class FunctionT>
class SomeImpl<DifferentiateImpl<hryky_template_arg>, FunctionT>
{
public :
	typedef typename FunctionT<TargetT>::type type;
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
#endif // SYMBOLIC_COMPUTATION_DIFFERENTIATE_H_20131008220037583
// end of file
