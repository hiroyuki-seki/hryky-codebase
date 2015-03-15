/**
  @file         test_http_parser.cpp
  @brief        tests the parsing HTTP Header.
  @author       HRYKY
  @version      $Id: test_http_parser.cpp 350 2014-04-24 10:10:31Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/http.h"
#include "hryky/strstr.h"
#include "hryky/back_inserter.h"
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
		
		/// tests the parsing HTTP Headers.
		virtual bool run_impl();
	};
	Test const g_test;

	char const * g_testname = "http_parser";
	
} // namespace "anonymous"
} // namespace test
} // namespace hryky
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
  @brief tests the parsing HTTP Headers.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;

	log.writer() << "random" << random;

	{
		octet_type const request_message[] = (
			"GET / HTTP/1.1\r\n"
			"Host: localhost\r\n"
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

		{
			typedef String<> line_type;
			typedef Vector<line_type> lines_type;
			
			typedef String<> token_type;
			typedef Vector<token_type> tokens_type;

			LiteralString<> const newline("\r\n");
			LiteralString<> const space(" ");
			LiteralString<> const colon(":");
			
			lines_type lines;

			LiteralString<>(
				reinterpret_cast<char const *>(&request_message[0]),
				sizeof(request_message) - 1)
				.split_to(back_inserter(lines), newline);
			
			hryky_log_info((json::writer() << hryky_stream_denote(lines)));

			lines_type::const_iterator const lines_begin = lines.begin();
			lines_type::const_iterator const lines_end = lines.end();
			lines_type::const_iterator lines_itr = lines_begin;

			if (lines_end == lines_itr) {
				hryky_log_alert("HTTP Method is not found.");
				return false;
			}

			{
				line_type const & line = *lines_itr;
				tokens_type tokens;
				line.split_to(back_inserter(tokens), space);

				if (3u != tokens.size()) {
					hryky_log_alert("Request-Line is invalid.");
					return false;
				}

				tokens_type::const_iterator tokens_itr = tokens.begin();

				http::method::kind_type const method(
					(*tokens_itr).begin(),
					(*tokens_itr).end(),
					http::method::g_equal_character);
				if (!method.verify()) {
					hryky_log_alert("unexpected method:" << (*tokens_itr));
					return false;
				}
				hryky_log_info((
					json::writer() << hryky_stream_denote(method)));
				++tokens_itr;

				token_type const & request_uri = *tokens_itr;
				
				hryky_log_info((
					json::writer() << hryky_stream_denote(request_uri)));
				{
					token_type::size_type token_pos = 0u;
					{
						token_type::size_type const found =
							request_uri.find(colon, token_pos);
						if (token_type::npos != found) {
							
						}
					}
				}
			}

		}
		
		http::parser_type parser;

		size_t const parsed_size = parser.parse(request_message);
		
		if (parser.fail()) {
			hryky_log_emerg(
				"failed to parse a HTTP Request. "
				<< (json::writer()
					<< "message"
					<< reinterpret_cast<char const *>(&request_message[0])
					));
			return false;
		}

		hryky_log_debug(
			"parsed "
			<< (json::writer()
			<< stream::denote("message_size") << sizeof(request_message)
			<< stream::denote("parsed_size") << parsed_size
			));
	}

	{
		octet_type const response_message[] = (
			"HTTP/1.1 301 Moved Permanently\r\n"
			"Location: http://www.google.com/\r\n"
			"Content-Type: text/html; charset=UTF-8\r\n"
			"Date: Mon, 14 Jan 2013 03:53:37 GMT\r\n"
			"Expires: Wed, 13 Feb 2013 03:53:37 GMT\r\n"
			"Cache-Control: public, max-age=2592000\r\n"
			"Allow: GES\r\n"
			"Server: gws\r\n"
			"Content-Length: 219\r\n"
			"X-XSS-Protection: 1; mode=block\r\n"
			"X-Frame-Options: SAMEORIGIN\r\n"
			"Alternate-Protocol: 80:quic\r\n"
			"\r\n"
			"<HTML><HEAD><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\">\n"
			"<TITLE>301 Moved</TITLE></HEAD><BODY>\n"
			"<H1>301 Moved</H1>\n"
			"The document has moved\n"
			"<A HREF=\"http://www.google.com/\">here</A>.\r\n"
			"</BODY></HTML>\r\n"
			);
		
		http::parser_type parser;

		size_t const parsed_size = parser.parse(response_message);
		if (parser.fail()) {
			hryky_log_emerg(
				"failed to parse a HTTP Response. "
				<< (json::writer()
					<< "message"
					<< reinterpret_cast<char const *>(&response_message[0])
					));
			return false;
		}

		hryky_log_debug(
			"parsed "
			<< (json::writer()
			<< stream::denote("message_size") << sizeof(response_message)
			<< stream::denote("parsed_size") << parsed_size
			));
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
