/**
  @file     bitsize_of.h
  @brief    retrieves the width in bits from type.
  @author   HRYKY
  @version  $Id: bitsize_of.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef BITSIZE_OF_H_20130525210011541
#define BITSIZE_OF_H_20130525210011541
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, typename ResultT
#define hryky_template_arg \
	ValueT, ResultT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the width in bits from type.
	template <hryky_template_param>
	class BitsizeOf;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the width in bits from type.
 */
template <typename ValueT, typename ResultT = size_t>
class hryky::BitsizeOf
{
public :

	static ResultT const value = sizeof(ValueT) << 3;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
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
#endif // BITSIZE_OF_H_20130525210011541
// end of file
