/**
  @file         is_as_string.h
  @brief        confirms whether a class can be used as string.
  @author       HRYKY
  @version      $Id: is_as_string.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef TYPE_IS_AS_STRING_H_20120925125540205
#define TYPE_IS_AS_STRING_H_20120925125540205
#include "hryky/stdint.h"
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// confirms whether a class can be used as string.
	template < typename ValueT >
	class IsAsString;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether a class can be used as string.
 */
template < typename ValueT >
class hryky::IsAsString
{
private :
	typedef uint16_t    yes;
	typedef uint8_t     no;

	template < typename TargetT, size_t (TargetT::*)() const>
		struct TestSize;
	template < typename TargetT
		, typename TargetT::const_pointer (TargetT::*)() const>
		struct TestData;
	
	template < typename TargetT >
	static yes test_size(TestSize<TargetT, &TargetT::size> *);
	
	template < typename TargetT >
	static no test_size(...);

	template < typename TargetT >
	static yes test_data(TestData<TargetT, &TargetT::data> *);
	
	template < typename TargetT >
	static no test_data(...);

public :
	typedef IntegralConstant<
		bool,
		(sizeof(test_size<ValueT>(0)) == sizeof(yes)
		 && sizeof(test_data<ValueT>(0)) == sizeof(yes))
	> type;
	
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
#endif // TYPE_IS_AS_STRING_H_20120925125540205
// end of file
