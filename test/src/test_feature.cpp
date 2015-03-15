/**
  @file     test_feature.cpp
  @brief    tests some feature.
  @author   HRYKY
  @version  $Id: test_feature.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/without_new.h"
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
		
		/// tests some feature.
		virtual bool run_impl();

	};
	Test const g_test;

	class DerivedWithoutNew :
		private WithoutNew
	{
	public :
		typedef DerivedWithoutNew this_type;
		DerivedWithoutNew()
		{
		}
	private :
		DerivedWithoutNew(this_type const &);
		this_type & operator=(this_type const &);
	};

	class First
	{
	public :
		First()
		{
			hryky_log_debug("First::First()");
		}

		virtual ~First()
		{
			hryky_log_debug("First::~First()");
		}
	};

	class Second : public First
	{
	public :
		Second()
		{
			hryky_log_debug("Second::Second()");
		}

		~Second()
		{
			hryky_log_debug("Second::~Second()");
		}
	};

	class Third : public Second
	{
	public :
		Third()
		{
			hryky_log_debug("Third::Third()");
		}

		~Third()
		{
			hryky_log_debug("Third::~Third()");
		}
	};

	char const * const g_testname = "feature";

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
  @brief tests some feature.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	{
		Second * const ptr = new Third();
		delete ptr;
	}

	{
		DerivedWithoutNew const instance;
	}

#if 0 // error
	{
		DerivedWithoutNew const * const instance = new DerivedWithoutNew();
		delete instance;
	}
#endif

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
