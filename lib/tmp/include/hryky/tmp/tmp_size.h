/**
  @file     tmp_size.h
  @brief    retrieves the size of container.
  @author   HRYKY
  @version  $Id: tmp_size.h 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#ifndef TMP_SIZE_H_20131216223157605
#define TMP_SIZE_H_20131216223157605
#include "hryky/tmp/tmp_eval.h"
#include "hryky/tmp/tmp_increment.h"
#include "hryky/tmp/tmp_is_list.h"
#include "hryky/tmp/tmp_list.h"
#include "hryky/type_traits/integral_constant.h"
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
	/// retrieves the size of container.
	template <hryky_template_param>
	class Size;

	/// implements Size<> for detailed type.
	template <hryky_template_param>
	class SizeImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the size of container.
 */
template <hryky_template_param>
class hryky::tmp::Size
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be list.");
public :
	typedef typename SizeImpl<typename ListT::type>::type type;

};
/**
  @brief implements Size<> for detailed type.
 */
template <hryky_template_param>
class hryky::tmp::SizeImpl
{
public :
	typedef typename Increment<
		Size<typename ListT::type::rest_type> >::type type;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  @brief termintes SizeImpl.
 */
template <>
class SizeImpl<null_list_type>
{
public :
	typedef IntegralConstant<int, 0> type;
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
#endif // TMP_SIZE_H_20131216223157605
// end of file
