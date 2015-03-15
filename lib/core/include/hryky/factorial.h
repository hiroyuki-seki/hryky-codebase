/**
  @file     factorial.h
  @brief    calculates the factorial at compile time.
  @author   HRYKY
  @version  $Id: factorial.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef FACTORIAL_H_20131119150520295
#define FACTORIAL_H_20131119150520295
#include "hryky/std/std_cstdint.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	size_t Num, typename ValueT
#define hryky_template_arg \
	Num, ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// calculates the factorial at compile time.
	template <size_t Num, typename ValueT = size_t>
	class Factorial;

	/// calculates the product of odd numbers up to 2*Num + 1.
	template <size_t Num, typename ValueT = size_t>
	class OddFactorial;

	typedef uint64_t factorial_result_type;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief calculates the factorial at compile time.
 */
template <hryky_template_param>
class hryky::Factorial
{
public :
	static ValueT const value = Num * Factorial<Num - 1, ValueT>::value;
};
/**
  @brief calculates the product of odd numbers up to 2*Num + 1.
 */
template <hryky_template_param>
class hryky::OddFactorial
{
public :
	static ValueT const value =
		(2 * Num + 1) * OddFactorial<Num - 1, ValueT>::value;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief terminates the recursion of Factorial.
 */
template <typename ValueT>
class Factorial<0, ValueT>
{
public :
	static ValueT const value = 1;
};
/**
  @brief terminates the recursion of OddFactorial.
 */
template <typename ValueT>
class OddFactorial<0, ValueT>
{
public :
	static ValueT const value = 1;
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
	/// calculates a factorial.
	template <typename ValueT>
	factorial_result_type factorial(ValueT const value);

	/// calculates a factorial with the specified type of the result.
	template <typename ResultT, typename ValueT>
	void factorial(ResultT & result, ValueT const value);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief calculates a factorial.
 */
template <typename ValueT>
hryky::factorial_result_type hryky::factorial(ValueT const value)
{
	factorial_result_type result;

	factorial(result, value);

	return result;
}
/**
  @brief calculates a factorial with the specified type of the result.
 */
template <typename ResultT, typename ValueT>
void hryky::factorial(ResultT & result, ValueT const value)
{
	result = 1u;
	
	ResultT factor = static_cast<ResultT>(value);

	while (1u < factor) {
		result *= factor;
		--factor;
	}
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // FACTORIAL_H_20131119150520295
// end of file
