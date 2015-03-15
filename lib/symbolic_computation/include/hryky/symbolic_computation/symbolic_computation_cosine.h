/**
  @file     symbolic_computation_cosine.h
  @brief    operates a trigonometric cosine function.
  @author   HRYKY
  @version  $Id: symbolic_computation_cosine.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_COSINE_H_20131128143549274
#define SYMBOLIC_COMPUTATION_COSINE_H_20131128143549274
#include "hryky/symbolic_computation/symbolic_computation_align.h"
#include "hryky/symbolic_computation/symbolic_computation_evalable.h"
#include "hryky/symbolic_computation/symbolic_computation_gather.h"
#include "hryky/symbolic_computation/symbolic_computation_scatter.h"
#include "hryky/symbolic_computation/symbolic_computation_some.h"
#include "hryky/symbolic_computation/symbolic_computation_with_stream_out.h"
#include "hryky/symbolic_computation/symbolic_computation_substitute.h"
#include "hryky/cosine.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename AngleT, typename EvalT
#define hryky_template_arg \
	AngleT, EvalT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// The alias of Cosine.
	template <hryky_template_param>
	class Cos;

	/// operates a trigonometric cosine function.
	template <hryky_template_param>
	class Cosine;

	/// implements Cosine about the detailed factor.
	template <hryky_template_param>
	class CosineImpl;

	template <typename TermT>
	class Complement;

	template <hryky_template_param>
	class Sin;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The alias of Cosine.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Cos :
	public WithStreamOut<Cos<hryky_template_arg> >,
	public Evalable<Cos<hryky_template_arg>, EvalT>
{
public :
	typedef typename Cosine<typename AngleT::type, EvalT>::type type;
};
/**
  @brief operates a trigonometric cosine function.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Cosine :
	public WithStreamOut<Cosine<hryky_template_arg> >,
	public Evalable<Cosine<hryky_template_arg>, EvalT>
{
public :
	typedef typename CosineImpl<typename AngleT::type, EvalT>::type type;
};
/**
  @brief implements Cosine.
 */
template <hryky_template_param>
class hryky::symbolic_computation::CosineImpl :
	public hryky::WithStreamOut<CosineImpl<hryky_template_arg> >
{
public :
	typedef typename EvalT                  eval_type;
	typedef CosineImpl<hryky_template_arg>  type;
	typedef typename AngleT::type           angle_type;

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;
	
	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters)
	{
		return eval_type(hryky::cos(angle_type::eval(parameters)));
	}
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief simplifies to one.
 */
template <typename IntEvalT, typename EvalT>
class CosineImpl<Integer<IntEvalT, 0>, EvalT >
{
public :
	typedef typename Integer<EvalT, 1>::type type;
};
//------------------------------------------------------------------------------
// specializes other classes in respect to this class.
//------------------------------------------------------------------------------
/**
  @brief evaluates function through cosine.
 */
template <hryky_template_param, template <typename> class FunctionT>
class SomeImpl<CosineImpl<hryky_template_arg>, FunctionT>
{
public :
	typedef typename FunctionT<AngleT>::type type;
};
/**
  @brief substites operations in the angular operation.
 */
template <hryky_template_param, typename ForT, typename AlternativeT>
class SubstituteImpl<CosineImpl<hryky_template_arg>, ForT, AlternativeT>
{
private :
	typedef CosineImpl<hryky_template_arg> target;
public :
	typedef typename Cos<
		Substitute<typename target::angle_type, ForT, AlternativeT>, EvalT
	>::type type;
};
/**
  @brief distributes multiplications in the angular operation.
 */
template <hryky_template_param>
class ScatterImpl<CosineImpl<hryky_template_arg> >
{
public :
	typedef typename Cos<Scatter<AngleT>, EvalT>::type type;
};
/**
  @brief extracts multiplier in angular operation.
 */
template <hryky_template_param>
class GatherImpl<CosineImpl<hryky_template_arg> >
{
public :
	typedef typename Cos<Gather<AngleT>, EvalT>::type type;
};
/**
  @brief aligns operations in the angular operation.
 */
template <hryky_template_param>
class AlignImpl<CosineImpl<hryky_template_arg> >
{
public :
	typedef typename Cos<Align<AngleT>, EvalT>::type type;
};
/**
  @brief differentiates a trigonometric cosine function.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<CosineImpl<hryky_template_arg>, WrtT>
{
public :
	typedef typename Complement<Sin<hryky_template_arg> >::type type;
};
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief prints a trigonometric cosine function.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::CosineImpl<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out << "cos(" << angle_type() << ')';
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
#endif // SYMBOLIC_COMPUTATION_COSINE_H_20131128143549274
// end of file
