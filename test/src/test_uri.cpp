/**
  @file         test_uri.cpp
  @brief        tests using hryky::uri module.
  @author       HRYKY
  @version      $Id: test_uri.cpp 364 2014-07-12 01:03:03Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/memory.h"
#include "hryky/uri.h"
#include "hryky/string.h"
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
		
		// constructor.
		Test();
		
	private :
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		// tests a operation of string container.
		virtual bool run_impl();
		
	};
	Test const g_test;

	typedef mempool::Adapter<mempool::Arbitrary<> > mempool_type;

	char const *    g_testname = "uri";
	size_t const    g_mempool_size = 0x400 * 0x400 * 0x200;
	uint32_t        g_mempool[g_mempool_size / sizeof(uint32_t)] = { 0, };

	/// confirms whether the specified URI can be parsed.
	template < size_t Size >
	bool verify(octet_type const (& uri_str)[Size], mempool_type & mempool);

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
  @brief tests an operation of handling URI.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;

	log.writer() << "random" << random;

	// initializes memory pool
	mempool_type mempool;
	if (!mempool.get()->reset(g_mempool, g_mempool_size)) {
		hryky_log_alert(
			"failed to reset mempool::Arbitrary "
			<< (json::writer()
			<< stream::denote("mempool_size") << g_mempool_size));
		return false;
	}

	{
		octet_type const uri[] =
			"http://localhost:8080/test/test?key=value#id";

		if (!verify(uri, mempool)) {
			hryky_log_alert(
				"Reading URI failed "
				<< (json::writer()
				<< stream::denote("URI") << uri));
			return false;
		}
	}

	{
		octet_type const uri[] =
			"http://127.0.0.1/test/test?key=value#id";

		if (!verify(uri, mempool)) {
			hryky_log_alert(
				"Reading URI failed "
				<< (json::writer()
				<< stream::denote("URI") << uri));
			return false;
		}
	}

	{
		// valid as regname.
		octet_type const uri[] = "http://256.0.0.1/";

		if (!verify(uri, mempool)) {
			hryky_log_alert(
				"Reading URI failed "
				<< (json::writer()
				<< stream::denote("URI") << uri));
			return false;
		}
	}

	{
		// valid as regname
		octet_type const uri[] = "http://255.0.0.1.0/";

		if (!verify(uri, mempool)) {
			hryky_log_alert(
				"Reading URI failed "
				<< (json::writer()
				<< stream::denote("URI") << uri));
			return false;
		}
	}

	return true;
}
/**
  @brief confirms whether the specified URI can be parsed.
 */
template < size_t Size >
bool verify(octet_type const (& uri_str)[Size], mempool_type & mempool)
{
	uri_type uri(&mempool);
	uri::parser_type parser(&mempool);
	parser.entity(&uri);

	size_t const parsed_size = parser(uri_str);
	
	if (parsed_size != Size - 1) {
		hryky_log_info(
			"failed to parse "
			<< (json::writer()
				<< "URI"
				<< reinterpret_cast<char const *>(&uri_str[0])
				));
		return false;
	}

	hryky_log_info(
		"Reading URI passed "
		<< (json::writer()
			<< stream::denote("URI") << reinterpret_cast<char const *>(&uri_str[0])
			<< stream::denote("URI_data") << uri
			<< stream::denote("parser") << parser
			));

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
