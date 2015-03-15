/**
  @file     difference_type_of.h
  @brief    retrieves the type of difference between two elements in container.
  @author   HRYKY
  @version  $Id: difference_type_of.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef DIFFERENCE_TYPE_OF_H_20140323185545455
#define DIFFERENCE_TYPE_OF_H_20140323185545455
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
	/// retrieves the type of difference between two elements in container.
	template <typename ValueT>
	class DifferenceTypeOf;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the type of difference between two elements in container.
 */
template <hryky_template_param>
class hryky::DifferenceTypeOf
{
public :
	typedef typename ValueT::difference_type type;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief retrieves the type of difference for built-in array.
 */
template <typename ValueT, size_t Size>
class DifferenceTypeOf<ValueT[Size]>
{
public :
	typedef ::std::ptrdiff_t type;
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
#endif // DIFFERENCE_TYPE_OF_H_20140323185545455
// end of file
