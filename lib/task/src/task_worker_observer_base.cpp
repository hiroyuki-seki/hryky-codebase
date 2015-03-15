/**
  @file         task_worker_observer_base.cpp
  @brief        notifies events in hryky::task::worker::Base.
  @author       HRYKY
  @version      $Id: task_worker_observer_base.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/task/task_worker_observer_base.h"
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
hryky::task::worker::observer::Base::Base()
	: intrusive_ptr_trait()
{
}
/**
  @brief instantiates with memory pool.
 */
hryky::task::worker::observer::Base::Base(mempool::Ptr const & mempool)
	: intrusive_ptr_trait(mempool)
{
}
/**
  @brief copy constructor.
 */
hryky::task::worker::observer::Base::Base(this_type const & rhs)
	: intrusive_ptr_trait(rhs)
{
}
/**
  @brief move constructor.
 */
hryky::task::worker::observer::Base::Base(this_type && rhs)
	: intrusive_ptr_trait(::std::move(rhs))
{
}
/**
  @brief destructor.
 */
hryky::task::worker::observer::Base::~Base()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::task::worker::observer::Base::clear()
{
	this->intrusive_ptr_trait::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::task::worker::observer::Base::swap(this_type &)
{
}
/**
  @brief callback function called just before the worker is attached.
 */
void hryky::task::worker::observer::Base::on_attach(worker_type & worker) {
	this->on_attach_impl(worker);
}
/**
  @brief callback function called just before the worker is detached.
 */
void hryky::task::worker::observer::Base::on_detach(worker_type & worker) {
	this->on_detach_impl(worker);
}
/**
  @brief callback function called just after some error occurs.
 */
void hryky::task::worker::observer::Base::on_error(worker_type & param) {
	this->on_error_impl(param);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
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
