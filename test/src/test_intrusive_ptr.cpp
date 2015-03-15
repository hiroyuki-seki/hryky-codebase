/**
  @file         test_intrusive_ptr.cpp
  @brief        tests hryky::IntrusivePtr.
  @author       HRYKY
  @version      $Id: test_intrusive_ptr.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/intrusive_ptr.h"
#include "hryky/intrusive_ptr_trait.h"
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
namespace intrusive
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
		
		/// tests hryky::IntrusivePtr.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "intrusive_ptr";

	// class having the availability of intrusive pointer.
	class Value : public IntrusivePtrTrait<>
	{
	public :
		Value()
		{
			hryky_log_debug("constructor is called.");
		};

		~Value()
		{
			hryky_log_debug("destructor is called.");
		}
	};

} // namespace "anonymous"
} // namespace intrusive
} // namespace test
} // namespace hryky

namespace hryky
{
/**
  @brief dereferences an intrusive pointer.
	/// dereferences an intrusive pointer.
	template <typename ValueT>
	ValueT const & dereference(IntrusivePtr<ValueT> const & ptr);

 */
template <typename ValueT>
typename RemovePointer<IntrusivePtr<ValueT> >::result_type
	dereference(IntrusivePtr<ValueT> const & ptr)
{
	return *ptr;
}
}
namespace hryky
{
namespace test
{
namespace intrusive
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
  @brief tests hryky::IntrusivePtr.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	typedef Value value_type;
	typedef IntrusivePtr<value_type> pointer;
	
	typedef allocator::Mempool<value_type> allocator_type;
	

	allocator_type allocator;

	{
		pointer ptr_a(instantiate_by(allocator));
		pointer ptr_b(instantiate_by(allocator));

		if (ptr_a == ptr_b ||
			ptr_a.get() == ptr_b ||
			ptr_a == ptr_b.get() ||
			ptr_a.get() == ptr_b.get()) {
			hryky_log_crit(
				"ptr_a must not be equal to ptr_b. "
				<< (json::writer()
				<< stream::denote("ptr_a") << ptr_a
				<< stream::denote("ptr_b") << ptr_b));
			return false;
		}

		ptr_a = ptr_b;

		if (ptr_a != ptr_b ||
			ptr_a.get() != ptr_b ||
			ptr_a != ptr_b.get() ||
			ptr_a.get() != ptr_b.get()) {
			hryky_log_crit(
				"ptr_a must not be equal to ptr_b. "
				<< (json::writer()
				<< stream::denote("ptr_a") << ptr_a
				<< stream::denote("ptr_b") << ptr_b));
			return false;
		}

		value_type const value_a = dereference(ptr_a);
	}

	return true;
}
} // namespace "anonymous"
} // namespace intrusive
} // namespace test
} // namespace hryky
