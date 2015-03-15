/**
  @file         test_bitset.cpp
  @brief        tests Bitset.
  @author       HRYKY
  @version      $Id: test_bitset.cpp 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/bitset.h"
#include "hryky/repeat.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
#define HRYKY_TEST_BITSET(bits) \
	if (!test_bitset<bits>(log, random)) { \
		hryky_log_alert("failed to test bitset<bits>."); \
		return false; \
	}

#define HRYKY_TEST_BITSET10(tenths) \
	if (!([&log, &random]() {\
		HRYKY_TEST_BITSET(tenths##0) \
		HRYKY_TEST_BITSET(tenths##1) \
		HRYKY_TEST_BITSET(tenths##2) \
		HRYKY_TEST_BITSET(tenths##3) \
		HRYKY_TEST_BITSET(tenths##4) \
		HRYKY_TEST_BITSET(tenths##5) \
		HRYKY_TEST_BITSET(tenths##6) \
		HRYKY_TEST_BITSET(tenths##7) \
		HRYKY_TEST_BITSET(tenths##8) \
		HRYKY_TEST_BITSET(tenths##9) \
		return true; \
	})()) { \
		return false; \
	}

#define HRYKY_TEST_BITSET100(hundredths) \
	HRYKY_TEST_BITSET10(hundredths##0) \
	HRYKY_TEST_BITSET10(hundredths##1) \
	HRYKY_TEST_BITSET10(hundredths##2) \
	HRYKY_TEST_BITSET10(hundredths##3) \
	HRYKY_TEST_BITSET10(hundredths##4) \
	HRYKY_TEST_BITSET10(hundredths##5) \
	HRYKY_TEST_BITSET10(hundredths##6) \
	HRYKY_TEST_BITSET10(hundredths##7) \
	HRYKY_TEST_BITSET10(hundredths##8) \
	HRYKY_TEST_BITSET10(hundredths##9)

#define HRYKY_TEST_BITSET1000(thousandths) \
	HRYKY_TEST_BITSET100(thousandths##0) \
	HRYKY_TEST_BITSET100(thousandths##1) \
	HRYKY_TEST_BITSET100(thousandths##2) \
	HRYKY_TEST_BITSET100(thousandths##3) \
	HRYKY_TEST_BITSET100(thousandths##4) \
	HRYKY_TEST_BITSET100(thousandths##5) \
	HRYKY_TEST_BITSET100(thousandths##6) \
	HRYKY_TEST_BITSET100(thousandths##7) \
	HRYKY_TEST_BITSET100(thousandths##8) \
	HRYKY_TEST_BITSET100(thousandths##9)

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
		
		/// tests Bitset.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "bitset";

	/// tests a bitset with the specified size.
	template <size_t Bits>
	bool test_bitset(testing::Log & log, testing::Random & random);

	/// randomizes the composition of bits.
	template <typename BitsetT>
	void scatter(BitsetT & bitset, testing::Random & random);

	/// checks the number of bits.
	template <typename BitsetT>
	bool popcount(BitsetT const & bitset);

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
  @brief tests Bitset.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	HRYKY_TEST_BITSET(1);
	HRYKY_TEST_BITSET(2);
	HRYKY_TEST_BITSET(3);
	HRYKY_TEST_BITSET(4);
	HRYKY_TEST_BITSET(5);
	HRYKY_TEST_BITSET(6);
	HRYKY_TEST_BITSET(7);
	HRYKY_TEST_BITSET(8);
	HRYKY_TEST_BITSET(9);

#if HRYKY_TEST_BIGOBJ
	HRYKY_TEST_BITSET10(1);
	HRYKY_TEST_BITSET10(2);
	HRYKY_TEST_BITSET10(3);
	HRYKY_TEST_BITSET10(4);
	HRYKY_TEST_BITSET10(5);
	HRYKY_TEST_BITSET10(6);
	HRYKY_TEST_BITSET10(7);
	HRYKY_TEST_BITSET10(8);
	HRYKY_TEST_BITSET10(9);
#endif

#if 0
	HRYKY_TEST_BITSET100(1);
	HRYKY_TEST_BITSET100(2);
	HRYKY_TEST_BITSET100(3);
	HRYKY_TEST_BITSET100(4);
	HRYKY_TEST_BITSET100(5);
	HRYKY_TEST_BITSET100(6);
	HRYKY_TEST_BITSET100(7);
	HRYKY_TEST_BITSET100(8);
	HRYKY_TEST_BITSET100(9);
#endif

	HRYKY_TEST_BITSET(128);
	HRYKY_TEST_BITSET(256);
	HRYKY_TEST_BITSET(512);
	HRYKY_TEST_BITSET(1024);
	HRYKY_TEST_BITSET(2048);
	HRYKY_TEST_BITSET(4096);

	return true;
}
/**
  @brief tests a bitset with the specified size.
 */
