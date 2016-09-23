/**
  @file         test_mempool_stack.cpp
  @brief        tests hryky::mempool::Stack.
  @author       HRYKY
  @version      $Id: test_mempool_stack.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/memory.h"
#include "hryky/raii.h"
#include "hryky/stream.h"
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
namespace memory
{
namespace mempool
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
		hryky_delete_copy_constructor(Test);
		hryky_delete_copy_assign_op(Test);
		
		typedef hryky::mempool::stack_type mempool_type;

		/// tests hryky::mempool::Stack.
		virtual bool run_impl();
	};
	Test const g_test;

	char const * const g_testname = "mempool_stack";

	/// fills a range of the buffer.
	void fill(void * const dest, size_t const size);

	/// confirms whether the values in the range of buffer are valid.
	bool verify(void const * const src, size_t const size);

} // namespace "anonymous"
} // namespace mempool
} // namespace memory
} // namespace test
} // namespace hryky
namespace hryky
{
namespace test
{
namespace memory
{
namespace mempool
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
  @brief tests hryky::mempool::Stack.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;

	log.writer() << "random" << random;

	// the distribution for the size of buffer.
	random::Uniform<size_t>
		buffer_size_dist(
			random.generator(),
			0x400, // min
			0x100000); // max
	
	// the distribution for the address alignment.
	random::Uniform<alignment_type>
		alignment_dist(
			random.generator(),
			0x3, // min
			0x8); // max
	
	// the distribution for the size of each allocation.
	random::Normal<size_t>
		size_dist(
			random.generator(),
			0x40, // deviation
			0x40, // mean
			0x1, // min
			0x400); // max

	size_t const buffer_size = buffer_size_dist();

	(log.writer()
	<< stream::denote("buffer_size") << buffer_size);

	void * buffer = ::std::malloc(buffer_size);
	AutoFree const free_buffer(buffer);
	if (hryky_nullptr == buffer) {
		hryky_log_crit(
			"failed to allocate the region for a mempool. "
			<< (json::writer()
				<< "buffer_size" << buffer_size));
		return false;
	}

	hryky::memset(buffer, 0, buffer_size);

	mempool_type mempool(buffer, buffer_size);

	log.writer() << "initial_mempool" << mempool;

	alignment_type alignment = alignment_dist();
	size_t rest = mempool.allocatable_size(alignment);

	typedef ::std::pair<void *, size_t>       address_type;
	typedef Vector<address_type>            addresses_type;
	typedef addresses_type::const_reference const_reference;
	typedef addresses_type::size_type       size_type;

	addresses_type addresses;

	while (0 < rest) {
		size_t const size = ::std::min<size_t>(rest, size_dist());
		void * const address = mempool.allocate(size, alignment);

		if (hryky_nullptr == address) {
			hryky_log_crit(
				"failed to allocate memory. "
				<< (json::writer()
				<< stream::denote("size") << size
				<< stream::denote("alignment") << alignment
				<< stream::denote("rest") << rest
				<< stream::denote("mempool") << mempool));
			return false;
		}

		if (!hryky::is_aligned(address, alignment)) {
			hryky_log_crit(
				"The allocated address is no aligned. "
				<< (json::writer()
				<< stream::denote("address") << address
				<< stream::denote("size") << size
				<< stream::denote("alignment") << alignment
				<< stream::denote("rest") << rest
				<< stream::denote("mempool") << mempool));
			return false;
		}

		fill(address, size);
		addresses.push_back(address_type(address, size));

		alignment = alignment_dist();
		rest = mempool.allocatable_size(alignment);
	}

	log.writer() << "completed_mempool" << mempool;

	// deallocates addresses.
	if (!hryky::range(addresses.rbegin(), addresses.rend()).every_at(
		[&mempool](
			const_reference element, size_type const) {
			if (!verify(element.first, element.second)) {
				hryky_log_crit(
					"The data in the allocated address is invalid. "
					<< (json::writer()
					<< stream::denote("address") << element.first
					<< stream::denote("size") << element.second));
				return false;
			}
			if (!mempool.deallocate(element.first)) {
				hryky_log_crit(
					"failed to deallocate memory. "
					<< (json::writer()
					<< stream::denote("address") << element.first
					<< stream::denote("size") << element.second));
				return false;
			}
			return true;
		})) {
		hryky_log_alert("failure of " << addresses);
		return false;
	}

	log.writer() << "deallocated_mempool" << mempool;

	return true;
}
/**
  @brief fills a range of the buffer.
 */
void fill(void * const dest, size_t const size)
{
	uint8_t * const begin = reinterpret_cast<uint8_t *>(dest);
	uint8_t * const end = begin + size;

	hryky::range(begin, end).foreach_at([](
		uint8_t & element, size_t const index) {
		element = static_cast<uint8_t>(index & 0xFF);
	});
}
/**
  @brief confirms whether the values in the range of buffer are valid.
 */
bool verify(void const * const src, size_t const size)
{
	uint8_t const * const begin = reinterpret_cast<uint8_t const *>(src);
	uint8_t const * const end = begin + size;

	return hryky::range(begin, end).every_at([](
		uint8_t const & element, size_t const index) {
		return element == static_cast<uint8_t>(index & 0xFF);
	});
}
} // namespace "anonymous"
} // namespace mempool
} // namespace memory
} // namespace test
} // namespace hryky
