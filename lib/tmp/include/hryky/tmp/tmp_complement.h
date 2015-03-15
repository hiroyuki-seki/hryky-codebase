/**
  @file     tmp_complement.h
  @brief    retrieves the complement of the term.
  @author   HRYKY
  @version  $Id: tmp_complement.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_COMPLEMENT_H_20131222152830311
#define TMP_COMPLEMENT_H_20131222152830311
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
	/// retrieves the complement of the term.
	template <hryky_template_param>
	class Complement;

	/// implements Complement<> for the actual type.
	template <hryky_template_param>
	class ComplementImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the complement of the term.
 */
template <hryky_template_param>
class hryky::tmp::Complement
{
public :
	typedef typename ComplementImpl<typename TermT::type>::type type;
};
/**
  @brief implements Complement<> for the actual type.
 */
template <hryky_template_param>
class hryky::tmp::ComplementImpl
{
public :
	typedef ComplementImpl<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  calculates the complement of the term.
 */
template <typename TermT, TermT Term>
class ComplementImpl<IntegralConstant<TermT, Term> >
{
public :
	typedef IntegralConstant<TermT, 0 - Term> type;
};
/**
  propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<ComplementImpl<hryky_template_arg> >
{
public :
	typedef typename Complement<Eval<TermT> >::type type;
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
#endif // TMP_COMPLEMENT_H_20131222152830311
// end of file
