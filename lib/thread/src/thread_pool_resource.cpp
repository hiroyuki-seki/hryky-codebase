/**
  @file         thread_pool_resource.cpp
  @brief        holds the resource of concurrent unit.
  @author       HRYKY
  @version      $Id: thread_pool_resource.cpp 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#include <precompiled.h>
#include "./thread_pool_resource.h"
#include "hryky/chrono.h"
#include "hryky/exclusion.h"
#include "hryky/thread/thread_common.h"
#include "hryky/thread/thread_pool_entity.h"
#include "hryky/thread/thread_processor_id.h"
#include "hryky/windows.h"
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
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
hryky::thread::pool::Resource::Resource()
	: pool_()
	  , next_()
	  , runnable_()
	  , raw_()
	  , lockable_()
	  , workable_()
	  , joinable_duration_(chrono::seconds(5000))
	  , used_count_()
	  , terminating_()
{
}
/**
  @brief destructor.
 */
hryky::thread::pool::Resource::~Resource()
{
	this->terminate();
	
	if (!this->join(this->joinable_duration_)) {
		hryky_log_alert(
			"a thread is not terminated in the expected time. "
			"The thread will be forced to terminate.");
	}

	this->pool_ = hryky_nullptr;
}
/**
  @brief starts this thread with a thread pool.
 */
void hryky::thread::pool::Resource::start(pool_type & pool)
{
	this->pool_ = &pool;
	this->raw_ = raw_type(RawRunnable(*this));
}
/**
  @brief confirms whether this thread started.
 */
bool hryky::thread::pool::Resource::started() const
{
	return !hryky_is_null(this->pool_);
}
/**
  @brief ends the concurrent unit.
 */
void hryky::thread::pool::Resource::terminate()
{
	if (this->terminating_) {
		return;
	}
	lock_type lock(this->lockable_);

	this->terminating_ = true;

	this->workable_.notify();
}
/**
  @brief indicates the preferred processor on which this
    concurrent unit will run.
 */
void hryky::thread::pool::Resource::ideal_processor(
	processor_id_type const & processor_id)
{
	thread::set_affinity(
		this->raw_.native_handle(), processor_id.raw());
}
/**
  @brief enregisters a new runnable object.
 */
void hryky::thread::pool::Resource::activate(
	runnable_type const & runnable)
{
	if (this->terminating_) {
		hryky_log_alert(
			"runnable object has been already terminated.");
		return;
	}
	
	if (!hryky_is_null(this->runnable_)) {
		hryky_log_alert(
			"runnable object has been already assigned.");
		return;
	}
	
	{
		lock_type const lock(this->lockable_);

		this->runnable_ = runnable;
	}

	this->workable_.notify();
}
/**
  @brief retrieves the next node of this instance.
 */
hryky::thread::pool::Resource *
hryky::thread::pool::Resource::next() const
{
	return this->next_;
}
/**
  @brief replace the next node of this instance with a new node.
 */
void hryky::thread::pool::Resource::next(Resource * const src)
{
	this->next_ = src;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief waits the end of concurrent unit until specified duration elapses.
 */
bool hryky::thread::pool::Resource::join(
	duration_type const & duration)
{
	if (this->raw_.joinable()) {
#if HRYKY_USE_BOOST_EXCLUSION
		this->raw_.timed_join(
			boost::posix_time::milliseconds(
				chrono::milliseconds(duration).count()));
#else
		/**
		  @todo needs timer using the duration.
		*/
		(void)duration;
		this->raw_.join();
#endif
	}

	this->raw_.detach();
	this->raw_ = raw_type();

	return true;
}
/**
  @brief invokes a runnable function for a concurrent unit.
 */
void hryky::thread::pool::Resource::run()
{
	hryky_log_debug(
		"thread resource starts"
		<< (json::writer()
			<< "resource" << *this
			<< "thread_id" << thread::this_thread::get_id()
			));
	
	while (1) {
		runnable_type runnable;

		{
			lock_type lock(this->lockable_);

			if (hryky_is_null(this->runnable_)) {
				if (this->terminating_) {
					break;
				}

				if (!hryky_is_null(this->pool_)) {
					pool_type::Inactivate(*this->pool_, *this);
				}
				this->workable_.join(lock);
			}

			runnable = this->runnable_;
			this->runnable_ = hryky_nullptr;
		}
		
		if (!hryky_is_null(runnable)) {
			++this->used_count_;
			runnable->run(make_tuple());
		}
	}

	hryky_log_debug(
		"thread resource terminated"
		<< (json::writer()
			<< "resource" << *this
			<< "thread_id" << thread::this_thread::get_id()));

	if (!hryky_is_null(this->pool_)) {
		pool_type::Terminate(*this->pool_, *this);
	}
}
/**
  @brief sets the duration to wait until the end of concurrent unit.
 */
void hryky::thread::pool::Resource::joinable_duration(
	duration_type const & src)
{
	this->joinable_duration_ = src;
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
