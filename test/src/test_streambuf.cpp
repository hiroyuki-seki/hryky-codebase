/**
  @file     test_streambuf.cpp
  @brief    tests streambuf module.
  @author   HRYKY
  @version  $Id: test_streambuf.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/streambuf.h"
#include "hryky/vector.h"
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
		
		/// tests streambuf module.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "streambuf";

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
  @brief tests streambuf module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	typedef Vector<char> container_type;
	typedef streambuf::Container<container_type> streambuf_type;

	container_type container;
	streambuf_type streambuf(container);

	typedef ::std::basic_ostream<
		streambuf_type::char_type,
		streambuf_type::traits_type
	> ostream_type;

	ostream_type ostream(&streambuf);

	ostream << "test" << ::std::endl;

	log.writer() << "container" << container;

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
