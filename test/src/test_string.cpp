/*
  @file         test_string.cpp
  @brief        tests a string container.
  @author       HRYKY
  @version      $Id: test_string.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/debug/debug_source.h"
#include "hryky/string.h"
#include "hryky/random.h"
#include "hryky/memory.h"
#include "hryky/vector.h"
#include "hryky/foreach.h"
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
	// enregisters a test
	class Test : testing::unit::Base
	{
	public :
		typedef testing::unit::Base base_type;
		typedef Test this_type;
		
		// constructor.
		Test();
		
	private :
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		// tests a operation of string container.
		virtual bool run_impl();

		/// tests strings of the specified type.
		template <typename StringT>
		bool test_string(testing::Log & log, testing::Random & random);
	};
	Test const g_test;

	/// confirms the result of the manipulation is valid.
	template < typename LhsT, typename RhsT >  
	bool verify(LhsT const & lhs, RhsT const & rhs, size_t offset = 0);

	char const *    g_testname = "string";
	size_t const    g_mempool_size = 0x400 * 0x400 * 0x200;
	uint32_t        g_mempool[g_mempool_size / sizeof(uint32_t)] = { 0, };
	
} // namespace "anonymous"
} // namespace test
} // namespace hryky
//------------------------------------------------------------------------------
// member function for Test
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
  @brief tests a operation of string container.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;

	// random.seed(1347867891);

	log.writer() << "random" << random;

	return Unroll<100>::every([this, &log, &random]() {
		return this->test_string<String<> >(log, random);
	});
}
/**
  @brief tests strings of the specified type.
 */
