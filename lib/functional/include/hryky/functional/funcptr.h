/**
  @file     functional_pointer_n.h
  @brief    calls the function by the function pointer.
  @author   HRYKY
  @version  $Id: funcptr.h 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#ifndef FUNCPTR_H_20140112131918221
#define FUNCPTR_H_20140112131918221
#include "hryky/retention/retention_value.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// calls the function by the function pointer without an argument.
	template <typename RetT>
	class Funcptr0;

	/// calls the function by the function pointer with an argument.
	template <typename RetT, typename Arg1T>
	class Funcptr1;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief calls the function by the function pointer without an argument.
 */
template <typename RetT>
class hryky::Funcptr0 :
	public retention::Value<RetT (*)(void)>
{
public :
	typedef retention::Value<RetT (*)(void)> retention_type;
	
	Funcptr0(value_type const funcptr)
		: retention_type(funcptr)
	{
	}
	
	RetT operator()() const
	{
		return (*this->get())();
	}
};
/**
  @brief calls the function by the function pointer with an argument.
 */
template <typename RetT, typename Arg1T>
class hryky::Funcptr1 :
	public retention::Value<RetT (*)(Arg1T)>
{
public :
	typedef retention::Value<RetT (*)(Arg1T)> retention_type;
	
	Funcptr1(value_type const funcptr)
		: retention_type(funcptr)
	{
	}
	
	RetT operator()(Arg1T arg1) const
	{
		return (*this->get())(arg1);
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
	/// creates a callable object from a function pointer without an argument.
	template <typename RetT>
	Funcptr0<RetT> function(
		RetT (* const raw)());

	/// creates a callable object from a function pointer with an argument.
	template <typename RetT, typename Arg1T>
	Funcptr1<RetT, Arg1T> function(
		RetT (* const raw)(Arg1T));

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a callable object from a function pointer without an argument.
 */
template <typename RetT>
hryky::Funcptr0<RetT>
hryky::function(RetT (* const raw)())
{
	return Funcptr0<RetT>(raw);
}
/**
  @brief creates a callable object from a function pointer with an argument.
 */
template <typename RetT, typename Arg1T>
hryky::Funcptr1<RetT, Arg1T>
hryky::function(RetT (* const raw)(Arg1T))
{
	return Funcptr1<RetT, Arg1T>(raw);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#endif // FUNCPTR_H_20140112131918221
// end of file
