/**
  @file     test_tuple.cpp
  @brief    tests tuple.
  @author   HRYKY
  @version  $Id: test_tuple.cpp 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/tuple.h"
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
		
		/// tests tuple.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "tuple";

	template <typename ValueT>
	struct FunctionTest
	{
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
  @brief tests tuple.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	char const * const cstr = "foo";

	{
		log.writer() << "array";
		testing::Log::array_type const array(log.writer());

		(log.writer()
		 << make_tuple()
		 << make_tuple(0x100)
		 << make_tuple(0x100, cstr)
		 << make_tuple(0x100, cstr, -10)
		);
	}

	{
		typedef Tuple1<float> tuple_type;
		tuple_type const source(1.0f);
		tuple_type modified(source);

		modified.at<0>() = 2.0f;

		(log.writer()
		 << "tuple1 "
		 << (json::writer()
			 << "source" << source
			 << "modified" << modified));
	}

	{
		typedef Tuple2<float, char const *> tuple_type;

		auto const source = make_tuple(1.0f, cstr);
		tuple_type modified(source);

		modified.at<0>() = 2.0f;
		modified.at<1>() = "bar";

		(log.writer() << "tuple2 "
		 << (json::writer()
			 << "source" << source
			 << "modified" << modified
			 ));
	}

	{
		typedef float array_type[3];
		array_type array = { 1.0f, 2.0f, 3.0f, };
		typedef TupleAdapter<array_type> tuple_type;

		tuple_type modified(array);

		modified.at<0>() = 4.0f;
		modified.at<1>() = 5.0f;
		modified.at<2>() = 6.0f;

		(log.writer() << "tuple2 "
		 << (json::writer()
			 << "modified" << modified));
	}

	{
		auto args = make_tuple(1, 0.5f, true);
		tuple::Call<void, decltype(args)>::by([&log](
			int const arg1, float const arg2, bool const arg3) {
			(log.writer() << "callWithTuple"
			 << (json::writer()
				 << "arg1" << arg1
				 << "arg2" << arg2
				 << "arg3" << arg3));
		}, args);
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
