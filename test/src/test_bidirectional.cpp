/**
  @file         test_bidirectional.cpp
  @brief        tests hryky::Bidirectional.
  @author       HRYKY
  @version      $Id: test_bidirectional.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/bidirectional.h"
#include "hryky/intrusive_ptr.h"
#include "hryky/intrusive_ptr_trait.h"
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
namespace bidirectional
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
		
		/// tests hryky::Bidirectional.
		virtual bool run_impl();

		/// tests to connect three nodes.
		template <typename PointerT>
		bool connect(PointerT const node_a, PointerT const node_b, PointerT const node_c);

	};
	Test const g_test;

	char const * const g_testname = "bidirectional";

	struct Node :
		public Bidirectional<Node *>
	{
		Node()
		{
			hryky_log_debug("in Node::Node.");
		}
		~Node()
		{
			hryky_log_debug("in Node::~Node.");
		}
	};

	struct SharedPtrNode :
		public Bidirectional<SharedPtr<SharedPtrNode> >
	{
		SharedPtrNode()
		{
			hryky_log_debug("in SharedPtrNode::SharedPtrNode.");
		}
		~SharedPtrNode()
		{
			hryky_log_debug("in SharedPtrNode::~SharedPtrNode.");
		}
	};

	struct IntrusivePtrNode :
		public IntrusivePtrTrait<>,
		public Bidirectional<IntrusivePtr<IntrusivePtrNode> >
	{
		IntrusivePtrNode()
		{
			hryky_log_debug("in IntrusivePtrNode::IntrusivePtrNode.");
		}

		~IntrusivePtrNode()
		{
			hryky_log_debug("in IntrusivePtrNode::~IntrusivePtrNode.");
		}
	};

} // namespace "anonymous"
} // namespace bidirectional
} // namespace test
} // namespace hryky
namespace hryky
{
namespace test
{
namespace bidirectional
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
  @brief tests hryky::Bidirectional.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	{
		Node node_a;
		Node node_b;
		Node node_c;

		if (!this->connect(&node_a, &node_b, &node_c)) {
			hryky_log_alert(
				"failed to test connection of nodes using raw pointer.");
			return false;
		}
	}

	{
		typedef SharedPtr<SharedPtrNode> pointer;
		allocator::Mempool<SharedPtrNode> allocator;
		pointer node_a(allocator::instantiate_by(allocator), allocator);
		pointer node_b(allocator::instantiate_by(allocator), allocator);
		pointer node_c(allocator::instantiate_by(allocator), allocator);

		if (!this->connect(node_a, node_b, node_c)) {
			hryky_log_alert(
				"failed to test connection of nodes using shared_ptr.");
			return false;
		}
	}

	{
		typedef IntrusivePtr<IntrusivePtrNode> pointer;
		allocator::Mempool<IntrusivePtrNode> allocator;
		pointer node_a(allocator::instantiate_by(allocator));
		pointer node_b(allocator::instantiate_by(allocator));
		pointer node_c(allocator::instantiate_by(allocator));

		if (!this->connect(node_a, node_b, node_c)) {
			hryky_log_alert(
				"failed to test connection of nodes using intrusive_ptr.");
			return false;
		}
	}

	return true;
}
/**
  @brief tests to connect three nodes.
 */
template <typename PointerT>
bool Test::connect(
	PointerT const node_a, PointerT const node_b, PointerT const node_c)
{
	hryky::insert_before(node_a, node_c);
	if (PointerT() != node_a->prev() ||
		node_c != node_a->next() ||
		node_a != node_c->prev() ||
		PointerT() != node_c->next()) {
		hryky_log_alert(
			"The expected result is A <=> C. "
			<< (json::writer()
			<< stream::denote("node_a") << *node_a
			<< stream::denote("node_b") << *node_b
			<< stream::denote("node_c") << *node_c));
		return false;
	}
	hryky::insert_before(node_b, node_c);
	if (PointerT() != node_a->prev() ||
		node_b != node_a->next() ||
		node_a != node_b->prev() ||
		node_c != node_b->next() ||
		node_b != node_c->prev() ||
		PointerT() != node_c->next()) {
		hryky_log_alert(
			"The expected result is A <=> B <=> C. "
			<< (json::writer()
			<< stream::denote("node_a") << *node_a
			<< stream::denote("node_b") << *node_b
			<< stream::denote("node_c") << *node_c));
		return false;
	}

	node_a->secede();
	if (PointerT() != node_a->prev() ||
		PointerT() != node_a->next() ||
		PointerT() != node_b->prev() ||
		node_c != node_b->next() ||
		node_b != node_c->prev() ||
		PointerT() != node_c->next()) {
		hryky_log_alert(
			"The expected result is B <=> C. "
			<< (json::writer()
			<< stream::denote("node_a") << *node_a
			<< stream::denote("node_b") << *node_b
			<< stream::denote("node_c") << *node_c));
		return false;
	}
	
	hryky::insert_after(node_a, node_c);
	if (PointerT() != node_b->prev() ||
		node_c != node_b->next() ||
		node_b != node_c->prev() ||
		node_a != node_c->next() ||
		node_c != node_a->prev() ||
		PointerT() != node_a->next()) {
		hryky_log_alert(
			"The expected result is B <=> C <=> A. "
			<< (json::writer()
			<< stream::denote("node_a") << *node_a
			<< stream::denote("node_b") << *node_b
			<< stream::denote("node_c") << *node_c));
		return false;
	}
	
	node_c->secede();
	if (node_b != node_a->prev() ||
		PointerT() != node_a->next() ||
		PointerT() != node_b->prev() ||
		node_a != node_b->next() ||
		PointerT() != node_c->prev() ||
		PointerT() != node_c->next()) {
		hryky_log_alert(
			"The expected result is B <=> A. "
			<< (json::writer()
			<< stream::denote("node_a") << *node_a
			<< stream::denote("node_b") << *node_b
			<< stream::denote("node_c") << *node_c));
		return false;
	}
	
	hryky::insert_after(node_c, node_a);
	if (PointerT() != node_b->prev() ||
		node_a != node_b->next() ||
		node_b != node_a->prev() ||
		node_c != node_a->next() ||
		node_a != node_c->prev() ||
		PointerT() != node_c->next()) {
		hryky_log_alert(
			"The expected result is B <=> A <=> C. "
			<< (json::writer()
			<< stream::denote("node_a") << *node_a
			<< stream::denote("node_b") << *node_b
			<< stream::denote("node_c") << *node_c));
		return false;
	}

	hryky::insert_before(node_a, node_b);
	if (PointerT() != node_a->prev() ||
		node_b != node_a->next() ||
		node_a != node_b->prev() ||
		node_c != node_b->next() ||
		node_b != node_c->prev() ||
		PointerT() != node_c->next()) {
		hryky_log_alert(
			"The expected result is A <=> B <=> C. "
			<< (json::writer()
			<< stream::denote("node_a") << *node_a
			<< stream::denote("node_b") << *node_b
			<< stream::denote("node_c") << *node_c));
		return false;
	}

	/**
	  @attention
	  IntrusivePtrNode can cause mutual reference.
	 */
	node_a->secede();
	node_b->secede();
	node_c->secede();
	
	return true;
}
} // namespace "anonymous"
} // namespace bidirectional
} // namespace test
} // namespace hryky
