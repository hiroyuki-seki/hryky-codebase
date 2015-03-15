/**
  @file     test_std.cpp
  @brief    tests the Standard Library.
  @author   HRYKY
  @version  $Id: test_std.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
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

		/// tests the Standard Library.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "std";

	template <typename ValueT>
	class Func
	{
	public :
		typedef Func<ValueT> this_type;
		
		Func(ValueT const & value)
			: value_(value)
		{
			hryky_log_info("Func is instantiated.");
		}

		Func(this_type const & rhs)
			: value_(rhs.value_)
		{
			hryky_log_info("Func is copied.");
		}

		Func(this_type && rhs)
			: value_(::std::move(rhs.value_))
		{
			hryky_log_info("Func is moved.");
		}

		~Func()
		{
			hryky::clear(this->value_);
			hryky_log_info("Func is destroied.");
		}
		
		int operator()(int)
		{
			hryky_log_info(
				(json::writer() << "value" << this->value_));
			return 0;
		}

	private :
		ValueT value_;
	};
	
	template <typename ValueT>
	Func<ValueT> func(ValueT const & src)
	{
		return Func<ValueT>(src);
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
  @brief tests the Standard Library.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	::std::function<int(int)> a;
	{
		Array<size_t, 100u> vec;
		vec.foreach_at([](size_t & elem, size_t const index) {
			elem = index;
		});
		a = func(vec);
	}
	a(0);
	hryky_log_info("size of a is " << sizeof(a));

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
