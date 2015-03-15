/*
  @file         test_mempool_arbitrary.cpp
  @brief        tests hryky::mempool::Arbitrary.
  @author       HRYKY
  @version      $Id: test_mempool_arbitrary.cpp 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#include <precompiled.h>
#include "hryky/testing.h"
#include "hryky/memory.h"
#include "hryky/random.h"
#include "hryky/common.h"
#include "hryky/raii.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
#define PRINT_ALLOCATION_HISTORY            (0)
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace
{
	// enregisters a test
	class Test : public testing::unit::Base
	{
	public :
		typedef testing::unit::Base base_type;
		typedef Test this_type;
		
		Test()
			: testing::unit::Base("mempool_arbitrary")
		{
		}

	private :
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		// calls a test.
		virtual bool run_impl();
	};
	Test const g_test;

	// tests mempool::Arbitrary with a seed of randomizer
	template < typename OffsetT = mempool::Arbitrary<>::offset_type >
	class TestPool
	{
	public :
		typedef TestPool<OffsetT> this_type;
		TestPool(
			Test & test, uint32_t seed)
			: test_(test)
			  , seed_(seed)
		{
		}

		bool run();

	private :
		TestPool(this_type const &);
		this_type & operator=(this_type const &);
		
		Test &      test_;
		uint32_t    seed_;
	};

}
} // namespace hryky
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace
{
/**
  @brief calls a test.
 */
bool Test::run_impl()
{
	uint32_t const seed = static_cast<uint32_t>(::std::time(0));

	if (!TestPool<uint8_t>(*this, seed).run()) {
		hryky_log_emerg("Testing mempool::Arbitrary<uint8_t> failed");
		return false;
	}

	if (!TestPool<uint16_t>(*this, seed).run()) {
		hryky_log_emerg("Testing mempool::Arbitrary<uint16_t> failed");
		return false;
	}

	if (!TestPool<uint32_t>(*this, seed).run()) {
		hryky_log_emerg("Testing mempool::Arbitrary<uint32_t> failed");
		return false;
	}

	if (!TestPool<uint64_t>(*this, seed).run()) {
		hryky_log_emerg("Testing mempool::Arbitrary<uint64_t> failed");
		return false;
	}

	if (!TestPool<>(*this, seed).run()) {
		hryky_log_emerg("Testing mempool::Arbitrary<> failed");
		return false;
	}

	return true;
}
/**
  @brief tests mempool::Arbitrary with seed of randomizer.
 */
