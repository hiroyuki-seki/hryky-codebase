/**
  @file         is_char.h
  @brief        confirmes whether the type is char.
  @author       HRYKY
  @version      $Id: is_char.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef IS_CHAR_H_20130101175611414
#define IS_CHAR_H_20130101175611414
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// confirmes whether the type is char.
	template <typename ValueT>
	class IsChar;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirmes whether the type is char.
 */
template <typename ValueT>
class hryky::IsChar
{
public :
	typedef false_type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief specializes IsChar of which the argument is char.
 */
template <>
class IsChar<char>
{
public :
	typedef true_type type;
};
/**
  @brief specializes IsChar of which the argument is wchar_t.
 */
template <>
class IsChar<wchar_t>
{
public :
	typedef true_type type;
};
/**
  @brief specializes IsChar of which the argument is char16_t.
 */
template <>
class IsChar<char16_t>
{
public :
	typedef true_type type;
};
/**
  @brief specializes IsChar of which the argument is char32_t.
 */
template <>
class IsChar<char32_t>
{
public :
	typedef true_type type;
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
#endif // IS_CHAR_H_20130101175611414
// end of file
