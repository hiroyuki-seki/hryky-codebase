/**
  @file         task_conveyer.h
  @brief        disposes of task workers in a single thread.
  @author       HRYKY
  @version      $Id: task_conveyer.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
  @addtogroup   task
  @{
 */
#ifndef TASK_CONVEYER_H_20111119163411357
#define TASK_CONVEYER_H_20111119163411357
#include "hryky/exclusion/exclusion_cond.h"
#include "hryky/exclusion/exclusion_mutex.h"
#include "hryky/exclusion/exclusion_lock.h"
#include "hryky/intrusive_ptr.h"
#include "hryky/log/log_definition.h"
#include "hryky/without_copy.h"
#include "hryky/task/task_common.h"
#include "hryky/vector.h"
#include "hryky/with_stream_out.h"
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
	class Factory;
	
	/// disposes of task workers in a single thread
	class Conveyer;

	class Terminal;
	
namespace worker
{
	/// executes tasks
	class Base;
}
}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @internal
  @brief        disposes of task-workers in a single thread.

   hryky::task::Conveyer can despose arbitrary task-workers as
  hryky::task::worker::Base polymorphically.
 */
class hryky::task::Conveyer :
	public WithStreamOut<Conveyer>,
	private WithoutCopy
{
public :
	typedef Conveyer                    this_type;
	typedef this_type                   instance_type;
	typedef Terminal                    terminal_type;
	typedef IntrusivePtr<worker::Base>  worker_type;

	/**
	  default constructor.
	  The memory pool is supplied from the default one.
	 */
	Conveyer();

	/// constructor with memory pool.
	explicit Conveyer(mempool::Ptr const & mempool);

	/// destructor
	~Conveyer();

	/// the entry function called by a concurrent unit
	void operator()();

	/// allocates the capacity of workers.
	bool reserve(size_t const capacity);

	/**
	  @brief    appends an executable worker.
	  @param    worker is appended to the buffer waiting for execution.
	 */
	bool append(worker::Base & worker);

	/// requests the end of the conveyer.
	void terminate();

	/// outputs the information formatted as string.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// retrieves the memory pool used in this instance.
	mempool_type mempool() const;

	/// assigns a new receiver of this completion.
	void terminal(terminal_type * const src);

protected :

private :
	typedef exclusion::Mutex                lockable_type;
	typedef exclusion::Cond                 cond_type;
	typedef Vector<worker_type>             workers_type;
	typedef exclusion::Lock<lockable_type>  lock_type;

	hryky_delete_this_copy_constructor(Conveyer);
	hryky_delete_this_copy_assign_op(Conveyer);
	
	/// clears resources
	void clear();

	terminal_type * terminal_;
	workers_type    appendeds_;
	lockable_type   lockable_;
	cond_type       workable_;
	bool volatile   terminating_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information formatted as string.
 */
template <typename StreamT>
StreamT &
hryky::task::Conveyer::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(appendeds);
	hryky_write_member(terminating);

	return out;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace task
{
}
}
#endif // TASK_CONVEYER_H_20111119163411357
/// @}
// end of file
