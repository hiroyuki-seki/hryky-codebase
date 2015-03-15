/*
  @file         test_vector.cpp
  @brief        tests a vector container.
  @author       HRYKY
  @version      $Id: test_vector.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/vector.h"
#include "hryky/random.h"
#include "hryky/memory.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace
{
	// enregisters a test
	class Test : testing::unit::Base
	{
	public :
		typedef testing::unit::Base base_type;
		typedef Test this_type;
		
		Test()
			: testing::unit::Base("vector")
		{
		}
	private :
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		// tests a operation of vector container.
		virtual bool run_impl();
	};
	Test const g_test;

	// verifies the equality between two vectors.
	template < typename ValueT, typename AllocatorT >
	bool operator==(
		Vector<ValueT, AllocatorT> const & lhs,
		Vector<ValueT, AllocatorT> const & rhs);

	// confirms the inequality between two vectors.
	template < typename ValueT, typename AllocatorT >
	bool operator!=(
		Vector<ValueT, AllocatorT> const & lhs,
		Vector<ValueT, AllocatorT> const & rhs);

	size_t const    g_mempool_size = 0x400u * 0x400u * 0x200u;
	uint32_t        g_mempool[g_mempool_size / sizeof(uint32_t)] = { 0u, };
	
}
} // namespace hryky
//------------------------------------------------------------------------------
// global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace
{
/**
  @brief tests a operation of vector container.
 */
bool Test::run_impl()
{
	// initialize logging.
	testing::Log log(*this);
	
	// initializes a random number generator
	testing::Random random;

	log.writer() << "random" << random;

	// initializes a instance for dynamic memory allocation.
	mempool::Adapter<mempool::Arbitrary<uint32_t> > mempool;
	if (!mempool.get()->reset(g_mempool, g_mempool_size)) {
		hryky_log_alert(
			"failed to reset mempool::Arbitrary "
			<< (json::writer()
			<< stream::denote("mempool_size") << g_mempool_size
			));
		return false;
	}

	// initializes a normal distribution
	random::Normal<uint32_t> dist(random.generator(), 0x1000u);
	(dist.mean(0x1000u).min(1u).max(0x10000u));

	typedef allocator::Mempool<int32_t>                            allocator_type;
	typedef Vector<int32_t, allocator_type>                     vector_type;
	typedef Vector<char, allocator_type::rebind<char>::other>   char_vector_type;
	typedef vector_type::size_type                              size_type;
	typedef vector_type::difference_type                        difference_type;
	typedef vector_type::const_reference                        const_reference;
	typedef vector_type::reference                              reference;
	typedef vector_type::iterator                               iterator;
	typedef vector_type::const_iterator                         const_iterator;
	typedef vector_type::reverse_iterator                       reverse_iterator;
	typedef vector_type::const_reverse_iterator                 const_reverse_iterator;

	allocator_type const        allocator(&mempool);
	vector_type                 original(allocator);

	// move semantics
	{
		vector_type moved(allocator);
		moved.push_back(-1);
		moved.push_back(2);

		vector_type const vector(::std::move(moved));

		if (2 != vector.size()) {
			hryky_log_alert(
				"copy constructor with move semantics failed.");
			return false;
		}
	}

	// assignment
	{
		char_vector_type char_vector;
		char_vector = char_vector_type::allocator_type(allocator);
	}

	size_t const vector_size = dist();

	// resizes the vector.
	if (!original.resize(vector_size)) {
		hryky_log_alert(
			"failed to resize vector "
			<< (json::writer()
			<< stream::denote("vector_size") << vector_size));
		return false;
	}

	// fills the original vector with random values.
	{
		iterator       itr = original.begin();
		iterator const end = original.end();

		for (; end != itr; ++itr) {
			reference ref = *itr;
			ref = static_cast<int32_t>(dist() - dist.mean());
		}
	}

	// copies a vector by assignment of the instance.
	{
		vector_type const copied = original;

		// verifies the equality
		if (copied != original) {
			hryky_log_alert(
				"copied vector is different from original one "
				<< (json::writer()
				<< stream::denote("copied") << copied
				<< stream::denote("original") << original
				));
			return false;
		}
	}

	// copies a vector by assignment of each element.
	{
		vector_type copied(allocator);

		copied.resize(original.size());

		const_iterator const   begin = original.begin();
		const_iterator const   end = original.end();

		const_iterator         itr = begin;
		
		for (; end != itr; ++itr) {
			size_type const    index = static_cast<size_type>(itr - begin);
			const_reference    src = *itr;
			reference          dest = copied[index];

			dest = src;
		}

		// verifies the equality
		if (copied != original) {
			hryky_log_alert(
				"copied vector is different from original one "
				<< (json::writer()
				<< stream::denote("copied") << copied
				<< stream::denote("original") << original
				));
			return false;
		}
	}

	// copies a vector by pushing each element at the last of the vector.
	{
		vector_type copied(allocator);

		const_iterator const   begin = original.begin();
		const_iterator const   end = original.end();

		const_iterator         itr = begin;
		
		for (; end != itr; ++itr) {
			copied.push_back(*itr);
		}

		// verifies the equality
		if (copied != original) {
			hryky_log_alert(
				"copied vector is different from original one "
				<< (json::writer()
				<< stream::denote("copied") << copied
				<< stream::denote("original") << original
				));
			return false;
		}
	}

	// copies a vector by insertion of each element at the beginning of the vector.
	{
		vector_type copied(allocator);

		const_reverse_iterator const   begin = original.rbegin();
		const_reverse_iterator const   end = original.rend();

		const_reverse_iterator         itr = begin;
		
		for (; end != itr; ++itr) {
			iterator const inserted_position =
				copied.insert(copied.begin(), *itr);
			
			if (copied.end() == inserted_position) {
				hryky_log_alert(
					"failed to insert element to copied container "
					<< (json::writer()
					<< stream::denote("index") << itr - begin
					<< stream::denote("copied") << copied
					<< stream::denote("original") << original
					));
				return false;
			}
		}

		// verifies the equality
		if (copied != original) {
			hryky_log_alert(
				"copied vector is different from original one "
				<< (json::writer()
				<< stream::denote("copied") << copied
				<< stream::denote("original") << original
				));
			return false;
		}
	}

	// copies a vector by insertion of each element at the beginning of the vector.
	{
		vector_type copied(allocator);

		const_iterator const   begin = original.begin();
		const_iterator const   end = original.end();

		copied.insert(copied.begin(), begin, end);
		
		// verifies the equality
		if (copied != original) {
			hryky_log_alert(
				"copied vector is different from original one "
				<< (json::writer()
				<< stream::denote("copied") << copied
				<< stream::denote("original") << original
				));
			return false;
		}
	}


	return true;
}
/**
  @brief verifies the equality between two vectors.
 */
