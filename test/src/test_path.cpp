/**
  @file     test_path.cpp
  @brief    tests hryky::path module.
  @author   HRYKY
  @version  $Id: test_path.cpp 362 2014-07-07 09:43:31Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/path.h"
#include "hryky/windows.h"
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

		/// tests hryky::path module.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "path";

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
  @brief tests hryky::path module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	{
		char const * const c_str = "C:/";
		log.writer() << c_str << path_type(c_str);
	}

	{
		char const * const c_str = "C:/foo";
		log.writer() << c_str << path_type(c_str);
	}

	{
		char const * const c_str = "C:/foo/";
		log.writer() << c_str << path_type(c_str);
	}

	{
		char const * const c_str = "C:/foo/bar";
		log.writer() << c_str << path_type(c_str);
	}

	{
		char const * const c_str = "C:\\foo\\bar";
		log.writer() << c_str << path_type(c_str);
	}

	{
		char const * const c_str = "C:/foo/bar/";
		log.writer() << c_str << path_type(c_str);
	}

	{
		char const * const c_str = "C:\\foo\\bar\\";
		log.writer() << c_str << path_type(c_str);
	}

	{
		char const * const c_str = "C:/././";
		log.writer() << c_str << path_type(c_str);
	}

	{
		char const * const c_str = "C:\\.\\.\\";
		log.writer() << c_str << path_type(c_str);
	}

	{
		char const * const c_str = "C:/foo/./";
		log.writer() << c_str << path_type(c_str);
	}

	{
		char const * const c_str = "C:/foo/../";
		log.writer() << c_str << path_type(c_str);
	}

	{
		char const * const c_str = "\\\\foo\\bar\\";
		log.writer() << c_str << path_type(c_str);
	}

	{
		char const * const c_str = "C:/foo/bar";
		path_type path(c_str);
		char const * const append = "foo";
		log.writer() << append << (path << append);
	}

	{
		char const * const c_str = "C:/foo/bar";
		path_type path(c_str);
		char const * const append = "foo/";
		log.writer() << append << (path << append);
	}

	{
		char const * const c_str = "C:/foo/bar";
		path_type path(c_str);
		char const * const append = "./foo";
		log.writer() << append << (path << append);
	}

	{
		char const * const c_str = "C:/foo/bar";
		path_type path(c_str);
		char const * const append = "../foo";
		log.writer() << append << (path << append);
	}

	{
		char const * const c_str = "C:/foo/bar";
		path_type path(c_str);
		char const * const append = "../foo/../";
		log.writer() << append << (path << append);
	}

	{
		char const * const c_str = "C:/foo/bar";
		path_type path(c_str);
		char const * const append = "../foo/../bar";
		log.writer() << append << (path << append);
	}

	{
		char const * const c_str = "C:/foo/bar";
		path_type path(c_str);
		char const * const append = "../foo/../bar/";
		log.writer() << append << (path << append);
	}

	{
		path_type const application = path::application();
		(log.writer()
		 << hryky_stream_denote(application)
		 << "exists" << application.exists());
	}

	{
		path_type const executable = path::executable();
		(log.writer()
		 << hryky_stream_denote(executable)
		 << "exists" << executable.exists());
	}

	{
		path_type application = path::application();
		application << "test-hryky-codebase/test-path";
		if (!application.mkdir()) {
			hryky_log_alert(
				"failed to create directory:"
				<< (json::writer()
					<< hryky_stream_denote(application)));
			return false;
		}
	}


	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
