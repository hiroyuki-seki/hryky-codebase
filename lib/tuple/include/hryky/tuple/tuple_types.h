/**
  @file     tuple_types.h
  @brief    retrieves the list of types from tuple.
  @author   HRYKY
  @version  $Id: tuple_types.h 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#ifndef TUPLE_TYPES_H_20140729191522469
#define TUPLE_TYPES_H_20140729191522469
#include "hryky/tmp/tmp_list.h"
#include "hryky/tuple/tuple_primal.h"
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
namespace tuple
{
	/// retrieves the list of types from tuple.
	template <typename TupleT>
	class Types;

} // namespace tuple
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the list of types from tuple.
 */
template <hryky_template_param>
class hryky::tuple::Types
{
public :
	typedef tmp::List<
		typename TupleT::first_type,
		typename Types<typename TupleT::rest_type>::type
	> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tuple
{
/**
  @brief retrieves the list of types from empty tuple.
 */
template <>
class Types<Tuple<> >
{
public :
	typedef tmp::null_list_type type;
};
/**
  @brief retrieves the list of types from tuple with one element.
 */
template <typename FirstT>
class Types<Tuple<FirstT> >
{
public :
	typedef tmp::List<FirstT, tmp::null_list_type> type;
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
#endif // TUPLE_TYPES_H_20140729191522469
// end of file
