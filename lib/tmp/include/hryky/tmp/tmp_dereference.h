/**
  @file     tmp_dereference.h
  @brief    dereferences an iterator.
  @author   HRYKY
  @version  $Id: tmp_dereference.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_DEREFERENCE_H_20131216224149612
#define TMP_DEREFERENCE_H_20131216224149612
#include "hryky/tmp/tmp_eval.h"
#include "hryky/tmp/tmp_unary_laze.h"
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
	/// dereferences a term lazily.
	template <hryky_template_param>
	class DereferenceLazily;

	/// dereferences an iterator.
	template <hryky_template_param>
	class Dereference;

	/// implements Dereference<> for the actual type.
	template <hryky_template_param>
	class DereferenceImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief dereferences a term lazily.
 */
template <hryky_template_param>
class hryky::tmp::DereferenceLazily
{
public :
	typedef typename UnaryLaze<Dereference, TermT>::type type;
};
/**
  @brief dereferences an iterator.
 */
template <hryky_template_param>
class hryky::tmp::Dereference
{
public :
	typedef typename DereferenceImpl<typename TermT::type>::type type;
};
/**
  @brief implements Dereference<> for the actual type.

  This class is implemented by specialization at each dereferenced type.
 */
template <hryky_template_param>
class hryky::tmp::DereferenceImpl
{
public :
	typedef DereferenceImpl<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<DereferenceImpl<hryky_template_arg> >
{
public :
	typedef typename Dereference<Eval<TermT> >::type type;
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
#endif // TMP_DEREFERENCE_H_20131216224149612
// end of file
