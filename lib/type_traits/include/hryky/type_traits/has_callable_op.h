/**
  @file     has_callable_op.h
  @brief    confirms whether a class overloads the function call operator.
  @author   HRYKY
  @version  $Id: has_callable_op.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef HAS_CALLABLE_OP_H_20140113104159112
#define HAS_CALLABLE_OP_H_20140113104159112
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
	/**
	  confirms whether a class overloads the function call operator
	  without an argument.
	 */
	template <typename ClsT, typename RetT>
	class HasCallableOp0;
	
	/**
	  confirms whether a class overloads the immutable function call operator
	  without an argument.
	 */
	template <typename ClsT, typename RetT>
	class HasCallableOp0C;
	
	/**
	  confirms whether a class overloads the function call operator
	  with an argument.
	 */
	template <typename ClsT, typename RetT, typename A1T>
	class HasCallableOp1;
	
	/**
	  confirms whether a class overloads the immutable function call operator
	  with an argument.
	 */
	template <typename ClsT, typename RetT, typename A1T>
	class HasCallableOp1C;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether a class overloads the function call operator
    without an argument.
 */
template <typename ClsT, typename RetT>
class hryky::HasCallableOp0
{
private :
	template <typename TargetT, RetT (TargetT::*)()>
		struct Test;
	
	template <typename TargetT>
	static uint16_t test(Test<TargetT, &TargetT::operator()> *);

	template <typename TargetT> 
	static uint8_t test(...);
	
public :
	typedef IntegralConstant<
		bool, sizeof(test<ClsT>(0)) == sizeof(uint16_t)> type;
};
/**
  @brief confirms whether a class overloads the immutable function call operator
    without an argument.
 */
template <typename ClsT, typename RetT>
class hryky::HasCallableOp0C
{
private :
	template <typename TargetT, RetT (TargetT::*)() const>
		struct Test;
	
	template <typename TargetT>
	static uint16_t test(Test<TargetT, &TargetT::operator()> *);

	template <typename TargetT> 
	static uint8_t test(...);
	
public :
	typedef IntegralConstant<
		bool, sizeof(test<ClsT>(0)) == sizeof(uint16_t)> type;
};
/**
  @brief confirms whether a class overloads the function call operator
    with an argument.
 */
template <typename ClsT, typename RetT, typename A1T>
class hryky::HasCallableOp1
{
private :
	template <typename TargetT, RetT (TargetT::*)(A1T)>
		struct Test;
	
	template <typename TargetT>
	static uint16_t test(Test<TargetT, &TargetT::operator()> *);

	template <typename TargetT> 
	static uint8_t test(...);
	
public :
	typedef IntegralConstant<
		bool, sizeof(test<ClsT>(0)) == sizeof(uint16_t)> type;
};
/**
  @brief confirms whether a class overloads the immutable function call operator
    with an argument.
 */
template <typename ClsT, typename RetT, typename A1T>
class hryky::HasCallableOp1C
{
private :
	template <typename TargetT, RetT (TargetT::*)(A1T) const>
		struct Test;
	
	template <typename TargetT>
	static uint16_t test(Test<TargetT, &TargetT::operator()> *);

	template <typename TargetT> 
	static uint8_t test(...);
	
public :
	typedef IntegralConstant<
		bool, sizeof(test<ClsT>(0)) == sizeof(uint16_t)> type;
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
#endif // HAS_CALLABLE_OP_H_20140113104159112
// end of file
