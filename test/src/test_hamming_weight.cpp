/**
  @file     test_hamming_weight.cpp
  @brief    tests hryky::hamming_weight.
  @author   HRYKY
  @version  $Id: test_hamming_weight.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/repeat.h"
#include "hryky/integer.h"
#include "hryky/hamming_weight.h"
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
namespace hamming
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
		
		/// tests hryky::hamming_weight.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "hamming_weight";

	/// tests by type.
	template <typename ValueT>
	bool test_hamming_weight(testing::Log & log, testing::Random & random);

	/// counts the number of non-zero bits by using loop.
	template <typename ValueT>
	size_t popcount(ValueT const value);

} // namespace "anonymous"
} // namespace hamming
} // namespace test
} // namespace hryky
namespace hryky
{
namespace test
{
namespace hamming
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
  @brief tests hryky::hamming_weight.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	if (!repeat(1000u).every([&log, &random]() {
		if (!test_hamming_weight<uint64_t>(log, random)) {
			hryky_log_alert("Testing uint64_t failed.");
			return false;
		}
		if (!test_hamming_weight<uint32_t>(log, random)) {
			hryky_log_alert("Testing uint32_t failed.");
			return false;
		}
		if (!test_hamming_weight<uint16_t>(log, random)) {
			hryky_log_alert("Testing uint16_t failed.");
			return false;
		}
		if (!test_hamming_weight<uint8_t>(log, random)) {
			hryky_log_alert("Testing uint8_t failed.");
			return false;
		}
		return true;
	})) {
		return false;
	}

	return true;
}
/**
  @brief tests by type.
 */
template <typename ValueT>
bool test_hamming_weight(
	testing::Log &, testing::Random & random)
{
	typedef ValueT value_type;

	// randomizes value.
	random::Uniform<ValueT> value_dist(
		random.generator(), 0x0u, MaxOf<ValueT>::value);

	value_type const value = value_dist();

	size_t const result = hamming_weight(value);
	size_t const check = popcount(value);

	if (result != check) {
		hryky_log_alert(
			"fail "
			<< (json::writer()
			<< stream::denote("result") << result
			<< stream::denote("check") << check
			<< stream::denote("value") << value
			));
		return false;
	}
	return true;
}
/**
  @brief counts the number of non-zero bits by using loop.
 */
template <typename ValueT>
size_t popcount(ValueT const value)
{
	size_t result = 0;
	repeat(sizeof(ValueT) << 3u).foreach_at([&result, value](
		size_t const index) {
		result += (value >> index) & 0x1u;
	});
	
	return result;
}
  
} // namespace "anonymous"
} // namespace hamming
} // namespace test
} // namespace hryky
