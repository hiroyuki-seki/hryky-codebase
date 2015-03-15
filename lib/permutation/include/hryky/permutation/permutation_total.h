/**
  @file     permutation_total.h
  @brief    retrieves the total number of permutations.
  @author   HRYKY
  @version  $Id: permutation_total.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef PERMUTATION_TOTAL_H_20131206214111570
#define PERMUTATION_TOTAL_H_20131206214111570
#include "hryky/factorial.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	size_t Length, typename ResultT
#define hryky_template_arg \
	Length, ResultT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace permutation
{
	/// retrieves the total number of permutations.
	template <size_t Length, typename ResultT = size_t>
	class Total;

	typedef factorial_result_type total_type;

} // namespace permutation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the total number of permutations.
 */
template <hryky_template_param>
class hryky::permutation::Total
{
public :
	static ResultT const value = hryky::Factorial<Length, ResultT>::value;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace permutation
{
} // namespace permutation
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
namespace permutation
{
	/// retrieves the total number of permutations.
	template <typename LengthT>
	total_type total(LengthT const value);

} // namespace permutation
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the total number of permutations.
 */
template <typename LengthT>
hryky::permutation::total_type hryky::permutation::total(LengthT const value)
{
	return factorial(value);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // PERMUTATION_TOTAL_H_20131206214111570
// end of file
