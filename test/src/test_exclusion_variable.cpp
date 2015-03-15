/**
  @file         test_exclusion_variable.cpp
  @brief        tests hryky::exclusion::Variable.
  @author       HRYKY
  @version      $Id: test_exclusion_variable.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/exclusion.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
#define hryky_assert(check) if (!(check)) { hryky_log_err(#check); return false; }
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace test
{
namespace exclusion
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
		
		/// tests hryky::exclusion::Variable.
		virtual bool run_impl();

		/// tests all operators.
		template < typename VariableT >
		bool test_integer(typename VariableT::value_type const & value);

	};
	Test const g_test;

	char const * const g_testname = "exclusion_variable";

} // namespace "anonymous"
} // namespace exclusion
} // namespace test
} // namespace hryky
namespace hryky
{
namespace test
{
namespace exclusion
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
  @brief tests hryky::exclusion::Variable.
 */
bool Test::run_impl()
{
	if (!this->test_integer<hryky::exclusion::Variable<int32_t> >(1)) {
		return false;
	}

	if (!this->test_integer<hryky::exclusion::Variable<int8_t> >(1)) {
		return false;
	}

	{
		hryky::exclusion::Variable<int32_t>   lhs(1);
		hryky::exclusion::Variable<int32_t>   rhs(2);

		int32_t const lhs_value = int32_t(lhs);
		int32_t const rhs_value = int32_t(rhs);
		
		int32_t const result = lhs + rhs;
		hryky_assert(result == lhs_value + rhs_value);
	}

	hryky::exclusion::Variable<float> variable_float;

	return true;
}
/**
  @brief tests operators for integer.
 */
template < typename VariableT >
bool Test::test_integer(typename VariableT::value_type const & value)
{
	typedef VariableT                             variable_type;
	typedef typename variable_type::value_type    value_type;
	
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	{
		variable_type src(value);
		hryky_assert(value == src);
		
		variable_type variable(src);
		hryky_assert(variable == src);
	}

	variable_type variable;

	variable = value;
	hryky_assert(variable == value);
	
	variable = variable_type(value);
	hryky_assert(variable == value);

	// '+' operations;

	{
		value_type const prev = variable;
		variable = variable + value;
		hryky_assert(variable == prev + value);
	}
	{
		value_type const prev = variable;
		variable = variable + variable;
		hryky_assert(variable == prev + prev);
	}
	{
		value_type const prev = variable;
		variable += value;
		hryky_assert(variable == prev + value);
	}
	{
		value_type const prev = variable;
		variable += variable;
		hryky_assert(variable == prev + prev);
	}
	{
		value_type const prev = variable;
		variable = value + variable;
		hryky_assert(variable == value + prev);
	}
	{
		value_type const prev = variable;
		variable++;
		hryky_assert(variable == prev + 1);
	}
	{
		value_type const prev = variable;
		++variable;
		hryky_assert(variable == prev + 1);
	}

	// '-' operations;

	{
		value_type const prev = variable;
		variable = variable - value;
		hryky_assert(variable == prev - value);
	}
	{
		value_type const prev = variable;
		variable = variable - variable;
		hryky_assert(variable == prev - prev);
	}
	{
		value_type const prev = variable;
		variable -= value;
		hryky_assert(variable == prev - value);
	}
	{
		value_type const prev = variable;
		variable -= variable;
		hryky_assert(variable == prev - prev);
	}
	{
		value_type const prev = variable;
		variable = value - variable;
		hryky_assert(variable == value - prev);
	}
	{
		value_type const prev = variable;
		variable--;
		hryky_assert(variable == prev - 1);
	}
	{
		value_type const prev = variable;
		--variable;
		hryky_assert(variable == prev - 1);
	}

	// '*' operations;

	{
		value_type const prev = variable;
		variable = variable * value;
		hryky_assert(variable == prev * value);
	}
	{
		value_type const prev = variable;
		variable = variable * variable;
		hryky_assert(variable == prev * prev);
	}
	{
		value_type const prev = variable;
		variable *= value;
		hryky_assert(variable == prev * value);
	}
	{
		value_type const prev = variable;
		variable *= variable;
		hryky_assert(variable == prev * prev);
	}
	{
		value_type const prev = variable;
		variable = value * variable;
		hryky_assert(variable == value * prev);
	}

	// '/' operations

	if (0 != value) {
		{
			value_type const prev       = variable;
			variable_type const result    = variable / value;
			hryky_assert(result == prev / value);
		}
		{
			value_type const prev       = variable;
			variable_type result          = variable;
			
			result /= value;
			hryky_assert(result == prev / value);
		}
	}

	if (0 != variable) {
		{
			value_type const prev       = variable;
			variable_type const result    = value / variable;
			hryky_assert(result == value / prev);
		}
		{
			value_type const prev       = variable;
			variable_type const result    = variable / variable;
			hryky_assert(result == prev / prev);
		}
		{
			value_type const prev       = variable;
			variable_type result          = variable;

			result /= variable;
			hryky_assert(result == prev / prev);
		}
	}
	
	// '%' operations

	if (0 != value) {
		{
			value_type const prev       = variable;
			variable_type const result    = variable % value;
			hryky_assert(result == prev % value);
		}
		{
			value_type const prev       = variable;
			variable_type result          = variable;
			
			result %= value;
			hryky_assert(result == prev % value);
		}
	}

	if (0 != variable) {
		{
			value_type const prev       = variable;
			variable_type const result    = value % variable;
			hryky_assert(result == value % prev);
		}
		{
			value_type const prev       = variable;
			variable_type const result    = variable % variable;
			hryky_assert(result == prev % prev);
		}
		{
			value_type const prev       = variable;
			variable_type result          = variable;

			result %= variable;
			hryky_assert(result == prev % prev);
		}
	}
	
	return true;
}
} // namespace "anonymous"
} // namespace exclusion
} // namespace test
} // namespace hryky
