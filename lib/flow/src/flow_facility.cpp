/**
  @file         flow_facility.cpp
  @brief        deploies workers onto the concurrent units.
  @author       HRYKY
  @version      $Id: flow_facility.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/flow/flow_facility.h"
#include "hryky/task.h"
#include "hryky/mempool.h"
#include "hryky/log.h"
#include "hryky/is_null.h"
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
} // namespace "anonymous"
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
hryky::flow::Facility::Facility()
	: distributor_()
	  , observer_()
{
}
/**
  @brief constructor with the memory pool.
 */
hryky::flow::Facility::Facility(mempool::Ptr const & mempool)
	: distributor_(mempool)
	  , observer_()
{
}
/**
  @brief constructor with the factory to provide concurrent units.
 */
hryky::flow::Facility::Facility(
	task::factory_type & factory, mempool::Ptr const & mempool)
	: distributor_(factory, mempool)
	  , observer_()
{
}
/**
  @brief destructor.
 */
hryky::flow::Facility::~Facility()
{
	this->join();
}
/**
  @brief attaches a worker onto the concurrent unit.
 */
bool hryky::flow::Facility::attach(worker_type & worker)
{
	if (hryky_is_null(this->observer_)) {
		mempool::Ptr const mempool = this->distributor_.mempool();
		this->observer_ = mempool::instantiate<observer_type::value_type>(
			mempool, mempool).release();
		if (hryky_is_null(this->observer_)) {
			hryky_log_err("failed to allocate an observer.");
			return false;
		}
	}
	
	worker.observer(this->observer_);
	
	return this->distributor_.attach(worker);
}
/**
  @brief waits until the all distributed worker finishes their tasks
    or the specified duration has elapsed.
 */
bool hryky::flow::Facility::join(duration_type const & duration)
{
	if (hryky_is_null(this->observer_)) {
		return true;
	}
	if (!this->observer_->join(duration)) {
		hryky_log_emerg(
			"failed to wait the completion of flow.");
		return false;
	}
	return true;
}
/**
  @brief waits until the all distributed worker finishes their tasks.
 */
void hryky::flow::Facility::join()
{
	if (hryky_is_null(this->observer_)) {
		return;
	}
	this->observer_->join();
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief releases the internal resources.
 */
void hryky::flow::Facility::clear()
{
	hryky::clear(this->observer_);
	hryky::clear(this->distributor_);
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace flow
{
namespace
{
} // namespace "anonymous"
} // namespace flow
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
