/**
  @file         is_base_of.h
  @brief        confirms whether two types are in the inheritance relationship.
  @author       HRYKY
  @version      $Id: is_base_of.h 355 2014-06-22 08:47:38Z hryky.private@gmail.com $
 */
#ifndef IS_BASE_OF_H_20130108145027285
#define IS_BASE_OF_H_20130108145027285
#include "hryky/type_traits/integral_constant.h"
#include "hryky/type_traits/remove_const.h"
#include "hryky/type_traits/remove_reference.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// confirms whether two types are in the inheritance relationship.
	template <typename BaseT, typename DerivedT> 
	class IsBaseOf;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether two types are in the inheritance relationship.
 */
template <typename BaseT, typename DerivedT> 
class hryky::IsBaseOf
{
private :
	typedef uint8_t yes;
	typedef uint16_t no;

	static yes test(BaseT *);
	static no test(...);
	
public :
	typedef IntegralConstant<
		bool,
		(sizeof(yes) == sizeof(test(
			reinterpret_cast<
			typename RemoveConst<
				typename RemoveReference<DerivedT>::type
			>::type *>(0))))
	> type;

	static typename type::value_type const value = type::value;
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
#endif // IS_BASE_OF_H_20130108145027285
// end of file
