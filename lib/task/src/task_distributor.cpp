/**
  @file         task_distributor.cpp
  @brief        attaches workers to the concurrent units.
  @author       HRYKY
  @version      $Id: task_distributor.cpp 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/scoped_registry.h"
#include "hryky/task/task_conveyer.h"
#include "hryky/task/task_distributor.h"
#include "hryky/task/task_factory.h"
#include "hryky/task/task_worker_base.h"
#include "hryky/is_null.h"
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
namespace
{
} // namespace "anonymous"
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
hryky::task::Distributor::Distributor()
	: factory_(factory_registry_type::instance())
	  , error_()
{
}
/**
  @brief copy constructor.
 */
hryky::task::Distributor::Distributor(this_type const & rhs)
	: hryky_copy_member(factory)
	  , hryky_copy_member(error)
{
}
/**
  @brief move constructor.
 */
hryky::task::Distributor::Distributor(this_type && rhs)
	: hryky_move_member(factory)
	  , hryky_move_member(error)
{
}
/**
  @brief constructor with memory pool.
 */
hryky::task::Distributor::Distributor(
	factory_type & factory, mempool::Ptr const &)
	: factory_(&factory)
	  , error_()
{
}
/**
  @brief constructor with memory pool.
 */
hryky::task::Distributor::Distributor(mempool::Ptr const &)
	: factory_(factory_registry_type::instance())
	  , error_()
{
}
/**
  @brief destructor.
 */
hryky::task::Distributor::~Distributor()
{
}
/**
  @brief clears resources.
 */
void hryky::task::Distributor::clear()
{
	hryky::clear(this->error_);
}
/**
  @brief attaches a worker to the concurrent unit.
 */
bool hryky::task::Distributor::attach(worker_type & worker)
{
	factory_type * const factory = this->factory();
	if (hryky_is_null(factory)) {
		hryky_log_err("factory is not specified.");
		return false;
	}

	factory_type::conveyer_type * const conveyer = factory->conveyer();
	if (hryky_is_null(conveyer)) {
		hryky_log_err(
			"failed to retrieve a concurrent unit for the worker.");
		return false;
	}

	if (!worker.attach(*conveyer)) {
		hryky_log_err("failed to attach a worker");
		return false;
	}
	
	return true;
}
/**
  @brief confirms whether some error occurred.
 */
bool hryky::task::Distributor::error() const
{
	return this->error_;
}
/**
  @brief retrieves the factory.
 */
hryky::task::factory_type * hryky::task::Distributor::factory()
{
	return this->factory_;
}
/**
  @brief assigns a new manager that provides a concurrent unit.
 */
void hryky::task::Distributor::factory(factory_type & src)
{
	this->factory_ = &src;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::task::Distributor::swap(this_type & src)
{
	hryky_swap_member(factory);
	hryky_swap_member(error);
}
/**
  @brief retrieves the memory pool.
 */
hryky::mempool::Ptr
hryky::task::Distributor::mempool() const
{
	if (hryky_is_null(this->factory_)) {
		return mempool::Ptr();
	}
	return this->factory_->mempool();
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
namespace
{
} // namespace "anonymous"
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
