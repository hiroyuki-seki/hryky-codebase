/**
  @file         thread_pool_entity.cpp
  @brief        manages the collection of reusable concurrent units.
  @author       HRYKY
  @version      $Id: thread_pool_entity.cpp 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
 */
#include <precompiled.h>
#include "./thread_pool_resource.h"
#include "hryky/allocator/allocator_instantiate.h"
#include "hryky/allocator/allocator_mempool.h"
#include "hryky/exclusion/exclusion_lock.h"
#include "hryky/foreach.h"
#include "hryky/is_null.h"
#include "hryky/mempool/mempool_instantiate.h"
#include "hryky/thread/thread_pool_entity.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace thread
{
namespace pool
{
namespace
{
	exclusion::duration_type const g_joinable_duration(chrono::seconds(10));
}
} // namespace pool
} // namespace thread
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
  @brief constructor.
 */
hryky::thread::pool::Entity::Entity()
	: mempool_()
	  , resources_()
	  , lockable_()
	  , inactives_()
	  , joinable_duration_(g_joinable_duration)
	  , terminal_()
{
}
/**
  @brief constructor with memory pool.
 */
hryky::thread::pool::Entity::Entity(mempool::Ptr const & mempool)
	: mempool_(mempool)
	  , resources_(mempool)
	  , lockable_()
	  , inactives_()
	  , joinable_duration_(g_joinable_duration)
	  , terminal_()
{
}
/**
  @brief destructor.
 */
hryky::thread::pool::Entity::~Entity()
{
	if (!this->join(this->joinable_duration_)) {
		hryky_log_alert(
			"some concurrent units are not terminated in the "
			"expected time. The concurrent units will be forced "
			"to terminate.");
	}

	mempool::Deleter<Resource> const deleter(this->mempool_);

	this->resources_.foreach([&deleter](
		resources_type::reference resource) {
		deleter(resource);
	});
	this->resources_.resize(0u);
}
/**
  @brief enregisters a runnable object.
 */
bool hryky::thread::pool::Entity::run(
	runnable_type const & runnable)
{
	resource_type const resource = this->activate(runnable);

	if (hryky_is_null(resource)) {
		hryky_log_alert(
			"failed to activate a resource of concurrent unit");
		return false;
	}
	
	return true;
}
/**
  @brief enregisters a runnable object with preferred thread.
 */
bool hryky::thread::pool::Entity::run(
	runnable_type const & runnable,
	processor_id_type const & processor_id)
{
	resource_type const resource = this->activate(runnable);

	if (hryky_is_null(resource)) {
		hryky_log_alert(
			"failed to activate a resource of concurrent unit "
			"with the preferred processor");
		return false;
	}

	resource->ideal_processor(processor_id);
	
	return true;
}
/**
  @brief creates concurrent units preliminarily.
 */
bool hryky::thread::pool::Entity::reserve(
	size_t const capacity)
{
	size_t const prev_size = this->resources_.size();
	
	if (prev_size >= capacity) {
		return true;
	}

	lock_type const lock(this->lockable_);

	this->resources_.reserve(capacity);

	return hryky::repeat(prev_size, capacity).every([this]() {
		return !hryky::is_null(this->issue());
	});
}
/**
  @brief assign a new duration in which each thread are waited
    for the completion.
 */
void hryky::thread::pool::Entity::joinable_duration(duration_type const & src)
{
	this->joinable_duration_ = src;
}
/**
  @brief ends the all of the concurrent untis.
 */
bool
hryky::thread::pool::Entity::join(duration_type const & duration)
{
	this->resources_.foreach([](resources_type::reference resource) {
		resource->terminate();
	});

	if (!this->terminal_.join(duration)) {
		return false;
	}

	return true;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief creates new resource and appends it to the resources.
 */
hryky::thread::pool::Entity::resource_type
hryky::thread::pool::Entity::issue()
{
	resource_type const resource =
		mempool::instantiate<Resource>(this->mempool_).release();
	if (hryky_is_null(resource)) {
		hryky_log_err(
			"failed to allocate resource of concurrent unit");
		return hryky_nullptr;
	}
	this->resources_.push_back(resource);

	this->terminal_.acquire();
	
	return resource;
}
/**
  @brief changes the state of concurrent unit from active to inactive.
 */
void hryky::thread::pool::Entity::inactivated(Resource & resource)
{
	lock_type const lock(this->lockable_);

	// inserts the resource to the front of inactive list.
	resource.next(this->inactives_);
	this->inactives_ = &resource;
}
/**
  @brief receives the termination of  a concurrent unit.
 */
void hryky::thread::pool::Entity::terminate(Resource &)
{
	this->terminal_.restore();
}
/**
  @brief extracts an inactive resource.
 */
hryky::thread::pool::Entity::resource_type
hryky::thread::pool::Entity::acquire()
{
	resource_type resource = hryky_nullptr;

	exclusion::Lock<lockable_type> const lock(this->lockable_);

	if (!hryky_is_null(this->inactives_)) {
		// pulls out a resource from the inactive list.
		resource = this->inactives_;
		this->inactives_ = this->inactives_->next();
	}
	else {
		// creates a new resource
		if (hryky_is_null((resource = this->issue()))) {
			return hryky_nullptr;
		}
	}
	
	return resource;
}
/**
  @brief invokes a new thread.
 */
hryky::thread::pool::Entity::resource_type
hryky::thread::pool::Entity::activate(
	runnable_type const & runnable)
{
	resource_type const resource = this->acquire();

	if (hryky_is_null(resource)) {
		hryky_log_alert(
			"failed to acquire a resource of concurrent unit");
		return hryky_nullptr;
	}

	resource->activate(runnable);

	if (!resource->started()) {
		resource->start(*this);
	}
	
	return resource;
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace
{
}
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
