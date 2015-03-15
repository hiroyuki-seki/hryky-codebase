/**
  @file     has_iterator.h
  @brief    confirmes whether a type has iterator.
  @author   HRYKY
  @version  $Id: has_iterator.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef HAS_ITERATOR_H_20131208173037396
#define HAS_ITERATOR_H_20131208173037396
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
	/// confirmes whether a type has iterator.
	template <hryky_template_param>
	class HasIterator;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirmes whether a type has iterator.
 */
template <typename ValueT>
class hryky::HasIterator
{
private :
	typedef uint16_t    yes;
	typedef uint8_t     no;

	template < typename TargetT >
	static yes test(typename TargetT::iterator const * const);
	
	template < typename TargetT >
	static no test(...);
	
public :
	typedef IntegralConstant<
		bool, sizeof(test<ValueT>(0)) == sizeof(yes)> type;
	typedef typename type::value_type value_type;
	static value_type const value = type::value;
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
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // HAS_ITERATOR_H_20131208173037396
// end of file
