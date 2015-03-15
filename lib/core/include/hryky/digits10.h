/**
  @file     digits10.h
  @brief    calculates the number of digits in decimal base.
  @author   HRYKY
  @version  $Id: digits10.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef DIGITS10_H_20130928154144320
#define DIGITS10_H_20130928154144320
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// calculates the number of digits in decimal base at compile-time.
	template <int Value>
	class Digits10;

} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief calculates the number of digits in decimal base at compile-time.
 */
template <int Value>
class hryky::Digits10
{
public :
	static int const value = 1 + Digits10<Value / 10>::value;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief specializes when the value is zero.
 */
template <>
class hryky::Digits10<0>
{
public :
	static int const value = 0;
};
} // namespace hryky
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
	/// calculates the number of digits in decimal base.
	template <typename ValueT>
	int digits10(ValueT src);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief calculates the number of digits in decimal base.
 */
template <typename ValueT>
int hryky::digits10(ValueT src)
{
	return ValueT() == src ? 0 : 1 + digits10(src / 10);
}
#endif // DIGITS10_H_20130928154144320
// end of file
