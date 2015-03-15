/**
  @file         test_align.cpp
  @brief        tests hryky::align_*** functions.
  @author       HRYKY
  @version      $Id: test_align.cpp 355 2014-06-22 08:47:38Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/align.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
#pragma hryky_pragma_disable_warning_aligned_padded
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
		
		/// tests hryky::align_*** functions.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "align";

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
  @brief tests hryky::align_*** functions.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	if (0 != align_floor(0, 0)) {
		hryky_log_err(
			"The smallest multiple of (1<<0) "
			"greater than or equal to 0 must be 0.");
		return false;
	}

	if (1 != align_floor(1, 0)) {
		hryky_log_err(
			"The smallest multiple of (1<<0) "
			"greater than or equal to 1 must be 1.");
		return false;
	}

	if (2 != align_floor(2, 0)) {
		hryky_log_err(
			"The smallest multiple of (1<<0) "
			"greater than or equal to 2 must be 2.");
		return false;
	}

	if (0 != align_floor(0, 1)) {
		hryky_log_err(
			"The smallest multiple of (1<<1) "
			"greater than or equal to 0 must be 0.");
		return false;
	}

	if (0 != align_floor(1, 1)) {
		hryky_log_err(
			"The smallest multiple of (1<<1) "
			"greater than or equal to 1 must be 0.");
		return false;
	}

	if (2 != align_floor(2, 1)) {
		hryky_log_err(
			"The smallest multiple of (1<<1) "
			"greater than or equal to 2 must be 2.");
		return false;
	}

	if (2 != align_floor(3, 1)) {
		hryky_log_err(
			"The smallest multiple of (1<<1) "
			"greater than or equal to 3 must be 2.");
		return false;
	}

	if (0 != align_ceil(0, 0)) {
		hryky_log_err(
			"The largest multiple of (1<<0) "
			"less than or equal to 0 must be 0.");
		return false;
	}

	if (1 != align_ceil(1, 0)) {
		hryky_log_err(
			"The largest multiple of (1<<0) "
			"less than or equal to 1 must be 1.");
		return false;
	}

	if (2 != align_ceil(2, 0)) {
		hryky_log_err(
			"The largest multiple of (1<<0) "
			"less than or equal to 2 must be 2.");
		return false;
	}

	if (0 != align_ceil(0, 1)) {
		hryky_log_err(
			"The largest multiple of (1<<1) "
			"less than or equal to 0 must be 0.");
		return false;
	}

	if (2 != align_ceil(1, 1)) {
		hryky_log_err(
			"The largest multiple of (1<<1) "
			"less than or equal to 1 must be 2.");
		return false;
	}

	if (2 != align_ceil(2, 1)) {
		hryky_log_err(
			"The largest multiple of (1<<1) "
			"less than or equal to 2 must be 2.");
		return false;
	}

	if (4 != align_ceil(3, 1)) {
		hryky_log_err(
			"The largest multiple of (1<<1) "
			"less than or equal to 3 must be 4.");
		return false;
	}

	if (0 != align_floor_unit(0, 1)) {
		hryky_log_err(
			"The smallest multiple of 1 "
			"greater than or equal to 0 must be 0.");
		return false;
	}

	if (1 != align_floor_unit(1, 1)) {
		hryky_log_err(
			"The smallest multiple of 1 "
			"greater than or equal to 1 must be 1.");
		return false;
	}

	if (2 != align_floor_unit(2, 1)) {
		hryky_log_err(
			"The smallest multiple of 1 "
			"greater than or equal to 2 must be 2.");
		return false;
	}

	if (0 != align_floor_unit(0, 2)) {
		hryky_log_err(
			"The smallest multiple of 2 "
			"greater than or equal to 0 must be 0.");
		return false;
	}

	if (0 != align_floor_unit(1, 2)) {
		hryky_log_err(
			"The smallest multiple of 2 "
			"greater than or equal to 1 must be 0.");
		return false;
	}

	if (2 != align_floor_unit(2, 2)) {
		hryky_log_err(
			"The smallest multiple of 2 "
			"greater than or equal to 2 must be 2.");
		return false;
	}

	if (2 != align_floor_unit(3, 2)) {
		hryky_log_err(
			"The smallest multiple of 2 "
			"greater than or equal to 3 must be 2.");
		return false;
	}

	if (4 != align_floor_unit(4, 2)) {
		hryky_log_err(
			"The smallest multiple of 2 "
			"greater than or equal to 4 must be 4.");
		return false;
	}

	if (4 != align_floor_unit(5, 2)) {
		hryky_log_err(
			"The smallest multiple of 2 "
			"greater than or equal to 5 must be 4.");
		return false;
	}

	if (0 != align_ceil_unit(0, 1)) {
		hryky_log_err(
			"The largest multiple of 1 "
			"less than or equal to 0 must be 0.");
		return false;
	}

	if (1 != align_ceil_unit(1, 1)) {
		hryky_log_err(
			"The largest multiple of 1 "
			"less than or equal to 1 must be 1.");
		return false;
	}

	if (2 != align_ceil_unit(2, 1)) {
		hryky_log_err(
			"The largest multiple of 1 "
			"less than or equal to 2 must be 2.");
		return false;
	}

	if (0 != align_ceil_unit(0, 2)) {
		hryky_log_err(
			"The largest multiple of 2 "
			"less than or equal to 0 must be 0.");
		return false;
	}

	if (2 != align_ceil_unit(1, 2)) {
		hryky_log_err(
			"The largest multiple of 2 "
			"less than or equal to 1 must be 2.");
		return false;
	}

	if (2 != align_ceil_unit(2, 2)) {
		hryky_log_err(
			"The largest multiple of 2 "
			"less than or equal to 2 must be 2.");
		return false;
	}

	if (4 != align_ceil_unit(3, 2)) {
		hryky_log_err(
			"The largest multiple of 2 "
			"less than or equal to 3 must be 4.");
		return false;
	}

	if (4 != align_ceil_unit(4, 2)) {
		hryky_log_err(
			"The largest multiple of 2 "
			"less than or equal to 4 must be 4.");
		return false;
	}

	if (6 != align_ceil_unit(5, 2)) {
		hryky_log_err(
			"The largest multiple of 2 "
			"less than or equal to 5 must be 6.");
		return false;
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
