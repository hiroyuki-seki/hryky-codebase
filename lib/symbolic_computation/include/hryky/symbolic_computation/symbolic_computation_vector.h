/**
  @file     symbolic_computation_vector.h
  @brief    represents a vector.
  @author   HRYKY
  @version  $Id: symbolic_computation_vector.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_VECTOR_H_20131109225905624
#define SYMBOLIC_COMPUTATION_VECTOR_H_20131109225905624
#include "hryky/tmp/null.h"
#include "hryky/symbolic_computation/symbolic_computation_align.h"
#include "hryky/symbolic_computation/symbolic_computation_dividable.h"
#include "hryky/symbolic_computation/symbolic_computation_gather.h"
#include "hryky/symbolic_computation/symbolic_computation_is_zero_vector.h"
#include "hryky/symbolic_computation/symbolic_computation_scatter.h"
#include "hryky/symbolic_computation/symbolic_computation_substitute.h"
#include "hryky/symbolic_computation/symbolic_computation_terminator.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ElementT, typename RestT, typename EvalT
#define hryky_template_arg \
	ElementT, RestT, EvalT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// facilitates Vector having three elements.
	template <
		typename E1T, typename E2T, typename E3T, typename EvalT
	>
	class Vector3;

	/// alises Vector.
	template <
		typename ElementT,
		typename RestT = Terminator,
		typename EvalT = hryky::Null
	>
	class V;

	/// represents a vector.
	template <
		typename ElementT,
		typename RestT = Terminator,
		typename EvalT = hryky::Null
	>
	class Vector;

	/// implements Vector.
	template <hryky_template_param>
	class VectorImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief facilitates Vector having three elements.
 */
template <
	typename E1T, typename E2T, typename E3T, typename EvalT
>
class hryky::symbolic_computation::Vector3 :
	public WithStreamOut<Vector3<E1T, E2T, E3T, EvalT> >,
	public Evalable<Vector3<E1T, E2T, E3T, EvalT>, EvalT>
{
private :
	typedef V<E1T, V<E2T, V<E3T> >, EvalT> impl;
public :
	typedef typename impl::type type;
};
/**
  @brief The alias of Vector.
 */
template <hryky_template_param>
class hryky::symbolic_computation::V :
	public WithStreamOut<V<hryky_template_arg> >,
	public Evalable<V<hryky_template_arg>, EvalT>
{
private :
	typedef Vector<
		typename ElementT::type, typename RestT::type, EvalT> impl;
public :
	typedef typename impl::type type;
};
/**
  @brief represents a vector.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Vector :
	public WithStreamOut<Vector<hryky_template_arg> >,
	public Evalable<Vector<hryky_template_arg>, EvalT>
{
private :
	typedef VectorImpl<
		typename ElementT::type, typename RestT::type, EvalT> impl;
public :
	typedef typename impl::type type;
};
/**
  @brief implements Vector.
 */
