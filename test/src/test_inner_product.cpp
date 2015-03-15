/**
  @file     test_inner_product.cpp
  @brief    tests hryky::inner_product.
  @author   HRYKY
  @version  $Id: test_inner_product.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/inner_product.h"
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
		
		/// tests hryky::inner_product.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "inner_product";

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
  @brief tests hryky::inner_product.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	{
		float const lhs = 0.5f;
		float const rhs = 1.0f;
		float const result = inner_product(lhs, rhs);
		if (0.5f != result) {
			hryky_log_alert(
				"0.5f != lhs * rhs "
				<< (json::writer()
				<< stream::denote("lhs") << lhs
				<< stream::denote("rhs") << rhs));
			return false;
		}
	}

	// confirms Hermitian inner product.
	{
		typedef ::std::complex<float> complex_type;
		complex_type const lhs = complex_type(1.0f, 1.0f);
		complex_type const rhs = complex_type(2.0f, 0.5f);
		complex_type const lhs_rhs = inner_product(lhs, rhs);
		complex_type const rhs_lhs = inner_product(rhs, lhs);
		if (lhs_rhs != ::std::conj(rhs_lhs)) {
			hryky_log_alert("lhs_rhs != rhs_lhs*");
			return false;
		}
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
