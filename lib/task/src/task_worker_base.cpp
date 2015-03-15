/**
  @file         task_worker_base.cpp
  @brief        executes tasks.
  @author       HRYKY
  @version      $Id: task_worker_base.cpp 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/exclusion/exclusion_lock.h"
#include "hryky/profiler/profiler_cumulate.h"
#include "hryky/raii.h"
#include "hryky/task/task_conveyer.h"
#include "hryky/task/task_worker_base.h"
#include "hryky/task/task_worker_observer_base.h"
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
  @brief constructor.
 */
hryky::task::worker::Base::Base()
	: intrusive_ptr_trait()
	  , observer_()
{
}
/**
  @brief constructor with mempool.
 */
hryky::task::worker::Base::Base(mempool::Ptr const & mempool)
	: intrusive_ptr_trait(mempool)
	  , observer_()
{
}
/**
  @brief destrunctor.
 */
hryky::task::worker::Base::~Base()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::task::worker::Base::clear()
{
	this->intrusive_ptr_trait::clear();
}
/**
  @brief attaches itself to the corresponding thread.
 */
bool hryky::task::worker::Base::attach(conveyer_type & conveyer)
{
	if (!hryky_is_null(this->observer_)) {
		this->observer_->on_attach(*this);
	}
	AutoMemFunc<this_type, void, &this_type::detach> detach(*this);

	if (!conveyer.append(*this)) {
		hryky_log_err(
			"failed to append the worker to the concurrent unit");
		return false;
	}

	detach.disable();

	return true;
}
/**
  @brief notifies that some error occurs.
 */
void hryky::task::worker::Base::error()
{
	if (!hryky_is_null(this->observer_)) {
		this->observer_->on_error(*this);
	}
}
/**
  @brief assigns a new observer.
 */
void hryky::task::worker::Base::observer(observer_type const & src)
{
	this->observer_ = src;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief executes derived work.
 */
void hryky::task::worker::Base::run()
{
	this->run_impl();
}
/**
  @brief notifies the detachment from conveyer.
 */
void hryky::task::worker::Base::detach()
{
	if (!hryky_is_null(this->observer_)) {
		this->observer_->on_detach(*this);
	}
}
/**
  @brief confirms whether the equality.
 */
bool hryky::task::worker::Base::operator==(this_type const & rhs) const
{
	return this == &rhs;
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
