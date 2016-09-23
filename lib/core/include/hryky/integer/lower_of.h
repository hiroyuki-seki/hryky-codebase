/**
  @file     lower_of.h
  @brief    retrieves the lower type.
  @author   HRYKY
  @version  $Id: lower_of.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef LOWER_OF_H_20130919232801644
#define LOWER_OF_H_20130919232801644
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
	/// retrieves the lower type.
	template <hryky_template_param>
	class LowerOf;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the lower type.
 */
template <typename ValueT>
class hryky::LowerOf
{
public :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief retrieves the lower type of uint64_t.
 */
template <>
class hryky::LowerOf<uint64_t>
{
public :
	typedef uint32_t type;
};
/**
  @brief retrieves the lower type of uint32_t.
 */
template <>
class hryky::LowerOf<uint32_t>
{
public :
	typedef uint16_t type;
};
/**
  @brief retrieves the lower type of uint16_t.
 */
template <>
class hryky::LowerOf<uint16_t>
{
public :
	typedef uint8_t type;
};
/**
  @brief retrieves the lower type of int64_t.
 */
template <>
class hryky::LowerOf<int64_t>
{
public :
	typedef int32_t type;
};
/**
  @brief retrieves the lower type of int32_t.
 */
template <>
class hryky::LowerOf<int32_t>
{
public :
	typedef int16_t type;
};
/**
  @brief retrieves the lower type of int16_t.
 */
template <>
class hryky::LowerOf<int16_t>
{
public :
	typedef int8_t type;
};
#if hryky_distinct_int_and_int32
/**
  @brief retrieves the lower type of signed int.
 */
template <>
class hryky::LowerOf<signed int>
{
public :
	typedef signed short type;
};
/**
  @brief retrieves the lower type of unsigned int.
 */
template <>
class hryky::LowerOf<unsigned int>
{
public :
	typedef unsigned short type;
};
#endif // hryky_distinct_int_and_int32
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
#endif // LOWER_OF_H_20130919232801644
// end of file
