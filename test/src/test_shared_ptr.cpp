/**
  @file         test_shared_ptr.cpp
  @brief        tests hryky::shared_ptr.
  @author       HRYKY
  @version      $Id: test_shared_ptr.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/shared_ptr.h"
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
		
		/// tests hryky::shared_ptr.
		virtual bool run_impl();

	};
	Test const g_test;

	class A
	{
	public :
		virtual void operator()() {
			hryky_log_debug("This is A.");
		}
	};

	class B : public A
	{
	public :
		virtual void operator()() {
			hryky_log_debug("This is B.");
		}
	};

	class C : public A
	{
	public :
		virtual void operator()() {
			hryky_log_debug("This is C.");
		}
	};

	char const * const g_testname = "shared_ptr";

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
  @brief tests hryky::shared_ptr.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	allocator::Mempool<A> allocator_a;
	allocator::Mempool<B> allocator_b;
	allocator::Mempool<C> allocator_c;

	SharedPtr<A> a(
		allocator::instantiate_by(allocator_a),
		allocator_a);

	{
		SharedPtr<A> mix_allocator(
			allocator::instantiate_by(allocator_b),
			allocator_a);
	}

	SharedPtr<B> b(
		allocator::instantiate_by(allocator_b),
		allocator_b);

	SharedPtr<C> c(
		allocator::instantiate_by(allocator_c),
		allocator_c);

	a = b;
	a = c;

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
