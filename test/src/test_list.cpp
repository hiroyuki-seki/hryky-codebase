/**
  @file     test_list.cpp
  @brief    tests hryky::List.
  @author   HRYKY
  @version  $Id: test_list.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/list.h"
#include "hryky/memory.h"
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
		
		/// tests hryky::List.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "list";

	template <typename ContainerT, typename AlternativeT>
	void scatter(
		ContainerT & container,
		size_t const size,
		AlternativeT & alternative,
		typename ContainerT::value_type value = ContainerT::value_type()) {
		hryky::repeat(size).foreach([&container, value, &alternative]() {
			if (0 == alternative()) {
				container.push_back(value);
			}
			else {
				container.push_front(value);
			}
		});
	}

	template <typename ContainerT, typename AlternativeT, typename AsciiDistT>
	void scatter(
		ContainerT & container,
		size_t const size,
		AlternativeT & alternative,
		AsciiDistT & ascii_dist) {
		hryky::repeat(size).foreach([&container, &ascii_dist, &alternative]() {
			if (0 == alternative()) {
				container.push_back(ascii_dist());
			}
			else {
				container.push_front(ascii_dist());
			}
		});
	}

	template <typename InputIterator, typename SizeT>
	InputIterator advance(InputIterator iterator, SizeT const size) {
		hryky::repeat(size).foreach([&iterator]() {
			++iterator;
		});
		return iterator;
	}

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
  @brief tests hryky::List.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	typedef uint16_t size_type;

	// randomizes the size of list.
	random::Uniform<size_type> size_dist(
		random.generator(), 0x1, 1 << 11);
	log.writer() << "size_dist" << size_dist;

	// randomizes alternative.
	random::Uniform<uint8_t> alternative(
		random.generator(), 0x0, 0x1);
	log.writer() << "alternative" << alternative;
	
	// randomizes ascii.
	random::Uniform<char> ascii_dist(
		random.generator(), 0x0, 0x7F);
	log.writer() << "ascii" << ascii_dist;
	
	typedef char value_type;

	value_type const sample[] = "ABCDEF";
	value_type const * const sample_begin = &sample[0];
	value_type const * const sample_end = &sample[sizeof(sample) - 1];
	size_type const sample_size = static_cast<size_type>(
		::std::distance(sample_begin, sample_end));

	typedef List<value_type>            list_type;
	typedef list_type::const_reference  const_reference;
	typedef list_type::reference        reference;

	mempool_type const mempool = mempool::global::Registry::instance();

	// default constructor.
	{
		list_type container;
	}
	// constructor with allocator.
	{
		list_type container(mempool);
	}
	// constructor with size.
	{
		size_type const size = size_dist();
		list_type const container(size, mempool);
		if (size != container.size()) {
			hryky_log_alert(
				"The result of constructor with size is invalid. "
				<< (json::writer()
				<< stream::denote("size") << size
				<< stream::denote("container") << container));
			return false;
		}
	}
	// constructor with a value.
	{
		value_type const value = '*';
		size_type const size = size_dist();
		list_type const container(size, '*', mempool);

		if (size != container.size()) {
			hryky_log_alert(
				"The result of constructor with a value is invalid. "
				<< (json::writer()
				<< stream::denote("size") << size
				<< stream::denote("container") << container));
			return false;
		}

		if (!container.every_at([value](
			const_reference ref,
			size_type const index) {
			if (value != ref) {
				hryky_log_alert(
					"invalid value "
					<< (json::writer()
					<< stream::denote("at") << index
					<< stream::denote("wrong") << ref
					<< stream::denote("correct") << value));
				return false;
			}
			return true;
		})) {
			hryky_log_alert(
				"The result of constructor with a value is invalid. "
				<< (json::writer()
				<< stream::denote("container") << container));
			return false;
		}
	}
	// constructor with the range of values.
	{
		list_type const container(sample_begin, sample_end, mempool);

		if (sample_size != container.size()) {
			hryky_log_alert(
				"The result of constructor with the range of values is invalid. "
				<< (json::writer()
				<< stream::denote("size") << sample_size
				<< stream::denote("container") << container));
			return false;
		}

		if (!container.every_at([&sample](
			const_reference ref,
			size_type const index) {
			if (sample[index] != ref) {
				hryky_log_alert(
					"invalid value "
					<< (json::writer()
					<< stream::denote("at") << index
					<< stream::denote("wrong") << ref
					<< stream::denote("correct") << sample[index]
					));
				return false;
			}
			return true;
		})) {
			hryky_log_alert(
				"The result of constructor with the range of values is invalid. "
				<< (json::writer()
				<< stream::denote("container") << container));
			return false;
		}
	}
	// copy constructor.
	{
		list_type const container_0;
		list_type const container_1(container_0);

		if (container_0 != container_1) {
			hryky_log_alert(
				"The result of copy constructor is invalid. "
				<< (json::writer()
				<< stream::denote("lhs") << container_0
				<< stream::denote("rhs") << container_1));
			return false;
		}
	}
	// constructor by rvalue reference.
	{
		list_type const container(::std::move(list_type(
			sample_begin, sample_end, mempool)));

		if (container != list_type(sample_begin, sample_end, mempool)) {
			hryky_log_alert(
				"The result of constructor with rvalue is invalid. "
				<< (json::writer()
				<< stream::denote("container") << container));
			return false;
		}
	}
	// operator=.
	{
		list_type container_0;
		list_type const container_1(sample_begin, sample_end, mempool);
		container_0 = container_1;

		if (container_0 != container_1) {
			hryky_log_alert(
				"The result of assignment operation is invalid. "
				<< (json::writer()
				<< stream::denote("lhs") << container_0
				<< stream::denote("rhs") << container_1));
			return false;
		}
	}
	// clear.
	{
		list_type container;
		container.clear();

		// empty.
		if (!container.empty()) {
			hryky_log_alert(
				"The result of clear is invalid. "
				<< (json::writer()
				<< stream::denote("container") << container));
			return false;
		}
	}
	// stream out.
	{
		log.writer() << "test_stream_out" << list_type();
	}
	// swap.
	{
		list_type const ascending(sample_begin, sample_end, mempool);
		list_type const descending(
			::std::reverse_iterator<value_type const *>(sample_end),
			::std::reverse_iterator<value_type const *>(sample_begin),
			mempool);
		
		list_type container_0(ascending);
		list_type container_1(descending);
		container_1.swap(container_0);

		if (ascending != container_1 || descending != container_0) {
			hryky_log_alert(
				"The result of swap is invalid. "
				<< (json::writer()
				<< stream::denote("container_0") << container_0
				<< stream::denote("container_1") << container_1
				));
			return false;
		}
	}
	// reverse iterator
	{
		list_type const container(sample_begin, sample_end);
		size_type const size = container.size();
		if (!hryky::range(container.rbegin(), container.rend()).every_at(
			[&sample, size](
				const_reference element, size_type const index) {
				if (sample[size - index - 1] != element) {
					hryky_log_alert(
						"The result of reverse operator is invalid. "
						<< (json::writer()
						<< stream::denote("index") << index
						<< stream::denote("correct") << sample[size - index - 1]
						<< stream::denote("wrong") << element
						));
					return false;
				}
				return true;
			})) {
			hryky_log_alert("failure of " << container);
			return false;
		}
	}
	// front()
	{
		list_type const container(sample_begin, sample_end);
		if (*sample_begin != container.front()) {
			hryky_log_alert(
				"The result of front() is invalid. "
				<< (json::writer()
				<< stream::denote("value") << *sample_begin
				<< stream::denote("container") << container
				));
			return false;
		}
	}
	// back()
	{
		list_type const container(sample_begin, sample_end);
		if (*(sample_end - 1) != container.back()) {
			hryky_log_alert(
				"The result of back() is invalid. "
				<< (json::writer()
				<< stream::denote("value") << *(sample_end - 1)
				<< stream::denote("container") << container
				));
			return false;
		}
	}
	// expands the buffer by resize()
	{
		list_type container(sample_begin, sample_end);
		size_type const size = size_dist();
		container.resize(size);

		// checks the size.
		if (size != container.size()) {
			hryky_log_alert(
				"The result of resize() is invalid "
				<< (json::writer()
				<< stream::denote("size") << size
				<< stream::denote("container") << container));
			return false;
		}

		list_type::const_iterator const last_half_begin = advance(
			container.begin(),
			(::std::min)(sample_size, container.size()));
		list_type::const_iterator const begin = container.begin();

		// confirms the previous values at the head of the container.
		if (!hryky::range(begin, last_half_begin).every_at([&sample](
			const_reference element, size_type const index) {
			if (sample[index] != element) {
				hryky_log_alert(
					"The result of resize() is invalid "
					<< (json::writer()
					<< stream::denote("index") << index
					<< stream::denote("correct") << sample[index]
					<< stream::denote("wrong") << element));
				return false;
			}
			return true;
		})) {
			hryky_log_alert("failure of " << container);
			return false;
		}

		list_type::const_iterator const end = container.end();
		value_type const value = value_type();

		// confirms whether the values at last half are default.
		if (!hryky::range(last_half_begin, end).every_at([value](
			const_reference element, size_type const index) {
			if (value != element) {
				hryky_log_alert(
					"The result of resize() is invalid "
					<< (json::writer()
					<< stream::denote("index") << index
					<< stream::denote("correct") << value
					<< stream::denote("wrong") << element));
				return false;
			}
			return true;
		})) {
			hryky_log_alert("failure of " << container);
			return false;
		}
	}
	// shorten the buffer by resize()
	{
		list_type container(sample_begin, sample_end);
		container.resize(
			static_cast<list_type::size_type>(sample_size >> 1));

		// checks the size.
		if ((sample_size >> 1) != container.size()) {
			hryky_log_alert(
				"The result of resize() is invalid "
				<< (json::writer()
				<< stream::denote("size") << sample_size
				<< stream::denote("container") << container));
			return false;
		}

		// confirms the previous values remains in the container.
		if (!container.every_at([&sample](
			const_reference element, size_type const index) {
			if (sample[index] != element) {
				hryky_log_alert(
					"The result of resize() is invalid "
					<< (json::writer()
					<< stream::denote("index") << index
					<< stream::denote("correct") << sample[index]
					<< stream::denote("wrong") << element
					));
				return false;
			}
			return true;
		})) {
			hryky_log_alert("failure of " << container);
			return false;
		}
	}
	// assign() by the range.
	{
		list_type container;
		container.assign(sample_begin, sample_end);

		if (sample_size != container.size()) {
			hryky_log_alert(
				"The result of assign() is invalid "
				<< (json::writer()
				<< stream::denote("size") << sample_size
				<< stream::denote("container") << container));
			return false;
		}

		if (!container.every_at([&sample](
			const_reference element, size_type const index) {
			if (sample[index] != element) {
				hryky_log_alert(
					"The result of assign() is invalid "
					<< (json::writer()
					<< stream::denote("index") << index
					<< stream::denote("correct") << sample[index]
					<< stream::denote("wrong") << element));
				return false;
			}
			return true;
		})) {
			hryky_log_alert("failure of " << container);
			return false;
		}
	}
	// assign() by multiple same values.
	{
		list_type container;
		size_type const size = size_dist();
		list_type::value_type const value = '*';
		container.assign(size, value);

		if (size != container.size()) {
			hryky_log_alert(
				"The result of assign() is invalid "
				<< (json::writer()
				<< stream::denote("size") << size
				<< stream::denote("container") << container));
			return false;
		}

		if (!container.every_at([value](
			const_reference element, size_type const index) {
			if (value != element) {
				hryky_log_alert(
					"The result of assign() is invalid "
					<< (json::writer()
					<< stream::denote("index") << index
					<< stream::denote("correct") << value
					<< stream::denote("wrong") << element));
				return false;
			}
			return true;
		})) {
			hryky_log_alert("failure of " << container);
			return false;
		}
	}
	// push_back()
	{
		list_type container;
		size_type const size = size_dist();

		hryky::repeat(size).foreach_at(
			[&container, &sample, sample_size](size_type const index) {
				container.push_back(sample[index % sample_size]);
			});

		if (size != container.size()) {
			hryky_log_alert(
				"The result of push_back() is invalid "
				<< (json::writer()
				<< stream::denote("size") << size
				<< stream::denote("container") << container));
			return false;
		}

		if (!container.every_at([&sample, sample_size](
			const_reference element, size_type const index) {
			value_type const correct = sample[index % sample_size];
			if (correct != element) {
				hryky_log_alert(
					"The result of push_back() is invalid "
					<< (json::writer()
					<< stream::denote("index") << index
					<< stream::denote("correct") << correct
					<< stream::denote("wrong") << element));
				return false;
			}
			return true;
		})) {
			hryky_log_alert("failure of " << container);
			return false;
		}
	}
	// push_back() by rvalue reference.
	{
		list_type container;
		size_type const size = size_dist();

		hryky::repeat(size).foreach_at(
			[&container, &sample, sample_size](size_type const index) {
				container.push_back(::std::move(sample[index % sample_size]));
			});

		if (size != container.size()) {
			hryky_log_alert(
				"The result of push_back() is invalid "
				<< (json::writer()
				<< stream::denote("size") << size
				<< stream::denote("container") << container));
			return false;
		}

		if (!container.every_at([&sample, sample_size](
			const_reference element, size_type const index) {
			value_type const correct = sample[index % sample_size];
			if (correct != element) {
				hryky_log_alert(
					"The result of push_back() is invalid "
					<< (json::writer()
					<< stream::denote("index") << index
					<< stream::denote("correct") << correct
					<< stream::denote("wrong") << element));
				return false;
			}
			return true;
		})) {
			hryky_log_alert("failure of " << container);
			return false;
		}
	}
	// push_front()
	{
		list_type container;
		size_type const size = size_dist();

		hryky::repeat(size).foreach_at(
			[&container, &sample, sample_size](size_type const index) {
				container.push_front(sample[index % sample_size]);
			});

		if (size != container.size()) {
			hryky_log_alert(
				"The result of push_back() is invalid "
				<< (json::writer()
				<< stream::denote("size") << size
				<< stream::denote("container") << container));
			return false;
		}

		if (!hryky::range(container.rbegin(), container.rend()).every_at(
			[&sample, sample_size](
				const_reference element, size_type const index) {
				value_type const correct = sample[index % sample_size];
				if (correct != element) {
					hryky_log_alert(
						"The result of push_back() is invalid "
						<< (json::writer()
						<< stream::denote("index") << index
						<< stream::denote("correct") << correct
						<< stream::denote("wrong") << element));
					return false;
				}
				return true;
			})) {
			hryky_log_alert("failure of " << container);
			return false;
		}
	}
	// push_front() by rvalue
	{
		list_type container;
		size_type const size = size_dist();

		hryky::repeat(size).foreach_at(
			[&container, &sample, sample_size](size_type const index) {
				container.push_front(::std::move(sample[index % sample_size]));
			});

		if (size != container.size()) {
			hryky_log_alert(
				"The result of push_back() is invalid "
				<< (json::writer()
				<< stream::denote("size") << size
				<< stream::denote("container") << container));
			return false;
		}

		if (!hryky::range(container.rbegin(), container.rend()).every_at(
			[&sample, sample_size](
				const_reference element, size_type const index) {
				value_type const correct = sample[index % sample_size];
				if (correct != element) {
					hryky_log_alert(
						"The result of push_back() is invalid "
						<< (json::writer()
						<< stream::denote("index") << index
						<< stream::denote("correct") << correct
						<< stream::denote("wrong") << element));
					return false;
				}
				return true;
			})) {
			hryky_log_alert("failure of " << container);
			return false;
		}
	}
	// push_back() and pop_front()
	{
		list_type container;
		size_type const size = size_dist();
		list_type::value_type const value = '*';

		scatter(container, size, alternative, value);

		if (size != container.size()) {
			hryky_log_alert(
				"The result of push_back()/pop_front() is invalid "
				<< (json::writer()
				<< stream::denote("size") << size
				<< stream::denote("container") << container));
			return false;
		}

		if (!container.every_at([value](
			const_reference element, size_type const index) {
			if (value != element) {
				hryky_log_alert(
					"The result of push_back()/pop_front() is invalid "
					<< (json::writer()
					<< stream::denote("index") << index
					<< stream::denote("correct") << value
					<< stream::denote("wrong") << element));
				return false;
			}
			return true;
		})) {
			hryky_log_alert("failure of " << container);
			return false;
		}
	}
	// pop_back()
	{
		list_type container;
		size_type const size = size_dist();

		scatter(container, size, alternative);

		if (!hryky::repeat(size).every_at([&container](size_type const index) {
			if (!container.pop_back()) {
				hryky_log_alert(
					"The result of pop_back() is invalid. "
					<< (json::writer()
					<< stream::denote("index") << index));
				return false;
			}
			return true;
		})) {
			hryky_log_alert("failure of " << container);
			return false;
		}
	}
	// pop_front()
	{
		list_type container;
		size_type const size = size_dist();

		scatter(container, size, alternative);

		if (!hryky::repeat(size).every_at([&container](size_type const index) {
			if (!container.pop_front()) {
				hryky_log_alert(
					"The result of pop_back() is invalid. "
					<< (json::writer()
					<< stream::denote("index") << index));
				return false;
			}
			return true;
		})) {
			hryky_log_alert("failure of " << container);
			return false;
		}
	}
	// pop_back() and pop_front()
	{
		list_type container;
		size_type const size = size_dist();

		scatter(container, size, alternative);

		if (!hryky::repeat(size).every_at(
			[&container, &alternative](size_type const index) {
				if (0 == alternative()) {
					if (!container.pop_back()) {
						hryky_log_alert(
							"The result of pop_back()/pop_front() is invalid. "
							<< (json::writer()
							<< stream::denote("index") << index));
						return false;
					}
				}
				else {
					if (!container.pop_front()) {
						hryky_log_alert(
							"The result of pop_back()/pop_front() is invalid. "
							<< (json::writer()
							<< stream::denote("index") << index));
						return false;
					}
				}
				return true;
			})) {
			hryky_log_alert("failure of " << container);
			return false;
		}
	}
	// inserts by a single value.
	{
		list_type container;

		if (!hryky::repeat(size_dist()).every_at(
			[&container, &ascii_dist, &size_dist](
				size_type const count) {
				value_type const value = ascii_dist();

				list_type const prev(container);
				size_type const distance = static_cast<size_type>(
					size_dist() % (container.size() + 1));
				list_type::iterator const inserted = container.insert(
					advance(container.begin(), distance), value);

				if (distance != ::std::distance(container.begin(), inserted)) {
					hryky_log_alert(
						"The result of insert() is invalid. "
						<< (json::writer()
						<< stream::denote("distance") << distance
						<< stream::denote("inserted") << inserted
						<< stream::denote("container") << container
						<< stream::denote("count") << count
						));
					return false;
				}

				list_type::iterator itr = container.begin();

				// confirms the first half.
				if (!hryky::range(
					prev.begin(), advance(prev.begin(), distance)).every_at(
						[&itr](
							const_reference element, size_type const index) {
							if (element != *itr) {
								hryky_log_alert(
									"The result of insert() is invalid. "
									<< (json::writer()
									<< stream::denote("index") << index
									<< stream::denote("correct") << element
									<< stream::denote("wrong") << *itr));
								return false;
							}
							++itr;
							return true;
						})) {
					hryky_log_alert(
						"failure of " << (json::writer()
						<< stream::denote("distance") << distance
						<< stream::denote("prev") << prev
						<< stream::denote("count") << count
						<< stream::denote("container") << container));
					return false;
				}

				// confirms the insertion
				if (value != *itr) {
					hryky_log_alert(
						"The result of insert() is invalid. "
						<< (json::writer()
						<< stream::denote("dinstance") << distance
						<< stream::denote("correct") << value
						<< stream::denote("wrong") << *itr
						<< stream::denote("prev") << prev
						<< stream::denote("container") << container
						<< stream::denote("count") << count
						));
					return false;
				}
				++itr;

				// confirms the last half.
				if (!hryky::range(
					advance(prev.begin(), distance), prev.end()).every_at(
						[&itr, distance](
							const_reference element, size_type const index) {
							if (element != *itr) {
								hryky_log_alert(
									"The result of insert() is invalid. "
									<< (json::writer()
									<< stream::denote("index") << distance + 1 + index
									<< stream::denote("correct") << element
									<< stream::denote("wrong") << *itr
									));
								return false;
							}
							++itr;
							return true;
						})) {
					hryky_log_alert(
						"failure of " << (json::writer()
						<< stream::denote("distance") << distance
						<< stream::denote("prev") << prev
						<< stream::denote("count") << count
						<< stream::denote("container") << container));
					return false;
				}
				return true;
			})) {
			hryky_log_alert("failure of " << container);
			return false;
		}
	}
	// insert by the range
	{
		list_type container;

		if (!hryky::repeat(size_dist()).every_at(
			[&container, &size_dist, &ascii_dist](
				size_type const count) {
				list_type insertion;
				{
					size_type const size = size_dist() % 4u + 1u;
					hryky::repeat(size).foreach([&insertion, &ascii_dist]() {
						insertion.push_back(ascii_dist());
					});
				}

				list_type const prev(container);
				size_type const distance = static_cast<size_type>(
					size_dist() % (container.size() + 1));
				list_type::iterator const inserted = container.insert(
					advance(container.begin(), distance),
					insertion.begin(),
					insertion.end());

				if (distance != ::std::distance(container.begin(), inserted)) {
					hryky_log_alert(
						"The result of insert() is invalid. "
						<< (json::writer()
						<< stream::denote("distance") << distance
						<< stream::denote("container") << container
						<< stream::denote("count") << count
						));
					return false;
				}

				list_type::iterator itr = container.begin();

				// confirms the first half.
				if (!hryky::range(
					prev.begin(), advance(prev.begin(), distance)).every_at(
						[&itr] (
							const_reference element, size_type const index) {
							if (element != *itr) {
								hryky_log_alert(
									"The result of insert() is invalid. "
									<< (json::writer()
									<< stream::denote("index") << index
									<< stream::denote("correct") << element
									<< stream::denote("wrong") << *itr));
								return false;
							}
							++itr;
							return true;
						})) {
					hryky_log_alert(
						"failure of " << (json::writer()
						<< stream::denote("count") << count
						<< stream::denote("distance") << distance
						<< stream::denote("prev") << prev
						<< stream::denote("container") << container));
					return false;
				}

				// confirms the insertion
				if (!insertion.every_at([&itr, distance](
					const_reference element, size_type const index) {
					if (element != *itr) {
						hryky_log_alert(
							"The result of insert() is invalid. "
							<< (json::writer()
							<< stream::denote("index") << distance + index
							<< stream::denote("correct") << element
							<< stream::denote("wrong") << *itr
							));
						return false;
					}
					++itr;
					return true;
				})) {
					hryky_log_alert(
						"failure of " << (json::writer()
						<< stream::denote("count") << count
						<< stream::denote("distance") << distance
						<< stream::denote("container") << container));
					return false;
				}

				size_type const last_half_offset = static_cast<size_type>(
					distance + insertion.size());

				// confirms the last half.
				if (!hryky::range(
					advance(prev.begin(), distance), prev.end()).every_at(
						[&itr, last_half_offset](
							const_reference element, size_type const index) {
							if (element != *itr) {
								hryky_log_alert(
									"The result of insert() is invalid. "
									<< (json::writer()
									<< stream::denote("index") << last_half_offset + index
									<< stream::denote("correct") << element
									<< stream::denote("wrong") << *itr));
								return false;
							}
							++itr;
							return true;
						})) {
					hryky_log_alert(
						"failure of " << (json::writer()
						<< stream::denote("count") << count
						<< stream::denote("distance") << distance
						<< stream::denote("prev") << prev
						<< stream::denote("container") << container));
					return false;
				}
				return true;
			})) {
			hryky_log_alert("failure of " << container);
			return false;
		}
	}
	// erase by a single value.
	{
		size_t count = 0;
		size_t const num = size_dist();
		list_type container;

		scatter(container, num, alternative, ascii_dist);

		while (!container.empty()) {
			list_type const prev(container);
			size_type const distance = static_cast<size_type>(
				size_dist() % container.size());
			list_type::iterator const erased = container.erase(
				advance(container.begin(), distance));

			if (distance != ::std::distance(container.begin(), erased)) {
				hryky_log_alert(
					"The result of erase() is invalid. "
					<< (json::writer()
					<< stream::denote("distance") << distance
					<< stream::denote("prev") << prev
					<< stream::denote("container") << container
					<< stream::denote("count") << count
					));
				return false;
			}

			list_type::iterator itr = container.begin();

			// confirms the first half.
			if (!hryky::range(
				prev.begin(),advance(prev.begin(), distance)).every_at(
					[&itr](
						const_reference element, size_type const index) {
						if (element != *itr) {
							hryky_log_alert(
								"The result of erase() is invalid. "
								<< (json::writer()
								<< stream::denote("index") << index
								<< stream::denote("correct") << element
								<< stream::denote("wrong") << *itr));
							return false;
						}
						++itr;
						return true;
					})) {
				hryky_log_alert(
					"failure of " << (json::writer()
					<< stream::denote("count") << count
					<< stream::denote("distance") << distance
					<< stream::denote("prev") << prev
					<< stream::denote("container") << container));
				return false;
			}

			// confirms the last half.
			if (!hryky::range(
				advance(prev.begin(), distance + 1), prev.end()).every_at(
					[&itr, distance](
						const_reference element, size_type const index) {
						if (element != *itr) {
							hryky_log_alert(
								"The result of insert() is invalid. "
								<< (json::writer()
								<< stream::denote("index") << distance + 1 + index
								<< stream::denote("correct") << element
								<< stream::denote("wrong") << *itr));
							return false;
						}
						++itr;
						return true;
					})) {
				hryky_log_alert(
					"failure of " << (json::writer()
					<< stream::denote("count") << count
					<< stream::denote("distance") << distance
					<< stream::denote("prev") << prev
					<< stream::denote("container") << container));
				return false;
			}
			++count;
		}
	}
	// erase by the range.
	{
		size_t count = 0;
		size_t const num = size_dist();
		list_type container;

		scatter(container, num, alternative, ascii_dist);

		while (!container.empty()) {
			list_type const prev(container);
			size_type const distance = static_cast<size_type>(
				size_dist() % container.size());
			size_type const erased_size = static_cast<size_type>(
				size_dist() % (container.size() - distance) + 1);
			list_type::iterator const erased = container.erase(
				advance(container.begin(), distance), 
				advance(container.begin(), distance + erased_size));

			if (distance != ::std::distance(container.begin(), erased)) {
				hryky_log_alert(
					"The result of erase() is invalid. "
					<< (json::writer()
					<< stream::denote("distance") << distance
					<< stream::denote("erased_size") << erased_size
					<< stream::denote("container") << container
					<< stream::denote("count") << count
					));
				return false;
			}

			list_type::iterator itr = container.begin();

			// confirms the first half.
			if (!hryky::range(
				prev.begin(), advance(prev.begin(), distance)).every_at(
					[&itr](
						const_reference element, size_type const index) {
						if (element != *itr) {
							hryky_log_alert(
								"The result of erase() is invalid. "
								<< (json::writer()
								<< stream::denote("index") << index
								<< stream::denote("correct") << element
								<< stream::denote("wrong") << *itr));
							return false;
						}
						++itr;
						return true;
					})) {
				hryky_log_alert(
					"failure of "
					<< (json::writer()
						<< stream::denote("count") << count
						<< stream::denote("distance") << distance
						<< stream::denote("erased_size") << erased_size
						<< stream::denote("prev") << prev
						<< stream::denote("container") << container
						));
				return false;
			}

			// confirms the last half.
			if (!hryky::range(
				advance(prev.begin(), distance + erased_size),
				prev.end()).every_at(
					[&itr, distance](
						const_reference element, size_type const index) {
						if (element != *itr) {
							hryky_log_alert(
								"The result of insert() is invalid. "
								<< (json::writer()
									<< stream::denote("index") << distance + 1 + index
									<< stream::denote("correct") << element
									<< stream::denote("wrong") << *itr
									));
							return false;
						}
						++itr;
						return true;
					})) {
				hryky_log_alert(
					"failure of "
					<< (json::writer()
						<< stream::denote("count") << count
						<< stream::denote("distance") << distance
						<< stream::denote("erased_size") << erased_size
						<< stream::denote("prev") << prev
						<< stream::denote("container") << container
						));
				return false;
			}
			++count;
		}
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
