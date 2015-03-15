/**
  @file         test_atomic.cpp
  @brief        tests atomic value.
  @author       HRYKY
  @version      $Id: test_atomic.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/assert.h"
#include "hryky/atomic.h"
#include "hryky/memory.h"
#include "hryky/testing.h"
#include "hryky/vector.h"
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
		
		/// tests to access atomic values.
		virtual bool run_impl();

		/// tests all operators.
		template < typename AtomicT >
		bool test_integer(typename AtomicT::value_type const & value);

	};
	Test const g_test;

	char const * g_testname = "atomic";
	
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
  @brief tests to access atomic values.
 */
bool Test::run_impl()
{
	if (!this->test_integer<atomic::Entity<int32_t> >(1)) {
		return false;
	}

	if (!this->test_integer<atomic::Entity<int8_t> >(1)) {
		return false;
	}

	{
		atomic::Entity<int32_t>   lhs(1);
		atomic::Entity<int32_t>   rhs(2);

		int32_t const lhs_value = int32_t(lhs);
		int32_t const rhs_value = int32_t(rhs);
		
		int32_t const result = lhs + rhs;
		hryky_assert(result == (lhs_value + rhs_value));
	}

	atomic::Entity<float> atomic_float;
	
	return true;
}
/**
  @brief tests operators for integer.
 */
template < typename AtomicT >
bool Test::test_integer(typename AtomicT::value_type const & value)
{
	typedef AtomicT                             atomic_type;
	typedef typename atomic_type::value_type    value_type;
	
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;

	{
		atomic_type src(value);
		hryky_assert(value == src);
		
	}

	atomic_type atomic;

	atomic = value;
	hryky_assert(atomic == value);
	
	// '+' operations;

	{
		value_type const prev = atomic;
		atomic = atomic + value;
		hryky_assert(atomic == (prev + value));
	}
	{
		value_type const prev = atomic;
		atomic = atomic + atomic;
		hryky_assert(atomic == (prev + prev));
	}
	{
		value_type const prev = atomic;
		atomic += value;
		hryky_assert(atomic == (prev + value));
	}
	{
		value_type const prev = atomic;
		atomic += atomic;
		hryky_assert(atomic == (prev + prev));
	}
	{
		value_type const prev = atomic;
		atomic = value + atomic;
		hryky_assert(atomic == (value + prev));
	}
	{
		value_type const prev = atomic;
		atomic++;
		hryky_assert(atomic == (prev + 1));
	}
	{
		value_type const prev = atomic;
		++atomic;
		hryky_assert(atomic == (prev + 1));
	}

	// '-' operations;

	{
		value_type const prev = atomic;
		atomic = atomic - value;
		hryky_assert(atomic == (prev - value));
	}
	{
		value_type const prev = atomic;
		atomic = atomic - atomic;
		hryky_assert(atomic == (prev - prev));
	}
	{
		value_type const prev = atomic;
		atomic -= value;
		hryky_assert(atomic == (prev - value));
	}
	{
		value_type const prev = atomic;
		atomic -= atomic;
		hryky_assert(atomic == (prev - prev));
	}
	{
		value_type const prev = atomic;
		atomic = value - atomic;
		hryky_assert(atomic == (value - prev));
	}
	{
		value_type const prev = atomic;
		atomic--;
		hryky_assert(atomic == (prev - 1));
	}
	{
		value_type const prev = atomic;
		--atomic;
		hryky_assert(atomic == (prev - 1));
	}

	// logical AND operations;

	{
		value_type const prev = atomic;
		atomic = atomic & value;
		hryky_assert(atomic == (prev & value));
	}
	{
		value_type const prev = atomic;
		atomic = atomic & atomic;
		hryky_assert(atomic == (prev & prev));
	}
	{
		value_type const prev = atomic;
		atomic &= value;
		hryky_assert(atomic == (prev & value));
	}
	{
		value_type const prev = atomic;
		atomic &= atomic;
		hryky_assert(atomic == (prev & prev));
	}
	{
		value_type const prev = atomic;
		atomic = value & atomic;
		hryky_assert(atomic == (value & prev));
	}

	// logical OR operations

	if (0 != value) {
		{
			value_type const prev       = atomic;
			atomic_type const result    = atomic | value;
			hryky_assert(result == (prev | value));
		}
		{
			value_type const prev       = atomic;
			atomic_type result          = atomic;
			
			result |= value;
			hryky_assert(result == (prev | value));
		}
	}

	if (0 != atomic) {
		{
			value_type const prev       = atomic;
			atomic_type const result    = value | atomic;
			hryky_assert(result == (value | prev));
		}
		{
			value_type const prev       = atomic;
			atomic_type const result    = atomic | atomic;
			hryky_assert(result == (prev | prev));
		}
		{
			value_type const prev       = atomic;
			atomic_type result          = atomic;

			result |= atomic;
			hryky_assert(result == (prev | prev));
		}
	}
	
	// logical XOR operations

	if (0 != value) {
		{
			value_type const prev       = atomic;
			atomic_type const result    = atomic ^ value;
			hryky_assert(result == (prev ^ value));
		}
		{
			value_type const prev       = atomic;
			atomic_type result          = atomic;
			
			result ^= value;
			hryky_assert(result == (prev ^ value));
		}
	}

	if (0 != atomic) {
		{
			value_type const prev       = atomic;
			atomic_type const result    = value ^ atomic;
			hryky_assert(result == (value ^ prev));
		}
		{
			value_type const prev       = atomic;
			atomic_type const result    = atomic ^ atomic;
			hryky_assert(result == (prev ^ prev));
		}
		{
			value_type const prev       = atomic;
			atomic_type result          = atomic;

			result ^= atomic;
			hryky_assert(result == (prev ^ prev));
		}
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
