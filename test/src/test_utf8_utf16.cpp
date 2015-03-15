/**
  @file     test_utf8_utf16.cpp
  @brief    tests to convert utf-16 to utf-8.
  @author   HRYKY
  @version  $Id: test_utf8_utf16.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/utf16.h"
#include "hryky/utf8.h"
#include "hryky/stream.h"
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
		
		/// tests to convert utf-16 to utf-8.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "utf8_utf16";

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
  @brief tests to convert utf-16 to utf-8.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	{
		typedef LiteralString<char16_t> src_type;
		typedef String<> dest_type;

		char16_t const string[] = {0x30C6, 0x30B9, 0x30C8, 0x0000};

		src_type const src(string);
		dest_type dest;

		auto encoder = utf8::encoder(ostream::back_inserter(dest));

		if (!utf16::decode(encoder, src.begin(), src.end())) {
			hryky_log_alert("failed to convert");
			return false;
		}

		hryky_log_info("result: " << dest);
	}

	{
		typedef LiteralString<wchar_t> src_type;
		typedef String<> dest_type;

		src_type const src(L"\u30C6\u30B9\u30C8");
		dest_type dest;

		auto encoder = utf8::encoder(ostream::back_inserter(dest));

		if (!utf16::decode(encoder, src.begin(), src.end())) {
			hryky_log_alert("failed to convert");
			return false;
		}

		hryky_log_info("result: " << dest);
	}

	{
		typedef LiteralString<char16_t> src_type;
		typedef String<> dest_type;

		char16_t const string[] = {0x30C6, 0x30B9, 0x30C8, 0x0000};

		src_type const src(string);
		dest_type dest;

		auto input = utf16::decoder(
			istream::range(src.begin(), src.end()));
		auto output = utf8::encoder(
			ostream::iterator(::std::back_inserter(dest)));

		while (!input.eof()) {
			input >> output;
		}

		hryky_log_info("result: " << dest);
	}

	{
		char16_t const string[] = {0x30C6, 0x30B9, 0x30C8, 0x0000};

		LiteralString<char16_t> const src(string);

		String<char> utf8_dest;
		auto utf8_encoder
			= utf8::encoder(ostream::back_inserter(utf8_dest));

		if (!utf16::decode(
			utf8_encoder, src.begin(), src.end())) {
			hryky_log_alert("failed to convert UTF-16 to UTF-8.");
			return false;
		}

		String<char16_t> utf16_dest;
		auto utf16_encoder
			= utf16::encoder(ostream::back_inserter(utf16_dest));

		if (!utf8::decode(
			utf16_encoder, utf8_dest.begin(), utf8_dest.end())) {
			hryky_log_alert("failed to convert UTF-8 to UTF-16.");
		}

		String<char> dest;
		auto encoder
			= utf8::encoder(ostream::back_inserter(dest));

		if (!utf16::decode(
			encoder, utf16_dest.begin(), utf16_dest.end())) {
			hryky_log_alert("failed to revert UTF-16 to UTF-8.");
			return false;
		}

		hryky_log_info("result: " << dest);
	}

	

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
