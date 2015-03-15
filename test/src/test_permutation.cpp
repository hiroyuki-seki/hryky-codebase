/**
  @file     test_permutation.cpp
  @brief    tests permutation module.
  @author   HRYKY
  @version  $Id: test_permutation.cpp 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/permutation.h"
#include "hryky/bitset.h"
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
		
		/// tests permutation module.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "permutation";

	/// check the result of permuation parity.
	template <typename ContainerT>
	bool check_parity(
		ContainerT & src, bool const correct, testing::Log & log);

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
  @brief tests permutation module.
 */
bool Test::run_impl()
{
	typedef testing::Log::writer_type log_writer_type;

	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	{
		typedef IntegralConstant<int, 0> zero;
		typedef IntegralConstant<int, 1> one;
		typedef IntegralConstant<int, 2> two;
		typedef IntegralConstant<int, 3> three;
		typedef tmp::List3<one,two,three> list_1_2_3;
		typedef tmp::List3<one,three,two> list_1_3_2;
		typedef tmp::List3<three,one,two> list_3_1_2;
		typedef tmp::List3<three,two,one> list_3_2_1;
		typedef tmp::List3<two,three,one> list_2_3_1;
		typedef tmp::List3<two,one,three> list_2_1_3;

		static_assert(
			!permutation::Parity<list_1_2_3>::type::value,
			"parity of <1,2,3> is 0");
		
		static_assert(
			permutation::Parity<list_1_3_2>::type::value,
			"parity of <1,3,2> is 1");

		static_assert(
			!permutation::Parity<list_3_1_2>::type::value,
			"parity of <3,1,2> is 0");

		static_assert(
			permutation::Parity<list_3_2_1>::type::value,
			"parity of <3,2,1> is 1");

		static_assert(
			!permutation::Parity<list_2_3_1>::type::value,
			"parity of <2,3,1> is 0");

		static_assert(
			permutation::Parity<list_2_1_3>::type::value,
			"parity of <2,1,3> is 1");

		typedef permutation::plainchanges::Directions<list_1_2_3> dirs_1_2_3;
		static_assert(
			!tmp::At<dirs_1_2_3, zero>::type::value &&
			!tmp::At<dirs_1_2_3, one>::type::value &&
			!tmp::At<dirs_1_2_3, two>::type::value,
			"directions of <1,2,3> is <0,0,0>");
		
		typedef permutation::plainchanges::Directions<list_1_3_2> dirs_1_3_2;
		static_assert(
			!tmp::At<dirs_1_3_2, zero>::type::value &&
			!tmp::At<dirs_1_3_2, one>::type::value &&
			!tmp::At<dirs_1_3_2, two>::type::value,
			"directions of <1,3,2> is <0,0,0>");
		
		typedef permutation::plainchanges::Directions<list_3_1_2> dirs_3_1_2;
		static_assert(
			!tmp::At<dirs_3_1_2, zero>::type::value &&
			!tmp::At<dirs_3_1_2, one>::type::value &&
			!tmp::At<dirs_3_1_2, two>::type::value,
			"directions of <3,1,2> is <0,0,0>");
		
		typedef permutation::plainchanges::Directions<list_3_2_1> dirs_3_2_1;
		static_assert(
			tmp::At<dirs_3_2_1, zero>::type::value &&
			!tmp::At<dirs_3_2_1, one>::type::value &&
			!tmp::At<dirs_3_2_1, two>::type::value,
			"directions of <3,2,1> is <1,0,0>");
		
		typedef permutation::plainchanges::Directions<list_2_3_1> dirs_2_3_1;
		static_assert(
			!tmp::At<dirs_2_3_1, zero>::type::value &&
			tmp::At<dirs_2_3_1, one>::type::value &&
			!tmp::At<dirs_2_3_1, two>::type::value,
			"directions of <2,3,1> is <0,1,0>");
		
		typedef permutation::plainchanges::Directions<list_2_1_3> dirs_2_1_3;
		static_assert(
			!tmp::At<dirs_2_1_3, zero>::type::value &&
			!tmp::At<dirs_2_1_3, one>::type::value &&
			tmp::At<dirs_2_1_3, two>::type::value,
			"directions of <2,1,3> is <0,0,1>");

		static_assert(
			tmp::Same<
				permutation::plainchanges::Next<list_1_2_3>, list_1_3_2
			>::type::value,
			"The next of <1,2,3> is <1,3,2>");

		static_assert(
			tmp::Same<
				permutation::plainchanges::Next<list_1_3_2>, list_3_1_2
			>::type::value,
			"The next of <1,3,2> is <3,1,2>");

		static_assert(
			tmp::Same<
				permutation::plainchanges::Next<list_3_1_2>, list_3_2_1
			>::type::value,
			"The next of <3,1,2> is <3,2,1>");
		
		static_assert(
			tmp::Same<
				permutation::plainchanges::Next<list_3_2_1>, list_2_3_1
			>::type::value,
			"The next of <3,2,1> is <2,3,1>");
		
		static_assert(
			tmp::Same<
				permutation::plainchanges::Next<list_2_3_1>, list_2_1_3
			>::type::value,
			"The next of <2,3,1> is <2,1,3>");

		static_assert(
			!permutation::plainchanges::Next<list_2_1_3>::at_end::value,
			"<2,1,3> is the last permutation.");
	}

	{
		log.writer() << stream::denote("totals");
		testing::Log::array_type const array(log.writer());
		
		size_t const totals_size = 11u;
		repeat(totals_size).foreach_at([&log](size_t const index) {
			log.writer() << permutation::total(index);
		});
	}

	size_t const array_size = 4u;

	// calculates the direction of each element in permutation.
	{
		uint32_t const array[array_size] = { 1u, 2u, 3u, 4u, };

		log.writer() << stream::denote("directions of Plain Changes");
		stream::map::Scope<log_writer_type> const map(log.writer());

		log.writer() << stream::denote("permutation") << array;
		stream::array::Scope<log_writer_type> const
			permutation_log(log.writer());

		repeat(array_size).foreach_at([&array, &log](
			size_t const index) {
			log.writer() << (permutation::plainchanges::direction(
				array, index) ? ">" : "<");
		});
	}

	// generates permutations by Plain Changes order.
	{
		uint32_t array[array_size] = { 1u, 2u, 3u, 4u, };

		log.writer() << stream::denote("plainchanges order");
		stream::map::Scope<log_writer_type> const map(log.writer());
		
		size_t count = 0u;
		size_t const limit = permutation::total(array_size);

		do {
			if (limit < ++count) {
				hryky_log_alert("enumeration doesn't finished.");
				return false;
			}

			(log.writer()
			 << stream::denote("count") << count
			 << stream::denote("permutation") << array
			 << stream::denote("parity") << permutation::parity(array));

			log.writer() << stream::denote("directions");
			stream::array::Scope<log_writer_type> const
				directions_log(log.writer());

			repeat(array_size).foreach_at([&array, &log](
				size_t const index) {
				log.writer() << (permutation::plainchanges::direction(
					array, index) ? ">" : "<");
			});
		} while (permutation::plainchanges::next(array, array));
	}

	// generates permutations by Plain Changes order with directions cache.
	{
		uint32_t array[array_size] = { 1u, 2u, 3u, 4u, };

		// The all directions of permutation by adscent order must be LEFT.
		Bitset<array_size> directions;
		permutation::plainchanges::directions(directions, array);
		if (directions.any()) {
			hryky_log_alert(
				"failed to generate the initial directions "
				<< (json::writer()
				<< stream::denote("array") << array
				<< stream::denote("wrong directions") << directions));
			return false;
		}

		log.writer() << "plainchanges order with directions cache";
		stream::map::Scope<log_writer_type> const map(log.writer());

		size_t count = 0u;
		size_t const limit = permutation::total(array_size);

		do {
			if (limit < ++count) {
				hryky_log_alert("enumeration doesn't finished.");
				return false;
			}
			
			(log.writer()
			 << stream::denote("count") << count
			 << stream::denote("permutation") << array
			 << stream::denote("parity") << permutation::parity(array));

			log.writer() << stream::denote("directions");
			stream::array::Scope<log_writer_type> const
				directions_log(log.writer());

			directions.foreach([&log](bool const element) {
				log.writer() << (element ? ">" : "<");
			});
		} while (permutation::plainchanges::next(array, array, directions));
	}

	// generates permutations by lexicographic order.
	{
		uint32_t array[array_size] = { 1u, 2u, 3u, 4u, };

		log.writer() << "lexicographical order";
		stream::map::Scope<log_writer_type> const map(log.writer());

		size_t count = 0;
		size_t const limit = permutation::total(array_size);

		do {
			if (limit < ++count) {
				hryky_log_alert("enumeration doesn't finished.");
				return false;
			}
			
			(log.writer()
			 << stream::denote("count") << count
			 << stream::denote("permutation") << array
			 << stream::denote("parity") << permutation::parity(array));

			log.writer() << stream::denote("directions");
			stream::array::Scope<log_writer_type> const
				directions_log(log.writer());

			repeat(array_size).foreach_at([&array, &log](
				size_t const index) {
				log.writer() << (permutation::plainchanges::direction(
					array, index) ? ">" : "<");
			});
		} while (permutation::lexicog::next(array, array));
	}

	{
		uint32_t const array[array_size] = { 1u, 2u, 3u, 4u, };
		if (!check_parity(array, false, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 2u, 1u, 3u, 4u, };
		if (!check_parity(array, true, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 1u, 3u, 2u, 4u, };
		if (!check_parity(array, true, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 3u, 1u, 2u, 4u, };
		if (!check_parity(array, false, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 2u, 3u, 1u, 4u, };
		if (!check_parity(array, false, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 3u, 2u, 1u, 4u, };
		if (!check_parity(array, true, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 1u, 2u, 4u, 3u, };
		if (!check_parity(array, true, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 2u, 1u, 4u, 3u, };
		if (!check_parity(array, false, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 1u, 4u, 2u, 3u, };
		if (!check_parity(array, false, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 4u, 1u, 2u, 3u, };
		if (!check_parity(array, true, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 2u, 4u, 1u, 3u, };
		if (!check_parity(array, true, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 4u, 2u, 1u, 3u, };
		if (!check_parity(array, false, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 1u, 3u, 4u, 2u, };
		if (!check_parity(array, false, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 3u, 1u, 4u, 2u, };
		if (!check_parity(array, true, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 1u, 4u, 3u, 2u, };
		if (!check_parity(array, true, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 4u, 1u, 3u, 2u, };
		if (!check_parity(array, false, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 3u, 4u, 1u, 2u, };
		if (!check_parity(array, false, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 4u, 3u, 1u, 2u, };
		if (!check_parity(array, true, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 2u, 3u, 4u, 1u, };
		if (!check_parity(array, true, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 3u, 2u, 4u, 1u, };
		if (!check_parity(array, false, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 2u, 4u, 3u, 1u, };
		if (!check_parity(array, false, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 4u, 2u, 3u, 1u, };
		if (!check_parity(array, true, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 3u, 4u, 2u, 1u, };
		if (!check_parity(array, true, log)) {
			return false;
		}
	}

	{
		uint32_t const array[array_size] = { 4u, 3u, 2u, 1u, };
		if (!check_parity(array, false, log)) {
			return false;
		}
	}

	return true;
}
/**
  @brief check the result of permuation parity.
 */
template <typename ContainerT>
bool check_parity(ContainerT & src, bool const correct, testing::Log & log)
{
	permutation::parity_type const result = permutation::parity(src);

	if (correct != result) {
		hryky_log_err(
			"The parity of permutation is incorrect. "
			<< (json::writer()
			<< stream::denote("permutation") << src
			<< stream::denote("correct") << correct
			<< stream::denote("wrong") << result));
		return false;
	}

	log.writer() << "check parity "
		<< (json::writer()
		<< stream::denote("permutation") << src
		<< stream::denote("parity") << result
		);
	
	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
