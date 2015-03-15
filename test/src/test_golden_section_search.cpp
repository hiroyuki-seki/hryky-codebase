/**
  @file     test_golden_section_search.cpp
  @brief    tests Golden Section Search algorithm.
  @author   HRYKY
  @version  $Id: test_golden_section_search.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/golden_section_search.h"
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
namespace golden
{
namespace section
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
		
		/// tests Golden Section Search algorithm.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "golden_section_search";

} // namespace "anonymous"
} // namespace section
} // namespace golden
} // namespace test
} // namespace hryky
namespace hryky
{
namespace test
{
namespace golden
{
namespace section
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
  @brief tests Golden Section Search algorithm.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	float result;
	float result_y;
	size_t count = 0;
	golden_section_search(
		0.0f, 1.0f,
		[] (float const x) {
			return (x - 0.3f) * (x - 0.3f) + 0.1f;
		},
		[&result, &result_y, &count, &log] (
			float const first,
			float const first_y,
			float const last,
			float const last_y) {
			++count;
			log.writer() << "progress "
				<< (json::writer()
				<< stream::denote("count") << count
				<< stream::denote("first") << first
				<< stream::denote("first_y") << first_y
				<< stream::denote("last") << last
				<< stream::denote("last_y") << last_y
				);
			
			if (0.0001f > (last - first)) {
				result = (first + last) * 0.5f;
				result_y = (first_y + last_y) * 0.5f;
				return true;
			}
			return false;
		});

	log.writer() << "The minimum of f(x) = (x-0.3)^2+0.1 "
		<< (json::writer()
		<< stream::denote("count") << count
		<< stream::denote("x") << result
		<< stream::denote("y") << result_y
		<< stream::denote("calc") << (result - 0.3f) * (result - 0.3f) + 0.1f
		);

	return true;
}
} // namespace "anonymous"
} // namespace section
} // namespace golden
} // namespace test
} // namespace hryky
