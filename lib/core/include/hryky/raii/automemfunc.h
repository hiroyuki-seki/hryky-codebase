/**
  @file         automemfunc.h
  @brief        invokes a member function at the end of scope.
  @author       HRYKY
  @version      $Id: automemfunc.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef AUTOMEMFUNC_H_20130216114653157
#define AUTOMEMFUNC_H_20130216114653157
#include "hryky/without_copy.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// base class for calling at the end of scope.
	template <typename InstanceT>
	class AutoMemFuncBase;

	/// calls a function when the current scope exits.
	template <
		typename InstanceT,
		typename RetT,
		RetT (InstanceT::*func)(void)
	>
	class AutoMemFunc;
	
	/// calls a function with a argument when the current scope exits.
	template <
		typename InstanceT,
		typename RetT,
		typename Arg1T,
		RetT (InstanceT::*func)(Arg1T)
	>
	class AutoMemFunc1;
	
} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief base class for calling at the end of scope.
 */
template <typename InstanceT>
class hryky::AutoMemFuncBase : WithoutCopy
{
public :
	typedef AutoMemFuncBase<InstanceT> this_type;
	
	AutoMemFuncBase(InstanceT & instance)
		: instance_(instance), disable_()
	{
	}

	/**
	  @brief cancels the deallocation.
	 */
	void disable()
	{
		this->disable_ = true;
	}

protected :
	AutoMemFuncBase(this_type const &);
	this_type & operator=(this_type const &);
	
	InstanceT & instance_;
	bool disable_;
};
/**
  @brief calls a function when the current scope exits.
  @param RetT is the type of return value.
  @param func is the name of function.
 */
template <
	typename InstanceT,
	typename RetT,
	RetT (InstanceT::*func)(void)
>
class hryky::AutoMemFunc : public AutoMemFuncBase<InstanceT>
{
public :
	typedef AutoMemFunc<InstanceT, RetT, func> this_type;
	
	AutoMemFunc(InstanceT & instance)
		: AutoMemFuncBase<InstanceT>(instance)
	{
	}
	
	~AutoMemFunc()
	{
		if (!this->disable_) {
			(this->instance_.*func)();
		}
	}
private :
	hryky_delete_this_copy_constructor(AutoMemFunc);
	hryky_delete_this_copy_assign_op(AutoMemFunc);
};
/**
  @brief calls a function when the current scope exits.
  @param RetT is the type of return value.
  @param Arg1T is the type of the first argument.
  @param func is the name of function.
 */
template <
	typename InstanceT,
	typename RetT,
	typename Arg1T,
	RetT (InstanceT::*func)(Arg1T)
>
class hryky::AutoMemFunc1 : public AutoMemFuncBase<InstanceT>
{
public :
	typedef AutoMemFunc1<InstanceT, RetT, Arg1T, func> this_type;
	
	AutoMemFunc1(InstanceT & instance, Arg1T arg1)
		: AutoMemFuncBase<InstanceT>(instance)
		  , arg1_(arg1)
	{
	}
	
	~AutoMemFunc1()
	{
		if (!this->disable_) {
			(this->instance_.*func)(this->arg1_);
		}
	}

private :
	hryky_delete_this_copy_constructor(AutoMemFunc1);
	hryky_delete_this_copy_assign_op(AutoMemFunc1);
	
	Arg1T   arg1_;
};
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // AUTOMEMFUNC_H_20130216114653157
// end of file
