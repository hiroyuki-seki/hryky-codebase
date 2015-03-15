/**
  @file         autofunc.h
  @brief        invokes a function at the end of scope.
  @author       HRYKY
  @version      $Id: autofunc.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef AUTOFUNC_H_20130216114450156
#define AUTOFUNC_H_20130216114450156
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
	class AutoFuncBase;

	/// calls a function when the current scope exits.
	template <typename RetT, RetT func(void)>
	class AutoFunc;
	
	/// calls a function with a argument when the current scope exits.
	template <
		typename RetT,
		typename Arg1T,
		RetT func(Arg1T)
	>
	class AutoFunc1;
	
	/// calls a function with two arguments when the current scope exits.
	template <
		typename RetT,
		typename Arg1T,
		typename Arg2T,
		RetT func(Arg1T, Arg2T)
	>
	class AutoFunc2;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief base class for calling at the end of scope.
 */
class hryky::AutoFuncBase : WithoutCopy
{
public :
	typedef AutoFuncBase this_type;
	
	AutoFuncBase()
		: disable_()
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
	AutoFuncBase(this_type const &);
	this_type & operator=(this_type const &);
	
	bool disable_;
};
/**
  @brief calls a function when the current scope exits.
  @param RetT is the type of return value.
  @param func is the name of function.
 */
template <typename RetT, RetT func(void)>
class hryky::AutoFunc : public AutoFuncBase
{
public :
	typedef AutoFunc<RetT, func> this_type;
	AutoFunc()
	{
	}
	
	~AutoFunc()
	{
		if (!this->disable_) {
			(*func)();
		}
	}
private :
	hryky_delete_this_copy_constructor(AutoFunc);
	hryky_delete_this_copy_assign_op(AutoFunc);
};

/**
  @brief calls a function when the current scope exits.
  @param RetT is the type of return value.
  @param Arg1T is the type of the first argument.
  @param func is the name of function.
 */
template <typename RetT, typename Arg1T, RetT func(Arg1T)>
class hryky::AutoFunc1 : public AutoFuncBase
{
public :
	typedef AutoFunc1<RetT, Arg1T, func> this_type;
	
	AutoFunc1(Arg1T arg1)
		: arg1_(arg1)
	{
	}
	
	~AutoFunc1()
	{
		if (!this->disable_) {
			(*func)(this->arg1_);
		}
	}

private :
	hryky_delete_this_copy_constructor(AutoFunc1);
	hryky_delete_this_copy_assign_op(AutoFunc1);
	
	Arg1T   arg1_;
};

/**
  @brief calls a function when the current scope exits.
  @param RetT is the type of return value.
  @param Arg1T is the type of the first argument.
  @param Arg2T is the type of the second argument.
  @param func is the name of function.
 */
template <
	typename RetT,
	typename Arg1T,
	typename Arg2T,
	RetT func(Arg1T, Arg2T)
>
class hryky::AutoFunc2 : public AutoFuncBase
{
public :
	typedef AutoFunc2<RetT, Arg1T, Arg2T, func> this_type;
	
	AutoFunc2(Arg1T arg1, Arg2T arg2)
		: arg1_(arg1), arg2_(arg2)
	{
	}
	
	~AutoFunc2()
	{
		if (!this->disable_) {
			(*func)(this->arg1_, this->arg2_);
		}
	}

private :
	hryky_delete_this_copy_constructor(AutoFunc2);
	hryky_delete_this_copy_assign_op(AutoFunc2);
	
	Arg1T   arg1_;
	Arg2T   arg2_;
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
#endif // AUTOFUNC_H_20130216114450156
// end of file
