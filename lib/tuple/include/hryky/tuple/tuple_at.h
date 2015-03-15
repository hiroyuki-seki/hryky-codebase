/**
  @file     tuple_at.h
  @brief    retrieves the type of element in tuple by literal index.
  @author   HRYKY
  @version  $Id: tuple_at.h 353 2014-06-17 04:55:19Z hryky.private@gmail.com $
 */
#ifndef TUPLE_AT_H_20131015232250640
#define TUPLE_AT_H_20131015232250640
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
	/// retrieves the base class of tuple by index.
	template <typename TupleT, size_t Index>
	class TupleAt;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  retrieves the base class of tuple by index.
 */
template <typename TupleT, size_t Index>
class hryky::TupleAt
{
public :
	typedef typename TupleAt<
		typename TupleT::rest_type, Index - 1>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  retrieves the tuple itself.
 */
template <typename TupleT>
class TupleAt<TupleT, 0>
{
public :
	typedef TupleT type;
};
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
