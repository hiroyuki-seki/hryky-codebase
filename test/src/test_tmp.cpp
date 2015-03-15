/**
  @file     test_tmp.cpp
  @brief    tests Template Metaprogramming module.
  @author   HRYKY
  @version  $Id: test_tmp.cpp 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
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
		
		/// tests TemplateMetaProgramming module.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "tmp";

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
  @brief tests Template Metaprogramming module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	typedef IntegralConstant<int, 0> zero;
	typedef IntegralConstant<int, 1> one;
	typedef IntegralConstant<int, 2> two;
	typedef IntegralConstant<int, 3> three;
	typedef IntegralConstant<int, 4> four;
	typedef IntegralConstant<int, 5> five;
	typedef IntegralConstant<int, 6> six;
	typedef IntegralConstant<int, 7> seven;
	typedef IntegralConstant<int, 8> eight;
	typedef IntegralConstant<int, 9> nine;
	typedef IntegralConstant<int, 10> ten;
	typedef IntegralConstant<int, 100> hundred;
	typedef IntegralConstant<int, 1000> thousand;

	typedef IntegralConstant<int, -1> minus_one;
	typedef IntegralConstant<int, -2> minus_two;
	typedef IntegralConstant<int, -3> minus_three;
	typedef IntegralConstant<int, -4> minus_four;
	typedef IntegralConstant<int, -5> minus_five;
	typedef IntegralConstant<int, -6> minus_six;
	typedef IntegralConstant<int, -7> minus_seven;
	typedef IntegralConstant<int, -8> minus_eight;
	typedef IntegralConstant<int, -9> minus_nine;
	typedef IntegralConstant<int, -10> minus_ten;

	static_assert(
		tmp::Equal<zero, zero>::type::value,
		"0 == 0");

	static_assert(
		tmp::NotEqual<zero, one>::type::value,
		"0 != 1");

	static_assert(
		tmp::Less<zero, one>::type::value,
		"0 < 1");

	static_assert(
		tmp::Greater<one, zero>::type::value,
		"1 > 0");

	static_assert(
		tmp::LessEqual<zero, one>::type::value,
		"0 <= 1");

	static_assert(
		tmp::LessEqual<zero, zero>::type::value,
		"0 <= 0");

	static_assert(
		tmp::GreaterEqual<one, zero>::type::value,
		"1 >= 0");

	static_assert(
		tmp::GreaterEqual<one, one>::type::value,
		"1 >= 1");

	static_assert(
		tmp::Equal<tmp::Increment<zero>, one>::type::value,
		"++0 == 1");
	
	static_assert(
		tmp::Equal<tmp::Decrement<two>, one>::type::value,
		"--2 == 1");

	static_assert(
		tmp::Equal<tmp::Add<one, two>, three>::type::value,
		"1+2 == 3");
	
	static_assert(
		tmp::Equal<tmp::Sub<three, two>, one>::type::value,
		"3-2 == 1");
	
	static_assert(
		tmp::Equal<tmp::Mul<two, three>, six>::type::value,
		"2*3 == 6");
	
	static_assert(
		tmp::Equal<tmp::Divide<six, two>, three>::type::value,
		"6/2 == 3");
	
	static_assert(
		tmp::Equal<tmp::Mod<five, two>, one>::type::value,
		"5%2 == 1");

	static_assert(
		tmp::Equal<
			tmp::Complement<one>, IntegralConstant<int, -1>
		>::type::value,
		"-(1) == -1");

	static_assert(
		tmp::Equal<true_type, true_type>::type::value,
		"true == true");

	static_assert(
		tmp::NotEqual<false_type, true_type>::type::value,
		"false != true");

	static_assert(
		tmp::Equal<tmp::Not<true_type>, false_type>::type::value,
		"!(true) == false");

	typedef tmp::List0 list0;
	typedef tmp::List1<one> list1;
	typedef tmp::List2<one, two> list2;
	typedef tmp::List3<one, two, three> list3;
	typedef tmp::List4<one, two, three, four> list4;
	typedef tmp::List5<one, two, three, four, five> list5;
	typedef tmp::List6<one, two, three, four, five, six> list6;
	typedef tmp::List7<one, two, three, four, five, six, seven> list7;
	typedef tmp::List8<one, two, three, four, five, six, seven, eight> list8;
	typedef tmp::List9<
		one, two, three, four, five, six, seven, eight, nine> list9;

	static_assert(
		tmp::Equal<tmp::Size<list0>, zero>::type::value,
		"<>.size() == 0");

	static_assert(
		tmp::Equal<tmp::Size<list1>, one>::type::value,
		"<1>.size() == 1");

	static_assert(
		tmp::Same<list0, list0>::type::value,
		"<> == <>");
		
	static_assert(
		!tmp::Same<list0, list1>::type::value,
		"<> != <1>");

	static_assert(
		tmp::Same<
			tmp::PushBack<list0, one>,
			list1
		>::type::value,
		"<> << 1 == <1>");

	static_assert(
		tmp::Same<
			tmp::PushBack<list1, two>,
			list2
		>::type::value,
		"<1> << 2 == <1,2>");

	static_assert(
		tmp::Same<
			tmp::PushFront<list0, one>,
			list1
		>::type::value,
		"1 >> <> == <1>");

	static_assert(
		tmp::Same<
			tmp::PushFront<tmp::List1<two>, one>,
			list2
		>::type::value,
		"1 >> <2> == <1,2>");

	static_assert(
		tmp::Same<
			tmp::PopBack<list2>,
			list1
		>::type::value,
		"<1,2>.pop_back() == <1>");

	static_assert(
		tmp::Same<
			tmp::PopFront<list2>,
			tmp::List1<two>
		>::type::value,
		"<1,2>.pop_front() == <2>");

	static_assert(
		tmp::Same<
			tmp::Dereference<tmp::Begin<list1> >,
			one
		>::type::value,
		"*(<1>.begin()) == 1");

	static_assert(
		tmp::Same<
			tmp::Dereference<tmp::Increment<tmp::Begin<list2> > >,
			two
		>::type::value,
		"*(++<1,2>.begin()) == 2");

	static_assert(
		tmp::Same<
			tmp::Dereference<tmp::Decrement<tmp::End<list1> > >,
			one
		>::type::value,
		"*(--<1>.end()) == 1");

	static_assert(
		tmp::Same<
			tmp::Dereference<
				tmp::Decrement<tmp::Decrement<tmp::End<list2> > > >,
			one
		>::type::value,
		"*(--(--<1,2>.end())) == 1");

	static_assert(
		tmp::Equal<
			tmp::Add<tmp::Begin<list2>, two>,
			tmp::End<list2>
		>::type::value,
		"<1,2>.begin()+2 == <1,2>.end()");

	static_assert(
		tmp::Equal<
			tmp::End<list2>,
			tmp::Add<tmp::Begin<list2>, two>
		>::type::value,
		"2+<1,2>.begin() == <1,2>.end()");

	static_assert(
		tmp::Equal<
			tmp::Sub<tmp::End<list2>, two>,
			tmp::Begin<list2>
		>::type::value,
		"<1,2>.end()-2 == <1,2>.begin()");

	static_assert(
		tmp::Equal<
			tmp::Sub<tmp::End<list2>, tmp::Begin<list2> >,
			tmp::Size<list2>
		>::type::value,
		"<1,2>.end()-<1,2>.begin() == <1,2>.size()");

	static_assert(
		tmp::Same<
			tmp::Insert<tmp::End<list1>, two>,
			list2
		>::type::value,
		"insert(<1>.end(),2) == <1,2>");

	static_assert(
		tmp::Same<
			tmp::Insert<tmp::Begin<tmp::List1<two> >, one>,
			list2
		>::type::value,
		"insert(<2>.begin(),1) == <1,2>");

	static_assert(
		tmp::Same<
			tmp::Erase<tmp::Begin<list2> >,
			tmp::List1<two>
		>::type::value,
		"erase(<1,2>.begin()) == <2>");

	static_assert(
		tmp::Same<
			tmp::EraseAt<list2, one>,
			tmp::List1<one>
		>::type::value,
		"erase_at(<1,2>, 1) == <1>");

	static_assert(
		tmp::Equal<tmp::At<list2, zero>, one>::type::value,
		"<1,2>[0] == 1");

	static_assert(
		tmp::Equal<tmp::At<list2, one>, two>::type::value,
		"<1,2>[1] == 2");

	static_assert(
		tmp::Same<
			tmp::Assign<tmp::Begin<list2>, zero>,
			tmp::List2<zero, two>
		>::type::value,
		"((*<1,2>.begin())=0) == <0,2>");

	static_assert(
		tmp::Same<
			tmp::AssignAt<list2, one, zero>,
			tmp::List2<one, zero>
		>::type::value,
		"(<1,2>[1]=0) == <1,0>");

	static_assert(
		tmp::Same<
			tmp::Swap<
				tmp::Begin<list3>,
				tmp::Decrement<tmp::End<list3> >
			>,
			tmp::List3<three, two, one>
		>::type::value,
		"swap(<1,2,3>.begin(),--<1,2,3>.end()) == <3,2,1>");

	static_assert(
		tmp::Find<list3, one>::result::type::value,
		"<1,2,3>.find(1) == true");
		
	static_assert(
		tmp::Find<list3, two>::result::type::value,
		"<1,2,3>.find(2) == true");
		
	static_assert(
		tmp::Find<list3, three>::result::type::value,
		"<1,2,3>.find(3) == true");
		
	static_assert(
		!tmp::Find<list3, zero>::result::type::value,
		"<1,2,3>.find(0) == false");

	static_assert(
		tmp::Same<
			tmp::Reverse<list3>,
			tmp::List3<three, two, one>
		>::type::value,
		"reverse(<1,2,3>) == <3,2,1>");

	static_assert(
		tmp::Same<
			tmp::Gcd<one, one>,
			one
		>::type::value,
		"GCD(1,1) == 1");

	static_assert(
		tmp::Same<
			tmp::Gcd<minus_one, one>,
			one
		>::type::value,
		"GCD(-1,1) == 1");

	static_assert(
		tmp::Same<
			tmp::Gcd<one, minus_one>,
			one
		>::type::value,
		"GCD(1,-1) == 1");

	static_assert(
		tmp::Same<
			tmp::Gcd<two, four>,
			two
		>::type::value,
		"GCD(2,4) == 2");

	static_assert(
		tmp::Same<
			tmp::Gcd<four, two>,
			two
		>::type::value,
		"GCD(4,2) == 2");

	static_assert(
		tmp::Same<
			tmp::Gcd<nine, six>,
			three
		>::type::value,
		"GCD(9,6) == 3");

	static_assert(
		tmp::Same<
			tmp::Gcd<six, nine>,
			three
		>::type::value,
		"GCD(6,9) == 3");

	static_assert(
		tmp::Same<
			tmp::Gcd<one, thousand>,
			one
		>::type::value,
		"GCD(1,1000) == 1");

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
