/**
  @file     test_range.cpp
  @brief    tests Range class.
  @author   HRYKY
  @version  $Id: test_range.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/range.h"
#include "hryky/array.h"
#include "hryky/vector.h"
#include "hryky/list.h"
#include "hryky/deque.h"
#include "hryky/fixed_vector.h"
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
		
		/// tests Range class.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "range";

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
  @brief tests Range class.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	size_t const array_size = 5;
	uint32_t const array[array_size] = { 0x1u, 0x2u, 0x3u, 0x4u, 0x5u, };
	uint32_t const * const array_begin = &array[0];
	uint32_t const * const array_end = &array[array_size];

	// immutable built-in array.
	{
		log.writer() << "immutable built-in array" << range(array);
	}

	// mutable built-in array.
	{
		uint32_t mutable_array[array_size] = { 0x1u, 0x2u, 0x3u, 0x4u, 0x5u, };

		range(mutable_array).foreach([](uint32_t & element) {
			element |= 0x80;
		});

		log.writer() << "mutable built-in array" << range(mutable_array);
	}

	// immutable Array.
	{
		typedef Array<uint32_t const, 5> immutable_array_type;
		
		immutable_array_type const immutable_array = { 0x1u, 0x2u, 0x3u, 0x4u, 0x5u, };

		typedef IteratorOf<immutable_array_type>::type immutable_array_iterator;

		log.writer() << "immutable Array" << range(immutable_array);
	}

	// mutable Array.
	{
		Array<uint32_t, 5> mutable_array = { 0x1u, 0x2u, 0x3u, 0x4u, 0x5u, };

		range(mutable_array).foreach([](uint32_t & element) {
			element |= 0x80;
		});

		log.writer() << "mutable Array" << range(mutable_array);
	}

	// immutable ::std::vector
	{
		::std::vector<uint32_t> const container(
			array_begin, array_end);

		log.writer() << "immutable ::std::vector" << range(container);
	}

	// mutable ::std::vector
	{
		::std::vector<uint32_t> container(array_begin, array_end);

		range(container).foreach([](uint32_t & element) {
			element |= 0x80;
		});
		
		log.writer() << "mutable ::std::vector" << range(container);
	}

	// immutable Vector
	{
		Vector<uint32_t> const container(array_begin, array_end);

		log.writer() << "immutable Vector" << range(container);
	}

	// mutable Vector
	{
		Vector<uint32_t> container(array_begin, array_end);

		range(container).foreach([](uint32_t & element) {
			element |= 0x80;
		});
		
		log.writer() << "mutable Vector" << range(container);
	}

	// immutable List
	{
		List<uint32_t> const container(array_begin, array_end);

		log.writer() << "immutable List" << range(container);
	}

	// mutable List
	{
		List<uint32_t> container(array_begin, array_end);

		range(container).foreach([](uint32_t & element) {
			element |= 0x80;
		});
		
		log.writer() << "mutable List" << range(container);
	}

	// immutable Deque
	{
		Deque<uint32_t> const container(array_begin, array_end);

		log.writer() << "immutable Deque" << range(container);
	}

	// mutable Deque
	{
		Deque<uint32_t> container(array_begin, array_end);

		range(container).foreach([](uint32_t & element) {
			element |= 0x80;
		});
		
		log.writer() << "mutable Deque" << range(container);
	}

	// immutable FixedVector
	{
		FixedVector<uint32_t, 5> const container(array_begin, array_end);

		log.writer() << "immutable FixedVector" << range(container);
	}

	// mutable FixedVector
	{
		FixedVector<uint32_t, 5> container(array_begin, array_end);

		range(container).foreach([](uint32_t & element) {
			element |= 0x80;
		});
		
		log.writer() << "mutable FixedVector" << range(container);
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
