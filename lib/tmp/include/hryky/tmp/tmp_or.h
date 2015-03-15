/**
  @file     tmp_or.h
  @brief    retrieves the logical OR.
  @author   HRYKY
  @version  $Id: tmp_or.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_OR_H_20131223124750199
#define TMP_OR_H_20131223124750199
#include "hryky/tmp/tmp_eval.h"
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename LhsT, typename RhsT
#define hryky_template_arg \
	LhsT, RhsT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// retrieves the logical OR.
	template <hryky_template_param>
	class Or;

	/// implements Or<> for the actual types.
	template <hryky_template_param>
	class OrImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the logical OR.
 */
template <hryky_template_param>
class hryky::tmp::Or
{
public :
	typedef typename OrImpl<
		typename LhsT::type, typename RhsT::type>::type type;
};
/**
  @brief implements Or<> for the actual types.
 */
template <hryky_template_param>
class hryky::tmp::OrImpl
{
public :
	typedef OrImpl<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  retrieves the logical OR between two booleans.
 */
template <typename RhsT>
class OrImpl<false_type, RhsT>
{
public :
	typedef typename RhsT::type type;
};
/**
  short-circuits the evaluation of the RHS term.
 */
template <typename RhsT>
class OrImpl<true_type, RhsT>
{
public :
	typedef true_type type;
};
/**
  propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<OrImpl<hryky_template_arg> >
{
public :
	typedef typename Or<Eval<LhsT>, Eval<RhsT> >::type type;
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
#endif // TMP_OR_H_20131223124750199
// end of file
