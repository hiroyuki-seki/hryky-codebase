/**
  @file     symbolic_computation_align.h
  @brief    sorts operations.
  @author   HRYKY
  @version  $Id: symbolic_computation_align.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_ALIGN_H_20131124203316523
#define SYMBOLIC_COMPUTATION_ALIGN_H_20131124203316523
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
	/// sorts operations.
	template <hryky_template_param>
	class Align;

	/// implements Align.
	template <hryky_template_param>
	class AlignImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief sorts operations.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Align :
	public WithStreamOut<Align<hryky_template_arg> >,
	public Evalable<
		Align<hryky_template_arg>, typename TargetT::type::eval_type>
{
public :
	typedef typename AlignImpl<typename TargetT::type>::type type;
};
/**
  @brief implements Align.
 */
template <hryky_template_param>
class hryky::symbolic_computation::AlignImpl
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
#endif // SYMBOLIC_COMPUTATION_ALIGN_H_20131124203316523
// end of file
