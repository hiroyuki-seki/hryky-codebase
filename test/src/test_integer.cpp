/**
  @file         test_integer.cpp
  @brief        tests the integer utility module.
  @author       HRYKY
  @version      $Id: test_integer.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/integer.h"
#include "hryky/type.h"
#pragma hryky_pragma_disable_warning_constant_condition
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
		
		/// tests the integer utility module.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "integer";

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
  @brief tests the integer utility module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	// tests BitsEnoughSigned

	if (1 != BitsEnoughSigned<0>::value) {
		hryky_log_alert(
			"The bits length of 0(bin:0) must be 1.");
		return false;
	}

	if (1 != BitsEnoughSigned<-1>::value) {
		hryky_log_alert(
			"The bits length of -1(bin:1) must be 1.");
		return false;
	}

	if (2 != BitsEnoughSigned<1>::value) {
		hryky_log_alert(
			"The bits length of 1(bin:01) must be 2.");
		return false;
	}

	if (2 != BitsEnoughSigned<-2>::value) {
		hryky_log_alert(
			"The bits length of -2(bin:10) must be 2.");
		return false;
	}

	if (3 != BitsEnoughSigned<3>::value) {
		hryky_log_alert(
			"The bits length of 3(bin:011) must be 3.");
		return false;
	}

	if (3 != BitsEnoughSigned<-3>::value) {
		hryky_log_alert(
			"The bits length of -3(bin:101) must be 3.");
		return false;
	}

	if (3 != BitsEnoughSigned<-4>::value) {
		hryky_log_alert(
			"The bits length of -4(bin:100) must be 3.");
		return false;
	}

	// tests BitsEnoughUnsigned

	if (1 != BitsEnoughUnsigned<0u>::value) {
		hryky_log_alert(
			"The bits length of 0u(bin:0) must be 1.");
		return false;
	}

	if (1 != BitsEnoughUnsigned<1u>::value) {
		hryky_log_alert(
			"The bits length of 1u(bin:1) must be 1.");
		return false;
	}

	if (2 != BitsEnoughUnsigned<2u>::value) {
		hryky_log_alert(
			"The bits length of 2u(bin:10) must be 2.");
		return false;
	}

	if (2 != BitsEnoughUnsigned<3u>::value) {
		hryky_log_alert(
			"The bits length of 3u(bin:11) must be 2.");
		return false;
	}

	if (3 != BitsEnoughUnsigned<4u>::value) {
		hryky_log_alert(
			"The bits length of 3(bin:100) must be 3.");
		return false;
	}

	if (3 != BitsEnoughUnsigned<5u>::value) {
		hryky_log_alert(
			"The bits length of 5u(bin:101) must be 3.");
		return false;
	}

	if (3 != BitsEnoughUnsigned<6u>::value) {
		hryky_log_alert(
			"The bits length of 6u(bin:110) must be 3.");
		return false;
	}

	// tests SignedEnough

	if (type::info<int8_t>() !=
		type::info<SignedEnoughBytes<0>::type>()) {
		hryky_log_alert(
			"The signed enough type to store 0 bytes must be int8_t.");
		return false;
	}

	if (type::info<int8_t>() !=
		type::info<SignedEnoughBytes<1>::type>()) {
		hryky_log_alert(
			"The signed enough type to store 1 bytes must be int8_t.");
		return false;
	}

	if (type::info<int16_t>() !=
		type::info<SignedEnoughBytes<2>::type>()) {
		hryky_log_alert(
			"The signed enough type to store 2 bytes must be int16_t.");
		return false;
	}

	if (type::info<int32_t>() !=
		type::info<SignedEnoughBytes<3>::type>()) {
		hryky_log_alert(
			"The signed enough type to store 3 bytes must be int32_t.");
		return false;
	}

	if (type::info<int32_t>() !=
		type::info<SignedEnoughBytes<4>::type>()) {
		hryky_log_alert(
			"The signed enough type to store 4 bytes must be int32_t.");
		return false;
	}

	if (type::info<int64_t>() !=
		type::info<SignedEnoughBytes<5>::type>()) {
		hryky_log_alert(
			"The signed enough type to store 5 bytes must be int64_t.");
		return false;
	}

	if (type::info<int64_t>() !=
		type::info<SignedEnoughBytes<6>::type>()) {
		hryky_log_alert(
			"The signed enough type to store 6 bytes must be int64_t.");
		return false;
	}

	if (type::info<int64_t>() !=
		type::info<SignedEnoughBytes<7>::type>()) {
		hryky_log_alert(
			"The signed enough type to store 7 bytes must be int64_t.");
		return false;
	}

	if (type::info<int64_t>() !=
		type::info<SignedEnoughBytes<8>::type>()) {
		hryky_log_alert(
			"The signed enough type to store 8 bytes must be int64_t.");
		return false;
	}

	// tests UnsignedEnough

	if (type::info<uint8_t>() !=
		type::info<UnsignedEnoughBytes<0>::type>()) {
		hryky_log_alert(
			"The unsigned enough type to store 0 bytes must be uint8_t.");
		return false;
	}

	if (type::info<uint8_t>() !=
		type::info<UnsignedEnoughBytes<1>::type>()) {
		hryky_log_alert(
			"The unsigned enough type to store 1 bytes must be uint8_t.");
		return false;
	}

	if (type::info<uint16_t>() !=
		type::info<UnsignedEnoughBytes<2>::type>()) {
		hryky_log_alert(
			"The unsigned enough type to store 2 bytes must be uint16_t.");
		return false;
	}

	if (type::info<uint32_t>() !=
		type::info<UnsignedEnoughBytes<3>::type>()) {
		hryky_log_alert(
			"The unsigned enough type to store 3 bytes must be uint32_t.");
		return false;
	}

	if (type::info<uint32_t>() !=
		type::info<UnsignedEnoughBytes<4>::type>()) {
		hryky_log_alert(
			"The unsigned enough type to store 4 bytes must be uint32_t.");
		return false;
	}

	if (type::info<uint64_t>() !=
		type::info<UnsignedEnoughBytes<5>::type>()) {
		hryky_log_alert(
			"The unsigned enough type to store 5 bytes must be uint64_t.");
		return false;
	}

	if (type::info<uint64_t>() !=
		type::info<UnsignedEnoughBytes<6>::type>()) {
		hryky_log_alert(
			"The unsigned enough type to store 6 bytes must be uint64_t.");
		return false;
	}

	if (type::info<uint64_t>() !=
		type::info<UnsignedEnoughBytes<7>::type>()) {
		hryky_log_alert(
			"The unsigned enough type to store 7 bytes must be uint64_t.");
		return false;
	}

	if (type::info<uint64_t>() !=
		type::info<UnsignedEnoughBytes<8>::type>()) {
		hryky_log_alert(
			"The unsigned enough type to store 8 bytes must be uint64_t.");
		return false;
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
