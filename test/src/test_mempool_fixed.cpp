/*
  @file         test_mempool_fixed.cpp
  @brief        tests hryky::mempool::Fixed.
  @author       HRYKY
  @version      $Id: test_mempool_fixed.cpp 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#include <precompiled.h>
#include "hryky/testing.h"
#include "hryky/random.h"
#include "hryky/memory.h"
#include "hryky/common.h"
#include "hryky/raii.h"
#include "hryky/bitsize_of.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
#define PRINT_ALLOCATION_HISTORY            (1)
//------------------------------------------------------------------------------
// declarations
//------------------------------------------------------------------------------
namespace hryky
{
namespace test
{
namespace
{
	// enregisters a test
	class Test : hryky::testing::unit::Base
	{
	public :
		typedef testing::unit::Base base_type;
		typedef Test this_type;
		
		Test()
			: testing::unit::Base("mempool_fixed")
		{
		}

	private :
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		// tests hryky::mempool::Fixed.
		virtual bool run_impl();
	};
	Test const g_test;

	/// tests mempool::Fixed for each IndexT.
	template <typename IndexT>
	bool test_by_index(testing::Log & log, testing::Random & random);

} // namespace *anonymous*
} // namespace test
} // namespace hryky
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace test
{
namespace
{
/**
  @brief tests hryky::mempool::Fixed.
 */
bool Test::run_impl()
{
	// initialize logging.
	testing::Log log(*this);

	// initialize a generator of pseudo random number.
	testing::Random random;

	log.writer() << "random" << random;

	if (!test_by_index<uint16_t>(log, random)) {
		hryky_log_alert("failed to test mempool::Fixed<uint16_t>");
		return false;
	}
	
	if (!test_by_index<uint32_t>(log, random)) {
		hryky_log_alert("failed to test mempool::Fixed<uint16_t>");
		return false;
	}
	
	if (!test_by_index<uint64_t>(log, random)) {
		hryky_log_alert("failed to test mempool::Fixed<uint16_t>");
		return false;
	}

	return true;
}
/**
  @brief tests mempool::Fixed for each IndexT.
 */
