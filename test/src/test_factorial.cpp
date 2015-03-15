/**
  @file     test_factorial.cpp
  @brief    tests hryky::Factorial<>.
  @author   HRYKY
  @version  $Id: test_factorial.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/factorial.h"
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
		
		/// tests hryky::Factorial<>.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "factorial";

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
  @brief tests hryky::Factorial<>.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	(log.writer()
	<< stream::denote("Factorial<0>") << Factorial<0>::value
	<< stream::denote("Factorial<1>") << Factorial<1>::value
	<< stream::denote("Factorial<2>") << Factorial<2>::value
	<< stream::denote("Factorial<3>") << Factorial<3>::value
	<< stream::denote("Factorial<4>") << Factorial<4>::value
	<< stream::denote("Factorial<5>") << Factorial<5>::value
	<< stream::denote("Factorial<6>") << Factorial<6>::value
	<< stream::denote("Factorial<7>") << Factorial<7>::value
	<< stream::denote("Factorial<8>") << Factorial<8>::value
	<< stream::denote("Factorial<9>") << Factorial<9>::value
	 );

	(log.writer()
	<< stream::denote("OddFactorial<0>") << OddFactorial<0>::value
	<< stream::denote("OddFactorial<1>") << OddFactorial<1>::value
	<< stream::denote("OddFactorial<2>") << OddFactorial<2>::value
	<< stream::denote("OddFactorial<3>") << OddFactorial<3>::value
	<< stream::denote("OddFactorial<4>") << OddFactorial<4>::value
	<< stream::denote("OddFactorial<5>") << OddFactorial<5>::value
	<< stream::denote("OddFactorial<6>") << OddFactorial<6>::value
	<< stream::denote("OddFactorial<7>") << OddFactorial<7>::value
	<< stream::denote("OddFactorial<8>") << OddFactorial<8>::value
	<< stream::denote("OddFactorial<9>") << OddFactorial<9>::value
	 );

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
