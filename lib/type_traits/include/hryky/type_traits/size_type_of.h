/**
  @file     size_type_of.h
  @brief    retrieves the type of size for container.
  @author   HRYKY
  @version  $Id: size_type_of.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SIZE_TYPE_OF_H_20131209093711067
#define SIZE_TYPE_OF_H_20131209093711067
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
	/// retrieves the type of size for container.
	template <hryky_template_param>
	class SizeTypeOf;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the type of size for container.
 */
template <typename ValueT>
class hryky::SizeTypeOf
{
public :
	typedef typename ValueT::size_type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief retrieves the type of size for built-in array.
 */
template <typename ValueT, size_t Size>
class SizeTypeOf<ValueT[Size]>
{
public :
	typedef size_t type;
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
#endif // SIZE_TYPE_OF_H_20131209093711067
// end of file
