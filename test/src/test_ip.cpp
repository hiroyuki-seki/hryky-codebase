/**
  @file         test_ip.cpp
  @brief        tests the parsing IP Address.
  @author       HRYKY
  @version      $Id: test_ip.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/ip.h"
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
		
		/// tests the parsing IP Address.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "ip";

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
  @brief tests the parsing IP Address.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	{
		octet_type const octets[] = "127.0.0.1";
		
		ip::v4::parser_type parser;

		size_t const parsed_size = parser(octets);
		if (parsed_size + 1 != sizeof(octets)) {
			hryky_log_emerg(
				"failed to parse IPv4 Address. "
				<< (json::writer()
					<< "message"
					<< reinterpret_cast<char const *>(&octets[0])
					));
			return false;
		}
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
