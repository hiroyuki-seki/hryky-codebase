/**
  @file     test_polymorph_buffer.cpp
  @brief    tests PolymorphBuffer.
  @author   HRYKY
  @version  $Id: test_polymorph_buffer.cpp 371 2014-07-22 15:08:20Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/polymorph_buffer.h"
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

		struct ClsKind
		{
			enum Raw
			{
				cls_a,
				cls_b,
			};
		};
		typedef ClsKind::Raw cls_kind_type;

		class ClsA
		{
		public :
			ClsA()
				: value_a_()
			{
			}

			virtual cls_kind_type get() const
			{
				return ClsKind::cls_a;
			};

		private :
			int32_t value_a_;
		};

		class ClsB : public ClsA
		{
		public :
			ClsB()
				: ClsA()
				  , value_b_()
			{
			}

			virtual cls_kind_type get() const
			{
				return ClsKind::cls_b;
			};

		private :
			int32_t value_b_;
		};

		/// tests PolymorphBuffer.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "polymorph_buffer";

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
  @brief tests PolymorphBuffer.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	typedef PolymorphBuffer<ClsA, sizeof(ClsB)> buffer_type;

	{
		buffer_type const buffer;
		if (!hryky_is_null(buffer)) {
			hryky_log_alert(
				"The result of default constructor has to be null.");
			return false;
		}
	}
		
	{
		buffer_type const buffer((ClsA()));
		if (ClsKind::cls_a != buffer->get()) {
			hryky_log_alert(
				"failed to instantiate by copy constructor.");
			return false;
		}
	}

	{
		buffer_type buffer;
		buffer = ClsA();
		if (ClsKind::cls_a != buffer->get()) {
			hryky_log_alert(
				"failed to assign an other instance.");
			return false;
		}
	}

	{
		buffer_type const buffer((ClsB()));
		if (ClsKind::cls_b != buffer->get()) {
			hryky_log_alert(
				"failed to instantiate by copy constructor.");
			return false;
		}
	}

	{
		buffer_type buffer;
		buffer = ClsB();
		if (ClsKind::cls_b != buffer->get()) {
			hryky_log_alert(
				"failed to assign an other instance.");
			return false;
		}
	}

	{
		buffer_type buffer((ClsA()));
		buffer = ClsB();
		if (ClsKind::cls_b != buffer->get()) {
			hryky_log_alert(
				"failed to change the instance.");
			return false;
		}
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
