/**
  @file     test_swap.cpp
  @brief    tests to interchange two instances.
  @author   HRYKY
  @version  $Id: test_swap.cpp 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/with_swap.h"
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
		
		/// tests to interchange two instances.
		virtual bool run_impl();

	};
	Test const g_test;

	class Swapped :
		public WithSwap<Swapped>
	{
	public :
		typedef Swapped this_type;
		
		Swapped(testing::Log & log)
			: log_(log)
		{
		}

		void swap(this_type &)
		{
			hryky_log_debug("swapped by defined function.");
		}

	private :
		hryky_delete_default_constructor(Swapped);
		hryky_delete_copy_constructor(Swapped);
		hryky_delete_copy_assign_op(Swapped);
		
		testing::Log & log_;
	};

	char const * const g_testname = "swap";

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
  @brief tests to interchange two instances.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	{
		Swapped lhs(log);
		Swapped rhs(log);

		hryky::swap(lhs, rhs);
	}

	{
		int x = 0;
		int y = 0;
		hryky::swap(x, y);
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
