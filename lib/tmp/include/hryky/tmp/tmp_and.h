/**
  @file     tmp_and.h
  @brief    retrieves the logical AND.
  @author   HRYKY
  @version  $Id: tmp_and.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_AND_H_20131223124330196
#define TMP_AND_H_20131223124330196
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
	/// retrieves the logical AND.
	template <hryky_template_param>
	class And;

	/// retrieves the logical AND with the concrete LHS value.
	template <hryky_template_param>
	class AndLhsImpl;

	/// retrieves the logical AND with the concrete RHS value.
	template <typename RhsT>
	class AndRhsImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the logical AND.
 */
template <hryky_template_param>
class hryky::tmp::And
{
public :
	typedef typename AndLhsImpl<
		typename LhsT::type, RhsT>::type type;
};
/**
  @brief retrieves the logical AND with the concrete LHS value.
 */
template <hryky_template_param>
class hryky::tmp::AndLhsImpl
{
public :
	typedef AndLhsImpl<hryky_template_arg> type;
};
/**
  @brief implements And<> for the actual types.
 */
template <typename RhsT>
class hryky::tmp::AndRhsImpl
{
public :
	typedef AndRhsImpl<RhsT> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  retrieves the logical AND between two booleans.
 */
template <typename RhsT>
class AndLhsImpl<true_type, RhsT>
{
public :
	typedef typename AndRhsImpl<
		typename RhsT::type>::type type;
};
/**
  short-circuits the evaluation of the RHS term.
 */
template <typename RhsT>
class AndLhsImpl<false_type, RhsT>
{
public :
	typedef false_type type;
};
/**
  retrieves the logical AND resulting in true.
 */
template <>
class AndRhsImpl<true_type>
{
public :
	typedef true_type type;
};
/**
  retrieves the logical AND resulting in false.
 */
template <>
class AndRhsImpl<false_type>
{
public :
	typedef false_type type;
};
/**
  propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<AndLhsImpl<hryky_template_arg> >
{
public :
	typedef typename And<Eval<LhsT>, Eval<RhsT> >::type type;
};
/**
  propagates the lazy evaluation.
 */
template <typename RhsT>
class EvalImpl<AndRhsImpl<RhsT> >
{
public :
	typedef typename And<true_type, Eval<RhsT> >::type type;
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
#endif // TMP_AND_H_20131223124330196
// end of file
