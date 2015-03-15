/**
  @file     test_kademlia.cpp
  @brief    tests kademlia module.
  @author   HRYKY
  @version  $Id: test_kademlia.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/kademlia.h"
#include "hryky/bignum.h"
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
		
		/// tests kademlia module.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "kademlia";

	/// generates a buffer with random octets.
	template <typename BufferT, typename RandomT>
	void generate(BufferT & buffer, RandomT & random, size_t const size);

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
  @brief tests kademlia module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	size_t const bits_length = 64;

	typedef kademlia::Endpoint<bits_length> endpoint_type;
	typedef endpoint_type::id_type          id_type;
	typedef Vector<endpoint_type>           endpoints_type;
	typedef Vector<uint8_t>                 data_type;

	random::Uniform<id_type> node_id_dist(
		random.generator());

	random::Normal<size_t> repeat_dist(
		random.generator(),
		0x100,      // deviation,
		0x100,      // mean
		0x10,       // min
		0x1000);    // max

	random::Normal<size_t> size_dist(
		random.generator(),
		0x100,      // deviation,
		0x1000,     // mean
		0x1,        // min
		0x10000);   // max

	random::Uniform<uint8_t> octet_dist(
		random.generator());

	data_type data;

	endpoint_type endpoint;
	endpoint.max_bucket_size(0x20);

	if (!endpoint.reserve()) {
		hryky_log_alert(
			"failed to allocate the buffer for buckets of Kademlia.");
		return false;
	}

	if (!hryky::repeat(repeat_dist()).every(
		[&data, &endpoint, &octet_dist, &size_dist]() {
			generate(data, octet_dist, size_dist());
			return true;
	})) {
		hryky_log_alert(
			"failed to generate.");
		return false;
	}
	

	return true;
}
/**
  @brief fills a buffer with random octets.
 */
template <typename BufferT, typename RandomT>
void generate(BufferT & buffer, RandomT & random, size_t const size)
{
	buffer.clear();
	hryky::repeat(size).foreach([&buffer, &random]() {
		buffer.push_back(random());
	});
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
