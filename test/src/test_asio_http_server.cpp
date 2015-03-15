/**
  @file         test_asio_http_server.cpp
  @brief        tests http server by boost::asio.
  @author       HRYKY
  @version      $Id: hryky-template.l 63 2012-05-01 03:42:24Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/boost.h"
#include "hryky/testing.h"
#include "hryky/vector.h"
#include "hryky/memory.h"
#include "hryky/http.h"
#include "hryky/thread.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace test
{
namespace
{
	// enregisters a test
	class Test : testing::unit::Base
	{
	public :
		typedef testing::unit::Base base_type;
		typedef Test this_type;
		
		/// constructor.
		Test();

	private :
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		/// tests a http server module.
		virtual bool run_impl();
	};
	Test const g_test;

	char const *    g_testname = "asio_http_server";
	
} // namespace "anonymous"
} // namespace test
} // namespace hryky

namespace bip = boost::asio::ip;
//------------------------------------------------------------------------------
// static variable
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// public member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace test
{
namespace
{
/**
  @brief constructor.
 */
Test::Test()
	: base_type(g_testname)
{
	return;
}
/**
  @brief tests a http server module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;

	log.writer() << "random" << random;

	boost::asio::io_service                     io_service;
	bip::tcp::resolver                           resolver(io_service);

	// enumerates endpoints as server.
	{
		bip::tcp::resolver::query                    query("http");
		bip::tcp::resolver::iterator endpoint_itr =  resolver.resolve(query);
		bip::tcp::resolver::iterator const           endpoint_itr_end;

		for (; endpoint_itr_end != endpoint_itr; ++endpoint_itr) {
			bip::tcp::endpoint const endpoint    = *endpoint_itr;
			bip::address const address           = endpoint.address();
			uint16_t const port                 = endpoint.port();

			(log.writer() << "endpoint as server "
				<< (json::writer()
				<< stream::denote("host") << address.to_string().c_str()
				<< stream::denote("service") << port
				<< stream::denote("is_loopback") << address.is_loopback()
				<< stream::denote("is_ipv4") << address.is_v4()
				<< stream::denote("is_ipv6") << address.is_v6()
				)
			 );
		}
	}

	// enumerates endpoints as localhost.
	{
		bip::tcp::resolver::query                    query("localhost", "http");
		bip::tcp::resolver::iterator endpoint_itr =  resolver.resolve(query);
		bip::tcp::resolver::iterator const           endpoint_itr_end;

		for (; endpoint_itr_end != endpoint_itr; ++endpoint_itr) {
			bip::tcp::endpoint const endpoint    = *endpoint_itr;
			bip::address const address           = endpoint.address();
			uint16_t const port                 = endpoint.port();

			(log.writer() << "endpoint as localhost "
				<< (json::writer()
				<< stream::denote("host") << address.to_string().c_str()
				<< stream::denote("service") << port
				<< stream::denote("is_loopback") << address.is_loopback()
				<< stream::denote("is_ipv4") << address.is_v4()
				<< stream::denote("is_ipv6") << address.is_v6()
				)
			 );
		}
	}

	// enumerates endpoints as local host.
	{
		bip::tcp::resolver::query                    query(bip::host_name(), "http");
		bip::tcp::resolver::iterator endpoint_itr =  resolver.resolve(query);
		bip::tcp::resolver::iterator const           endpoint_itr_end;

		for (; endpoint_itr_end != endpoint_itr; ++endpoint_itr) {
			bip::tcp::endpoint const endpoint    = *endpoint_itr;
			bip::address const address           = endpoint.address();
			uint16_t const port                 = endpoint.port();

			(log.writer() << "endpoint as local hostname "
				<< (json::writer()
				<< stream::denote("host") << address.to_string().c_str()
				<< stream::denote("service") << port
				<< stream::denote("is_loopback") << address.is_loopback()
				<< stream::denote("is_ipv4") << address.is_v4()
				<< stream::denote("is_ipv6") << address.is_v6()
				));
		}
	}

	bip::tcp::acceptor acceptor(io_service);
	{
		bip::tcp::resolver::query            query("http");
		bip::tcp::resolver::iterator         itr =  resolver.resolve(query);
		bip::tcp::resolver::iterator const   end;

		for (; end != itr; ++itr) {
			bip::tcp::endpoint const endpoint    = *itr;
			bip::address const address           = endpoint.address();
			uint16_t const port                 = endpoint.port();

			if (address.is_v6()) {
				// opens a socket for listening.
				{
					boost::system::error_code error;
					acceptor.open(endpoint.protocol(), error);
					if (error) {
						hryky_log_alert(
							"failed to open a socket "
							<< (json::writer()
							<< stream::denote("error") << error.message().c_str()
							<< stream::denote("host") << address.to_string().c_str()
							<< stream::denote("service") << port
							<< stream::denote("is_loopback") << address.is_loopback()
							<< stream::denote("is_ipv4") << address.is_v4()
							<< stream::denote("is_ipv6") << address.is_v6()
							));
						continue;
					}
				}
				
				acceptor.set_option(
					boost::asio::socket_base::reuse_address(true));

				// binds the socket.
				{
					boost::system::error_code error;
					acceptor.bind(endpoint, error);
					if (error) {
						hryky_log_alert(
							"failed to bind the socket "
							<< (json::writer()
							<< stream::denote("error") << error.message().c_str()
							<< stream::denote("host") << address.to_string().c_str()
							<< stream::denote("service") << port
							<< stream::denote("is_loopback") << address.is_loopback()
							<< stream::denote("is_ipv4") << address.is_v4()
							<< stream::denote("is_ipv6") << address.is_v6()
							));
						continue;
					}
				}

				(log.writer() << "bind an endpoint "
					<< (json::writer()
					<< stream::denote("host") << address.to_string().c_str()
					<< stream::denote("service") << port
					<< stream::denote("is_loopback") << address.is_loopback()
					<< stream::denote("is_ipv4") << address.is_v4()
					<< stream::denote("is_ipv6") << address.is_v6()
					));
				
				break;
			}
		}

		if (end == itr) {
			hryky_log_alert(
				"current network address is not found "
				<< (json::writer()
				));
			return false;
		}
	}

	// listens the socket.
	{
		boost::system::error_code error;
		int const backlog = boost::asio::socket_base::max_connections;
		acceptor.listen(backlog, error);
		if (error) {
			hryky_log_alert(
				"failed to listen the socket "
				<< (json::writer()
				<< stream::denote("error") << error.message().c_str()));
			return false;
		}
	}

	thread::pool_type thread_pool;
	if (!thread_pool.run([](){
		::std::system("curl http://localhost/");
	})) {
		hryky_log_alert("failed to send HTTP Request asynchronously.");
		return false;
	}

	// accepts a client.
	bip::tcp::socket peer(io_service);
	{
		boost::system::error_code error;

		acceptor.accept(peer, error);
		if (error) {
			hryky_log_alert(
				"failed to accept a peer "
				<< (json::writer()
				<< stream::denote("error") << error.message().c_str()));
			return false;
		}
	}

	// receive data.
	{
		size_t const buffer_size = 0x100 << 1;

		typedef Vector<octet_type>              buffer_type;
		typedef buffer_type::difference_type    difference_type;

		buffer_type buffer;
		if (!buffer.resize(buffer_size + 1)) {
			hryky_log_alert(
				"failed to allocate buffer "
				<< (json::writer()
				<< stream::denote("buffer_size") << buffer_size));
			return false;
		}

		http::Entity entity;
		http::parser_type parser;
		parser.entity(&entity);

		while (peer.is_open()) {
			boost::system::error_code error;

			size_t const received_size = peer.receive(
				boost::asio::buffer(&buffer[0], buffer_size),
				0,
				error);
			if (error) {
				hryky_log_alert(
					"failed to reaceive data from the peer "
					<< (json::writer()
					<< stream::denote("error") << error.message().c_str()));
				return false;
			}
			buffer[received_size] = '\0';

			hryky_log_debug(
				"received "
				<< (json::writer()
				<< stream::denote("size") << received_size
				<< stream::denote("data") << reinterpret_cast<char const *>(&buffer[0])
				));

			if (0 == received_size) {
				break;
			}

			size_t const parsed_size = parser.parse(
				buffer.begin(),
				buffer.end() + static_cast<difference_type>(received_size));

			if (parser.fail()) {
				hryky_log_alert(
					"failed to parse HTTP Request "
					<< (json::writer()
					<< stream::denote("size") << received_size
					<< stream::denote("parsed_size") << parsed_size
					<< stream::denote("data") << &buffer[0]
					<< stream::denote("parser") << parser
					));
				return false;
			}

			if (parser.accepted()) {
				break;
			}
		}

		if (!parser.accepted()) {
			hryky_log_alert(
				"HTTP request is incomplete. "
				<< (json::writer()
				<< stream::denote("entity") << entity
				<< stream::denote("parser") << parser
				));
			return false;
		}
	}

	// responses date.
	{
		octet_type const response[] = (
			"HTTP/1.1 200 \r\n"
			"\r\n");

		size_t sent_size = 0;

		while (peer.is_open()) {
			boost::system::error_code error;

			sent_size += peer.send(
				boost::asio::buffer(
					&response[sent_size], sizeof(response) - 1 - sent_size),
				0,
				error);
			if (error) {
				hryky_log_alert(
					"failed to send data to the peer "
					<< (json::writer()
					<< stream::denote("error") << error.message().c_str()));
				return false;
			}

			hryky_log_debug(
				"sent "
				<< (json::writer()
				<< stream::denote("size") << sent_size
				));

			if (sizeof(response) == sent_size + 1) {
				break;
			}
		}

		hryky_log_debug(
			"HTTP Response is sent. "
			<< (json::writer()
			<< stream::denote("data") << reinterpret_cast<char const *>(&response[0])));
	}

	return true;
}

} // namespace "anonymous"
} // namespace test
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
