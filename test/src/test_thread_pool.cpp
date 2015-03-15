/*
  @file         test_thread_pool.cpp
  @brief        tests to reuse concurrent units.
  @author       HRYKY
  @version      $Id: test_thread_pool.cpp 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
 */
#include <precompiled.h>
#include "hryky/log.h"
#include "hryky/random.h"
#include "hryky/scoped_array.h"
#include "hryky/thread.h"
#include "hryky/testing.h"
#include "hryky/mempool.h"
#include "hryky/exclusion.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace
{
	// enregisters a test
	class Test : testing::unit::Base
	{
	public :
		typedef testing::unit::Base base_type;
		typedef Test this_type;
		
		Test()
			: testing::unit::Base("thread_pool")
		{
		}
		
	private :
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		// tests to reuse concurrent units.
		virtual bool run_impl();
	};
	Test const g_test;

}
} // namespace hryky
//------------------------------------------------------------------------------
// global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace
{
/**
  @brief tests to reuse concurrent units.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes a random number generator
	testing::Random random;

	log.writer() << "random" << random;

	thread::raw_processor_id_type const hardware_concurrency =
		thread::hardware_concurrency();
	hryky_log_info((
		json::writer()
		<< hryky_stream_denote(hardware_concurrency)));

	// decides the size of callable units
	random::Normal<size_t>
		dist(random.generator(), 0x1000);
	(dist.mean(0x800).min(0x100).max(0x1000));

	// decides the size of callable units
	random::Uniform<size_t>
		allocate_size_dist(random.generator(), 0x1, 0x100);

	size_t const callables_size = dist();

	(log.writer()
	 << "callables_size" << callables_size
	 << "callables_size_distribution" << dist);

	// executes callable units on multiple threads concurrently.
	{
		// the pool of thread resources.
		thread::pool_type thread_pool;

		exclusion::Counter<> counter;

		// enregisters multiple callable units.
		if (!repeat(callables_size).every_at([&thread_pool, &counter](
			size_t const index) {
			if (!thread_pool.run([&counter]() {
				++counter;
			})) {
				hryky_log_err(
					"failed to run a concurrent unit: "
					<< index);
				return false;
			}
			return true;
		})) {
			hryky_log_alert(
				"failed to run concurrent units.");
			return false;
		}

		// waits until the all callable units terminate
		size_t const joinable_sec = 10u;
		if (!thread_pool.join(chrono::seconds(joinable_sec))) {
			hryky_log_alert("elapsed seconds " << joinable_sec);
			return false;
		}

		if (callables_size != counter.value()) {
			hryky_log_alert(
				"failed to count the number concurrently.");
			return false;
		}
	}
	
	return true;
}
} // namespace
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
