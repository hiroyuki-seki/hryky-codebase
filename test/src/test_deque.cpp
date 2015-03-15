/**
  @file     test_deque.cpp
  @brief    tests hryky::Deque.
  @author   HRYKY
  @version  $Id: test_deque.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/deque.h"
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
		
		/// tests hryky::Deque.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "deque";

	template <typename ContainerT, typename AlternativeT>
	void scatter(
		ContainerT & container,
		typename ContainerT::size_type const size,
		AlternativeT & alternative,
		typename ContainerT::value_type value = ContainerT::value_type())
	{
		hryky::repeat(size).foreach([&container, &alternative, value]() {
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
		typename ContainerT::size_type const size,
		AlternativeT & alternative,
		AsciiDistT & ascii_dist)
	{
		hryky::repeat(size).foreach([&container, &ascii_dist, &alternative]() {
			if (0 == alternative()) {
				container.push_back(ascii_dist());
			}
			else {
				container.push_front(ascii_dist());
			}
		});
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
  @brief tests hryky::Deque.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	typedef char                        value_type;
	typedef Deque<value_type>           deque_type;
	typedef deque_type::size_type       size_type;
	typedef deque_type::difference_type difference_type;
	typedef deque_type::reference       reference;
	typedef deque_type::const_reference const_reference;

	// randomizes the size of deque.
	random::Uniform<size_type> size_dist(
		random.generator(), 0x1, 1 << 10);
	log.writer() << "size_dist" << size_dist;

	// randomizes the number of repetition.
	random::Normal<size_t> repeat_dist(
		random.generator(),
		0x10u,      // deviation
		0x100u,     // mean
		0x1u,       // min
		0x1000u);   // max
	log.writer() << "repeat_dist" << repeat_dist;

	// randomizes alternative.
	random::Uniform<uint8_t> alternative(
		random.generator(), 0x0, 0x1);
	log.writer() << "alternative" << alternative;
	
	// randomizes ascii.
	random::Uniform<char> ascii_dist(
		random.generator(), 0x0, 0x7F);
	log.writer() << "ascii" << ascii_dist;
	
	value_type const sample[] = "ABCDEF";
	value_type const * const sample_begin = &sample[0];
	value_type const * const sample_end = &sample[sizeof(sample) - 1];
	size_type const sample_size = static_cast<size_type>(
		::std::distance(sample_begin, sample_end));

	mempool_type const mempool = mempool::global::Registry::instance();

	// default constructor.
	{
		deque_type container;
	}
	// constructor with allocator.
	{
		deque_type container(mempool);
	}
	// constructor with size.
	{
		size_type const size = size_dist();
		deque_type const container(size, mempool);
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
		deque_type::value_type const value = '*';
		size_type const size = size_dist();
		deque_type const container(size, '*', mempool);

		if (size != container.size()) {
			hryky_log_alert(
				"The result of constructor with a value is invalid. "
				<< (json::writer()
				<< stream::denote("size") << size
				<< stream::denote("container") << container));
			return false;
		}

		if (!container.every_at([value](
			const_reference element, size_type const index) {
			if (value != element) {
				hryky_log_alert(
					"The result of constructor with a value is invalid. "
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
	// constructor with the range of values.
	{
		deque_type const container(sample_begin, sample_end, mempool);

		if (sample_size != container.size()) {
			hryky_log_alert(
				"The result of constructor with the range of values is invalid. "
				<< (json::writer()
				<< stream::denote("size") << sample_size
				<< stream::denote("container") << container));
			return false;
		}

		if (!container.every_at([&sample](
			const_reference element, size_type const index) {
			if (sample[index] != element) {
				hryky_log_alert(
					"The result of constructor with the range of values is invalid. "
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
	// copy constructor.
	{
		deque_type const container_0;
		deque_type const container_1(container_0);

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
		deque_type const container(::std::move(deque_type(
			sample_begin, sample_end, mempool)));

		if (container != deque_type(sample_begin, sample_end, mempool)) {
			hryky_log_alert(
				"The result of constructor with rvalue is invalid. "
				<< (json::writer()
				<< stream::denote("container") << container));
			return false;
		}
	}
	// operator=.
	{
		deque_type container_0;
		deque_type const container_1(sample_begin, sample_end, mempool);
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
		deque_type container;
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
		log.writer() << "test_stream_out" << deque_type();
	}
	// swap.
	{
		deque_type const ascending(sample_begin, sample_end, mempool);
		deque_type const descending(
			::std::reverse_iterator<value_type const *>(sample_end),
			::std::reverse_iterator<value_type const *>(sample_begin),
			mempool);
		
		deque_type container_0(ascending);
		deque_type container_1(descending);
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
	// operator[]
	{
		deque_type const container(sample_begin, sample_end);
		if (!hryky::repeat(container.size()).every_at([&sample, &container](
			size_type const index) {
			if (sample[index] != container[index]) {
				hryky_log_alert(
					"The result of operator[] is invalid. "
					<< (json::writer()
					<< stream::denote("index") << index
					<< stream::denote("wrong") << container[index]
					<< stream::denote("correct") << sample[index]
					));
				return false;
			}
			return true;
		})) {
			hryky_log_alert("failure of " << container);
			return false;
		}
	}
	// reverse iterator
	{
		deque_type const container(sample_begin, sample_end);
		size_type const size = container.size();
		if (!hryky::range(container.rbegin(), container.rend()).every_at(
			[&sample, size](const_reference element, size_type const index) {
				if (sample[size - index - 1] != element) {
					hryky_log_alert(
						"The result of reverse operator is invalid. "
						<< (json::writer()
						<< stream::denote("index") << index
						<< stream::denote("wrong") << element
						<< stream::denote("correct") << sample[size - index - 1]
						));
					return false;
				}
				return true;
			})) {
			hryky_log_alert("failure of " << container);
			return false;
		}
	}
	// at()
	{
		deque_type const container(sample_begin, sample_end);
		if (!hryky::repeat(container.size()).every_at([&sample, &container](
			size_type const index) {
			if (sample[index] != container.at(index)) {
				hryky_log_alert(
					"The result of at() is invalid. "
					<< (json::writer()
					<< stream::denote("index") << index
					<< stream::denote("wrong") << container.at(index)
					<< stream::denote("correct") << sample[index]
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
		deque_type const container(sample_begin, sample_end);
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
		deque_type const container(sample_begin, sample_end);
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
		deque_type container(sample_begin, sample_end);
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

		typedef deque_type::const_iterator const_iterator;

		const_iterator const begin = container.begin();
		const_iterator const last_half_begin =
			begin + static_cast<difference_type>(
				(::std::min)(sample_size, container.size()));

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

		const_iterator const end = container.end();
		value_type const value = value_type();

		// confirms whether the values at last half are default.
		if (!hryky::range(last_half_begin, end).every_at([value](
			const_reference element, size_type const index) {
			if (value != element) {
				hryky_log_alert(
					"The result of resize() is invalid "
					<< (json::writer()
					<< stream::denote("index") << index
					<< stream::denote("correct") << static_cast<uint32_t>(value)
					<< stream::denote("wrong") << static_cast<uint32_t>(element)));
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
		deque_type container(sample_begin, sample_end);
		container.resize(sample_size >> 1);

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
					<< stream::denote("wrong") << element));
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
		deque_type container;
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
		deque_type container;
		size_type const size = size_dist();
		deque_type::value_type const value = '*';
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
		deque_type container;
		size_type const size = size_dist();

		hryky::repeat(size).foreach_at([&container, &sample, sample_size](
			size_type const index) {
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
		deque_type container;
		size_type const size = size_dist();

		hryky::repeat(size).foreach_at([&container, &sample, sample_size](
			size_type const index) {
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
		deque_type container;
		size_type const size = size_dist();

		hryky::repeat(size).foreach_at([&container, &sample, sample_size](
			size_type const index) {
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
		deque_type container;
		size_type const size = size_dist();

		hryky::repeat(size).foreach_at([&container, &sample, sample_size](
			size_type const index) {
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
		deque_type container;
		size_type const size = size_dist();
		deque_type::value_type const value = '*';

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
		deque_type container;
		size_type const size = size_dist();

		scatter(container, size, alternative);

		if (!hryky::repeat(size).every_at([&container](
			size_type const index) {
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
		deque_type container;
		size_type const size = size_dist();

		scatter(container, size, alternative);

		if (!hryky::repeat(size).every_at([&container](
			size_type const index) {
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
		deque_type container;
		size_type const size = size_dist();

		scatter(container, size, alternative);

		if (!hryky::repeat(size).every_at([&container, &alternative](
			size_type const index) {
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
		deque_type container;

		if (!hryky::repeat(repeat_dist()).every_at(
			[&container, &size_dist, &ascii_dist](
				size_type const count) {
				value_type const value = ascii_dist();

				deque_type const prev(container);
				size_type const distance =
					size_dist() % (container.size() + 1);
				deque_type::iterator const inserted = container.insert(
					container.begin() + static_cast<difference_type>(distance),
					value);

				if (static_cast<difference_type>(distance)
					!= ::std::distance(container.begin(), inserted)) {
					hryky_log_alert(
						"The result of insert() is invalid. "
						<< (json::writer()
						<< stream::denote("distance") << distance
						<< stream::denote("container") << container));
					return false;
				}

				deque_type::iterator itr = container.begin();

				// confirms the first half.
				if (!hryky::range(
					prev.begin(),
					prev.begin() + static_cast<difference_type>(distance)).every_at(
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
						<< stream::denote("count") << count
						<< stream::denote("distance") << distance
						<< stream::denote("prev") << prev
						<< stream::denote("container") << container));
					return false;
				}

				// confirms the insertion
				if (value != *itr) {
					hryky_log_alert(
						"The result of insert() is invalid. "
						<< (json::writer()
						<< stream::denote("dinstance") << distance
						<< stream::denote("lhs") << value
						<< stream::denote("rhs") << *itr
						<< stream::denote("prev") << prev
						<< stream::denote("container") << container));
					return false;
				}
				++itr;

				// confirms the last half.
				if (!hryky::range(
					prev.begin() + static_cast<difference_type>(distance),
					prev.end()).every_at(
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
				return true;
			})) {
			hryky_log_alert("failure of " << container);
		}
	}
	// inserts a plurality of single values by the range
	{
		deque_type container;

		if (!hryky::repeat(repeat_dist()).every_at(
			[&container, &ascii_dist, &size_dist](
				size_type const count) {
				value_type const value = ascii_dist();
				size_type const insertion_size = (size_dist() >> 2) + 1;
				deque_type const prev(container);
				size_type const distance =
					size_dist() % (container.size() + 1);
				deque_type::iterator const inserted = container.insert(
					container.begin() + static_cast<difference_type>(distance),
					insertion_size,
					value);

				if (static_cast<difference_type>(distance)
					!= ::std::distance(container.begin(), inserted)) {
					hryky_log_alert(
						"The result of insert() is invalid. "
						<< (json::writer()
						<< stream::denote("distance") << distance
						<< stream::denote("container") << container));
					return false;
				}

				deque_type::iterator itr = container.begin();

				// confirms the first half.
				if (!hryky::range(
					prev.begin(),
					prev.begin() + static_cast<difference_type>(distance)).every_at(
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
						<< stream::denote("count") << count
						<< stream::denote("distance") << distance
						<< stream::denote("prev") << prev
						<< stream::denote("container") << container));
					return false;
				}

				// confirms the insertion
				if (!hryky::repeat(insertion_size).every_at(
					[&itr, value, distance](
						size_type const index) {
						if (value != *itr) {
							hryky_log_alert(
								"The result of insert() is invalid. "
								<< (json::writer()
								<< stream::denote("index") << distance + index
								<< stream::denote("correct") << value
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

				size_type const last_half_offset = distance + insertion_size;

				// confirms the last half.
				if (!hryky::range(
					prev.begin() + static_cast<difference_type>(distance),
					prev.end()).every_at(
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
	// inserts multiple values by the range
	{
		deque_type container;

		if (!hryky::repeat(repeat_dist()).every_at(
			[&container, &ascii_dist, &size_dist](
				size_type const count) {
				deque_type insertion;
				{
					size_type const size = (size_dist() >> 2) + 1;
					hryky::repeat(size).foreach([&insertion, &ascii_dist]() {
						insertion.push_back(ascii_dist());
					});
				}

				deque_type const prev(container);
				size_type const distance =
					size_dist() % (container.size() + 1);
				deque_type::iterator const inserted = container.insert(
					container.begin() + static_cast<difference_type>(distance),
					insertion.begin(),
					insertion.end());

				if (static_cast<difference_type>(distance)
					!= ::std::distance(container.begin(), inserted)) {
					hryky_log_alert(
						"The result of insert() is invalid. "
						<< (json::writer()
						<< stream::denote("distance") << distance
						<< stream::denote("container") << container));
					return false;
				}

				deque_type::iterator itr = container.begin();

				// confirms the first half.
				if (!hryky::range(
					prev.begin(),
					prev.begin() + static_cast<difference_type>(distance)).every_at(
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

				size_type const last_half_offset = distance + insertion.size();

				// confirms the last half.
				if (!hryky::range(
					prev.begin() + static_cast<difference_type>(distance),
					prev.end()).every_at(
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
		
		size_type const num = size_dist();
		deque_type container;

		scatter(container, num, alternative, ascii_dist);

		size_type count = 0;

		while (!container.empty()) {
			log.writer() << stream::denote("prev") << container;
			
			deque_type const prev(container);
			size_type const distance =
				size_dist() % container.size();
			deque_type::iterator const erased = container.erase(
				container.begin() + static_cast<difference_type>(distance));

			if (static_cast<difference_type>(distance)
				!= ::std::distance(container.begin(), erased)) {
				hryky_log_alert(
					"The result of erase() is invalid. "
					<< (json::writer()
					<< stream::denote("distance") << distance
					<< stream::denote("prev") << prev
					<< stream::denote("container") << container));
				return false;
			}

			deque_type::iterator itr = container.begin();

			// confirms the first half.
			if (!hryky::range(
				prev.begin(),
				prev.begin() + static_cast<difference_type>(distance)).every_at(
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
				prev.begin() + static_cast<difference_type>(distance) + 1,
				prev.end()).every_at(
					[&itr, distance](
						const_reference element, size_type const index) {
						if (element != *itr) {
							hryky_log_alert(
								"The result of insert() is invalid. "
								<< (json::writer()
								<< stream::denote("distance") << distance
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
		size_type const num = size_dist();
		deque_type container;

		scatter(container, num, alternative, ascii_dist);

		size_type erase_count = 0;

		while (!container.empty()) {
			log.writer() << stream::denote("prev") << container;
			
			deque_type const prev(container);
			size_type const distance =
				size_dist() % container.size();
			size_type const erased_size =
				size_dist() % (container.size() - distance) + 1;
			deque_type::iterator const erased = container.erase(
				container.begin() + static_cast<difference_type>(distance), 
				container.begin()
				+ static_cast<difference_type>(distance + erased_size));

			if (static_cast<difference_type>(distance)
				!= ::std::distance(container.begin(), erased)) {
				hryky_log_alert(
					"The result of erase() is invalid. "
					<< (json::writer()
					<< stream::denote("distance") << distance
					<< stream::denote("erased_size") << erased_size
					<< stream::denote("container") << container
					<< stream::denote("erase_count") << erase_count
					));
				return false;
			}

			deque_type::iterator itr = container.begin();

			// confirms the first half.
			if (!hryky::range(
				prev.begin(),
				prev.begin() + static_cast<difference_type>(distance)).every_at(
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
					<< stream::denote("erase_count") << erase_count
					<< stream::denote("erased_size") << erased_size
					<< stream::denote("distance") << distance
					<< stream::denote("prev") << prev
					<< stream::denote("container") << container));
				return false;
			}

			// confirms the last half.
			if (!hryky::range(
				prev.begin() + static_cast<difference_type>(distance + erased_size),
				prev.end()).every_at(
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
					<< stream::denote("erase_count") << erase_count
					<< stream::denote("erased_size") << erased_size
					<< stream::denote("distance") << distance
					<< stream::denote("prev") << prev
					<< stream::denote("container") << container));
				return false;
			}
			++erase_count;
		}
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
