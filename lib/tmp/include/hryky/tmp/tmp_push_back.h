/**
  @file     tmp_push_back.h
  @brief    inserts a new value at the end of container.
  @author   HRYKY
  @version  $Id: tmp_push_back.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef TMP_PUSH_BACK_H_20131219071425968
#define TMP_PUSH_BACK_H_20131219071425968
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
	/// inserts a new value at the end of container.
	template <hryky_template_param>
	class PushBack;

	/// implements PushBack<> for detailed type.
	template <hryky_template_param>
	class PushBackImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief inserts a new value at the end of container.
 */
template <hryky_template_param>
class hryky::tmp::PushBack
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
public :
	typedef typename PushBackImpl<
		typename ListT::type, typename ValueT::type>::type type;
};
/**
  @brief implements PushBack<> for detailed type.
 */
template <hryky_template_param>
class hryky::tmp::PushBackImpl
{
public :
	typedef typename List<
		typename ListT::first_type,
		PushBackImpl<typename ListT::rest_type, ValueT>
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
  @brief terminates PushBackImpl
 */
template <typename ValueT>
class PushBackImpl<null_list_type, ValueT>
{
public :
	typedef typename List<ValueT, null_list_type>::type type;
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
#endif // TMP_PUSH_BACK_H_20131219071425968
// end of file
