/**
  @file     golden_ratio.h
  @brief    retrieves the golden ratio in mathematics.
  @author   HRYKY
  @version  $Id: golden_ratio.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef GOLDEN_RATIO_H_20140112160845339
#define GOLDEN_RATIO_H_20140112160845339
#include "hryky/std/std_cmath.h"
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
	/// retrieves the golden ratio in mathematics.
	template <hryky_template_param>
	class GoldenRatio;

	/// retrieves the reciprocal of golden ratio in mathematics.
	template <hryky_template_param>
	class RecipGoldenRatio;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the golden ratio in mathematics.
 */
template <typename ValueT>
class hryky::GoldenRatio
{
public :
	static ValueT const value;
};
/**
  @brief retrieves the reciprocal of the golden ratio in mathematics.
 */
template <typename ValueT>
class hryky::RecipGoldenRatio
{
public :
	static ValueT const value;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  The golden ratio by single precision floating-point.
 */
template <>
class GoldenRatio<float>
{
public :
	static float const value;
};
float const GoldenRatio<float>::value = (::std::sqrt(5.0f) + 1.0f) / 2.0f;
/**
  The golden ratio by double precision floating-point.
 */
template <>
class GoldenRatio<double>
{
public :
	static double const value;
};
double const GoldenRatio<double>::value = (::std::sqrt(5.0) + 1.0) / 2.0;
/**
  The reciprocal of the golden ratio by single precision floating-point.
 */
template <>
class RecipGoldenRatio<float>
{
public :
	static float const value;
};
float const RecipGoldenRatio<float>::value = (::std::sqrt(5.0f) - 1.0f) / 2.0f;
/**
  The reciprocal of the golden ratio by double precision floating-point.
 */
template <>
class RecipGoldenRatio<double>
{
public :
	static double const value;
};
double const RecipGoldenRatio<double>::value = (::std::sqrt(5.0) - 1.0) / 2.0;
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
	/// retrieves the middle position based on the golden ratio between two positions.
	template <typename ValueT>
	ValueT golden_ratio(ValueT first, ValueT last);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the middle position based on the golden ratio between two positions.
 */
template <typename ValueT>
ValueT hryky::golden_ratio(ValueT first, ValueT last)
{
	return first + (last - first) * RecipGoldenRatio<ValueT>::value;
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // GOLDEN_RATIO_H_20140112160845339
// end of file
