/**
  @file     test_pi.h
  @brief    tests hryky::CalcPi<>.
  @author   HRYKY
  @version  $Id: test_pi.cpp 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/pi.h"
#include "hryky/unroll.h"
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
		
		/// tests hryky::CalcPi<>.
		virtual bool run_impl();

		struct TestCalcPi
		{
			typedef TestCalcPi this_type;
			
			TestCalcPi(testing::Log & log)
				: log_(log)
			{
			}

			template <size_t Index>
			void operator()() const
			{
				ostream::String<String<> > os;
				(this->log_.writer()
				 << (os <<
					 "CalcPi<float, " << Index << '>')
				 << CalcPi<float, Index>::value);
			}

		private :
			TestCalcPi(this_type const &);
			this_type & operator=(this_type const &);

			testing::Log & log_;
		};

	};
	Test const g_test;

	char const * const g_testname = "pi";

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
  @brief tests hryky::CalcPi<>.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	(log.writer()
	<< stream::denote("Pi<>") << Pi<>::value
	<< stream::denote("Pi<float>") << Pi<float>::value
	<< stream::denote("Pi<double") << Pi<double>::value
	 );
	
	// log.writer() << "hryky_pi" << hryky_pi;
	
	Unroll<24>::foreach_at_c(TestCalcPi(log));

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
