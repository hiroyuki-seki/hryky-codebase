/**
  @file     tmp_concat.h
  @brief    concatenates two containers.
  @author   HRYKY
  @version  $Id: tmp_concat.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef TMP_CONCAT_H_20131223174443406
#define TMP_CONCAT_H_20131223174443406
#include "hryky/tmp/tmp_list.h"
#include "hryky/tmp/tmp_is_list.h"
#include "hryky/tmp/tmp_eval.h"
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
	/// concatenates two containers.
	template <hryky_template_param>
	class Concat;

	/// implements Concat<> for the actual types.
	template <hryky_template_param>
	class ConcatImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief concatenates two containers.
 */
template <hryky_template_param>
class hryky::tmp::Concat
{
public :
	typedef typename ConcatImpl<
		typename LhsT::type,
		typename RhsT::type>::type type;
};
/**
  @brief implements Concat<> for the actual types.
 */
template <hryky_template_param>
class hryky::tmp::ConcatImpl
{
	static_assert(
		IsList<LhsT>::type::value, "The LHS type has to be list.");
	static_assert(
		IsList<RhsT>::type::value, "The RHS type has to be list.");
	
public :
	typedef typename List<
		typename LhsT::first_type,
		typename ConcatImpl<typename LhsT::rest_type, RhsT>
	>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  concatenates the RHS list to the end of the LHS list.
 */
template <typename RhsT>
class ConcatImpl<null_list_type, RhsT>
{
public :
	typedef RhsT type;
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
#endif // TMP_CONCAT_H_20131223174443406
// end of file