template <size_t Bits>
bool test_bitset(testing::Log &, testing::Random & random)
{
	typedef Bitset<Bits>                            bitset_type;
	typedef typename bitset_type::size_type         size_type;
	typedef typename bitset_type::reference         reference;
	typedef typename bitset_type::const_reference   const_reference;

	random::Normal<size_type> pos_dist(
		random.generator(),
		static_cast<size_type>(Bits >> 1), // deviation
		static_cast<size_type>(Bits >> 1), // mean
		0, // min
		static_cast<size_type>(Bits - 1) // max
		);

	random::Normal<size_t> repeat_dist(
		random.generator(),
		0x80u, // deviation
		0x80u, // mean
		0x10u, // min
		0x100u // max
		);

	bitset_type bitset;

	if (!bitset.none()) {
		hryky_log_alert(
			"The all of the default bits must be zero "
			<< (json::writer()
			<< stream::denote("bitset") << bitset));
		return false;
	}

	if (!popcount(bitset)) {
		hryky_log_alert(
			"The popcount is invalid at the beginning.");
		return false;
	}

	// tests whether the default values are false.
	{
		if (!repeat(repeat_dist()).every_at([&pos_dist, &bitset](
			size_t const index) {
			size_type const pos = pos_dist();
			
			if (bitset.get(pos)) {
				hryky_log_alert(
					"The default value must be false. "
					<< (json::writer()
					<< stream::denote("position") << pos
					<< stream::denote("bitset") << bitset
					<< stream::denote("index") << index));
				return false;
			}
			return true;
		})) {
			return false;
		}
	}

	size_t count = 0u;

	// checks the result of set(true).
	{
		bitset.set(Bits - 1, true);
		if (!bitset.get(Bits - 1)) {
			hryky_log_alert("error");
		}
		++count;

		if (count != bitset.count()) {
			hryky_log_alert(
				"The number of bits must be one. "
				<< (json::writer()
				<< stream::denote("bitset") << bitset));
			return false;
		}

		if (!repeat(repeat_dist()).every_at([&bitset, &pos_dist, &count](
			size_t const index) {
			size_type const pos = pos_dist();

			if (!bitset.get(pos)) {
				++count;
			}

			bitset.set(pos, true);
			if (!bitset.get(pos)) {
				hryky_log_alert(
					"The result of set(true) must be true. "
					<< (json::writer()
					<< stream::denote("position") << pos
					<< stream::denote("bitset") << bitset
					<< stream::denote("index") << index
					));
				return false;
			}
			return true;
		})) {
			return false;
		}

		if (count != bitset.count() || Bits < count) {
			hryky_log_alert(
				"The number of bits is invalid "
				"after some bits are enabled. "
				<< (json::writer()
				<< stream::denote("result") << bitset.count()
				<< stream::denote("test") << count
				<< stream::denote("bitset") << bitset));
			return false;
		}

		if (!popcount(bitset)) {
			hryky_log_alert(
				"The popcount is invalid after enabling bits by set().");
			return false;
		}
	}

	// checks the result of set(false).
	{
		if (!repeat(repeat_dist()).every_at([&bitset, &pos_dist, &count](
			size_t const index) {
			size_type const pos = pos_dist();

			if (bitset.get(pos)) {
				--count;
			}

			bitset.set(pos, false);
			if (bitset.get(pos)) {
				hryky_log_alert(
					"The result of set(false) must be false. "
					<< (json::writer()
					<< stream::denote("position") << pos
					<< stream::denote("bitset") << bitset
					<< stream::denote("index") << index
					));
				return false;
			}
			return true;
		})) {
			return false;
		}

		if (count != bitset.count() || Bits < count) {
			hryky_log_alert(
				"The number of bits is invalid "
				"after some bits are disabled. "
				<< (json::writer()
				<< stream::denote("result") << bitset.count()
				<< stream::denote("test") << count
				<< stream::denote("bitset") << bitset));
			return false;
		}

		if (!popcount(bitset)) {
			hryky_log_alert(
				"The popcount is invalid after disabling bits by set().");
			return false;
		}
	}

	// checks the result of on().
	{
		if (!repeat(repeat_dist()).every_at([&bitset, &pos_dist, &count](
			size_t const index) {
			size_type const pos = pos_dist();

			if (!bitset.get(pos)) {
				++count;
			}

			bitset.on(pos);
			if (!bitset.get(pos)) {
				hryky_log_alert(
					"The result of on() must be true. "
					<< (json::writer()
					<< stream::denote("position") << pos
					<< stream::denote("bitset") << bitset
					<< stream::denote("index") << index
					));
				return false;
			}
			return true;
		})) {
			return false;
		}

		if (count != bitset.count() || Bits < count) {
			hryky_log_alert(
				"The number of bits is invalid "
				"after some bits are enabled. "
				<< (json::writer()
				<< stream::denote("result") << bitset.count()
				<< stream::denote("test") << count
				<< stream::denote("bitset") << bitset));
			return false;
		}

		if (!popcount(bitset)) {
			hryky_log_alert(
				"The popcount is invalid after enabling bits.");
			return false;
		}
	}

	// checks the result of off().
	{
		if (!repeat(repeat_dist()).every_at([&bitset, &pos_dist, &count](
			size_t const index) {
			size_type const pos = pos_dist();

			if (bitset.get(pos)) {
				--count;
			}

			bitset.off(pos);
			if (bitset.get(pos)) {
				hryky_log_alert(
					"The result of off() must be false. "
					<< (json::writer()
					<< stream::denote("position") << pos
					<< stream::denote("bitset") << bitset
					<< stream::denote("index") << index
					));
				return false;
			}
			return true;
		})) {
			return false;
		}

		if (count != bitset.count() || Bits < count) {
			hryky_log_alert(
				"The number of bits is invalid "
				"after some bits are disabled. "
				<< (json::writer()
				<< stream::denote("result") << bitset.count()
				<< stream::denote("test") << count
				<< stream::denote("bitset") << bitset));
			return false;
		}

		if (!popcount(bitset)) {
			hryky_log_alert(
				"The popcount is invalid after disabling bits.");
			return false;
		}
	}

	// checks the result of flip().
	{
		if (!repeat(repeat_dist()).every_at([&bitset, &pos_dist, &count](
			size_t const index) {
			size_type const pos = pos_dist();

			bool const prev = bitset.get(pos);

			if (prev) {
				--count;
			}
			else {
				++count;
			}

			bitset.flip(pos);
			if (prev == bitset.get(pos)) {
				hryky_log_alert(
					"The result of flip() must be reversed. "
					<< (json::writer()
					<< stream::denote("position") << pos
					<< stream::denote("bitset") << bitset
					<< stream::denote("index") << index
					));
				return false;
			}
			return true;
		})) {
			return false;
		}

		if (count != bitset.count() || Bits < count) {
			hryky_log_alert(
				"The number of bits is invalid "
				"after some bits are reversed. "
				<< (json::writer()
				<< stream::denote("result") << bitset.count()
				<< stream::denote("test") << count
				<< stream::denote("bitset") << bitset));
			return false;
		}

		if (!popcount(bitset)) {
			hryky_log_alert(
				"The popcount is invalid after reversing bits.");
			return false;
		}
	}

	// checks the result of all() after the all bits are enabled.
	{
		if (!bitset.every_at([](reference element, size_type const index) {
			element = true;
			if (!element) {
				hryky_log_alert(
					"The result of flip() must be enabled. "
					<< (json::writer()
					<< stream::denote("index") << index
					));
				return false;
			}
			return true;
		})) {
			hryky_log_alert("failure of " << bitset);
			return false;
		}

		if (!bitset.all()) {
			hryky_log_alert(
				"The number of bits is invalid "
				"after all bits are enabled. "
				<< (json::writer()
				<< stream::denote("bitset") << bitset
				));
			return false;
		}

		if (!popcount(bitset)) {
			hryky_log_alert(
				"The popcount is invalid after enabling bits by assignment.");
			return false;
		}
	}

	// checks the result of none() after the all bits are disabled.
	{
		if (!bitset.every_at([](reference element, size_type const index) {
			element = false;
			if (element) {
				hryky_log_alert(
					"The result of flip() must be disabled. "
					<< (json::writer()
					<< stream::denote("index") << index
					));
				return false;
			}
			return true;
		})) {
			hryky_log_alert("failure of " << bitset);
			return false;
		}

		if (!bitset.none()) {
			hryky_log_alert(
				"The number of bits is invalid "
				"after all bits are disabled. "
				<< (json::writer()
				<< stream::denote("bitset") << bitset
				));
			return false;
		}

		if (!popcount(bitset)) {
			hryky_log_alert(
				"The popcount is invalid after disabling bits by assignment.");
			return false;
		}
	}

	// checks the copy constructor.
	{
		scatter(bitset, random);
		
		bitset_type const copied(bitset);

		if (!popcount(copied)) {
			hryky_log_alert(
				"The popcount is invalid after copy-constructor.");
			return false;
		}

		if (!repeat(static_cast<size_type>(Bits)).every_at([&bitset, &copied](
			size_type const index) {
			if (bitset.get(index) != copied.get(index)) {
				hryky_log_alert(
					"mismatch after copy constructor. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("copied") << copied
					<< stream::denote("index") << index
					));
				return false;
			}
			return true;
		})) {
			return false;
		}

		if (bitset.count() != copied.count()) {
			hryky_log_alert(
				"The each number of bits are different "
				"after copy constructor. "
				<< (json::writer()
				<< stream::denote("original") << bitset
				<< stream::denote("copied") << copied
				));
			return false;
		}

		if (bitset != copied) {
			hryky_log_alert(
				"Two instances are different "
				"after copy constructor. "
				<< (json::writer()
				<< stream::denote("original") << bitset
				<< stream::denote("copied") << copied
				));
			return false;
		}

		if (!(bitset == copied)) {
			hryky_log_alert(
				"Two instances are different "
				"after copy constructor. "
				<< (json::writer()
				<< stream::denote("original") << bitset
				<< stream::denote("copied") << copied
				));
			return false;
		}
	}

	// on()
	{
		scatter(bitset, random);
		bitset.on();
		if (!popcount(bitset)) {
			hryky_log_alert("The popcount is invalid after on().");
			return false;
		}

		if (!bitset.all()) {
			hryky_log_alert(
				"The all bits must be enabled after on(). "
				<< (json::writer()
				<< stream::denote("bitset") << bitset));
			return false;
		}
	}

	// off()
	{
		scatter(bitset, random);
		bitset.off();
		if (!popcount(bitset)) {
			hryky_log_alert("The popcount is invalid after off().");
			return false;
		}

		if (!bitset.none()) {
			hryky_log_alert(
				"The all bits must be disabled after off(). "
				<< (json::writer()
				<< stream::denote("bitset") << bitset));
			return false;
		}
	}

	// flip()
	{
		scatter(bitset, random);
		bitset_type const prev(bitset);
		bitset.flip();
		if (!popcount(bitset)) {
			hryky_log_alert("The popcount is invalid after flip().");
			return false;
		}

		if (bitset.count() != bitset.size() - prev.count()) {
			hryky_log_alert(
				"The number of bits is invalid after flip(). "
				<< (json::writer()
				<< stream::denote("bitset") << bitset
				<< stream::denote("prev") << prev
				));
			return false;
		}
	}

	// operator&
	{
		scatter(bitset, random);

		{
			bitset_type const copied(bitset);
			bitset_type const result = bitset & copied;
			if (result != bitset) {
				hryky_log_alert(
					"The all bits must be same "
					"after logical AND with the same bits. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("copied") << copied
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical AND with the same bits.");
				return false;
			}
		}

		{
			bitset_type const none;
			bitset_type const result = bitset & none;
			if (result.any()) {
				hryky_log_alert(
					"There are some bits."
					"after logical AND with zero. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("none") << none
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical AND with zero.");
				return false;
			}
		}
		
		{
			bitset_type all;
			all.on();
			bitset_type const result = bitset & all;
			if (bitset.count() != result.count()) {
				hryky_log_alert(
					"The each number of bits are different "
					"after logical AND with the filled bitset. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("all") << all
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical AND with the filled bitset.");
				return false;
			}
		}

		{
			bitset_type other;
			scatter(other, random);
			bitset_type const result = bitset & other;

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical AND with an arbitrary bitset.");
				return false;
			}
		}
	}

	// operator|
	{
		scatter(bitset, random);

		{
			bitset_type const copied(bitset);
			bitset_type const result = bitset | copied;
			if (result != bitset) {
				hryky_log_alert(
					"The bitsets are different "
					"after logical OR with the same bits. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("copied") << copied
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical OR with the same bits.");
				return false;
			}
		}

		{
			bitset_type const none;
			bitset_type const result = bitset | none;
			if (result != bitset) {
				hryky_log_alert(
					"The bitsets are different "
					"after logical OR with zero. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("none") << none
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical OR with zero.");
				return false;
			}
		}
		
		{
			bitset_type all;
			all.on();
			bitset_type const result = bitset | all;
			if (!result.all()) {
				hryky_log_alert(
					"The all bits must be filled "
					"after logical OR with the filled bitset. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("all") << all
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical OR with the filled bitset.");
				return false;
			}
		}

		{
			bitset_type other;
			scatter(other, random);
			bitset_type const result = bitset | other;

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical OR with an arbitrary bitset.");
				return false;
			}
		}
	}

	// operator^
	{
		scatter(bitset, random);

		{
			bitset_type const copied(bitset);
			bitset_type const result = bitset ^ copied;
			if (!result.none()) {
				hryky_log_alert(
					"The result must be zero "
					"after logical XOR with the same bits. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("copied") << copied
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical XOR with the same bits.");
				return false;
			}
		}

		{
			bitset_type const none;
			bitset_type const result = bitset ^ none;
			if (result != bitset) {
				hryky_log_alert(
					"The result must be same to the original bitset "
					"after logical XOR with zero. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("none") << none
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical XOR with zero.");
				return false;
			}
		}
		
		{
			bitset_type all;
			all.on();
			bitset_type flipped(bitset);
			flipped.flip();

			bitset_type const result = bitset ^ all;

			if (result != flipped) {
				hryky_log_alert(
					"The each bit must be reversed "
					"after logical XOR with the filled bitset. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("all") << all
					<< stream::denote("flipped") << flipped
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical XOR with the filled bitset.");
				return false;
			}
		}

		{
			bitset_type other;
			scatter(other, random);
			bitset_type const result = bitset ^ other;

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical XOR with an arbitrary bitset.");
				return false;
			}
		}
	}

	// operator&=
	{
		scatter(bitset, random);

		{
			bitset_type result(bitset);
			result &= result;
			if (result != bitset) {
				hryky_log_alert(
					"The all bits must be same "
					"after logical AND with the same bits. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical AND with the same bits.");
				return false;
			}
		}

		{
			bitset_type result(bitset);
			bitset_type const none;
			result &= none;
			if (result.any()) {
				hryky_log_alert(
					"There are some bits."
					"after logical AND with zero. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("none") << none
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical AND with zero.");
				return false;
			}
		}
		
		{
			bitset_type result(bitset);
			bitset_type all;
			all.on();
			result &= all;
			if (bitset.count() != result.count()
				|| bitset != result) {
				hryky_log_alert(
					"The each number of bits are different "
					"after logical AND with the filled bitset. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("all") << all
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical AND with the filled bitset.");
				return false;
			}
		}

		{
			bitset_type other;
			scatter(other, random);
			bitset_type result(bitset);
			result &= other;

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical AND with an arbitrary bitset.");
				return false;
			}
		}
	}

	// operator|=
	{
		scatter(bitset, random);

		{
			bitset_type result(bitset);
			result |= result;
			if (result != bitset) {
				hryky_log_alert(
					"The bitsets are different "
					"after logical OR with the same bits. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical OR with the same bits.");
				return false;
			}
		}

		{
			bitset_type result(bitset);
			bitset_type const none;
			result |= none;
			if (result != bitset) {
				hryky_log_alert(
					"The bitsets are different "
					"after logical OR with zero. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("none") << none
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical OR with zero.");
				return false;
			}
		}
		
		{
			bitset_type result(bitset);
			bitset_type all;
			all.on();
			result |= all;
			if (!result.all()) {
				hryky_log_alert(
					"The all bits must be filled "
					"after logical OR with the filled bitset. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("all") << all
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical OR with the filled bitset.");
				return false;
			}
		}

		{
			bitset_type result(bitset);
			bitset_type other;
			scatter(other, random);
			result |= other;

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical OR with an arbitrary bitset.");
				return false;
			}
		}
	}

	// operator^=
	{
		scatter(bitset, random);

		{
			bitset_type result(bitset);
			bitset_type const copied(bitset);
			result ^= result;
			if (!result.none()) {
				hryky_log_alert(
					"The result must be zero "
					"after logical XOR with the same bits. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical XOR with the same bits.");
				return false;
			}
		}

		{
			bitset_type result(bitset);
			bitset_type const none;
			result ^= none;
			if (result != bitset) {
				hryky_log_alert(
					"The result must be same to the original bitset "
					"after logical XOR with zero. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("none") << none
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical XOR with zero.");
				return false;
			}
		}
		
		{
			bitset_type result(bitset);
			bitset_type all;
			all.on();
			bitset_type flipped(bitset);
			flipped.flip();

			result ^= all;

			if (result != flipped) {
				hryky_log_alert(
					"The each bit must be reversed "
					"after logical XOR with the filled bitset. "
					<< (json::writer()
					<< stream::denote("original") << bitset
					<< stream::denote("all") << all
					<< stream::denote("flipped") << flipped
					<< stream::denote("result") << result
					));
				return false;
			}

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical XOR with the filled bitset.");
				return false;
			}
		}

		{
			bitset_type result(bitset);
			bitset_type other;
			scatter(other, random);
			result ^= other;

			if (!popcount(result)) {
				hryky_log_alert(
					"The popcount is invalid "
					"after logical XOR with an arbitrary bitset.");
				return false;
			}
		}
	}

	// operator<<
	{
		scatter(bitset, random);

		{
			size_type const shift = pos_dist();
			bitset_type const other = (bitset << shift);

			if (!other.every_at([shift, &bitset](
				bool const bit, size_type const pos) {
				if (pos < shift) {
					if (bit) {
						hryky_log_alert(
							"The moved bit at LSB side must be zero. "
							<< (json::writer()
							<< stream::denote("pos") << pos));
						return false;
					}
				}
				else if (bitset[static_cast<size_type>(pos - shift)] != bit) {
					hryky_log_alert(
						"The moved bit is not same to the one at "
						"the original position. "
						<< (json::writer()
							<< stream::denote("pos") << pos
							<< "correct"
							<< static_cast<bool>(
								bitset[static_cast<size_type>(pos - shift)])
							<< "wrong" << bit
							));
					return false;
				}
				return true;
			})) {
				hryky_log_alert(
					"failed to logical left shift "
					<< (json::writer()
					<< stream::denote("shift") << shift
					<< stream::denote("bitset") << bitset
					<< stream::denote("shifted") << other));
				return false;
			}

			if (!popcount(other)) {
				hryky_log_alert(
					"The popcount is invalid after Left shift operation");
				return false;
			}
		}
	}
	
	// operator>>
	{
		scatter(bitset, random);

		{
			size_type const shift = pos_dist();
			bitset_type const other = (bitset >> shift);
			size_type const size = bitset.size();

			if (!other.every_at([shift, size, &bitset](
				bool const bit, size_type const pos) {
				if (pos >= size - shift) {
					if (bit) {
						hryky_log_alert(
							"The moved bit at MSB side must be zero. "
							<< (json::writer()
							<< stream::denote("pos") << pos));
						return false;
					}
				}
				else if (bitset[static_cast<size_type>(pos + shift)] != bit) {
					hryky_log_alert(
						"The moved bit is not same to the one at "
						"the original position. "
						<< (json::writer()
							<< stream::denote("pos") << pos
							<< "correct"
							<< static_cast<bool>(
								bitset[static_cast<size_type>(pos + shift)])
							<< "wrong" << bit
							));
					return false;
				}
				return true;
			})) {
				hryky_log_alert(
					"failed to logical left shift "
					<< (json::writer()
					<< stream::denote("shift") << shift
					<< stream::denote("bitset") << bitset
					<< stream::denote("shifted") << other));
				return false;
			}

			if (!popcount(other)) {
				hryky_log_alert(
					"The popcount is invalid after Left shift operation");
				return false;
			}
		}
	}
	
	return true;
}
/**
  @brief randomizes the composition of bits.
 */
template <typename BitsetT>
void scatter(BitsetT & bitset, testing::Random & random)
{
	random::Uniform<uint8_t> operation_dist(
		random.generator(), 0x0, 0x1);

	bitset.foreach([&operation_dist](BitsetT::reference element) {
		element = (1 == operation_dist());
	});
}
/**
  @brief checks the number of bits.
 */
template <typename BitsetT>
bool popcount(BitsetT const & bitset)
{
	BitsetT::size_type count = 0;
	bitset.foreach([&count](BitsetT::const_reference bit) {
		count += bit ? 1 : 0;
	});

	if (bitset.count() != count) {
		hryky_log_alert(
			"popcount is invalid "
			<< (json::writer()
			<< stream::denote("bitset") << bitset
			<< stream::denote("count") << count
			));
		return false;
	}
	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
