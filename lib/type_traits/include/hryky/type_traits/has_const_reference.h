/**
  @file     has_const_reference.h
  @brief    confirmes whether a type has const_reference.
  @author   HRYKY
  @version  $Id: has_const_reference.h 352 2014-06-08 08:48:59Z hryky.private@gmail.com $
 */
#ifndef HAS_CONST_REFERENCE_H_20131209150640296
#define HAS_CONST_REFERENCE_H_20131209150640296
#include "hryky/std/std_cstdint.h"
#include "hryky/type_traits/integral_constant.h"
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
	/// confirmes whether a type has const_reference.
	template <hryky_template_param>
	class HasConstReference;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirmes whether a type has const_reference.
 */
template <typename ValueT>
class hryky::HasConstReference
{
public :
	typedef uint16_t    yes;
	typedef uint8_t     no;

	template < typename TargetT >
	static yes test(typename TargetT::const_reference const * const);
	
	template < typename TargetT >
	static no test(...);
	
public :
	typedef IntegralConstant<
		bool, sizeof(test<ValueT>(0)) == sizeof(yes)> type;
	static bool const value = type::value;
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
// tests
//------------------------------------------------------------------------------
static_assert(
	!hryky::HasConstReference<int>::type::value,
	"int doesn't have const_reference");
static_assert(
	!hryky::HasConstReference<int[1]>::type::value,
	"int[1] doesn't have const_reference");
static_assert(
	!hryky::HasConstReference<const hryky::uint32_t[4]>::type::value,
	"const uint32_t[4] doesn't have const_reference");
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // HAS_CONST_REFERENCE_H_20131209150640296
// end of file
