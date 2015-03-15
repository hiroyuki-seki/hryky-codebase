/**
  @file     tmp_binary_laze.h
  @brief    delays a binary operation.
  @author   HRYKY
  @version  $Id: tmp_binary_laze.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef TMP_BINARY_LAZE_H_20131228224631615
#define TMP_BINARY_LAZE_H_20131228224631615
#include "hryky/tmp/tmp_eval.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	template <typename,typename> class OpT, typename LhsT, typename RhsT
#define hryky_template_arg \
	OpT, LhsT, RhsT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// delays a binary operation.
	template <hryky_template_param>
	class BinaryLaze;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief delays a binary operation.
 */
template <hryky_template_param>
class hryky::tmp::BinaryLaze
{
public :
	typedef BinaryLaze<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  evaluates the binary lazy operation.
 */
template <hryky_template_param>
class EvalImpl<BinaryLaze<hryky_template_arg> >
{
	typedef typename OpT<LhsT, RhsT>::type type;
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
#endif // TMP_BINARY_LAZE_H_20131228224631615
// end of file
