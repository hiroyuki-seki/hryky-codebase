/**
  @file     pi.h
  @brief    retrieves the mathematical constant pi.
  @author   HRYKY
  @version  $Id: pi.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef PI_H_20131119152041306
#define PI_H_20131119152041306
#include "hryky/factorial.h"
#include "hryky/std/std_cmath.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the mathematical constant pi.
	template <typename ValueT = float>
	class Pi;
	
	/// retrieves the half of PI.
	template <typename ValueT = float>
	class HalfPi;

	/// retrieves the quarter of PI.
	template <typename ValueT = float>
	class QuarterPi;

	/// approximates the mathematical constant pi.
	template <typename ValueT, size_t Precision>
	class CalcPi;

	template <size_t Index>
	class CalcPiDividend;

	template <size_t Index, size_t Num, bool End = (Num >= 2 * Index + 1)>
	class CalcPiDivisor;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the mathematical constant pi.
 */
template <typename ValueT>
class hryky::Pi
{
};
/**
  @brief retrieves the half of PI.
 */
template <typename ValueT>
class hryky::HalfPi
{
};
/**
  @brief retrieves the quarter of PI.
 */
template <typename ValueT>
class hryky::QuarterPi
{
};
/**
  @brief approximates the mathematical constant pi.
 */
template <typename ValueT, size_t Precision>
class hryky::CalcPi
{
public :
	static ValueT const value;
};
/**
  @brief The dividend of series of the approximation of PI.
 */
template <size_t Index>
class hryky::CalcPiDividend
{
public :
	static size_t const value =
		(Index / 2 * 2) * CalcPiDividend<Index - 2>::value;
};
/**
  @brief The divisor of series of the approximation of PI.
 */
template <size_t Index, size_t Num, bool End>
class hryky::CalcPiDivisor
{
public :
	static size_t const value =
		(2 * Index + 1) * CalcPiDivisor<Index - 1, Num>::value;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief retrieves the mathematical constant pi by single-precision.
 */
template <>
class Pi<float>
{
public :
	static float const value;
};
/**
  @brief retrieves the mathematical constant pi by double-precision.
 */
template <>
class Pi<double>
{
public :
	static double const value;
};
/**
  @brief retrieves the half of PI by single-precision.
 */
template <>
class HalfPi<float>
{
public :
	static float const value;
};
/**
  @brief retrieves the half of PI by double-precision.
 */
template <>
class HalfPi<double>
{
public :
	static double const value;
};
/**
  @brief retrieves the quarter of PI by single-precision.
 */
template <>
class QuarterPi<float>
{
public :
	static float const value;
};
/**
  @brief retrieves the quarter of PI by double-precision.
 */
template <>
class QuarterPi<double>
{
public :
	static double const value;
};
/**
  @brief terminates the recursion of CalcPiDividend
 */
template <>
class CalcPiDividend<0>
{
public :
	static size_t const value = 1;
};
template <>
class CalcPiDividend<1>
{
public :
	static size_t const value = 1;
};
/**
  @brief terminates the recursion of CalcPiDivisor
 */
template <size_t Index, size_t Num>
class CalcPiDivisor<Index, Num, true>
{
public :
	static size_t const value = 1;
};
/**
  @brief terminates the recursion of CalcPi.
 */
template <typename ValueT>
class CalcPi<ValueT, 0>
{
public :
	static ValueT const value;
};
template <typename ValueT>
ValueT const CalcPi<ValueT, 0>::value = ValueT(2);
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
template <typename ValueT, size_t Precision>
ValueT const hryky::CalcPi<ValueT, Precision>::value = ValueT(
	ValueT(2 * CalcPiDividend<Precision>::value) /
	ValueT(CalcPiDivisor<Precision, Precision>::value) +
	hryky::CalcPi<ValueT, Precision - 1>::value);
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
#endif // PI_H_20131119152041306
// end of file
