/**
  @file     tmp_type_of.h
  @brief    retrieves the 'type' member if possible.
  @author   HRYKY
  @version  $Id: tmp_type_of.h 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#ifndef TMP_TYPE_OF_H_20140729184327446
#define TMP_TYPE_OF_H_20140729184327446
#include "hryky/type_traits/has_type.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, bool HasType
#define hryky_template_arg \
	ValueT, HasType
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// retrieves the 'type' member if possible.
	template <
		typename ValueT,
		bool HasType = hryky::HasType<ValueT>::value
	>
	class TypeOf;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the 'type' member if possible.
 */
template <hryky_template_param>
class hryky::tmp::TypeOf
{
public :
	typedef ValueT type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  @brief retrieves the 'type' member.
 */
template <typename ValueT>
class TypeOf<ValueT, true>
{
public :
	typedef typename ValueT::type type;
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
#endif // TMP_TYPE_OF_H_20140729184327446
// end of file
