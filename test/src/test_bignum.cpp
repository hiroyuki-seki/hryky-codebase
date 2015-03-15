/**
  @file     test_bignum.cpp
  @brief    tests the bignum module.
  @author   HRYKY
  @version  $Id: test_bignum.cpp 369 2014-07-20 21:33:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/bignum.h"
#include "hryky/clock.h"
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
		
		/// tests the bignum module.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "bignum";

	/// tests a bigger precision integer.
	template <typename BiguintT>
	bool test_biguint(testing::Log & log, testing::Random & random);

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
  @brief tests the bignum module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	bool result = true;

	if (!test_biguint<uint128_t>(log, random)) {
		hryky_log_alert("failed to test uint128_t.");
		result = false;
	}

	if (!test_biguint<uint256_t>(log, random)) {
		hryky_log_alert("failed to test uint256_t.");
		result = false;
	}

	if (!test_biguint<uint512_t>(log, random)) {
		hryky_log_alert("failed to test uint512_t.");
		result = false;
	}

	if (!test_biguint<uint1024_t>(log, random)) {
		hryky_log_alert("failed to test uint1024_t.");
		result = false;
	}

	return result;
}
/**
  @brief tests a bigger precision integer.
 */
template <typename BiguintT>
bool test_biguint(testing::Log & log, testing::Random & random)
{
	BiguintT const zero;
	BiguintT const max = -1;
	BiguintT const one = 1;
	BiguintT const msb = BiguintT(1) << (BitsizeOf<BiguintT>::value - 1);

	bool result = true;

	BiguintT zero_one;
	hryky::repeat(BitsizeOf<BiguintT>::value >> 1).foreach([&zero_one]() {
		zero_one <<= 2;
		zero_one |= 1;
	});
	BiguintT one_zero;
	hryky::repeat(BitsizeOf<BiguintT>::value >> 1).foreach([&one_zero]() {
		one_zero <<= 1;
		one_zero |= 1;
		one_zero <<= 1;
	});

	{
		log.writer() << "bitwiseAnd";
		auto const elapse = clock::auto_elapse(log.writer());

		if (zero != (one_zero & zero_one)) {
			hryky_log_alert("0 != b10.. & b01..");
			result = false;
		}
	}

	{
		log.writer() << "bitwiseOr";
		auto const elapse = clock::auto_elapse(log.writer());

		if (max != (one_zero | zero_one)) {
			hryky_log_alert("max != b10.. | b01..");
			result = false;
		}
	}

	{
		log.writer() << "bitwiseXor";
		auto const elapse = clock::auto_elapse(log.writer());

		if (max != (one_zero ^ zero_one)) {
			hryky_log_alert("max != b10.. ^ b01..");
			result = false;
		}
	}

	{
		log.writer() << "add";
		auto const elapse = clock::auto_elapse(log.writer());

		if (max != (one_zero + zero_one)) {
			hryky_log_alert("max != b10.. + b01..");
			result = false;
		}
	}

	{
		log.writer() << "sub";
		auto const elapse = clock::auto_elapse(log.writer());

		if (zero_one != (one_zero - zero_one)) {
			hryky_log_alert("b01.. != b10.. - b01..");
			result = false;
		}
	}

	{
		log.writer() << "logicalLeftShiftPlusOne";
		auto const elapse = clock::auto_elapse(log.writer());

		if (zero_one != ((one_zero << 1) | 1)) {
			hryky_log_alert("b01.. != ((b10.. << 1) | 1)");
			result = false;
		}
	}

	{
		log.writer() << "logicalLeftShift";
		auto const elapse = clock::auto_elapse(log.writer());

		if (one_zero != (zero_one << 1)) {
			hryky_log_alert("b10.. != (b01.. << 1)");
			result = false;
		}
	}

	{
		log.writer() << "logicalRightShift";
		auto const elapse = clock::auto_elapse(log.writer());

		if (zero_one != (one_zero >> 1)) {
			hryky_log_alert("b01.. != (b10.. >> 1)");
			result = false;
		}
	}

	{
		log.writer() << "logicalRightShift";
		auto const elapse = clock::auto_elapse(log.writer());

		if (one_zero != ((zero_one >> 1) | msb)) {
			hryky_log_alert("b10.. != ((b01.. >> 1) | MSB)");
			result = false;
		}
	}

	{
		log.writer() << "notEqualToXor";
		auto const elapse = clock::auto_elapse(log.writer());

		if (one_zero != ~zero_one) {
			hryky_log_alert("b10.. != ~b01..");
			result = false;
		}
	}

	{
		log.writer() << "notEqualToHalf";
		auto const elapse = clock::auto_elapse(log.writer());

		if (zero_one != one_zero / 2) {
			hryky_log_alert("b01.. != b10.. / 2");
			log.writer() << "one_zero / 2" << one_zero / 2;
			result = false;
		}
	}

	{
		log.writer() << "b10..^MSB!=b01../2";
		auto const elapse = clock::auto_elapse(log.writer());

		if ((one_zero ^ msb) != zero_one / 2) {
			hryky_log_alert("b10.. ^ MSB != b01.. / 2");
			log.writer() << "zero_one / 2" << zero_one / 2;
			result = false;
		}
	}

	{
		log.writer() << "1!=b01..%2";
		auto const elapse = clock::auto_elapse(log.writer());

		if (one != zero_one % 2) {
			hryky_log_alert("1 != b01.. % 2");
			log.writer() << "zero_one % 2" << zero_one % 2;
			result = false;
		}
	}

	{
		log.writer() << "0!=b10..%2";
		auto const elapse = clock::auto_elapse(log.writer());

		if (zero != one_zero % 2) {
			hryky_log_alert("0 != b10.. % 2");
			log.writer() << "one_zero % 2" << one_zero % 2;
			result = false;
		}
	}

	if (zero != (one_zero >> BitsizeOf<BiguintT>::value)) {
		hryky_log_alert("0 != b10.. >> bits_size");
		result = false;
	}

	if (zero != (zero_one >> BitsizeOf<BiguintT>::value)) {
		hryky_log_alert("0 != b01.. >> bits_size");
		result = false;
	}

	if ((zero_one >> (BitsizeOf<LowerOf<BiguintT>::type>::value - 1)) !=
		(one_zero >> BitsizeOf<LowerOf<BiguintT>::type>::value)) {
		hryky_log_alert(
			"b01.. >> (bits_size -1) != b10.. >> bits_size");
		result = false;
	}

	{
		BiguintT rhs(one_zero);
		if (zero != (rhs >>= BitsizeOf<BiguintT>::value)) {
			hryky_log_alert("0 != b10.. >>= bits_size");
			result = false;
		}
	}

	{
		BiguintT rhs(zero_one);
		if (zero != (rhs >>= BitsizeOf<BiguintT>::value)) {
			hryky_log_alert("0 != b01.. >>= bits_size");
			result = false;
		}
	}

	{
		BiguintT lhs(zero_one);
		BiguintT rhs(one_zero);
		if ((lhs >>= (BitsizeOf<LowerOf<BiguintT>::type>::value - 1)) !=
			(rhs >>= BitsizeOf<LowerOf<BiguintT>::type>::value)) {
			hryky_log_alert(
				"b01.. >>= (bits_size - 1) != b10.. >>= bits_size");
			result = false;
		}
	}

	if (zero_one * 2 != one_zero) {
		hryky_log_alert("b01.. * 2 != b10..");
		result = false;
	}

	{
		BiguintT lhs(zero_one);
		if ((lhs *= 2) != one_zero) {
			hryky_log_alert("b01.. * 2 != b10..");
			result = false;
		}
	}

	if (zero_one * 3 != max) {
		hryky_log_alert("b01.. * 3 != max");
		result = false;
	}

	{
		BiguintT lhs(zero_one);
		if ((lhs *= 3) != max) {
			hryky_log_alert("b01.. * 3 != max");
			result = false;
		}
	}

	if (zero >= one) {
		hryky_log_alert("0 >= 1");
		result = false;
	}

	if (zero >= max) {
		hryky_log_alert("0 >= max");
		result = false;
	}

	if (one >= max) {
		hryky_log_alert("1 >= max");
		result = false;
	}

	if (max - one >= max) {
		hryky_log_alert("max - 1 >= max");
		result = false;
	}

	if (zero != max + one) {
		hryky_log_alert("0 != max + 1");
		result = false;;
	}

	if (zero + 1 != one) {
		hryky_log_alert("0 + 1 != 1");
		result = false;;
	}
	
	if (zero - 1 != max) {
		hryky_log_alert("0 - 1 != max");
		result = false;;
	}
	
	if (zero - 1 != max) {
		hryky_log_alert("0 - 1 != max");
		result = false;;
	}

	if (max - zero != max) {
		hryky_log_alert("max - 0 != max");
		result = false;;
	}

	{
		BiguintT value(zero);
		if (++value != one) {
			hryky_log_alert("++0 != 1");
			result = false;;
		}
	}

	{
		BiguintT value(zero);
		if (value++ != zero) {
			hryky_log_alert("0++ != 0");
			result = false;;
		}
	}
	
	{
		BiguintT value(zero);
		if (--value != max) {
			hryky_log_alert("--0 != max");
			result = false;;
		}
	}

	{
		BiguintT value(zero);
		if (value-- != zero) {
			hryky_log_alert("0-- != 0");
			result = false;;
		}
	}

	{
		random::Uniform<size_t> repeat_dist(
			random.generator(), 0x1, 0x100);

		random::Uniform<BiguintT> dist(
			random.generator());

		log.writer() << "dist";
		testing::Log::array_type const array(log.writer());

		hryky::repeat(repeat_dist()).foreach([&dist, &log]() {
			log.writer() << dist();
		});
	}

	return result;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
