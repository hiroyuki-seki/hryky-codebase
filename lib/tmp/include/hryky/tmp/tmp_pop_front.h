/**
  @file     tmp_pop_front.h
  @brief    removes the value at the beginning of container.
  @author   HRYKY
  @version  $Id: tmp_pop_front.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef TMP_POP_FRONT_H_20131222163646358
#define TMP_POP_FRONT_H_20131222163646358
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
	/// removes the value at the beginning of container.
	template <hryky_template_param>
	class PopFront;

	/// implements PopFront<> for the actual type.
	template <hryky_template_param>
	class PopFrontImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief removes the value at the beginning of container.
 */
template <hryky_template_param>
class hryky::tmp::PopFront
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
public :
	typedef typename PopFrontImpl<typename ListT::type>::type type;
};
/**
  @brief implements PopFront<> for the actual type.
 */
template <hryky_template_param>
class hryky::tmp::PopFrontImpl
{
public :
	typedef typename ListT::rest_type type;
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
#endif // TMP_POP_FRONT_H_20131222163646358
// end of file
