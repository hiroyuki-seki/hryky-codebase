/**
  @file     tmp_not.h
  @brief    inverts the boolean value.
  @author   HRYKY
  @version  $Id: tmp_not.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_NOT_H_20131222153104313
#define TMP_NOT_H_20131222153104313
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
	/// inverts the boolean value.
	template <hryky_template_param>
	class Not;

	/// implements Not<> for the actual type.
	template <hryky_template_param>
	class NotImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief inverts the boolean value.
 */
template <hryky_template_param>
class hryky::tmp::Not
{
public :
	typedef typename NotImpl<typename TermT::type>::type type;
};
/**
  @brief implements Not<> for the actual type.
 */
template <hryky_template_param>
class hryky::tmp::NotImpl
{
public :
	typedef NotImpl<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  retrieves the inverse of the boolean.
 */
template <bool Term>
class NotImpl<IntegralConstant<bool, Term> >
{
public :
	typedef typename IntegralConstant<bool, !Term> type;
};
/**
  propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<NotImpl<hryky_template_arg> >
{
public :
	typedef typename Not<Eval<TermT> >::type type;
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
#endif // TMP_NOT_H_20131222153104313
// end of file
