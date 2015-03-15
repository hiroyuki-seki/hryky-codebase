/**
  @file     tmp_push_front.h
  @brief    inserts a new value at the beginning of container.
  @author   HRYKY
  @version  $Id: tmp_push_front.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef TMP_PUSH_FRONT_H_20131219233125646
#define TMP_PUSH_FRONT_H_20131219233125646
#include "hryky/tmp/tmp_list.h"
#include "hryky/tmp/tmp_is_list.h"
#include "hryky/tmp/tmp_eval.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ListT, typename ValueT
#define hryky_template_arg \
	ListT, ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// inserts a new value at the beginning of container.
	template <hryky_template_param>
	class PushFront;

	/// implements PushFront<> for the actual type.
	template <hryky_template_param>
	class PushFrontImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief inserts a new value at the beginning of container.
 */
template <hryky_template_param>
class hryky::tmp::PushFront
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
public :
	typedef typename PushFrontImpl<
		typename ListT::type, typename ValueT::type>::type type;
};
/**
  @brief implements PushFront<> for the actual type.
 */
template <hryky_template_param>
class hryky::tmp::PushFrontImpl
{
public :
	typedef typename List<ValueT, ListT>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
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
#endif // TMP_PUSH_FRONT_H_20131219233125646
// end of file
