/**
  @file     tmp_unary_laze.h
  @brief    delays an unary operation.
  @author   HRYKY
  @version  $Id: tmp_unary_laze.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_UNARY_LAZE_H_20131228230318627
#define TMP_UNARY_LAZE_H_20131228230318627
#include "hryky/tmp/tmp_eval.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	template <typename> class OpT, typename TermT
#define hryky_template_arg \
	OpT, TermT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// delays an unary operation.
	template <hryky_template_param>
	class UnaryLaze;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief delays an unary operation.
 */
template <hryky_template_param>
class hryky::tmp::UnaryLaze
{
public :
	typedef UnaryLaze<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  evaluates the unary operation.
 */
template <hryky_template_param>
class EvalImpl<UnaryLaze<hryky_template_arg> >
{
public :
	typedef typename OpT<TermT>::type type;
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
#endif // TMP_UNARY_LAZE_H_20131228230318627
// end of file
