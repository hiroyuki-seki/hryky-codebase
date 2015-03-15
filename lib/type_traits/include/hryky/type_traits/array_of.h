/**
  @file     array_of.h
  @brief    facilitates the declaration of built-in array.
  @author   HRYKY
  @version  $Id: array_of.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef ARRAY_OF_H_20131209124624198
#define ARRAY_OF_H_20131209124624198
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, size_t Size
#define hryky_template_arg \
	ValueT, Size
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// facilitates the declaration of built-in array.
	template <hryky_template_param>
	class ArrayOf;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief facilitates the declaration of built-in array.
 */
template <hryky_template_param>
class hryky::ArrayOf
{
public :

	typedef ValueT type[Size];
	typedef ValueT (&reference)[Size];

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
#endif // ARRAY_OF_H_20131209124624198
// end of file
