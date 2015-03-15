/**
  @file     transpose_of.h
  @brief    retrieves the transposed type.
  @author   HRYKY
  @version  $Id: transpose_of.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef TRANSPOSE_OF_H_20131113152613309
#define TRANSPOSE_OF_H_20131113152613309
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
	/// retrieves the transposed type.
	template <hryky_template_param>
	class TransposeOf;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the transposed type.
 */
template <typename ValueT>
class hryky::TransposeOf
{
public :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief transposes a type of built-in array.
 */
template <typename ValueT, size_t Columns, size_t Rows>
class TransposeOf<ValueT[Columns][Rows]>
{
public :
	typedef ValueT type[Rows][Columns];
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
#endif // TRANSPOSE_OF_H_20131113152613309
// end of file
