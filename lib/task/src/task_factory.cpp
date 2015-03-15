/**
  @file         task_factory.cpp
  @brief        manages concurrent units.
  @author       HRYKY
  @version      $Id: task_factory.cpp 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
 */
#include <precompiled.h>
#include "hryky/task/task_factory.h"
#include "hryky/task/task_conveyer.h"
#include "hryky/thread.h"
#include "hryky/foreach.h"
#include "hryky/scoped_registry.h"
#include "hryky/mempool/mempool_instantiate.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace
{
}
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
hryky::task::Factory::Factory()
	: thread_pool_(thread::pool::registry_type::instance())
	  , conveyers_()
	  , terminal_()
	  , lockable_()
	  , rotation_()
{
}
/**
  @brief constructor with the memory pool.
 */
hryky::task::Factory::Factory(mempool::Ptr const & mempool)
	: thread_pool_(thread::pool::registry_type::instance())
	  , conveyers_(mempool)
	  , terminal_()
	  , lockable_()
	  , rotation_()
{
}
/**
  @brief constructor with the mempool of threads and the memory pool.
 */
hryky::task::Factory::Factory(
	thread::pool_type & thread_pool, mempool::Ptr const & mempool)
	: thread_pool_(&thread_pool)
	  , conveyers_(mempool)
	  , terminal_()
	  , lockable_()
	  , rotation_()
{
}
/**
  @brief destrunctor.
 */
hryky::task::Factory::~Factory()
{
	if (!this->join(chrono::minutes(3))) {
		hryky_log_emerg(
			"some conveyers are not terminated in the expected time.");
	}
}
/**
  @brief waits until the all conveyers end.
 */
bool hryky::task::Factory::join(duration_type const & duration)
{
	this->conveyers_.foreach([&duration](
		conveyers_type::reference conveyer) {
		conveyer.terminate();
	});

	return this->terminal_.join(duration);
}
/**
  @brief retrieves a conveyer.
 */
hryky::task::Factory::conveyer_type *
hryky::task::Factory::conveyer()
{
	if (!this->ensure()) {
		hryky_log_err("failed to prepare concurrent units.");
		return hryky_nullptr;
	}

	size_type const conveyers_size = this->conveyers_.size();

	if (0 == conveyers_size) {
		hryky_log_alert("There is no conveyer.");
		return hryky_nullptr;
	}

	size_type const rotation = this->rotation_.update(
		[&conveyers_size](size_type const prev) {
			size_type const next = prev + 1;
			if (next == conveyers_size) {
				return static_cast<size_type>(0u);
			}
			return next;
		});

	return &this->conveyers_[rotation];
}
/**
  @brief retrieves the memory pool.
 */
hryky::mempool_type hryky::task::Factory::mempool() const
{
	return this->conveyers_.get_allocator().mempool();
}
/**
  @brief retrieves the minimum number of concurrent units.
 */
hryky::size_t hryky::task::Factory::min_conveyers_size() const
{
	return thread::hardware_concurrency();
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief clears resources.
 */
void hryky::task::Factory::clear()
{
	if (!this->join(chrono::minutes(1u))) {
		hryky_log_emerg(
			"some conveyers are not terminated in the expected time.");
	}
	
	hryky::clear(this->conveyers_);
}
/**
  @brief supplies a new conveyer.
 */
bool hryky::task::Factory::ensure()
{
	if (!this->conveyers_.empty()) {
		return true;
	}

	lock_type const lock(this->lockable_);

	if (!this->conveyers_.empty()) {
		return true;
	}

	mempool::Ptr const mempool(this->mempool());

	conveyers_type conveyers(mempool);

	size_t const conveyers_size = this->min_conveyers_size();

	if (!conveyers.resize(conveyers_size, this->mempool())) {
		hryky_log_err(
			"failed to allocated concurrent units."
			<< (json::writer()
				<< stream::denote("size") << conveyers_size));
		return false;
	}

	if (hryky_is_null(this->thread_pool_)) {
		hryky_log_alert("The thread mempool is null.");
		return false;
	}

	thread::ProcessorId processor_id;

	if (!conveyers.every([&processor_id, this, &mempool](
		conveyers_type::reference conveyer) {
		this->terminal_.activate(conveyer);
		Terminal::AutoInactivate inactivate(this->terminal_, conveyer);

		if (!this->thread_pool_->run(
			runnable::reference(conveyer, mempool),
			processor_id)) {
			hryky_log_err(
				"failed to enregister a concurrent conveyer.");
			return false;
		}
		++processor_id;
		inactivate.disable();
		return true;
	})) {
		hryky_log_err(
			"failed to enregister conveyers. to "
			"the thread pool\n");
		return false;
	}

	this->conveyers_.swap(conveyers);

	return true;
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
