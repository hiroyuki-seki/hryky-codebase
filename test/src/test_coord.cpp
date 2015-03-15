/**
  @file     test_coord.cpp
  @brief    tests coords module.
  @author   HRYKY
  @version  $Id: test_coord.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/coord.h"
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
		
		/// tests coords module.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "coord";

	/// tests operations of cartesian coordinates.
	template <typename CoordT>
	bool test_cartesian(testing::Log & log, testing::Random & random);

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
  @brief tests coords module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	typedef float value_type;

	if (!test_cartesian<coord::Cartesian<value_type, 5> >(log, random)) {
		hryky_log_alert("failed to test Cartesian[5]");
		return false;
	}
	
	if (!test_cartesian<coord::Cartesian2<value_type> >(log, random)) {
		hryky_log_alert("failed to test Cartesian2");
		return false;
	}
	
	if (!test_cartesian<coord::Cartesian3<value_type> >(log, random)) {
		hryky_log_alert("failed to test Cartesian3");
		return false;
	}
	
	if (!test_cartesian<coord::Cartesian4<value_type> >(log, random)) {
		hryky_log_alert("failed to test Cartesian4");
		return false;
	}
	
	return true;
}
/**
  @brief tests operations of cartesian coordinates.
 */
template <typename CoordT>
bool test_cartesian(testing::Log &, testing::Random &)
{
	typedef CoordT coord_type;
	typedef typename coord_type::value_type value_type;

	// default constructor.
	{
		coord_type coord;
	}
		// copy constructor
	{
		coord_type const copied;
		coord_type const coord(copied);
	}
	// copy constructor by move semantics
	{
		coord_type const coord(::std::move(coord_type()));
	}
	// construct with a scalar.
	{
		value_type const scalar = value_type();
		coord_type const coord(scalar);
	}
	// assignment
	{
		coord_type coord;
		coord = coord_type();
	}
	// add
	{
		coord_type const lhs;
		coord_type const rhs;
		coord_type const result = lhs + rhs;
	}
	// sub
	{
		coord_type const lhs;
		coord_type const rhs;
		coord_type const result = lhs - rhs;
	}
	// mul
	{
		coord_type const lhs;
		coord_type const rhs;
		coord_type const result = lhs * rhs;
	}
	// div
	{
		coord_type const lhs;
		coord_type const rhs;
		coord_type const result = lhs / rhs;
	}
	// scalar mul from right.
	{
		coord_type const lhs;
		coord_type const result = lhs * value_type();
	}
	// scalar mul from left.
	{
		coord_type const rhs;
		coord_type const result = value_type() * rhs;
	}
	
	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
