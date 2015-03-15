/**
  @file     test_result_of.cpp
  @brief    tests ResultOf.
  @author   HRYKY
  @version  $Id: test_result_of.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/type_traits.h"
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

		/// tests ResultOf.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "result_of";

	struct BinaryFunctor :
		public ::std::binary_function<int, float, bool>
	{
		bool operator()(int, float)
		{
			return false;
		}
	};

	struct BinaryMemfun
	{
		bool operator()(int, float)
		{
			return false;
		}
	};

	struct ImmutableBinaryMemfun
	{
		bool operator()(int, float) const
		{
			return false;
		}
	};

	bool function(int, float)
	{
		return false;
	}

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
  @brief tests ResultOf.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	{
		typedef ResultOf<BinaryFunctor>::type type;
	}

	{
		auto function = &BinaryMemfun::operator();
		typedef ResultOf<decltype(function)>::type result_type;
		result_type const result = (BinaryMemfun().*function)(0, 0.0f);
		log.writer() << result;
	}

	{
		auto function = &ImmutableBinaryMemfun::operator();
		typedef ResultOf<decltype(function)>::type result_type;
		result_type const result = (ImmutableBinaryMemfun().*function)(0, 0.0f);
		log.writer() << result;
	}

	{
		typedef int (*function_type)(int, float);
		typedef ResultOf<function_type>::type result_type;
		result_type const result = function(0, 0.0f);
		log.writer() << result;
	}

	{
		auto lambda = [](int x, float y){ return x == static_cast<int>(y); };
		typedef ResultOf<decltype(lambda)(int, float)>::type result_type;
		result_type const result = lambda(0, 0.0f);
		log.writer() << result;
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
