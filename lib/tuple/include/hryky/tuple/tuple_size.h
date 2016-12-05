/**
  @file     tuple_size.h
  @brief    retrieves the number of elements in a tuple.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef TUPLE_SIZE_H_20161205172530392
#define TUPLE_SIZE_H_20161205172530392
#include "hryky/tmp/null.h"
#include "hryky/tmp/tmp_add.h"
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TupleT
#define hryky_template_arg \
	TupleT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	template <typename FirstT, typename RestT>
	class Tuple;

namespace tuple
{
	/// retrieves the number of elements in a tuple.
	template <hryky_template_param>
	class Size;

} // namespace tuple
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the number of elements in a tuple.
 */
template <typename TupleT>
class hryky::tuple::Size
{
public :
	typedef typename tmp::Add<
		IntegralConstant<size_t, 1u>,
		Size<typename TupleT::rest_type> >::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tuple
{
/**
  The tuple is empty.
 */
template <>
class Size<Tuple<hryky::Null, hryky::Null> >
{
public :
	typedef IntegralConstant<size_t, 0> type;
};
/**
  The tuple is empty.
 */
template <>
class Size<hryky::Null>
{
public :
	typedef IntegralConstant<size_t, 0> type;
};
} // namespace tuple
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
namespace tuple
{
} // namespace tuple
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // TUPLE_SIZE_H_20161205172530392
// end of file
