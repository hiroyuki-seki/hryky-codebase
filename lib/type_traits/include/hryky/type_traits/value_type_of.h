/**
  @file     value_type_of.h
  @brief    retrieves the value_type of arbitrary class.
  @author   HRYKY
  @version  $Id: value_type_of.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef VALUE_TYPE_OF_H_20131113085818040
#define VALUE_TYPE_OF_H_20131113085818040
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT
#define hryky_template_arg \
	ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the value_type of arbitrary class.
	template <hryky_template_param>
	class ValueTypeOf;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the value_type of arbitrary class.
 */
template <typename ValueT>
class hryky::ValueTypeOf
{
public :
	typedef typename ValueT::value_type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief assumes a type of element of built-in array as value_type.
 */
template <typename ValueT>
class ValueTypeOf<ValueT[]>
{
public :
	typedef ValueT type;
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
#endif // VALUE_TYPE_OF_H_20131113085818040
// end of file
