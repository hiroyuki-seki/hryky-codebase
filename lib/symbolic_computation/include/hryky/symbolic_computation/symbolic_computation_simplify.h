/**
  @file     symbolic_computation_simplify.h
  @brief    simplifies operations.
  @author   HRYKY
  @version  $Id: symbolic_computation_simplify.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_SIMPLIFY_H_20131114220012583
#define SYMBOLIC_COMPUTATION_SIMPLIFY_H_20131114220012583
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
	template <typename TargetT>
	class Scatter;

	template <typename TargetT>
	class Align;

	template <typename TargetT>
	class Reduce;

	/// simplifies operations.
	template <hryky_template_param>
	class Simplify;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief simplifies operations.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Simplify :
	public WithStreamOut<Simplify<hryky_template_arg> >,
	public Evalable<
		Simplify<hryky_template_arg>,
		typename TargetT::type::eval_type>
{
public :
	typedef typename Reduce<Align<Scatter<TargetT> > >::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
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
#endif // SYMBOLIC_COMPUTATION_SIMPLIFY_H_20131114220012583
// end of file
