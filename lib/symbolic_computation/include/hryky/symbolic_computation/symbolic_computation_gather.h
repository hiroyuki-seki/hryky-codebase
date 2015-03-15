/**
  @file     symbolic_computation_gather.h
  @brief    collects up by same multiplication.
  @author   HRYKY
  @version  $Id: symbolic_computation_gather.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_GATHER_H_20131125231550635
#define SYMBOLIC_COMPUTATION_GATHER_H_20131125231550635
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
	/// collects up by same multiplication.
	template <hryky_template_param>
	class Gather;

	/// implements Gather.
	template <hryky_template_param>
	class GatherImpl;

	/// gathers the multiplier from target if the condition::value is true.
	template <
		typename ConditionT, typename TargetT, typename ElseT = TargetT>
	class GatherIf;

	/// gathers the multiplier from target if the condition is true.
	template <
		bool Condition, typename TargetT, typename ElseT = TargetT>
	class GatherIfC;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief collects up by same multiplication.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Gather :
	public WithStreamOut<Gather<hryky_template_arg> >,
	public Evalable<
		Gather<hryky_template_arg>, typename TargetT::type::eval_type >
{
public :
	typedef typename GatherImpl<typename TargetT::type>::type type;
};
/**
  @brief implements Gather.
 */
template <typename TargetT>
class hryky::symbolic_computation::GatherImpl
{
public :
	typedef TargetT type;
};
/**
  @brief gathers the multiplier from target if the condition::value is true.
 */
template <typename ConditionT, typename TargetT, typename ElseT>
class hryky::symbolic_computation::GatherIf
{
public :
	typedef typename GatherIfC<ConditionT::value, TargetT, ElseT>::type type;
};
/**
  @brief gathers the multiplier from target if the condition is true.
 */
template <bool Condition, typename TargetT, typename ElseT>
class hryky::symbolic_computation::GatherIfC
{
public :
	typedef typename ElseT::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief gathers the multiplier from target 
 */
template <typename TargetT, typename ElseT>
class GatherIfC<true, TargetT, ElseT>
{
public :
	typedef typename Gather<TargetT>::type type;
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
#endif // SYMBOLIC_COMPUTATION_GATHER_H_20131125231550635
// end of file