template <typename StringT>
bool Test::test_string(testing::Log &, testing::Random & random)
{
	// initializes memory pool
	mempool::Adapter<mempool::Arbitrary<> > mempool;
	if (!mempool.get()->reset(g_mempool, g_mempool_size)) {
		hryky_log_alert(
			"failed to reset mempool::Arbitrary "
			<< (json::writer()
			<< stream::denote("mempool_size") << g_mempool_size));
		return false;
	}

	typedef StringT string_type;

	// invokes default constructor.
	string_type const construct_default;

	// invokes constructor with allocator.
	string_type const construct_with_allocator(&mempool);

	typedef string_type::value_type         value_type;
	typedef string_type::size_type          size_type;
	typedef string_type::difference_type    difference_type;
	size_type const npos = string_type::npos;

	size_type const string_size = random::Normal<uint32_t>(
		random.generator(), 0x1000)
		.mean(0x1000).min(0x1).max(0x10000)();

	typedef Vector<value_type> buffer_type;

	// allocates buffer
	buffer_type buffer(&mempool);
	if (!buffer.resize(string_size)) {
		hryky_log_alert(
			"failed to allocate buffer "
			<< (json::writer()
			<< stream::denote("string_size") << string_size));
		return false;
	}

	// assigns random characters to the buffer.
	{
		random::Uniform<uint8_t> characters(
			random.generator(), 0x1u, 0xFFu);

		buffer.foreach([&characters](buffer_type::reference element) {
			element = static_cast<buffer_type::value_type>(characters());
		});
	}

	// constructs with characters.
	{
		string_type dest(&buffer[0], buffer.size(), &mempool);

		// compares the entities of string.
		if (!verify(buffer, dest)) {
			hryky_log_alert("failed");
			return false;
		}
	}

	// copy constructor
	{
		string_type src(&buffer[0], buffer.size(), &mempool);
		string_type dest(src);

		// compares the entities of string.
		if (!verify(buffer, dest)) {
			hryky_log_alert("failed");
			return false;
		}
	}

	// appends characters one by one
	{
		string_type dest(&mempool);

		buffer.foreach([&dest](buffer_type::const_reference element) {
			dest += element;
		});

		// compares the entities of string.
		if (!verify(buffer, dest)) {
			hryky_log_alert("failed");
			return false;
		}
	}

	// appends characters one by one.
	{
		string_type dest(&mempool);

		buffer.foreach([&dest](buffer_type::const_reference element) {
			dest.push_back(element);
		});

		// compares the entities of string.
		if (!verify(buffer, dest)) {
			hryky_log_alert("failed");
			return false;
		}
	}

	// appends characters at a time
	{
		string_type dest(&mempool);
		string_type src(&buffer[0], buffer.size(), &mempool);

		dest += src;

		// compares the entities of string.
		if (!verify(buffer, dest)) {
			hryky_log_alert("failed");
			return false;
		}
	}

	// appends string at a time
	{
		string_type dest(&mempool);

		dest.append(&buffer[0], buffer.size());

		// compares the entities of string.
		if (!verify(buffer, dest)) {
			hryky_log_alert("failed");
			return false;
		}
	}

	// appends substring
	{
		size_type const offset = random::Uniform<size_type>(
			random.generator(), 0x0u, string_size)();

		string_type dest(&mempool);
		string_type src(&buffer[0], buffer.size(), &mempool);

		dest.append(src, offset, src.size() - offset);

		// compares the entities of string.
		if (!verify(buffer, dest, offset)) {
			hryky_log_alert("failed");
			return false;
		}
	}

	// appends substring specified by the range between two iterator.
	{
		size_type const offset = random::Uniform<size_type>(
			random.generator(), 0x0u, string_size)();

		string_type dest(&mempool);

		dest.append(
			buffer.begin() + static_cast<difference_type>(offset),
			buffer.end());

		// compares the entities of string.
		if (!verify(buffer, dest, offset)) {
			hryky_log_alert("failed");
			return false;
		}
	}

	// assigns new content from the other string.
	{
		string_type dest(&mempool);
		string_type src(&buffer[0], buffer.size(), &mempool);

		dest.assign(src);

		// compares the entities of string.
		if (!verify(buffer, dest, 0)) {
			hryky_log_alert("failed");
			return false;
		}
	}

	// assigns the substring of the other string.
	{
		size_type const offset = random::Uniform<size_type>(
			random.generator(), 0x0u, string_size)();

		string_type dest(&mempool);
		string_type src(&buffer[0], buffer.size(), &mempool);

		dest.assign(src, offset, src.size() - offset);

		// compares the entities of string.
		if (!verify(buffer, dest, offset)) {
			hryky_log_alert("failed");
			return false;
		}
	}

	// assigns an array of characters.
	{
		size_type const size = random::Uniform<size_type>(
			random.generator(), 0x0u, string_size)();

		string_type dest(&mempool);

		dest.assign(&buffer[0], size);

		// compares the entities of string.
		if (!verify(buffer, dest, 0)) {
			hryky_log_alert("failed");
			return false;
		}
	}

	// assigns substring specified by the range between two iterator.
	{
		size_type const offset = random::Uniform<size_type>(
			random.generator(), 0x0u, string_size)();

		string_type dest(&mempool);

		dest.assign(
			buffer.begin() + static_cast<difference_type>(offset),
			buffer.end());

		// compares the entities of string.
		if (!verify(buffer, dest, offset)) {
			hryky_log_alert("failed");
			return false;
		}
	}

	// inserts the other string
	{
		size_type const offset = random::Uniform<size_type>(
			random.generator(), 0x0u, string_size)();

		string_type src(&buffer[0], buffer.size(), &mempool);
		string_type dest(src);

		dest.insert(offset, src);

		if ((buffer.size() << 1) != dest.size()
			 || string_type::terminator() != dest.c_str()[dest.size()])
		{
			hryky_log_alert(
				"invalid string "
				<< (json::writer()));
			return false;
		}

		if (0 == offset || string_size == offset) {
			if (0 != ::std::memcmp(&buffer[0], &dest[0], string_size)) {
				hryky_log_alert(
					"The first half of the result is invalid.");
				return false;
			}

			if (0 != ::std::memcmp(
				&buffer[0], &dest[string_size], string_size)) {
				hryky_log_alert(
					"The last half of the result is invalid.");
				return false;
			}
		}
		else {
			if (0 != ::std::memcmp(&buffer[0], &dest[0], offset)) {
				hryky_log_alert(
					"The first part of the result is invalid");
				return false;
			}

			if (0 != ::std::memcmp(&buffer[0], &dest[offset], string_size)) {
				hryky_log_alert(
					"The middle part of the result is invalid");
				return false;
			}

			if (0 != ::std::memcmp(
				&buffer[offset],
				&dest[offset + string_size],
				string_size - offset)) {
				hryky_log_alert(
					"The last part of the result is invalid.");
				return false;
			}
		}
	}

	// inserts the other string specified by the range between two iterator.
	{
		size_type const offset = random::Uniform<size_type>(
			random.generator(), 0x0u, string_size)();

		string_type src(&buffer[0], buffer.size(), &mempool);
		string_type dest(src);

		dest.insert(
			dest.begin() + static_cast<difference_type>(offset),
			src.begin(),
			src.end());

		if ((buffer.size() << 1) != dest.size()) {
			hryky_log_alert("The size of the result is invalid");
			return false;
		}

		if (string_type::terminator() != dest.c_str()[dest.size()]) {
			hryky_log_alert("failed to get NULL");
			return false;
		}

		if (0 == offset || string_size == offset) {
			if (0 != ::std::memcmp(&buffer[0], &dest[0], string_size)) {
				hryky_log_alert("The first half of the result is invalid.");
				return false;
			}

			if (0 != ::std::memcmp(
				&buffer[0], &dest[string_size], string_size)) {
				hryky_log_alert("The last half of the result is invalid.");
				return false;
			}
		}
		else {
			if (0 != ::std::memcmp(&buffer[0], &dest[0], offset)) {
				hryky_log_alert("The first part of the result is invalid.");
				return false;
			}

			if (0 != ::std::memcmp(&buffer[0], &dest[offset], string_size)) {
				hryky_log_alert("The middle part of the result is invalid.");
				return false;
			}

			if (0 != ::std::memcmp(
				&buffer[offset],
				&dest[offset + string_size],
				string_size - offset)) {
				hryky_log_alert("The last part of the result is invlaid.");
				return false;
			}
		}
	}

	// inserts characters one by one.
	{
		size_type const offset = random::Uniform<size_type>(
			random.generator(), 0x0u, string_size)();

		string_type src(&buffer[0], buffer.size(), &mempool);
		string_type dest(src);

		string_type::const_reverse_iterator const src_begin    = src.rbegin();
		string_type::const_reverse_iterator const src_end      = src.rend();
		string_type::const_reverse_iterator src_itr            = src_begin;

		for (; src_end != src_itr; ++src_itr) {
			dest.insert(
				dest.begin() + static_cast<difference_type>(offset),
				*src_itr);
		}

		if ((buffer.size() << 1) != dest.size()) {
			hryky_log_alert("The size of the result is invalid.");
			return false;
		}

		if (string_type::terminator() != dest.c_str()[dest.size()]) {
			hryky_log_alert("c_str() doesn't include NULL at the end.");
			return false;
		}

		if (0 == offset || string_size == offset) {
			if (0 != ::std::memcmp(&buffer[0], &dest[0], string_size)) {
				hryky_log_alert("The first half of the result is invalid.");
				return false;
			}

			if (0 != ::std::memcmp(
				&buffer[0], &dest[string_size], string_size)) {
				hryky_log_alert("The last half of the result is invalid.");
				return false;
			}
		}
		else {
			if (0 != ::std::memcmp(&buffer[0], &dest[0], offset)) {
				hryky_log_alert("The first part of the result is invalid.");
				return false;
			}

			if (0 != ::std::memcmp(&buffer[0], &dest[offset], string_size)) {
				hryky_log_alert("The middle part of the result is invalid.");
				return false;
			}

			if (0 != ::std::memcmp(
				&buffer[offset],
				&dest[offset + string_size],
				string_size - offset)) {
				hryky_log_alert("The last part of the result is invalid.");
				return false;
			}
		}
	}

	// removes characters one by one.
	{
		string_type dest(&buffer[0], buffer.size(), &mempool);

		size_type index = 0;
		for (; string_size != index; ++index) {
			size_type const offset = random::Uniform<size_type>(
				random.generator(), 0x0u, dest.size() - 1)();

			dest.erase(
				dest.begin() + static_cast<difference_type>(offset));
		}

		if (0u != dest.size()) {
			hryky_log_alert(
				"invalid string "
				<< (json::writer()));
			return false;
		}
	}

	// removes characters specified by the range between two iterators.
	{
		string_type dest(&buffer[0], buffer.size(), &mempool);

		while (!dest.empty()) {
			size_type const first = random::Uniform<size_type>(
				random.generator(), 0x0u, dest.size() - 1)();
			size_type const last = random::Uniform<size_type>(
				random.generator(), first + 1, dest.size())();

			dest.erase(
				dest.begin() + static_cast<difference_type>(first),
				dest.begin() + static_cast<difference_type>(last));
		}
	}

	// replaces characters specified by the array of characters.
	{
		string_type dest(&buffer[0], buffer.size(), &mempool);

		size_type const dest_pos = random::Uniform<size_type>(
			random.generator(), 0x0u, dest.size())();

		size_type const dest_size = random::Uniform<size_type>(
			random.generator(), 0x0u, dest.size() - dest_pos)();

		size_type const src_pos = random::Uniform<size_type>(
			random.generator(), 0x0u, buffer.size())();

		size_type const src_size = random::Uniform<size_type>(
			random.generator(), 0x0u, buffer.size() - src_pos)();

		dest.replace(dest_pos, dest_size, &buffer[src_pos], src_size);

		if (dest.size() != string_size + src_size - dest_size) {
			hryky_log_alert("The size of the result is invalid.");
			return false;
		}

		if (0 != dest_pos
			 && 0 != ::std::memcmp(&buffer[0], &dest[0], dest_pos)) {
			hryky_log_alert("The first part of the result is invalid.");
			return false;
		}

		if (0 != src_size
			 && 0 != ::std::memcmp(&buffer[src_pos], &dest[dest_pos], src_size)) {
			hryky_log_alert("The middle part of the result is invalid.");
			return false;
		}

		if (0 != string_size - dest_pos - dest_size
			 && 0 != ::std::memcmp(
				 &buffer[dest_pos + dest_size],
				 &dest[dest_pos + src_size],
				 string_size - dest_pos - dest_size)) {
			hryky_log_alert("The last part of the result is invalid.");
			return false;
		}

		if (string_type::terminator() != dest.c_str()[dest.size()]) {
			hryky_log_alert(
				"The result of c_str() doesn't include NULL at the end.");
			return false;
		}
	}

	// replaces characters specified by the range between two iterators.
	{
		string_type dest(&buffer[0], buffer.size(), &mempool);

		size_type const dest_pos = random::Uniform<size_type>(
			random.generator(), 0x0u, dest.size())();

		size_type const dest_size = random::Uniform<size_type>(
			random.generator(), 0x0u, dest.size() - dest_pos)();

		size_type const src_pos = random::Uniform<size_type>(
			random.generator(), 0x0u, buffer.size())();

		size_type const src_size = random::Uniform<size_type>(
			random.generator(), 0x0u, buffer.size() - src_pos)();

		dest.replace(
			dest.begin() + static_cast<difference_type>(dest_pos),
			dest.begin() + static_cast<difference_type>(dest_pos + dest_size),
			buffer.begin() + static_cast<difference_type>(src_pos),
			buffer.begin() + static_cast<difference_type>(src_pos + src_size));

		if (dest.size() != string_size + src_size - dest_size) {
			hryky_log_alert("The size of the result is invalid.");
			return false;
		}

		if (0 != dest_pos
			 && 0 != ::std::memcmp(&buffer[0], &dest[0], dest_pos)) {
			hryky_log_alert("The first part of the result is invalid.");
			return false;
		}

		if (0 != src_size
			 && 0 != ::std::memcmp(&buffer[src_pos], &dest[dest_pos], src_size)) {
			hryky_log_alert("The middle part of the result is invalid.");
			return false;
		}

		if (0 != string_size - dest_pos - dest_size
			 && 0 != ::std::memcmp(
				 &buffer[dest_pos + dest_size],
				 &dest[dest_pos + src_size],
				 string_size - dest_pos - dest_size)) {
			hryky_log_alert("The last part of the result is invalid.");
			return false;
		}

		if (string_type::terminator() != dest.c_str()[dest.size()]) {
			hryky_log_alert(
				"The result of c_str() doesn't include NULL at the end.");
			return false;
		}
	}

	// finds substring
	{
		string_type const src(&buffer[0], buffer.size(), &mempool);

		size_type const target_begin = random::Uniform<size_type>(
			random.generator(), 0x0u, src.size())();

		size_type const target_end = random::Uniform<size_type>(
			random.generator(), target_begin, src.size())();

		string_type const target(
			src.begin() + static_cast<difference_type>(target_begin),
			src.begin() + static_cast<difference_type>(target_end),
			&mempool);

		size_type const position = random::Uniform<size_type>(
			random.generator(), 0x0u, src.size())();

		size_type const found = src.find(target, position);

		size_type const target_size = target_end - target_begin;

		auto dump = auto_call([
			&src,
			target_begin,
			target_end,
			&target,
			position,
			found]() {
				hryky_log_alert((
					json::writer()
					<< hryky_stream_denote(src)
					<< hryky_stream_denote(target_begin)
					<< hryky_stream_denote(target_end)
					<< hryky_stream_denote(target)
					<< hryky_stream_denote(position)
					<< hryky_stream_denote(found)));
			});

		if (0u == target_size) {
			if (npos != found) {
				hryky_log_alert("npos if the target is empty");
				return false;
			}
		}
		else if (src.size() < target_size + position) {
			if (npos != found) {
				hryky_log_alert(
					"npos if the target exceeds the end of src");
				return false;
			}
		}
		else {
			if (npos == found) {
				if (target_begin >= position) {
					hryky_log_alert(
						"The target has to be found.");
					return false;
				}
			}
			else if (string_type(
				src.begin() + static_cast<difference_type>(found),
				src.begin() + static_cast<difference_type>(found + target_size),
				&mempool) != target) {
				hryky_log_alert(
					"The found substring has to match the target.");
				return false;
			}
		}

		dump.disable();
	}

	// finds a character forward.
	{
		string_type const src(&buffer[0], buffer.size(), &mempool);

		size_type const target_pos = random::Uniform<size_type>(
			random.generator(), 0x0u, src.size())();

		value_type const target =
			src.size() > target_pos ? src[target_pos] : value_type();

		size_type const position = random::Uniform<size_type>(
			random.generator(), 0x0u, src.size())();

		size_type const found = src.find(target, position);

		size_type confirm_found = npos;
		
		auto dump = auto_call([&src, target, position, found, &confirm_found]() {
			hryky_log_alert((
				json::writer()
				<< hryky_stream_denote(src)
				<< hryky_stream_denote(target)
				<< hryky_stream_denote(position)
				<< hryky_stream_denote(found)
				<< hryky_stream_denote(confirm_found)
				));
		});

		if (npos != found && target != src[found]) {
			hryky_log_alert("found position is invalid");
			return false;
		}

		auto src_range = range(
			src.begin() + static_cast<difference_type>(position),
			src.end());

		src_range.some_at([target, &confirm_found](
			value_type const value, size_type const at) {
			if (value == target) {
				confirm_found = at;
				return true;
			}
			return false;
		});
		if (npos == found) {
			if (npos != confirm_found) {
				hryky_log_alert("target is not found.");
				return false;
			}
		}
		else if (position + confirm_found != found) {
			hryky_log_alert("found position is not found.");
			return false;
		}

		dump.disable();
	}
	
	// finds a character backward.
	{
		string_type const src(&buffer[0], buffer.size(), &mempool);

		size_type const target_pos = random::Uniform<size_type>(
			random.generator(), 0x0u, src.size())();

		value_type const target =
			src.size() > target_pos ? src[target_pos] : value_type();

		size_type const position = random::Uniform<size_type>(
			random.generator(), 0x0u, src.size())();

		size_type const found = src.rfind(target, position);

		size_type confirm_found = npos;
		
		auto dump = auto_call([&src, target, position, found, &confirm_found]() {
			hryky_log_alert((
				json::writer()
				<< hryky_stream_denote(src)
				<< hryky_stream_denote(target)
				<< hryky_stream_denote(position)
				<< hryky_stream_denote(found)
				<< hryky_stream_denote(confirm_found)
				));
		});

		if (npos != found && target != src[found]) {
			hryky_log_alert("found position is invalid");
			return false;
		}

		size_type const offset
			= src.size() > position ? src.size() - position - 1 : 0;

		auto src_range = range(
			src.rbegin() + static_cast<difference_type>(offset),
			src.rend());

		src_range.some_at([target, &confirm_found](
			value_type const value, size_type const at) {
			if (value == target) {
				confirm_found = at;
				return true;
			}
			return false;
		});

		if (npos == found) {
			if (npos != confirm_found) {
				hryky_log_alert("target is not found.");
				return false;
			}
		}
		else if (src_range.size() - confirm_found - 1 != found) {
			hryky_log_alert("found position is not found.");
			return false;
		}

		dump.disable();
	}
	
	

	return true;
}
/**
  @brief confirms the result of the manipulation is valid.
 */
template < typename LhsT, typename RhsT >
bool verify(LhsT const & lhs, RhsT const & rhs, size_t const offset)
{
	if (lhs.size() < (rhs.size() + offset)) {
		hryky_log_alert(
			"the size of the result is invalid "
			<< (json::writer()
			<< stream::denote("lhs") << lhs
			<< stream::denote("rhs") << rhs
			<< stream::denote("offset") << offset));
		return false;
	}

	if (offset != lhs.size()
		&& 0 != ::std::memcmp(
			&lhs[offset], &rhs[0], rhs.size())) {
		hryky_log_alert(
			"the content of the result is invalid "
			<< (json::writer()
			<< stream::denote("lhs") << lhs
			<< stream::denote("rhs") << rhs
			<< stream::denote("offset") << offset
			));
		return false;
	}

	if (String<>::terminator() != rhs.c_str()[rhs.size()]) {
		hryky_log_alert(
			"There is not NULL at the end of the result "
			<< (json::writer()
			<< stream::denote("lhs") << lhs
			<< stream::denote("rhs") << rhs
			<< stream::denote("offset") << offset
			));
		return false;
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
