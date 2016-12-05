/**
  @file     tuple_at.h
  @brief    retrieves the type of element in tuple by literal index.
  @author   HRYKY
  @version  $Id: tuple_at.h 353 2014-06-17 04:55:19Z hryky.private@gmail.com $
 */
#ifndef TUPLE_AT_H_20131015232250640
#define TUPLE_AT_H_20131015232250640
#include "hryky/tuple/tuple_size.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TupleT, size_t Index
#define hryky_template_arg \
	TupleT, Index
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tuple
{
	/// retrieves the base class of tuple by index.
	template <typename TupleT, size_t Index>
	class At;

namespace detail
{
	/// ascend the base of the tuple.
	template <typename TupleT, size_t Count>
	class AtImpl;
	
} // namespace detail
} // namespace tuple
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  retrieves the base class of tuple by index.
 */
template <typename TupleT, size_t Index>
class hryky::tuple::At
{
	static_assert(
		Size<TupleT>::type::value > Index,
		"The Index exceeds the size of the tuple.");
public :
	typedef typename detail::AtImpl<
		TupleT,
		Size<TupleT>::type::value - Index - 1>::type type;
};
/**
  ascends the base of the tuple.
 */
template <typename TupleT, size_t Count>
class hryky::tuple::detail::AtImpl
{
public :
	typedef typename detail::AtImpl<
		typename TupleT::rest_type,
		Count - 1u
	>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tuple
{
namespace detail
{
/**
  retrieves the tuple itself.
 */
template <typename TupleT>
class AtImpl<TupleT, 0u>
{
public :
	typedef TupleT type;
};
} // namespace detail
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
namespace detail
{
} // namespace detail
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
#endif // TUPLE_AT_H_20131015232250640
// end of file
