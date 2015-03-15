/**
  @file         test_asio_http_client.cpp
  @brief        tests http client by boost::asio.
  @author       HRYKY
  @version      $Id: test_asio_http_client.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/http.h"
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
		
		/// tests http client module.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "asio_http_client";

} // namespace "anonymous"
} // namespace test
} // namespace hryky

namespace bip = boost::asio::ip;

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
  @brief tests http client module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	boost::asio::io_service io_service;
	bip::tcp::resolver resolver(io_service);
	bip::tcp::resolver::query query("google.com", "http");
	bip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	bip::tcp::socket socket(io_service);

	// connects to the peer.
	{
		boost::system::error_code error;
		
		boost::asio::connect(socket, endpoint_iterator, error);

		if (error) {
			hryky_log_alert(
				"failed to connect to the peer "
				<< (json::writer()
				<< stream::denote("error") << error.message().c_str()));
			return false;
		}
	}

	// requests data.
	{
		char const request[] = (
			"GET / HTTP/1.1\r\n"
			"Host: google.com\r\n"
			"Connection: keep-alive\r\n"
			"Cache-Control: max-age=0\r\n"
			"User-Agent: "
			"Mozilla/5.0 (Windows NT 6.1; WOW64) "
			"AppleWebKit/537.11 (KHTML, like Gecko) "
			"Chrome/23.0.1271.64 "
			"Safari/537.11\r\n"
			"Accept: "
			"text/html,"
			"application/xhtml+xml,"
			"application/xml;q=0.9,"
			"*/*;q=0.8\r\n"
			"Accept-Encoding: gzip,deflate,sdch\r\n"
			"Accept-Language: ja,en-US;q=0.8,en;q=0.6\r\n"
			"Accept-Charset: UTF-8,*;q=0.5\r\n"
			"\r\n");

		size_t sent_size = 0;

		while (socket.is_open()) {
			boost::system::error_code error;

			sent_size += socket.send(
				boost::asio::buffer(
					&request[sent_size], sizeof(request) - 1 - sent_size),
				0,
				error);
			if (error) {
				hryky_log_alert(
					"failed to send data to the peer. "
					<< (json::writer()
					<< stream::denote("error") << error.message().c_str()));
				return false;
			}

			hryky_log_debug(
				"sent "
				<< (json::writer()
				<< stream::denote("size") << sent_size));

			if (sizeof(request) == sent_size + 1) {
				break;
			}
		}

		if (sizeof(request) != sent_size + 1) {
			hryky_log_alert(
				"failed to send data "
				<< (json::writer()));
			return false;
		}
	}

	// receives the response.
	{
		size_t const buffer_size = 0x200 << 8;

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

		size_t received_size = 0;

		while (socket.is_open()) {
			boost::system::error_code error;

			if (buffer_size < received_size) {
				hryky_log_alert(
					"There is no space in received buffer. "
					<< (json::writer()));
				return false;
			}

			size_t const current_received_size = socket.receive(
				boost::asio::buffer(
					&buffer[received_size], buffer_size - received_size),
				0,
				error);
			if (boost::asio::error::eof == error) {
				break;
			}
			if (error) {
				hryky_log_alert(
					"failed to receive data from the peer "
					<< (json::writer()
					<< stream::denote("error") << error.message().c_str()));
				return false;
			}

			buffer[received_size + current_received_size] = '\0';

			hryky_log_debug(
				"received "
				<< (json::writer()
					<< stream::denote("size") << current_received_size
					<< "data"
					<< reinterpret_cast<char const *>(&buffer[received_size])
					));

			if (0 == current_received_size) {
				break;
			}

			size_t const parsed_size = parser.parse(
				buffer.begin()
				+ static_cast<difference_type>(received_size),
				buffer.begin()
				+ static_cast<difference_type>(
					received_size + current_received_size));

			if (parser.fail()) {
				hryky_log_alert(
					"failed to parse HTTP Response "
					<< (json::writer()
					<< stream::denote("size") << received_size
					<< stream::denote("data") << reinterpret_cast<char const *>(&buffer[0])
					<< stream::denote("parser") << parser
					));
				return false;
			}

			hryky_log_debug(
				"parsing "
				<< (json::writer()
				<< stream::denote("received_size") << current_received_size
				<< stream::denote("parsed_size") << parsed_size
				));

			received_size += current_received_size;

			if (parser.accepted()) {
				break;
			}
		}

		hryky_log_debug(
			"received "
			<< (json::writer()
			<< stream::denote("received_size") << received_size
			<< stream::denote("data") << reinterpret_cast<char const *>(&buffer[0])));
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