template < typename ValueT, typename AllocatorT >
bool operator==(
	Vector<ValueT, AllocatorT> const & lhs, Vector<ValueT, AllocatorT> const & rhs)
{
	typedef Vector<ValueT, AllocatorT> vector_type;
	
	vector_type::size_type const    size = lhs.size();

	// verifies the equality of size
	if (size != rhs.size()) {
		hryky_log_alert(
			"the invalid size of vector "
			<< (json::writer()
			<< stream::denote("lhs") << lhs.size()
			<< stream::denote("rhs") << rhs.size()
			));
		return false;
	}

	// verifies the equality of each element
	vector_type::size_type          index = 0;
	for (; size != index; ++index) {
		vector_type::const_reference lhs_element = lhs[index];
		vector_type::const_reference rhs_element = rhs[index];

		if (lhs_element != rhs_element) {
			hryky_log_alert(
				"the invalid element of vector "
				<< (json::writer()
				<< stream::denote("index") << index
				<< stream::denote("lhs") << lhs_element
				<< stream::denote("rhs") << rhs_element
				));
			return false;
		}
	}

	return true;
}
/**
  @brief confirms the inequality between two vectors.
 */
template < typename ValueT, typename AllocatorT >
bool operator!=(
	Vector<ValueT, AllocatorT> const & lhs, Vector<ValueT, AllocatorT> const & rhs)
{
	return !(lhs == rhs);
}
}
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
