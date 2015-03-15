/**
  @file     test_instance_buffer.cpp
  @brief    tests InstanceBuffer.
  @author   HRYKY
  @version  $Id: test_instance_buffer.cpp 372 2014-07-23 14:10:41Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/instance_buffer.h"
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

		class Foo
		{
		public :
			Foo()
				: value_()
			{
			}

			Foo(int32_t const value)
				: value_(value)
			{
			}

			int32_t value() const
			{
				return this->value_;
			}
		private :
			int32_t value_;
		};

		/// tests InstanceBuffer.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "instance_buffer";

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
  @brief tests InstanceBuffer.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	typedef InstanceBuffer<Foo> buffer_type;

	{
		buffer_type const buffer;
		if (!hryky_is_null(buffer)) {
			hryky_log_alert(
				"The result of the default constructor has to be null.");
			return false;
		}
	}

	{
		buffer_type const buffer((Foo()));
		if (hryky_is_null(buffer)) {
			hryky_log_alert(
				"The result of the constructor must not be null.");
			return false;
		}
	}

	{
		buffer_type buffer;
		buffer = Foo();
		if (hryky_is_null(buffer)) {
			hryky_log_alert(
				"The result of assignment must not be null.");
			return false;
		}
	}

	{
		buffer_type const one((Foo(1)));
		if (1 != one->value()) {
			hryky_log_alert(
				"failed to call the member function.");
			return false;
		}
	}

	{
		buffer_type const one((Foo(1)));
		if (1 != (*one).value()) {
			hryky_log_alert(
				"failed to call the member function.");
			return false;
		}
	}

	{
		buffer_type one((Foo(1)));
		buffer_type two((Foo(2)));
		hryky::swap(one, two);
		if (1 != two->value() || 2 != one->value()) {
			hryky_log_alert(
				"failed to interchange instances.");
			return false;
		}
	}

	{
		buffer_type one((Foo(1)));
		buffer_type empty;
		hryky::swap(one, empty);
		if (!hryky_is_null(one) || 1 != empty->value()) {
			hryky_log_alert(
				"failed to interchange instance and empty buffer.");
			return false;
		}
	}

	{
		buffer_type one((Foo(1)));
		buffer_type empty;
		hryky::swap(empty, one);
		if (!hryky_is_null(one) || 1 != empty->value()) {
			hryky_log_alert(
				"failed to interchange instance and empty buffer.");
			return false;
		}
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
