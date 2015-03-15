/**
  @file     test_bits_length.cpp
  @brief    tests bits_length function.
  @author   HRYKY
  @version  $Id: test_bits_length.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/bits_length.h"
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
namespace bits_length
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
		
		/// tests bits_length function.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "bits_length";

} // namespace "anonymous"
} // namespace bits_length
} // namespace test
} // namespace hryky
namespace hryky
{
namespace test
{
namespace bits_length
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
  @brief tests bits_length function.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	if (0 != hryky::bits_length(0x0)) {
		hryky_log_alert(
			"The length of 0x0000 0000 has to be 0.");
		return false;
	}

	if (1 != hryky::bits_length(static_cast<uint8_t>(0x1))) {
		hryky_log_alert(
			"The length of 0x01 has to be 1.");
		return false;
	}

	if (1 != hryky::bits_length(static_cast<uint16_t>(0x1))) {
		hryky_log_alert(
			"The length of 0x0001 has to be 1.");
		return false;
	}

	if (1 != hryky::bits_length(0x1)) {
		hryky_log_alert(
			"The length of 0x0000 0001 has to be 1.");
		return false;
	}

	if (2 != hryky::bits_length(static_cast<uint8_t>(0x03))) {
		hryky_log_alert(
			"The length of 0x03 has to be 2.");
		return false;
	}

	if (2 != hryky::bits_length(static_cast<uint16_t>(0x03))) {
		hryky_log_alert(
			"The length of 0x0003 has to be 2.");
		return false;
	}

	if (2 != hryky::bits_length(0x03)) {
		hryky_log_alert(
			"The length of 0x0000 0003 has to be 2.");
		return false;
	}

	if (5 != hryky::bits_length(0x10)) {
		hryky_log_alert(
			"The length of 0x0000 0010 has to be 5.");
		return false;
	}

	if (8 != hryky::bits_length(0x80)) {
		hryky_log_alert(
			"The length of 0x0000 0080 has to be 9.");
		return false;
	}

	if (9 != hryky::bits_length(static_cast<uint16_t>(0x100))) {
		hryky_log_alert(
			"The length of 0x0100 has to be 9.");
		return false;
	}

	if (9 != hryky::bits_length(0x100)) {
		hryky_log_alert(
			"The length of 0x0000 0100 has to be 9.");
		return false;
	}

	if (16 != hryky::bits_length(static_cast<uint16_t>(0x8000))) {
		hryky_log_alert(
			"The length of 0x8000 has to be 16.");
		return false;
	}

	if (16 != hryky::bits_length(0x8000)) {
		hryky_log_alert(
			"The length of 0x0000 8000 has to be 16.");
		return false;
	}

	if (17 != hryky::bits_length(0x10000)) {
		hryky_log_alert(
			"The length of 0x0001 0000 has to be 17.");
		return false;
	}

	if (32 != hryky::bits_length(0x80000000)) {
		hryky_log_alert(
			"The length of 0x8000 0000 has to be 32.");
		return false;
	}

	if (33 != hryky::bits_length(static_cast<uint64_t>(1) << 32)) {
		hryky_log_alert(
			"The length of 0x0000 0001 0000 0000 has to be 33.");
		return false;
	}

	if (64 != hryky::bits_length(static_cast<uint64_t>(1) << 63)) {
		hryky_log_alert(
			"The length of 0x8000 0000 0000 0000 has to be 64.");
		return false;
	}

	if (64 != hryky::bits_length(static_cast<uint128_t>(1) << 63)) {
		hryky_log_alert(
			"The length of "
			"0x0000 0000 0000 0000 8000 0000 0000 0000 "
			"has to be 64.");
		log.writer() << "wrong_result" << static_cast<uint128_t>(1) << 63;
		return false;
	}

	if (65 != hryky::bits_length(static_cast<uint128_t>(1) << 64)) {
		hryky_log_alert(
			"The length of "
			"0x0000 0000 0000 0001 0000 0000 0000 0000 "
			"has to be 65.");
		return false;
	}

	if (128 != hryky::bits_length(static_cast<uint128_t>(1) << 127)) {
		hryky_log_alert(
			"The length of "
			"0x8000 0000 0000 0000 0000 0000 0000 0000 "
			"has to be 128.");
		log.writer() << "wrong_result" << static_cast<uint128_t>(1) << 127;
		return false;
	}

	if (129 != hryky::bits_length(static_cast<uint256_t>(1) << 128)) {
		hryky_log_alert(
			"The length of "
			"0x0000 0000 0000 0000 0000 0000 0000 0001 "
			"0000 0000 0000 0000 0000 0000 0000 0000 "
			"has to be 129.");
		log.writer() << "wrong_result" << static_cast<uint256_t>(1) << 128;
		return false;
	}

	if (256 != hryky::bits_length(static_cast<uint256_t>(1) << 255)) {
		hryky_log_alert(
			"The length of "
			"0x8000 0000 0000 0000 0000 0000 0000 0000 "
			"0000 0000 0000 0000 0000 0000 0000 0000 "
			"has to be 256.");
		log.writer() << "wrong_result" << static_cast<uint256_t>(1) << 255;
		return false;
	}

	if (257 != hryky::bits_length(static_cast<uint512_t>(1) << 256)) {
		hryky_log_alert(
			"The length of "
			"0x0000 0000 0000 0000 0000 0000 0000 0000 "
			"0000 0000 0000 0000 0000 0000 0000 0001 "
			"0000 0000 0000 0000 0000 0000 0000 0000 "
			"0000 0000 0000 0000 0000 0000 0000 0000 "
			"has to be 257.");
		log.writer() << "wrong_result" << static_cast<uint512_t>(1) << 255;
		return false;
	}

	return true;
}
} // namespace "anonymous"
} // namespace bits_length
} // namespace test
} // namespace hryky
