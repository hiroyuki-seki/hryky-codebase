/**
  @file     symbolic_computation_complement.h
  @brief    operates a complement.
  @author   HRYKY
  @version  $Id: symbolic_computation_complement.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_COMPLEMENT_H_20131010123355190
#define SYMBOLIC_COMPUTATION_COMPLEMENT_H_20131010123355190
#include "hryky/symbolic_computation/symbolic_computation_align.h"
#include "hryky/symbolic_computation/symbolic_computation_differentiate.h"
#include "hryky/symbolic_computation/symbolic_computation_evalable.h"
#include "hryky/symbolic_computation/symbolic_computation_gather.h"
#include "hryky/symbolic_computation/symbolic_computation_scatter.h"
#include "hryky/symbolic_computation/symbolic_computation_some.h"
#include "hryky/symbolic_computation/symbolic_computation_with_stream_out.h"
#include "hryky/symbolic_computation/symbolic_computation_substitute.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TermT
#define hryky_template_arg \
	TermT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// operates a complement.
	template <hryky_template_param>
	class Complement;

	/// operates a complement internally.
	template <hryky_template_param>
	class ComplementImpl;

	template <typename EvalT, int Value>
	class Integer;

	template <typename EvalT, int Dividend, int Divisor>
	class Fraction;

	template <typename EvalT, int Dividend, int Divisor>
	class FractionImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief operates a complement.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Complement :
	public WithStreamOut<Complement<hryky_template_arg> >,
	public Evalable<
		Complement<hryky_template_arg>,
		typename TermT::type::eval_type>
{
private :
	typedef ComplementImpl<typename TermT::type> impl;

public :
	typedef typename impl::type type;
};
/**
  @brief operates a complement internally.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ComplementImpl :
	public hryky::WithStreamOut<ComplementImpl<hryky_template_arg> >
{
public :
	typedef typename TermT::type                term_type;
	typedef ComplementImpl<hryky_template_arg>  type;

	typedef decltype(-(typename term_type::eval_type())) eval_type;

	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters)
	{
		return -term_type::eval(parameters);
	}

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief calculates the complement of integral value.
 */
template <typename EvalT, int Value>
class ComplementImpl<Integer<EvalT, Value> >
{
public :
	typedef typename Integer<EvalT, -Value>::type type;
};
/**
  @brief calculates the complement of fractional number.
 */
template <typename EvalT, int Dividend, int Divisor>
class ComplementImpl<FractionImpl<EvalT, Dividend, Divisor> >
{
public :
	typedef typename Fraction<EvalT, -Dividend, Divisor>::type type;
};
/**
  @brief cancels duplicated complement.
 */
template <hryky_template_param>
class ComplementImpl<ComplementImpl<ComplementImpl<TermT> > >
{
public :
	typedef typename TermT::type type;
};
//------------------------------------------------------------------------------
// specializes other classes in respect to this class.
//------------------------------------------------------------------------------
/**
  @brief evaluates function through complement.
 */
template <hryky_template_param, template <typename> class FunctionT>
class SomeImpl<ComplementImpl<hryky_template_arg>, FunctionT>
{
public :
	typedef typename FunctionT<TermT>::type type;
};
/**
  @brief Complement can be divided if the term can be divided.
 */
template <hryky_template_param, typename WrtT>
class DividableImpl<ComplementImpl<hryky_template_arg>, WrtT>
{
private :
	typedef Dividable<TermT, WrtT> term;
public :
	typedef typename ConditionalC<
		term::value,
		typename Complement<term>::type,
		typename Complement<TermT>::type
	>::type type;
	static bool const value = term::value;
};
/**
  @brief substitutes an operation in the term.
 */
template <hryky_template_param, typename ForT, typename AlternativeT>
class SubstituteImpl<ComplementImpl<hryky_template_arg>, ForT, AlternativeT>
{
public :
	typedef typename Complement<
		Substitute<TermT, ForT, AlternativeT> >::type type;
};
/**
  @brief differentiates a complementary operation.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<ComplementImpl<hryky_template_arg>, WrtT>
{
private :
	typedef ComplementImpl<hryky_template_arg> target;
public :
	typedef typename Complement<
		D<typename target::term_type, WrtT>
	>::type type;
};
/**
  @brief distributes multiplications in the term.
 */
template <hryky_template_param>
class ScatterImpl<ComplementImpl<hryky_template_arg> >
{
public :
	typedef typename Complement<Scatter<TermT> >::type type;
};
/**
  @brief extracts multiplier in the term.
 */
template <hryky_template_param>
class GatherImpl<ComplementImpl<hryky_template_arg> >
{
public :
	typedef typename Complement<Gather<TermT> >::type type;
};
/**
  @brief aligns operations in the term.
 */
template <hryky_template_param>
class AlignImpl<ComplementImpl<hryky_template_arg> >
{
public :
	typedef typename Complement<Align<TermT> >::type type;
};
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief prints a complementary operation.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::ComplementImpl<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out << '-' << term_type();
}
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
#endif // SYMBOLIC_COMPUTATION_COMPLEMENT_H_20131010123355190
// end of file
