/**
  @file     test_bind.cpp
  @brief    tests hryky::Binder.
  @author   HRYKY
  @version  $Id: test_bind.cpp 353 2014-06-17 04:55:19Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/functional/binder.h"
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

		/// tests hryky::Binder.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "bind";

	struct Functor1 :
		public FunctionTraits1<int, int>
	{
		int operator()(int const x)
		{
			return x;
		}
	};

	struct Multiply :
		public FunctionTraits2<int, int, int>
	{
		int operator()(int const lhs, int const rhs)
		{
			return lhs * rhs;
		}
	};

	struct Functor3 :
		public FunctionTraits3<int, int, int, int>
	{
		int operator()(int const a, int const b, int const c)
		{
			return a * (b - c);
		}
	};

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
  @brief tests hryky::Binder.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	{
		typedef Binder1<Functor1, int> binder_type;
		binder_type binder(Functor1(), 1);
		if (1 != binder()) {
			hryky_log_alert("failed to bind.");
			return false;
		}
	}

	{
		typedef Binder1<Functor1, int> binder_type;
		binder_type binder(Functor1(), 1);
		if (1 != binder(2)) {
			hryky_log_alert("failed to bind.");
			return false;
		}
	}

	{
		typedef Binder1<Functor1, Placeholder<0> > binder_type;
		binder_type binder = binder_type(Functor1(), Placeholder<0>());
		if (1 != binder(1)) {
			hryky_log_alert("failed to bind.");
			return false;
		}
	}

	{
		if (1 != bind(Multiply(), 1, 1)()) {
			hryky_log_alert("failed to bind.");
			return false;
		}
	}
	
	{
		if (2 != bind(Multiply(), Placeholder<0>(), 2)(1)) {
			hryky_log_alert("failed to bind.");
			return false;
		}
	}
	
	{
		if (2 != bind(Multiply(), 2, Placeholder<0>())(1)) {
			hryky_log_alert("failed to bind.");
			return false;
		}
	}
	
	{
		if (4 != bind(Multiply(), Placeholder<0>(), Placeholder<0>())(2)) {
			hryky_log_alert("failed to bind.");
			return false;
		}
	}

	{
		if (-1 != bind(
			Functor3(),
			Placeholder<0>(),
			Placeholder<1>(),
			Placeholder<2>())(1, 2, 3)) {
			hryky_log_alert("failed to bind.");
			return false;
		}
	}
	
	{
		if (-3 != bind(
			Functor3(),
			Placeholder<2>(),
			Placeholder<0>(),
			Placeholder<1>())(1, 2, 3)) {
			hryky_log_alert("failed to bind.");
			return false;
		}
	}
	
	{
		if (-2 != bind(
			Functor3(),
			Placeholder<1>(),
			Placeholder<2>(),
			4)(1, 2, 3)) {
			hryky_log_alert("failed to bind.");
			return false;
		}
	}
	

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
