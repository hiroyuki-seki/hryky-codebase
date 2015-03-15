/**
  @file         task_worker_observer_joinable.cpp
  @brief        observes the end of the process of tasks.
  @author       HRYKY
  @version      $Id: task_worker_observer_joinable.cpp 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/task/task_worker_observer_joinable.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace task
{
namespace worker
{
namespace observer
{
namespace
{
} // namespace "anonymous"
} // namespace observer
} // namespace worker
} // namespace task
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
hryky::task::worker::observer::Joinable::Joinable()
	: base_type()
	  , working_()
{
}
/**
  @brief instantiates with memory pool.
 */
hryky::task::worker::observer::Joinable::Joinable(
	mempool::Ptr const & mempool)
	: base_type(mempool)
	  , working_()
{
}
/**
  @brief copy constructor.
 */
hryky::task::worker::observer::Joinable::Joinable(
	this_type const & rhs)
	: base_type(rhs)
	  , working_()
{
}
/**
  @brief move constructor.
 */
hryky::task::worker::observer::Joinable::Joinable(
	this_type && rhs)
	: base_type(::std::move(rhs))
	  , working_()
{
}
/**
  @brief destructor.
 */
hryky::task::worker::observer::Joinable::~Joinable()
{
	this->join();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::task::worker::observer::Joinable::swap(this_type & src)
{
	this->base_type::swap(src);
}
/**
  @brief releases the internal resources.
 */
void hryky::task::worker::observer::Joinable::clear()
{
	this->join();
	this->base_type::clear();
}
/**
  @brief waits until the all workers finish their processes.
 */
void hryky::task::worker::observer::Joinable::join()
{
	this->working_.join();
}
/**
  @brief    waits until the all distributed workers finish their
            tasks or the specified duration has elapsed.
 */
bool
hryky::task::worker::observer::Joinable::join(
	duration_type const & duration)
{
	if (!this->working_.join(duration)) {
		hryky_log_crit(
			"failed to wait for the completion of the all workers.");
		return false;
	}
	return true;
}
/**
  @brief confirmes whether the all distributed workers completed their tasks.
 */
bool hryky::task::worker::observer::Joinable::completed() const
{
	return 0 == this->working_.value();
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief increments the number of attached workers.
 */
hryky::size_t hryky::task::worker::observer::Joinable::acquire()
{
	return this->working_.acquire();
}
/**
  @brief decrements the number of attached workers.
 */
hryky::size_t hryky::task::worker::observer::Joinable::restore()
{
	if (0 == this->working_.value()) {
		hryky_log_emerg(
			"invalid context : all workers have been already detached.");
		return 0;
	}

	return this->working_.restore();
}
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief notifies to attach a new worker.
 */
void hryky::task::worker::observer::Joinable::on_attach_impl(worker_type &)
{
	this->acquire();
}
/**
  @brief notifies to detach the attached worker.
 */
void hryky::task::worker::observer::Joinable::on_detach_impl(worker_type &)
{
	this->restore();
}
/**
  @brief notifies an error occurred in the attached worker.
 */
void hryky::task::worker::observer::Joinable::on_error_impl(worker_type &)
{
	return;
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace task
{
namespace worker
{
namespace observer
{
namespace
{
} // namespace "anonymous"
} // namespace observer
} // namespace worker
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
