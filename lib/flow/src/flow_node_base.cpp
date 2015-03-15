/**
  @file         flow_node_base.cpp
  @brief        The base class in order to handle the common interface.
  @author       HRYKY
  @version      $Id: flow_node_base.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/flow/flow_node_base.h"
#include "hryky/flow/flow_facility.h"
#include "hryky/scoped_registry.h"
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
namespace
{
	node_type const g_null;
	
} // namespace "anonymous"
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
hryky::flow::node::Base::Base()
	: base_type()
	  , facility_(ScopedRegistry<facility_type>::instance())
	  , lockable_()
	  , next_()
	  , completed_()
{
}
/**
  @brief constructor.
 */
hryky::flow::node::Base::Base(
	facility_type & facility, mempool::Ptr const & mempool)
	: base_type(mempool)
	  , facility_(&facility)
	  , lockable_()
	  , next_()
	  , completed_()
{
}
/**
  @brief destructor.
 */
hryky::flow::node::Base::~Base()
{
}
/**
  @brief retrieves the facility to distribute this node with a task worker.
 */
hryky::flow::Facility *
hryky::flow::node::Base::facility()
{
	return this->facility_;
}
/**
  @brief attaches the instance of oneself through the facility.
 */
bool hryky::flow::node::Base::attach()
{
	if (hryky_is_null(this->facility_)) {
		hryky_log_alert("The facility is not specified.");
		return false;
	}

	this->completed_ = false;

	return this->facility_->attach(*this);
}
/**
  @brief appends a node to the end of the chain of nodes.
 */
hryky::flow::node_type const &
hryky::flow::node::Base::append(node_type const & src)
{
	exclusion::Lock<> const lock(this->lockable_);

	if (!hryky_is_null(this->next_)) {
		return this->next_->append(src);
	}

	if (this->completed_) {
		src->attach();
	}
	else {
		this->next_ = src;
	}
	
	return src;
}
/**
  @brief inserts a new node just after this node.
 */
hryky::flow::node_type const &
hryky::flow::node::Base::insert(node_type const & src)
{
	this->consign(src);
	this->next(src);
	return src;
}
/**
  @brief confirms whether this node had been completed.
 */
bool hryky::flow::node::Base::completed() const
{
	return this->completed_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief releases the internal resources.
 */
void hryky::flow::node::Base::clear()
{
	hryky::clear(this->completed_);
	hryky::clear(this->next_);
	this->base_type::clear();
}
/**
  @brief disposes the succeeding nodes.
 */
bool hryky::flow::node::Base::forward()
{
	exclusion::Lock<> const lock(this->lockable_);

	this->completed_ = true;
	
	if (hryky_is_null(this->next_)) {
		return true;
	}
	
	node_type const node = this->next_;
	hryky::clear(this->next_);
	return node->attach();
}
/**
  @brief assigns a new node as the succeeding node.
 */
hryky::flow::node_type const &
hryky::flow::node::Base::next(node_type const & src)
{
	exclusion::Lock<> const lock(this->lockable_);

	if (this->completed_) {
		src->attach();
		return src;
	}

	this->next_ = src;
	return src;
}
/**
  @brief gives the following nodes over the other node.
 */
hryky::flow::node_type const &
hryky::flow::node::Base::consign(node_type const & delegated)
{
	exclusion::Lock<> const lock(this->lockable_);

	node_type const next = this->next_;
	hryky::clear(this->next_);

	delegated->append(next);
	
	return delegated;
}
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the invalid node.
 */
hryky::flow::node_type const & hryky::flow::null()
{
	return g_null;
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
