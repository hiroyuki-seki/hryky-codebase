/**
  @file         task_conveyer.cpp
  @brief        manages workers in a single thread.
  @author       HRYKY
  @version      $Id: task_conveyer.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include <precompiled.h>
#include "hryky/task/task_terminal.h"
#include "hryky/exclusion/exclusion_lock.h"
#include "hryky/foreach.h"
#include "hryky/log/log_definition.h"
#include "hryky/profiler/profiler_cumulate.h"
#include "hryky/task/task_conveyer.h"
#include "hryky/task/task_worker_base.h"
#include "hryky/thread.h"
#include "hryky/mempool/mempool_instantiate.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_disable_warning_constant_condition
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
// public member function
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
hryky::task::Conveyer::Conveyer()
	: terminal_()
	  , appendeds_()
	  , lockable_()
	  , workable_()
	  , terminating_()
{
}
/**
  @brief constructor with memory pool.
 */
hryky::task::Conveyer::Conveyer(mempool::Ptr const & mempool)
	: terminal_()
	  , appendeds_(mempool)
	  , lockable_()
	  , workable_()
	  , terminating_()
{
}
/**
  @brief destrunctor.
 */
hryky::task::Conveyer::~Conveyer()
{
}
/**
  @brief the entry function called by a concurrent unit.
 */
void hryky::task::Conveyer::operator()()
{
	hryky_log_debug(
		"task conveyer starts"
		<< (json::writer()
			<< "conveyer" << *this
			<< "thread_id" << thread::this_thread::get_id()
			));
	
	workers_type workers(this->mempool());

	size_t wait_count =     0;
	size_t execute_count =  0;
	size_t error_count =    0;
	
	chrono::nanoseconds     wait_total;
	chrono::nanoseconds     execute_total;
	
	while (1) {
		// locks while append_buffer is accessed.
		{
			lock_type lock(this->lockable_);

			if (this->terminating_) {
				break;
			}
			
			// appends workers
			if (!this->appendeds_.empty()) {
				this->appendeds_.foreach([&workers, &error_count](
					worker_type & worker) {
					if (!workers.push_back(worker)) {
						hryky_log_alert(
							"failed to append a worker to concurrent conveyer"
							<< (json::writer()
								<< stream::denote("workers") << workers
								));

						++error_count;

						worker->error();
						worker->detach();
					}
				});
				this->appendeds_.resize(0);
			}

			// suspends if there is no active worker.
			if (workers.empty()) {
				profiler::Cumulate<chrono::nanoseconds> const
					profile(wait_total);

				++wait_count;

				this->workable_.join(lock);
			}
		}

		workers.foreach([&execute_total, &execute_count](
			worker_type & worker) {
			profiler::Cumulate<chrono::nanoseconds> const
				profile(execute_total);
			
			++execute_count;

			worker->run();
			worker->detach();
		});
		workers.resize(0);
	}

	hryky_log_debug(
		"task conveyer terminated"
		<< (json::writer()
			<< stream::denote("conveyer") << *this
			<< stream::denote("thread_id") << thread::this_thread::get_id()
			<< stream::denote("wait_count") << wait_count
			<< stream::denote("wait_total") << wait_total.count()
			<< stream::denote("execute_count") << execute_count
			<< stream::denote("execute_total") << execute_total.count()
			<< stream::denote("error_count") << error_count
			));

	if (!hryky_is_null(this->terminal_)) {
		this->terminal_->inactivate(*this);
	}
}
/**
  @brief allocates the capacity of workers.
 */
bool hryky::task::Conveyer::reserve(size_t const capacity)
{
	lock_type const lock(this->lockable_);
	
	return this->appendeds_.reserve(capacity);
}
/**
  @brief appends an executable worker.
 */
bool hryky::task::Conveyer::append(worker::Base & worker)
{
	if (this->terminating_) {
		hryky_log_err("The conveyer is terminating.");
		return false;
	}
	
	{
		lock_type const lock(this->lockable_);
	
		if (!this->appendeds_.push_back(worker_type(&worker))) {
			hryky_log_err(
				"failed to push a worker to the waiting buffer"
				<< (json::writer()
					<< stream::denote("appendeds") << this->appendeds_));
			return false;
		}
	}

	this->workable_.notify();

	return true;
}
/**
  @brief requests the end of the conveyer.
 */
void hryky::task::Conveyer::terminate()
{
	if (this->terminating_) {
		return;
	}
	
	lock_type lock(this->lockable_);

	this->terminating_ = true;

	this->workable_.notify();
}
/**
  @brief assigns a new receiver of this completion.
 */
void hryky::task::Conveyer::terminal(terminal_type * const src)
{
	this->terminal_ = src;
}
/**
  @brief retrieves the memory pool used in this instance.
 */
hryky::mempool_type hryky::task::Conveyer::mempool() const
{
	return this->appendeds_.get_allocator().mempool();
}
//------------------------------------------------------------------------------
// protected member function
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// private member function
//------------------------------------------------------------------------------
/**
  @brief clears resources.
 */
void hryky::task::Conveyer::clear()
{
	lock_type const lock(this->lockable_);
	hryky::clear(this->appendeds_);
}
//------------------------------------------------------------------------------
// global function
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static function
//------------------------------------------------------------------------------
namespace
{
}
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
