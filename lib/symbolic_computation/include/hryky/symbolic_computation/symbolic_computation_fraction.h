/**
  @file     symbolic_computation_fraction.h
  @brief    retrieves a fraction at compile-time.
  @author   HRYKY
  @version  $Id: symbolic_computation_fraction.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_FRACTION_H_20131020215452579
#define SYMBOLIC_COMPUTATION_FRACTION_H_20131020215452579
#include "hryky/symbolic_computation/symbolic_computation_differentiate.h"
#include "hryky/symbolic_computation/symbolic_computation_evalable.h"
#include "hryky/symbolic_computation/symbolic_computation_with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename EvalT, int Dividend, int Divisor
#define hryky_template_arg \
	EvalT, Dividend, Divisor
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// retrieves a fraction at compile-time.
	template <hryky_template_param>
	class Fraction;

	/// specializes division in regard to Dividend.
	template <hryky_template_param>
	class FractionDividend;

	/// specializes division in regard to Divisor.
	template <hryky_template_param>
	class FractionDivisor;

	/// retrieves a fraction at compile-time.
	template <hryky_template_param>
	class FractionImpl;

	template <typename EvalT, int Value>
	class Integer;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves a fraction at compile-time.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Fraction :
	public WithStreamOut<Fraction<hryky_template_arg> >,
	public Evalable<Fraction<hryky_template_arg>, EvalT >
{
public :
	typedef typename FractionDividend<hryky_template_arg>::type type;
};
/**
  @brief specializes division in regard to Dividend.
 */
template <hryky_template_param>
class hryky::symbolic_computation::FractionDividend
{
public :
	typedef typename FractionDivisor<hryky_template_arg>::type type;
};
/**
  @brief specializes division in regard to Divisor.
 */
template <hryky_template_param>
class hryky::symbolic_computation::FractionDivisor
{
public :
	typedef typename FractionImpl<hryky_template_arg>::type type;
};
/**
  @brief retrieves a fraction at compile-time.
 */
template <hryky_template_param>
class hryky::symbolic_computation::FractionImpl :
	public hryky::WithStreamOut<FractionImpl<hryky_template_arg> >
{
public :
	typedef EvalT                               eval_type;
	typedef FractionImpl<hryky_template_arg>    type;

	template <typename ParametersT>
	static eval_type eval(ParametersT const &)
	{
		return eval_type(value);
	}

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;
	
private :
	static eval_type const value;
};
template <hryky_template_param>
EvalT const
hryky::symbolic_computation::FractionImpl<hryky_template_arg>::value = (
	EvalT(Dividend) / Divisor);
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief reduces to zero.
 */
template <typename EvalT, int Divisor>
class FractionDividend<EvalT, 0, Divisor>
{
public :
	typedef typename Integer<EvalT, 0>::type type;
};
/**
  @brief reduces to only dividend.
 */
template <typename EvalT, int Dividend>
class FractionDivisor<EvalT, Dividend, 1>
{
public :
	typedef typename Integer<EvalT, Dividend>::type type;
};
/**
  @brief inverses the sign of the dividend.
 */
template <typename EvalT, int Dividend>
class FractionDivisor<EvalT, Dividend, -1>
{
public :
	typedef typename Integer<EvalT, -Dividend>::type type;
};
/**
  @brief divides by integer.
 */
template <hryky_template_param, int Wrt>
class DividableImpl<FractionImpl<hryky_template_arg>, Integer<EvalT, Wrt> >
{
public :
	static bool const value = true;
	typedef typename Fraction<EvalT, Dividend, Divisor * Wrt>::type type;
};
/**
  @brief divides by other fraction.
 */
template <hryky_template_param, int WrtDividend, int WrtDivisor>
class DividableImpl<
	FractionImpl<hryky_template_arg>,
	FractionImpl<EvalT, WrtDividend, WrtDivisor>
>
{
public :
	static bool const value = true;
	typedef typename Fraction<
		EvalT, Dividend * WrtDivisor, Divisor * WrtDividend>::type type;
};
/**
  @brief differentiates to zero.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<FractionImpl<hryky_template_arg>, WrtT>
{
public :
	typedef typename Integer<EvalT, 0>::type type;
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
/**
  @brief prints a fraction.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::FractionImpl<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out << "(" << Dividend << "/" << Divisor << ")";
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SYMBOLIC_COMPUTATION_FRACTION_H_20131020215452579
// end of file
