/**
  @file     symbolic_computation_scatter.h
  @brief    unfolds a multiplication to addtions.
  @author   HRYKY
  @version  $Id: symbolic_computation_scatter.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_SCATTER_H_20131124150711296
#define SYMBOLIC_COMPUTATION_SCATTER_H_20131124150711296
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
	/// unfolds a multiplication to addtions.
	template <hryky_template_param>
	class Scatter;

	/// implements Scatter.
	template <hryky_template_param>
	class ScatterImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief unfolds a multiplication to addtions.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Scatter :
	public WithStreamOut<Scatter<hryky_template_arg> >,
	public Evalable<
		Scatter<hryky_template_arg>, typename TargetT::type::eval_type>
{
private :
	typedef ScatterImpl<typename TargetT::type> impl;
public :
	typedef typename impl::type type;
};
/**
  @brief implements Scatter.
 */
template <hryky_template_param>
class hryky::symbolic_computation::ScatterImpl
{
public :
	typedef TargetT type;
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
#endif // SYMBOLIC_COMPUTATION_SCATTER_H_20131124150711296
// end of file
