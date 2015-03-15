/**
  @file     tmp_increment.h
  @brief    increments a value.
  @author   HRYKY
  @version  $Id: tmp_increment.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_INCREMENT_H_20131217225925624
#define TMP_INCREMENT_H_20131217225925624
#include "hryky/tmp/tmp_eval.h"
#include "hryky/type_traits/integral_constant.h"
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
namespace tmp
{
	/// increments a value.
	template <hryky_template_param>
	class Increment;

	/// implements Increment with respect to the actual type.
	template <hryky_template_param>
	class IncrementImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief increments a value.
 */
template <hryky_template_param>
class hryky::tmp::Increment
{
public :
	typedef typename IncrementImpl<typename TermT::type>::type type;
};
/**
  @brief implements Increment with respect to the actual type.
 */
template <hryky_template_param>
class hryky::tmp::IncrementImpl
{
public :
	typedef IncrementImpl<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  increments an integral value.
 */
template <typename ValueT, ValueT Value>
class IncrementImpl<IntegralConstant<ValueT, Value> >
{
public :
	typedef IntegralConstant<ValueT, Value + 1> type;
};
/**
  propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<IncrementImpl<hryky_template_arg> >
{
public :
	typedef typename Increment<Eval<TermT> >::type type;
};
} // namespace tmp
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
namespace tmp
{
} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // TMP_INCREMENT_H_20131217225925624
// end of file
