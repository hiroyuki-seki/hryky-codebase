/**
  @file     capacity_of.h
  @brief    retrieves the static capacity.
  @author   HRYKY
  @version  $Id: capacity_of.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef CAPACITY_OF_H_20131104102512100
#define CAPACITY_OF_H_20131104102512100
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, typename RetT
#define hryky_template_arg \
	ValueT, RetT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the static capacity.
	template <hryky_template_param>
	class CapacityOf;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the static capacity.
 */
template <typename ValueT, typename RetT = size_t>
class hryky::CapacityOf
{
public :
	static RetT const value = CapacityOf<ValueT::base_type>::value;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief retrieves the size of built-in array.
 */
template <typename ValueT, typename RetT, size_t Size>
class CapacityOf<ValueT[Size], RetT>
{
public :
	static RetT const value = Size;
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
#endif // CAPACITY_OF_H_20131104102512100
// end of file
