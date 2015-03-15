/**
  @file     test_singleton.cpp
  @brief    tests SingletonTrait.
  @author   HRYKY
  @version  $Id: test_singleton.cpp 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/singleton_trait.h"
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

		/// tests SingletonTrait.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "singleton";

	class Singleton :
		public SingletonTrait<Singleton>
	{
	public :

		template <typename StreamT>
		StreamT & write_to(StreamT & out) const
		{
			return this->SingletonTrait<Singleton>::write_to(out);
		}

	private :
		hryky_delete_copy_constructor(Singleton);
		hryky_delete_copy_assign_op(Singleton);
		
		friend class SingletonTrait<Singleton>;
		
		Singleton()
		{
		}
	};

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
  @brief tests SingletonTrait.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	Singleton::instance_type const singleton;

	log.writer() << "singleton" << *singleton;

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
