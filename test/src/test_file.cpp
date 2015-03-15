/**
  @file     test_file.cpp
  @brief    tests hryky::file.
  @author   HRYKY
  @version  $Id: test_file.cpp 363 2014-07-10 10:46:29Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/file.h"
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

		/// tests hryky::file.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "file";

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
  @brief tests hryky::file.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	{
		char const * const name
			= "test-hryky-codebase/test-file/test-file-reader.txt";

		{
			file::writer_type writer(
				path::application() + name);
			if (hryky_is_null(writer)) {
				hryky_log_alert("failed to open " << name);
				return false;
			}
		}
		
		{
			file::reader_type reader(
				path::application() + name);
			if (hryky_is_null(reader)) {
				hryky_log_alert("failed to open " << name);
				return false;
			}
		}
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
