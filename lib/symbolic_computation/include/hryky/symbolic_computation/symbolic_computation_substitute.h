/**
  @file     symbolic_computation_substitute.h
  @brief    substitutes an operation.
  @author   HRYKY
  @version  $Id: symbolic_computation_substitute.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_SUBSTITUTE_H_20131123144954284
#define SYMBOLIC_COMPUTATION_SUBSTITUTE_H_20131123144954284
#include "hryky/symbolic_computation/symbolic_computation_evalable.h"
#include "hryky/symbolic_computation/symbolic_computation_with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TargetT, typename ForT, typename AlternativeT
#define hryky_template_arg \
	TargetT, ForT, AlternativeT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// substitutes an operation.
	template <hryky_template_param>
	class Substitute;

	/// replaces the type same to ForT.
	template <hryky_template_param>
	class SubstituteSame;

	/// implement Substitute.
	template <hryky_template_param>
	class SubstituteImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief substitutes an operation.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Substitute :
	public WithStreamOut<Substitute<hryky_template_arg> >,
	public Evalable<
		Substitute<hryky_template_arg>, typename TargetT::type::eval_type >
{
private :
	typedef SubstituteSame<
		typename TargetT::type,
		typename ForT::type,
		typename AlternativeT::type> impl;
public :
	typedef typename impl::type type;
};
/**
  @brief constrains the specialization for same type.
 */
template <hryky_template_param>
class hryky::symbolic_computation::SubstituteSame
{
private :
	typedef SubstituteImpl<hryky_template_arg> impl;
public :
	typedef typename impl::type type;
};
/**
  @brief implements Substitute.
 */
template <hryky_template_param>
class hryky::symbolic_computation::SubstituteImpl
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
/**
  @brief substitutes the alternative for the operation itself.
 */
template <typename TargetT, typename AlternativeT>
class SubstituteSame<TargetT, TargetT, AlternativeT>
{
public :
	typedef AlternativeT type;
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
#endif // SYMBOLIC_COMPUTATION_SUBSTITUTE_H_20131123144954284
// end of file
