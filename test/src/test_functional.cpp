/**
  @file     test_functional.cpp
  @brief    tests functional module.
  @author   HRYKY
  @version  $Id: test_functional.cpp 353 2014-06-17 04:55:19Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/functional.h"
#include "hryky/type_traits.h"
#include "hryky/function_traits.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace test
{
namespace
{
	// enretisters a test.
	class Test : testing::unit::Base
	{
	public:
		typedef testing::unit::Base base_type;
		typedef Test this_type;

		/// constructor.
		Test();

	private:
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		/// tests functional module.
		virtual bool run_impl();

	};
	Test const g_test;

	int func0()
	{
		return 0;
	}

	void void_func0()
	{
	}

	int func1(int const)
	{
		return 0;
	}

	void void_func1(int const)
	{
	}

	class Cls
	{
	public :
		int func0()
		{
			return 0;
		}

		void void_func0()
		{
		}

		int func1(int const)
		{
			return 0;
		}

		void void_func1(int const)
		{
		}
		
		int func0_c() const
		{
			return 0;
		}

		void void_func0_c() const
		{
		}

		int func1_c(int const) const
		{
			return 0;
		}

		void void_func1_c(int const) const
		{
		}
		
	};

	class VoidCls0
	{
	public :
		void operator()();

		void operator()(int);
	};
		
	class VoidCls0C
	{
	public :
		void operator()() const;
	};
		

	char const * const g_testname = "functional";

} // namespace "anonymous"
} // namespace test
} // namespace hryky
namespace hryky
{
namespace test
{
namespace
{
//------------------------------------------------------------------------------
// public member functions of Test
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
Test::Test()
	: base_type(g_testname)
{
}
//------------------------------------------------------------------------------
// private member functions of Test
//------------------------------------------------------------------------------
/**
  @brief tests functional module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	{
		typedef int (*func_ptr)(void);

		static_assert(
			IsSame<
				int,
				FunctionTraits<func_ptr>::result_type
			>::type::value,
			"failed");
	}

	{
		typedef int (Cls::*func_ptr)(void);
		static_assert(
			IsSame<
				int,
				FunctionTraits<func_ptr>::result_type
			>::type::value,
			"failed");
	}

	static_assert(
		!HasCallableOp0<Cls, void>::type::value,
		"Cls doesn't overload the function call operator.");

	static_assert(
		HasCallableOp0<VoidCls0, void>::type::value,
		"VoidCls0 overloads the function call operator.");

	static_assert(
		!HasCallableOp0C<VoidCls0, void>::type::value,
		"VoidCls0 overloads the function call operator.");

	static_assert(
		HasCallableOp0C<VoidCls0C, void>::type::value,
		"VoidCls0C overloads the function call operator.");

	static_assert(
		!HasCallableOp0<VoidCls0C, void>::type::value,
		"VoidCls0C overloads the function call operator.");

	static_assert(
		HasCallableOp1<VoidCls0, void, int>::type::value,
		"VoidCls0 overloads the function call operator.");

	static_assert(
		!HasCallableOp1C<VoidCls0, void, int>::type::value,
		"VoidCls0 overloads the function call operator.");

	{
		auto func = function(func0);
		func();

		func = function(func0);
	}

	{
		auto func = function(void_func0);
		func();
	}

	{
		auto func = function(func1);
		func(0);

		func = function(func1);
	}

	{
		auto func = function(void_func1);
		func(0);
	}

	{
		auto func = function(&Cls::func0);
		Cls cls;
		func(cls);
	}

	{
		auto func = function(&Cls::void_func0);
		Cls cls;
		func(cls);
	}

	{
		Memfun1<Cls, int, int> func = function(&Cls::func1);
		Cls cls;
		func(cls, 0);
	}

	{
		auto func = function(&Cls::void_func1);
		Cls cls;
		func(cls, 0);
	}

	{
		auto func = function(&Cls::func0_c);
		func(Cls());
	}

	{
		auto func = function(&Cls::void_func0_c);
		func(Cls());
	}

	

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
