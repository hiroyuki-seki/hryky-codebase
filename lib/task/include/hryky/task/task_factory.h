/**
  @file         task_factory.h
  @brief        dispose concurrenct units on conveyers.
  @author       HRYKY
  @version      $Id: task_factory.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
  @addtogroup   task
  @{
 */
#ifndef TASK_FACTORY_H_20111120180213418
#define TASK_FACTORY_H_20111120180213418
#include "hryky/exclusion/exclusion_variable.h"
#include "hryky/exclusion/exclusion_stack.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/type_traits/add_reference.h"
#include "hryky/intrusive_ptr.h"
#include "hryky/intrusive_ptr_trait.h"
#include "hryky/log/log_definition.h"
#include "hryky/mempool/mempool_base.h"
#include "hryky/without_copy.h"
#include "hryky/scoped_array.h"
#include "hryky/task/task_common.h"
#include "hryky/task/task_terminal.h"
#include "hryky/vector.h"
#include "hryky/scoped_registry.h"
#include "hryky/with_stream_out.h"
#include "hryky/without_copy.h"
#include "hryky/without_new.h"
#include "hryky/is_null.h"
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
	/// dispose concurrenct conveyers.
	class Factory;
	typedef Factory factory_type;
	typedef ScopedRegistry<Factory> factory_registry_type;

	/// A concurrent conveyer of disposed workers.
	class Conveyer;

}
namespace thread
{
namespace pool
{
	class Entity;
}
typedef pool::Entity pool_type;
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief dispose concurrenct units on conveyers.

    hryky::task::Factory retains several hryky::task::Conveyer.
  The each conveyer owns a context in the thread.
 */
class hryky::task::Factory :
	public WithStreamOut<Factory>,
	private WithoutCopy,
	private WithoutNew
{
public :

	typedef Factory     this_type;
	typedef Conveyer    conveyer_type;
	typedef Terminal    terminal_type;
	typedef size_t      size_type;

	/// default constructor.
	Factory();

	/// constructor with the memory pool.
	explicit Factory(mempool::Ptr const & mempool);

	/// constructor with the mempool of threads and the memory pool.
	Factory(thread::pool_type & thread_pool, mempool::Ptr const & mempool);

	/// destructor
	~Factory();

	/// waits until the all conveyers end.
	bool join(duration_type const & duration);

	/// outputs the information formatted as string.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/**
	  retrieves a conveyer.
	  
	  The counter for the rotation of conveyers is NOT thread safe.
	 */
	conveyer_type * conveyer();

	/// confirms whether a conveyer is allocated.
	bool empty() const;

	/// retrieves the memory pool.
	mempool_type mempool() const;

	/// retrieves the minimum number of concurrent units.
	size_type min_conveyers_size() const;

protected :

private :

	typedef Vector<conveyer_type>           conveyers_type;
	typedef exclusion::Mutex                lockable_type;
	typedef exclusion::Variable<size_type>  rotation_type;
	typedef exclusion::Lock<lockable_type>  lock_type;

	hryky_delete_this_copy_constructor(Factory);
	hryky_delete_this_copy_assign_op(Factory);

	/// clears resources
	void clear();

	/// prepares the conveyers.
	bool ensure();

	thread::pool_type *     thread_pool_;
	conveyers_type          conveyers_;
	terminal_type           terminal_;
	lockable_type           lockable_;
	rotation_type           rotation_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information formatted as string.
 */
template <typename StreamT>
StreamT &
hryky::task::Factory::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(conveyers);
	hryky_write_member(terminal);
	hryky_write_member(rotation);


	if (!hryky_is_null(this->thread_pool_)) {
		out << stream::denote("thread_pool") << *this->thread_pool_;
	}
	
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
#endif // TASK_FACTORY_H_20111120180213418
/// @}
// end of file
