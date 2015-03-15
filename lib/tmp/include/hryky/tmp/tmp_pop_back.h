/**
  @file     tmp_pop_back.h
  @brief    removes the value at the end of container.
  @author   HRYKY
  @version  $Id: tmp_pop_back.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef TMP_POP_BACK_H_20131222162211348
#define TMP_POP_BACK_H_20131222162211348
#include "hryky/tmp/tmp_list.h"
#include "hryky/tmp/tmp_is_list.h"
#include "hryky/tmp/tmp_eval.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ListT
#define hryky_template_arg \
	ListT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// removes the value at the end of container.
	template <hryky_template_param>
	class PopBack;

	/// implements PopBack<> for the actual type.
	template <hryky_template_param>
	class PopBackImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief removes the value at the end of container.
 */
template <hryky_template_param>
class hryky::tmp::PopBack
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
private :
	typedef PopBackImpl<typename ListT::type> impl;
public :
	typedef typename impl::type type;
};
/**
  @brief implements PopBack<> for the actual type.
 */
template <hryky_template_param>
class hryky::tmp::PopBackImpl
{
public :
	typedef typename List<
		typename ListT::first_type,
		PopBackImpl<typename ListT::rest_type>
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
  removes the last element in the container.
 */
template <typename FirstT>
class PopBackImpl<List<FirstT, null_list_type> >
{
public :
	typedef null_list_type type;
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
#endif // TMP_POP_BACK_H_20131222162211348
// end of file
