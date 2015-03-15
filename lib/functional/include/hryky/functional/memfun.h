/**
  @file     memfun.h
  @brief    wraps a member function pointer as a callable functor.
  @author   HRYKY
  @version  $Id: memfun.h 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#ifndef MEMFUN_H_20140112143253272
#define MEMFUN_H_20140112143253272
#include "hryky/function_traits.h"
#include "hryky/type_traits/add_reference.h"
#include "hryky/retention/retention_value.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/**
	  wraps a member function pointer as a callable functor without an argument.
	 */
	template <typename ClsT, typename RetT>
	class Memfun0;

	/**
	  wraps a member function pointer as a callable functor with an argument.
	 */
	template <typename ClsT, typename RetT, typename Arg1T>
	class Memfun1;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief wraps a member function pointer as a callable functor
    without an argument.
 */
template <typename ClsT, typename RetT>
class hryky::Memfun0 :
	public retention::Value<RetT (ClsT::*)()>,
	public FunctionTraits1<RetT, typename AddReference<ClsT>::type>
{
public :
	typedef retention::Value<RetT (ClsT::*)()> retention_type;
	
	Memfun0(value_type const memfun)
		: retention_type(memfun)
	{
	}

	result_type operator()(arg1_type cls) const
	{
		return (cls.*(*this->get()))();
	}
};
/**
  @brief wraps a member function pointer as a callable functor
    with an argument.
 */
template <typename ClsT, typename RetT, typename Arg1T>
class hryky::Memfun1 :
	public retention::Value<RetT (ClsT::*)(Arg1T)>,
	public FunctionTraits2<
		RetT, typename AddReference<ClsT>::type, Arg1T>
{
public :
	typedef retention::Value<RetT (ClsT::*)(Arg1T)> retention_type;
	
	Memfun1(value_type const memfun)
		: retention_type(memfun)
	{
	}

	result_type operator()(arg1_type cls, arg2_type arg1) const
	{
		return (cls.*(*this->get()))(arg1);
	}
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
	/// creates a functor from a member function without an argument.
	template <typename ClsT, typename RetT>
	Memfun0<ClsT, RetT> function(
		RetT (ClsT::* const raw)());

	/// creates a functor from a member function with an argument.
	template <typename ClsT, typename RetT, typename Arg1T>
	Memfun1<ClsT, RetT, Arg1T> function(
		RetT (ClsT::* const raw)(Arg1T));

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a functor from a member function without an argument.
 */
template <typename ClsT, typename RetT>
hryky::Memfun0<ClsT, RetT>
hryky::function(RetT (ClsT::* const raw)())
{
	return Memfun0<ClsT, RetT>(raw);
}
/**
  @brief creates a functor from a member function with an argument.
 */
template <typename ClsT, typename RetT, typename Arg1T>
hryky::Memfun1<ClsT, RetT, Arg1T>
hryky::function(RetT (ClsT::* const raw)(Arg1T))
{
	return Memfun1<ClsT, RetT, Arg1T>(raw);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#endif // MEMFUN_H_20140112143253272
// end of file
