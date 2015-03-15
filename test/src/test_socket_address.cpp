/**
  @file     test_socket_address.cpp
  @brief    tests to resolve the address of network.
  @author   HRYKY
  @version  $Id: test_socket_address.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/socket.h"
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
		
		/// tests socket module.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "socket_address";

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
  @brief tests socket module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	socket::Module module;
	if (!module.reset()) {
		hryky_log_alert("failed to reset socket module.");
	}
	auto const enregister_module = scoped_registry(&module);

	log.writer() << "addresses";
	auto const addresses_log = stream::array::scope(log.writer());

	{
		auto const address_log = stream::map::scope(log.writer());

		char const * const host = hryky_nullptr;
		char const * const service = hryky_nullptr;

		log.writer() << hryky_stream_denote(host);
		log.writer() << hryky_stream_denote(service);

		size_t count = 0u;
		(socket::FindAddress()
		 .host(host)
		 .service(service)
		 ([&log, &count](
			 socket::Address const & address) {
			 ++count;
			 log.writer() << hryky_stream_denote(address);
			 return false;
		 }));
		log.writer() << hryky_stream_denote(count);
	}

	{
		auto const address_log = stream::map::scope(log.writer());

		char const * const host = hryky_nullptr;
		char const * const service = "80";

		log.writer() << hryky_stream_denote(host);
		log.writer() << hryky_stream_denote(service);

		size_t count = 0u;
		(socket::FindAddress()
		 .host(host)
		 .service(service)
		 ([&log, &count](
			socket::Address const & address) {
			 ++count;
			log.writer() << hryky_stream_denote(address);
			return false;
		}));
		log.writer() << hryky_stream_denote(count);
	}

	{
		auto const address_log = stream::map::scope(log.writer());

		char const * const host = hryky_nullptr;
		char const * const service = "56731";

		log.writer() << hryky_stream_denote(host);
		log.writer() << hryky_stream_denote(service);

		size_t count = 0u;
		(socket::FindAddress()
		 .host(host)
		 .service(service)
		 .as_ipv6()
		 ([&log, &count](
			 socket::Address const & address) {
			 ++count;
			 log.writer() << hryky_stream_denote(address);
			 return false;
		 }));
		log.writer() << hryky_stream_denote(count);
	}

	{
		auto const address_log = stream::map::scope(log.writer());

		char const * const host = hryky_nullptr;
		char const * const service = "56732";

		log.writer() << hryky_stream_denote(host);
		log.writer() << hryky_stream_denote(service);

		size_t count = 0u;
		(socket::FindAddress()
		 .host(host)
		 .service(service)
		 .as_ipv6()
		 .as_server()
		 ([&log, &count](
			 socket::Address const & address) {
			 ++count;
			 log.writer() << hryky_stream_denote(address);
			 return false;
		 }));
		log.writer() << hryky_stream_denote(count);
	}

	{
		auto const address_log = stream::map::scope(log.writer());

		char const * const host = hryky_nullptr;
		char const * const service = "56733";

		log.writer() << hryky_stream_denote(host);
		log.writer() << hryky_stream_denote(service);

		size_t count = 0u;
		(socket::FindAddress()
		 .host(host)
		 .service(service)
		 .as_ipv6()
		 .as_client()
		 ([&log, &count](
			 socket::Address const & address) {
			 ++count;
			 log.writer() << hryky_stream_denote(address);
			 return false;
		 }));
		log.writer() << hryky_stream_denote(count);
	}
	
	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
