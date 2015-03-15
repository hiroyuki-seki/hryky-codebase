/**
  @file     test_aligned_on.cpp
  @brief    tests AlignedOn.
  @author   HRYKY
  @version  $Id: test_aligned_on.cpp 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/aligned_on.h"
#include "hryky/array.h"
#include "hryky/tmp.h"
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

		/// tests AlignedOn.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "aligned_on";

	/// prints an aligned array.
	template <size_t Bits>
	void test_aligned_array(testing::Log & log);

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
  @brief tests AlignedOn.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	{
		AlignedOn<4>::type aligned;
		(log.writer()
		 << "aligned16"
		 << stream::map::Begin()
		 << "address" << stream::Hex() << &aligned
		 << "size" << stream::Hex() << sizeof(aligned)
		 << stream::map::End());
	}

	test_aligned_array<0>(log);
	test_aligned_array<1>(log);
	test_aligned_array<2>(log);
	test_aligned_array<3>(log);
	test_aligned_array<4>(log);
	test_aligned_array<5>(log);
	test_aligned_array<6>(log);
	test_aligned_array<7>(log);
	test_aligned_array<8>(log);

	return true;
}
/**
  @brief prints an aligned array.
 */
template <size_t Bits>
void test_aligned_array(testing::Log & log)
{
	ostream::String<String<> > os;
	os << "aligned" << tmp::PowC<2, Bits>::value;

	log.writer() << os.str();
	auto const scoped_array = stream::array::scope(log.writer());

	typedef Array<AlignedOn<Bits>::type, 4u> aligned_type;
	aligned_type const aligned = {0, };
	aligned.foreach([&log](aligned_type::const_reference ref) {
		auto const scoped_map = stream::map::scope(log.writer());
		(log.writer()
		 << "address" << stream::Hex() << &ref
		 << "size" << stream::Hex() << sizeof(ref));
	});
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
