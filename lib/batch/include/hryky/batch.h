/**
  @file         batch.h
  @brief        The module to dispose same works simultaneously..
  @author       HRYKY
  @version      $Id: batch.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
  @ingroup      concurrent_programming
  @{
 */
#ifndef BATCH_H_20130303182938437
#define BATCH_H_20130303182938437

/**
  @page hryky::batch disposing same tasks

  @section worker_Batch                 hryky::task::worker::Batch

   hryky::task::worker::Batch is one example of the deriviation of
  task::worker::Base.
   The downside of this implementation is that an execution of worker might
  occupy the long time period of concurrent unit relatively.
   This implementation is intended to execute more fine grained tasks than
  one worker.
   The implementation of task must be decided staticly. But each task does
  not call virtual function for light overhead.
   The instantiation of this class is invoked in
  hryky::task::distributor::Batch::reset(). If this class is directly used
  without hryky::task::worker::Batch, the notifications at attaching and
  detaching must be implemented.

  @section worker_distributor_Batch     hryky::task::worker::distributor::Batch

   hryky::task::distributor::Batch instantiates task::worker::Batch and assign
  them to each concurrent unit. This class has the methods to distribute
  multiple tasks to each worker.

  @dontinclude  test_task_hello.cpp

  @subsection   Initialization Initialization
  @skip         distributor_type distributor;
  @until        return false;
  @until        }

  @subsection   Distribution Distribution of each task to concurrent units
  @skipline     distributor.distribute(task_type

  @subsection   attach assignment of workers to each concurrent unit
  @skipline     distributor.attach

  @subsection   join wait until the workers complete tasks
  @skipline     distributor.join

  @subsection   HelloTask Simple task

   The example of implementation of an operation for task::worker::Batch.
   This operation merely prints "hello" along with the index of task.

  @dontinclude  test_task_hello.cpp

  @skip         struct HelloTask
  @until        size_t id_;
  @until        };
  @skip         HelloTask::operator()
  @until        }

  @subsection   QuicksortTask Concurrent Sorting

   The following code is the example of the implementation of task for
  task::worker::Batch.
   This example concurrently performs Quicksort by each partition.
   Each concurrent operation generates a new task internally and passes the
  task to own distributer.

  @dontinclude  test_task_quicksort.cpp

  @skip         struct SortTask
  @until        sample_type *
  @until        };
  @skip         SortTask::operator()
  @until        the end of SortTask::operator()

  @example      test_task_hello.cpp
  @example      test_task_quicksort.cpp
 */

#include "hryky/batch/batch_facility.h"
#include "hryky/batch/batch_worker.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // BATCH_H_20130303182938437
/// @}
// end of file
