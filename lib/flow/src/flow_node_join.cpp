/**
  @file         flow_node_join.cpp
  @brief        waits for the completion of the nodes.
  @author       HRYKY
  @version      $Id: flow_node_join.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/flow/flow_node_join.h"
#include "hryky/is_null.h"
#include "hryky/log.h"
#include "hryky/mempool.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace flow
{
namespace node
{
namespace
{
} // namespace "anonymous"
} // namespace node
} // namespace flow
} // namespace hryky
//------------------------------------------------------------------------------
// static variable
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
hryky::flow::node::Join::Join()
	: base_type()
	  , counter_()
{
}
/**
  @brief constructor.
 */
hryky::flow::node::Join::Join(
	facility_type & facility, mempool::Ptr const & mempool)
	: base_type(facility, mempool)
	  , counter_()
{
}
/**
  @brief destructor.
 */
hryky::flow::node::Join::~Join()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::flow::node::Join::clear()
{
	hryky::clear(this->counter_);
	this->base_type::clear();
}
/**
  @brief enregisters a node whose completion this instance waits for.
 */
hryky::flow::node::Join *
hryky::flow::node::Join::join(node_type const & src)
{
	++this->counter_;

	src->append(node_type(this));

	return this;
}
/**
  @brief enregisters two nodes whose completions this instance waits for.
 */
hryky::flow::node::Join *
hryky::flow::node::Join::join(
	node_type const & src0, node_type const & src1)
{
	this->counter_ += 2;

	src0->append(node_type(this));
	src1->append(node_type(this));
	
	return this;
}
/**
  @brief enregisters three nodes whose completions this instance waits for.
 */
hryky::flow::node::Join *
hryky::flow::node::Join::join(
	node_type const & src0, node_type const & src1, node_type const & src2)
{
	this->counter_ += 3;

	src0->append(node_type(this));
	src1->append(node_type(this));
	src2->append(node_type(this));
	
	return this;
}
/**
  @brief enregisters four nodes whose completions this instance waits for.
 */
hryky::flow::node::Join *
hryky::flow::node::Join::join(
	node_type const & src0, node_type const & src1, node_type const & src2,
	node_type const & src3)
{
	this->counter_ += 4;

	src0->append(node_type(this));
	src1->append(node_type(this));
	src2->append(node_type(this));
	src3->append(node_type(this));
	
	return this;
}
/**
  @brief enregisters five nodes whose completions this instance waits for.
 */
hryky::flow::node::Join *
hryky::flow::node::Join::join(
	node_type const & src0, node_type const & src1, node_type const & src2,
	node_type const & src3, node_type const & src4)
{
	this->counter_ += 5;

	src0->append(node_type(this));
	src1->append(node_type(this));
	src2->append(node_type(this));
	src3->append(node_type(this));
	src4->append(node_type(this));
	
	return this;
}
/**
  @brief enregisters six nodes whose completions this instance waits for.
 */
hryky::flow::node::Join *
hryky::flow::node::Join::join(
	node_type const & src0, node_type const & src1, node_type const & src2,
	node_type const & src3, node_type const & src4, node_type const & src5)
{
	this->counter_ += 6;

	src0->append(node_type(this));
	src1->append(node_type(this));
	src2->append(node_type(this));
	src3->append(node_type(this));
	src4->append(node_type(this));
	src5->append(node_type(this));
	
	return this;
}
/**
  @brief enregisters seven nodes whose completions this instance waits for.
 */
hryky::flow::node::Join *
hryky::flow::node::Join::join(
	node_type const & src0, node_type const & src1, node_type const & src2,
	node_type const & src3, node_type const & src4, node_type const & src5,
	node_type const & src6)
{
	this->counter_ += 7;

	src0->append(node_type(this));
	src1->append(node_type(this));
	src2->append(node_type(this));
	src3->append(node_type(this));
	src4->append(node_type(this));
	src5->append(node_type(this));
	src6->append(node_type(this));
	
	return this;
}
/**
  @brief enregisters eight nodes whose completions this instance waits for.
 */
hryky::flow::node::Join *
hryky::flow::node::Join::join(
	node_type const & src0, node_type const & src1, node_type const & src2,
	node_type const & src3, node_type const & src4, node_type const & src5,
	node_type const & src6, node_type const & src7)
{
	this->counter_ += 8;

	src0->append(node_type(this));
	src1->append(node_type(this));
	src2->append(node_type(this));
	src3->append(node_type(this));
	src4->append(node_type(this));
	src5->append(node_type(this));
	src6->append(node_type(this));
	src7->append(node_type(this));
	
	return this;
}
/**
  @brief indicates the number of the joined nodes.
 */
hryky::flow::node::Join *
hryky::flow::node::Join::acquire(size_t const src)
{
	this->counter_ += src;
	return this;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief disposes the succeeding node if the enregisterred flows have been
    completed.
 */
void hryky::flow::node::Join::run_impl()
{
	if (0u == this->counter_) {
		hryky_log_alert(
			"Some nodes are not enregisterred as awaited nodes.");
		return;
	}
	
	if (0u == --this->counter_) {
		this->forward();
	}
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief instantiates a new node waiting for the completion of the
    preceding nodes.
 */
hryky::flow::join_type
hryky::flow::join(
	facility_type & facility, mempool::Ptr const & mempool)
{
	auto instance = mempool::instantiate<node::Join>(
		mempool, facility, mempool);
	if (hryky_is_null(instance)) {
		hryky_log_alert(
			"failed to instantiate a waiting node.");
		return join_type();
	}
	return join_type(instance.release());
}
/**
  @brief instantiates a new node waiting for the completion of the
    preceding nodes.
 */
hryky::flow::join_type
hryky::flow::join()
{
	facility_type * const facility = ScopedRegistry<facility_type>::instance();
	if (hryky_is_null(facility)) {
		hryky_log_alert(
			"The default facility to control the flow of task is initialized.");
		return join_type();
	}

	return join(*facility, mempool::Ptr());
}
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace flow
{
namespace node
{
namespace
{
} // namespace "anonymous"
} // namespace node
} // namespace flow
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
