/**
  @file         task_worker_quicksort.h
  @brief        executes quick-sort concurrently.
  @author       HRYKY
  @version      $Id: task_worker_quicksort.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
  @addtogroup   task
  @{
 */
#ifndef TASK_WORKER_QUICKSORT_H_20111126111856138
#define TASK_WORKER_QUICKSORT_H_20111126111856138
#include "task/task_worker_base.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace task
{
namespace worker
{
	/// executes quick-sort concurrently
	template < typename TaskT >
	class Quicksort;
}
}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief executes quick-sort concurrently.
 */
template < typename TaskT >
class hryky::task::worker::Quicksort
	: public hryky::task::worker::Batch<TaskT>
{
public :

	typedef Quicksort<TaskT>                this_type;///< self
	typedef Batch<TaskT>                    base_type;
	typedef distributor::Batch<this_type>   distributor_type;///< type of distributor

protected :

	/// default constructor
	Quicksort();

	/// destructor
	~Quicksort();

	/// initialization
	bool initialize();

private :

	hryky_delete_this_copy_constructor(Quicksort);
	hryky_delete_this_copy_assign_op(Quicksort);
};
//------------------------------------------------------------------------------
// inline functions
//------------------------------------------------------------------------------
#endif // TASK_WORKER_QUICKSORT_H_20111126111856138
/// @}
// end of file