template <hryky_template_param>
class hryky::symbolic_computation::VectorImpl :
	public hryky::WithStreamOut<VectorImpl<hryky_template_arg> >
{
public :
	typedef EvalT                           eval_type;
	typedef typename ElementT::type         element_type;
	typedef typename RestT::type            rest_type;
	typedef VectorImpl<hryky_template_arg>  type;

	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters)
	{
		eval_type ret;
		eval<ParametersT, 0>(parameters, ret);
		return ret;
	}

	template <typename ParametersT, size_t Offset, typename PartEvalT>
	static void eval(ParametersT const & parameters, PartEvalT & ret)
	{
		ret[Offset] = element_type::eval(parameters);
		rest_type::eval<ParametersT, Offset + 1>(parameters, ret);
	}

	template <typename StreamT>
	static StreamT & write_element_to(StreamT & dest)
	{
		dest << element_type() << ',';
		return rest_type::write_element_to(dest);
	}
	
	template <typename StreamT>
	StreamT & write_to(StreamT & dest) const
	{
		dest << '(';
		return write_element_to(dest);
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
  terminates VectorImpl.
 */
template <typename ElementT, typename EvalT>
class VectorImpl<ElementT, Terminator, EvalT> :
	public hryky::WithStreamOut<VectorImpl<ElementT, Terminator, EvalT> >
{
public :
	typedef EvalT                           eval_type;
	typedef typename ElementT::type         element_type;
	typedef typename Terminator::type   rest_type;
	
	typedef VectorImpl<element_type, rest_type, EvalT> type;

	template <typename ParametersT>
	static eval_type eval(ParametersT const & parameters)
	{
		eval_type ret;
		eval<0>(parameters, ret);
		return ret;
	}

	template <typename ParametersT, size_t Offset, typename PartEvalT>
	static void eval(ParametersT const & parameters, PartEvalT & ret)
	{
		ret[Offset] = element_type::eval(parameters);
	}

	template <typename StreamT>
	static StreamT & write_element_to(StreamT & dest)
	{
		dest << element_type() << ')';
		return dest;
	}
	
	template <typename StreamT>
	StreamT & write_to(StreamT & dest) const
	{
		dest << '(';
		return write_element_to(dest);
	}
};
//------------------------------------------------------------------------------
// specializes other class in respect to this class.
//------------------------------------------------------------------------------
/**
  @brief evaluates vector until the function succeed.
 */
template <hryky_template_param, template <typename> class FunctionT>
class SomeImpl<VectorImpl<hryky_template_arg>, FunctionT>
{
public :
	typedef typename Some2<ElementT, RestT, FunctionT>::type type;
};
/**
  @brief confirms whether all elements can be divided.
 */
template <hryky_template_param, typename WrtT>
class DividableImpl<VectorImpl<hryky_template_arg>, WrtT>
{
private :
	typedef Dividable<ElementT, WrtT> element;
	typedef Dividable<RestT, WrtT> rest;
public :
	typedef typename V<element, rest, EvalT>::type type;
	static bool const value = element::value && rest::value;
};
/**
  @brief substitutes an element of Vector.
 */
template <hryky_template_param, typename ForT, typename AlternativeT>
class SubstituteImpl<VectorImpl<hryky_template_arg>, ForT, AlternativeT>
{
private :
	typedef VectorImpl<hryky_template_arg> target;
public :
	typedef typename V<
		Substitute<typename target::element_type, ForT, AlternativeT>,
		Substitute<typename target::rest_type, ForT, AlternativeT>,
		EvalT
	>::type type;
};
/**
  @brief distributes multiplications in all elements.
 */
template <hryky_template_param>
class ScatterImpl<VectorImpl<hryky_template_arg> >
{
public :
	typedef typename V<Scatter<ElementT>, Scatter<RestT>, EvalT>::type type;
};
/**
  @brief extracts multiplier in all elements.
 */
template <hryky_template_param>
class GatherImpl<VectorImpl<hryky_template_arg> >
{
public :
	typedef typename V<Gather<ElementT>, Gather<RestT>, EvalT>::type type;
};
/**
  @brief aligns operations in all elements.
 */
template <hryky_template_param>
class AlignImpl<VectorImpl<hryky_template_arg> >
{
public :
	typedef typename V<Align<ElementT>, Align<RestT>, EvalT>::type type;
};
//------------------------------------------------------------------------------
// differentiates an operation
//------------------------------------------------------------------------------
/**
  @brief differentiates each element of Vector.
 */
template <hryky_template_param, typename WrtT>
class DifferentiateImpl<VectorImpl<hryky_template_arg>, WrtT>
{
private :
	typedef VectorImpl<hryky_template_arg> target;
public :
	typedef typename V<
		D<typename target::element_type, WrtT>,
		D<typename target::rest_type, WrtT>,
		EvalT
	>::type type;
};
/**
  @brief differentiates each element of terminal Vector.
 */
template <typename ElementT, typename EvalT, typename WrtT>
class DifferentiateImpl<VectorImpl<ElementT, Terminator, EvalT>, WrtT>
{
private :
	typedef VectorImpl<ElementT, Terminator, EvalT> target;
public :
	typedef typename V<
		D<typename target::element_type, WrtT>,
		Terminator,
		EvalT
	>::type type;
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
#endif // SYMBOLIC_COMPUTATION_VECTOR_H_20131109225905624
// end of file
