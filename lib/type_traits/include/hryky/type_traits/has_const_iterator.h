/**
  @file         has_const_iterator.h
  @brief        confirms whether a container has const_iterator.
  @author       HRYKY
  @version      $Id: has_const_iterator.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef TYPE_HAS_CONST_ITERATOR_H_20120909001446676
#define TYPE_HAS_CONST_ITERATOR_H_20120909001446676
#include "hryky/std/std_cstdint.h"
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// confirms whether a container has const_iterator.
	template < typename ContainerT >
	class HasConstIterator;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether a container has const_iterator.
 */
template < typename ContainerT >
class hryky::HasConstIterator
{
private :
	typedef uint16_t    yes;
	typedef uint8_t     no;

	template < typename TargetT >
	static yes test(typename TargetT::const_iterator const * const);
	
	template < typename TargetT >
	static no test(...);
	
public :
	typedef IntegralConstant<
		bool, sizeof(test<ContainerT>(0)) == sizeof(yes)> type;
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
#endif // TYPE_HAS_CONST_ITERATOR_H_20120909001446676
// end of file