template <typename IndexT>
bool test_by_index(testing::Log & log, testing::Random & random)
{
	/**
	  initializes the generator of pseudo-random number according to the
	  uniform distribution.
	 */
	random::Uniform<uint32_t>
		allocations_number_dist(random.generator(), 1, 0x1000);

	typedef hryky::mempool::Fixed<IndexT>  fixed_mempool_type;
	typedef fixed_mempool_type::index_type       index_type;
	typedef fixed_mempool_type::unit_size_type   unit_size_type;
	
	/**
	  initializes the generator of pseudo-random number according to the
	  normal distribution.
	 */
	random::Normal<unit_size_type>
		unit_size_dist(
			random.generator(),
			0x40,           // deviation
			0x40,           // mean
			1,              // min
			0x10000);       // max
	unit_size_type const unit_size = unit_size_dist();

	/**
	  initializes the generator of pseudo-random number according to the
	  normal distribution.
	 */
	random::Normal<alignment_type> alignment_dist(
		random.generator(),
		0x4, // deviation
		0x8, // mean
		fixed_mempool_type::min_alignment,// min
		0x10);// max
	alignment_type const alignment = alignment_dist();

	// initialize a fixed memory pool.
	fixed_mempool_type mempool(unit_size, alignment);

	/**
	  initializes the generator of pseudo-random number according to the
	  normal distribution.
	 */
	random::Normal<index_type>
		units_size_dist(
			random.generator(),
			0x1000,         // deviation
			0x400,          // mean
			1,              // min
			MaxOf<index_type>::value >>
			(BitsizeOf<index_type>::value / 3u));       // max
	index_type const units_size = units_size_dist();

	size_t const buffer_size =
		mempool.buffer_size(units_size) + mempool.byte_alignment();

	(log.writer()
	<< stream::denote("alignment") << alignment
	<< stream::denote("unit_size") << unit_size
	<< stream::denote("units_size") << units_size
	<< stream::denote("buffer_size") << buffer_size
	 );

	void * buffer = ::std::malloc(buffer_size);
	AutoFree const free_buffer(buffer);

	if (hryky_nullptr == buffer) {
		hryky_log_crit(
			"failed to allocate buffer for the test of "
			"memory::Pool::Arbitrary "
			<< (json::writer()
				<< "the size of one unit" << unit_size
				<< "the number of units" << units_size
				<< "the size of buffer" << buffer_size
				));
		return false;
	}

	hryky::memset(buffer, -1, buffer_size);

	if (!mempool.reset(buffer, buffer_size)) {
		hryky_log_crit(
			"failed to reset mempool::Arbitrary "
			<< (json::writer()
				<< "buffer_size" << buffer_size
				));
		return false;
	}

	if (!mempool.verify()) {
		hryky_log_crit("Verification failed.");
		return false;
	}

	size_t const allocations_size_width =   0x10000u;
	size_t const allocations_size_min =     0x1000u;

	size_t const allocations_size =
		allocations_number_dist() % allocations_size_width +
			allocations_size_min;

	log.writer() << "allocations size" << allocations_size;

	typedef ::std::list< void * > allocations_type;

	allocations_type allocations;

	{
		size_t allocation_id = 0;
		for (; allocations_size != allocation_id; ++allocation_id) {
			if (allocations.empty() ||
				0 == (allocations_number_dist() & 1)) {
				void * allocated = mempool.allocate();

				if (hryky_nullptr == allocated) {
					log.writer() << "failed to allocate";
					auto const map = stream::map::scope(log.writer());
					(log.writer()
					 << "index" << allocation_id
					 << "mempool" << mempool
					 );

					if (0 != mempool.available_size()) {
						hryky_log_crit(
							"unexpected allocation failure occurred "
							<< (json::writer()
								<< "allocation_id" << allocation_id
								<< "units_size" << units_size
								));
						return false;
					}
					
					break;
				}

				{
					uint8_t * ptr = reinterpret_cast<uint8_t *>(allocated);
					uint8_t * const end = ptr + unit_size;

					for (; end != ptr; ++ptr) {
						*ptr = static_cast<uint8_t>(
							reinterpret_cast<size_t>(ptr));
					}
				}

#if PRINT_ALLOCATION_HISTORY
				(log.writer()
				 << "allocate" << fixed_mempool_type::address_type(mempool, allocated)
				 << "available" << mempool.available_size()
				 );
#endif // PRINT_ALLOCATION_HISTORY

				allocations_type::iterator itr = allocations.begin();

				size_t const offset =
					allocations_number_dist() % (allocations.size() + 1);

				size_t offset_id = 0;
				for (; offset != offset_id; ++offset_id) {
					++itr;
				}

				allocations.insert(
					itr, allocations_type::value_type(allocated));
			}
			else {
				allocations_type::iterator itr = allocations.begin();

				size_t const offset =
					allocations_number_dist() % allocations.size();

				size_t offset_id = 0;
				for (; offset != offset_id; ++offset_id) {
					++itr;
				}

#if PRINT_ALLOCATION_HISTORY
				(log.writer()
				<< stream::denote("deallocate") << fixed_mempool_type::address_type(mempool, *itr)
				<< stream::denote("avaiable") << mempool.available_size()
				 );
#endif // PRINT_ALLOCATION_HISTORY

				if (!mempool.deallocate(*itr)) {
					hryky_log_crit(
						"failed to deallocate "
						<< (json::writer()
							<< "index" << allocation_id
							<< "address" << *itr
							<< "mempool" << mempool
							));
					return false;
				}

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
			uint8_t * ptr = reinterpret_cast<uint8_t *>(*itr);
			uint8_t * const end = ptr + unit_size;

			for (; end != ptr; ++ptr) {
				if ((*ptr) !=
					 static_cast<uint8_t>(reinterpret_cast<size_t>(ptr)))
				{
					hryky_log_crit(
						"memory corruption occurred "
						<< (json::writer()
							<< "count" << count
							<< "octet_address" << ptr
							<< "begin" << *itr
							<< "end" << end
							<< "address"
							<< fixed_mempool_type::address_type(mempool,  *itr)
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
		(log.writer()
		 << stream::denote("deallocate")
		 << fixed_mempool_type::address_type(mempool, *itr)
		 << stream::denote("available")
		 << mempool.available_size()
		 );
#endif // PRINT_ALLOCATION_HISTORY

		if (!mempool.deallocate(*itr)) {
			hryky_log_crit(
				"failed to deallocate "
				<< (json::writer()
					<< "index" << count
					<< "address" << *itr
					<< "mempool" << mempool
					));
			return false;
		}

		allocations.erase(itr);
		++count;
	}

	if (!mempool.verify()) {
		hryky_log_crit("Verification failed.");
		return false;
	}

	(log.writer() << "mempool" << mempool);

	// log_out.disable();

	return true;
}
} // namespace *anonymous*
} // namespace test
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