template < typename OffsetT >
bool TestPool<OffsetT>::run()
{
	uint32_t const seed = this->seed_;

	// initializes logging.
	testing::Log log(this->test_);

	// initializes a generator of pseudo random number.
	testing::Random random;
	random.seed(seed);

	log.writer() << "randomd" << random;

	// initializes the generator of random number according to the normal distribution.
	random::Normal<size_t> allocation_size_dist(
		random.generator(),
		0x1000,         // deviation
		0x400,          // mean
		0x1,            // min
		0x80000);       // max

	// initializes the generator of random number according to the uniform distribution.
	random::Uniform<uint32_t> allocations_number_dist(
		random.generator(),
		1,              // min
		0x80000);       // max

	alignment_type const alignment = allocations_number_dist() % 5 + 1;

	log.writer() << "alignment" << static_cast<size_t>(alignment);

	size_t const buffer_size = 0x10000u << alignment;

	void * buffer = ::std::malloc(buffer_size);
	AutoFree const free_buffer(buffer);

	if (hryky_nullptr == buffer) {
		hryky_log_crit(
			"failed to allocate buffer "
			"for the test of memory::Pool::Arbitrary "
			<< (json::writer()
				<< "buffer_size" << buffer_size));
		return false;
	}

	hryky::memset(buffer, -1, buffer_size);

	typedef mempool::Arbitrary<OffsetT> mempool_type;

	mempool_type mempool;

	if (!mempool.reset(buffer, buffer_size, alignment)) {
		hryky_log_crit(
			"failed to reset mempool::Arbitrary "
			<< (json::writer()
				<< "buffer_size" << buffer_size));
		return false;
	}

	log.writer() << "mempool" << mempool;

	if (!mempool.verify()) {
		hryky_log_crit("Verification failed.");
		return false;
	}

	size_t const allocations_size = allocations_number_dist() % 0x100000 + 0x100000;

	log.writer() << "allocations size" << allocations_size;

	typedef ::std::list< ::std::pair<void *, size_t> > allocations_type;

	allocations_type allocations;

	{
		size_t allocation_id = 0;
		for (; allocations_size != allocation_id; ++allocation_id) {
			if (allocations.empty() || 0 == (allocations_number_dist() & 1)) {
				size_t const size = allocation_size_dist();

				alignment_type const alignment =
					static_cast<alignment_type>((allocations_number_dist() % 8 + 1));

				void * allocated = mempool.allocate(size, alignment);

				if (hryky_nullptr == allocated) {
					log.writer() << "failed to allocate";
					auto const map = stream::map::scope(log.writer());
					(log.writer()
					 << "index" << allocation_id
					 << "size" << size
					 << "alignment" << static_cast<uint32_t>(alignment)
					 << "mempool" << mempool
					 );
					break;
				}

				{
					uint8_t * ptr = reinterpret_cast<uint8_t *>(allocated);
					uint8_t * const end = ptr + size;

					for (; end != ptr; ++ptr) {
						*ptr = static_cast<uint8_t>(reinterpret_cast<size_t>(ptr));
					}
				}

#if PRINT_ALLOCATION_HISTORY
				{
					(log.writer()
					 << "allocate" << mempool_type::Address(mempool, allocated)
					 << "fragments" << static_cast<size_t>(mempool.free_nodes_size())
					 << "mempool" << mempool
					 );
				}
#endif // PRINT_ALLOCATION_HISTORY

				allocations_type::iterator itr = allocations.begin();

				size_t const offset = allocations_number_dist() % (allocations.size() + 1);

				size_t offset_id = 0;
				for (; offset != offset_id; ++offset_id) {
					++itr;
				}

				allocations.insert(
					itr, allocations_type::value_type(allocated, size));
			}
			else {
				allocations_type::iterator itr = allocations.begin();

				size_t const offset = allocations_number_dist() % allocations.size();

				size_t offset_id = 0;
				for (; offset != offset_id; ++offset_id) {
					++itr;
				}

#if PRINT_ALLOCATION_HISTORY
				{
					(log.writer()
					 << "deallocate" << mempool_type::Address(mempool, (*itr).first)
					 << "fragments" << static_cast<size_t>(mempool.free_nodes_size())
					 );
				}
#endif // PRINT_ALLOCATION_HISTORY

				if (!mempool.deallocate((*itr).first)) {
					hryky_log_crit(
						"failed to deallocate "
						<< (json::writer()
							<< "index" << allocation_id
							<< "address" << (*itr).first
							<< "size" << (*itr).second
							<< "mempool" << mempool));
					return false;
				}

#if PRINT_ALLOCATION_HISTORY
				log.writer() << "mempool" << mempool;
#endif

				allocations.erase(itr);
			}
		}

		if (!mempool.verify()) {
			hryky_log_crit("Verification failed.");
			return false;
		}
	}

	size_t count = 0;

	while (!allocations.empty()) {
		allocations_type::iterator itr = allocations.begin();

		{
			uint8_t * ptr = reinterpret_cast<uint8_t *>((*itr).first);
			uint8_t * const end = ptr + (*itr).second;

			for (; end != ptr; ++ptr) {
				if ((*ptr) !=
					 static_cast<uint8_t>(reinterpret_cast<size_t>(ptr)))
				{
					hryky_log_crit(
						"memory corruption occurred "
						<< (json::writer()
							<< "count" << count
							<< "address" << reinterpret_cast<size_t>(ptr)
							<< "begin" << (*itr).first
							<< "end" << reinterpret_cast<size_t>(end)
							<< "info" << mempool_type::Address(mempool, (*itr).first)
							));
					return false;
				}
			}
		}

		size_t const offset = allocations_number_dist() % allocations.size();

		size_t offset_id = 0;
		for (; offset != offset_id; ++offset_id) {
			++itr;
		}

#if PRINT_ALLOCATION_HISTORY
		{
			(log.writer()
			 << "deallocate" << mempool_type::Address(mempool, (*itr).first)
			 << "fragments" << static_cast<size_t>(mempool.free_nodes_size())
			 );
		}
#endif // PRINT_ALLOCATION_HISTORY

		if (!mempool.deallocate((*itr).first)) {
			hryky_log_crit(
				"failed to deallocate "
				<< (json::writer()
					<< "index" << count
					<< "address" << (*itr).first
					<< "size" << (*itr).second
					<< "mempool" << mempool));
			return false;
		}

		allocations.erase(itr);
		++count;
	}

	if (!mempool.verify()) {
		hryky_log_crit("Verification failed.");
		return false;
	}

	// log_out.disable();

	return true;
}
} // namespace *anonymous*
} // namespace hryky

//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
