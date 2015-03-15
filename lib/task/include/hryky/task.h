/**
  @file         task.h
  @brief        task modules.
  @author       HRYKY
  @version      $Id: task.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef TASK_H_20120109164954367
#define TASK_H_20120109164954367

/**
  @defgroup     task Concurrent Task
  modules to execute multiple tasks concurrently.
  
  @ingroup      concurrent_programming
  @{
 */
/**
  @page hryky::task concurrent tasks
  @section facility                     hryky::task::Factory

   hryky::task::Factory has the collection of concurrent units
  internally. This class generates and manages the concurrent units. Each
  concurrent unit, hryky::task::Conveyer occupies one thread resource.
   hryky::task::Factory and internal hryky::task::Conveyer
  can be shared between different kinds of hryky::task::Distributor and
  hryky::task::worker::Base.

  @dontinclude  test_batch_hello.cpp

  @subsection   Initialization
  @skip         task::Factory
  @until        return false;
  @until        }
  
  @section worker_Base                  hryky::task::worker::Base

   hryky::task::worker::Base is the interface class of a coarsest-grained
  unit executed on one concurrent unit.
   This class shall be derived for an implementation.
   The method of execution is pure virtual function, therefore a derived
  class must implement hryky::task::worker::Base::run_impl().
   In many cases, the instance of derived class will be used from
  hryky::task::Distributor. But the derived class can be used without
  hryky::task::Distributor.
  
  @section worker_distributor_Base      hryky::task::worker::Distributor

   hryky::task::Distributor is the interface class to assign workers to
  the concurrent units. The instance of this class has only the pointers of
  each worker. The implementations derived from
  hryky::task::Distributor must hold the entities of each worker.

  @example      test_batch_hello.cpp
  @example      test_batch_quicksort.cpp
  
 */
#include "hryky/task/task_factory.h"
#include "hryky/task/task_worker_base.h"
#include "hryky/task/task_distributor.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
/// modules for running tasks concurrently.
namespace task
{
}
}
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// define global functions
//------------------------------------------------------------------------------
#endif // TASK_H_20120109164954367
/// @}
// end of file
