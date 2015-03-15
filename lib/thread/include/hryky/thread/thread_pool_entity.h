/**
  @file         thread_pool_entity.h
  @brief        manages the collection of reusable concurrent units.
  @author       HRYKY
  @version      $Id: thread_pool_entity.h 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
 */
#ifndef THREAD_POOL_ENTITY_H_20111223150404294
#define THREAD_POOL_ENTITY_H_20111223150404294
#include "hryky/chrono.h"
#include "hryky/exclusion/exclusion_counter.h"
#include "hryky/exclusion/exclusion_mutex.h"
#include "hryky/exclusion/exclusion_lock.h"
#include "hryky/intrusive_ptr.h"
#include "hryky/mempool/mempool_base.h"
#include "hryky/mempool/mempool_ptr.h"
#include "hryky/thread/thread_common.h"
#include "hryky/runnable/runnable_value.h"
#include "hryky/runnable/runnable_reference.h"
#include "hryky/vector.h"
#include "hryky/scoped_registry.h"
#include "hryky/without_copy.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace thread
{
	class ProcessorId;
	typedef ProcessorId processor_id_type;
	
namespace pool
{
	/// manages the collection of reusable concurrent units
	class Entity;

	typedef ScopedRegistry<Entity> registry_type;

	class Resource;
	
} // namespace pool
typedef pool::Entity pool_type;

} // namespace thread
namespace exclusion
{
	template < typename LockableT >
	class Lock;
	
} // namespace exclusion
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief manages the collection of reusable concurrent units.
 */
class hryky::thread::pool::Entity :
	public WithStreamOut<Entity>,
	private WithoutCopy
{
public :

	typedef Entity                      this_type;
	typedef exclusion::duration_type    duration_type;
	typedef runnable::Base<>::pointer   runnable_type;

	/// default constructor.
	Entity();

	/// constructor with memory pool.
	Entity(mempool::Ptr const & mempool);

	/// destructor.
	~Entity();

	/// enregisters a callable object.
	bool run(runnable_type const & runnable);

	/// enregisters a callable object with the preferred thread.
	bool run(
		runnable_type const & runnable,
		processor_id_type const & processor_id);

	/// enregister the runnable object.
	template <typename FunctorT>
	bool run(
		FunctorT const & functor,
		processor_id_type const & processor_id);

	/// enregister the runnable object without specifing a processor.
	template <typename FunctorT>
	bool run(FunctorT const & functor);

	/// creates concurrent units preliminarily.
	bool reserve(size_t const capacity);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/**
	  assign a new duration in which each thread are waited
	  for the completion.
	 */
	void joinable_duration(duration_type const & src);

	/// waits the end of the all concurrent untis.
	bool join(duration_type const & duration);

protected :

private :

	typedef exclusion::Mutex                lockable_type;
	typedef Resource *                      resource_type;
	typedef Vector<resource_type>           resources_type;
	typedef exclusion::Counter<>            counter_type;
	typedef exclusion::Lock<lockable_type>  lock_type;

	hryky_delete_this_copy_constructor(Entity);
	hryky_delete_this_copy_assign_op(Entity);

	/// create new resource and append it to the resources.
	resource_type issue();

	/// changes the state of concurrent unit from active to inactive.
	void inactivated(Resource & resource);

	/// receives the termination of a concurrent unit.
	void terminate(Resource & resource);

	/// extracts an inactive resource.
	resource_type acquire();

	/// invokes a new thread.
	resource_type activate(runnable_type const & runnable);

	mempool::Ptr const      mempool_;
	resources_type          resources_;
	lockable_type mutable   lockable_;
	resource_type           inactives_;
	duration_type           joinable_duration_;
	counter_type            terminal_;

public :
	/**
	  @brief the wrapper to call inactivated().
	  @attention internal use only.
	 */
	class Inactivate : WithoutCopy
	{
		friend class Resource;
		
		typedef Inactivate this_type;
		
		Inactivate(Entity & pool, Resource & resource)
		{
			pool.inactivated(resource);
		}

		hryky_delete_copy_constructor(Inactivate);
		hryky_delete_copy_assign_op(Inactivate);
	};

	/**
	  @brief the wrapper to call terminate().
	  @attention internal use only.
	 */
	class Terminate : WithoutCopy
	{
		friend class Resource;

		typedef Terminate this_type;
		
		Terminate(Entity & pool, Resource & resource)
		{
			pool.terminate(resource);
		}

		hryky_delete_copy_constructor(Terminate);
		hryky_delete_copy_assign_op(Terminate);
	};

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief enregister the runnable object.
 */
template <typename FunctorT>
bool hryky::thread::pool::Entity::run(
	FunctorT const & functor,
	processor_id_type const & processor_id)
{
	return this->run(
		runnable::value(functor, this->mempool_),
		processor_id);
}
/**
  @brief enregister the runnable object without specifing a processor.
 */
template <typename FunctorT>
bool hryky::thread::pool::Entity::run(
	FunctorT const & functor)
{
	return this->run(
		runnable::value(functor, this->mempool_));
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::thread::pool::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	{
		lock_type const lock(this->lockable_);

		out << "resources_size" << this->resources_.size();

		stream::array::Scope<StreamT> const resources(out);

		this->resources_.foreach([&out](
			resources_type::const_reference resource) {
			out << *resource;
		});
	}

	out << "resources" << resources;
	
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
namespace thread
{
namespace pool
{
	/// executes a functor asynchronously by thread.
	template <typename FunctorT>
	bool run(FunctorT const & functor);

} // namespace pool
} // namespace thread
} // namespace hryky
//------------------------------------------------------------------------------
// global function definition
//------------------------------------------------------------------------------
/**
  @brief executes a functor asynchronously by thread.
 */
template <typename FunctorT>
bool hryky::thread::pool::run(FunctorT const & functor)
{
	Entity * const entity = registry_type::instance();
	if (hryky_is_null(entity)) {
		hryky_log_err("A thread::pool::Entity is not registered.");
		return false;
	}
	return entity->run(functor);
}
#endif // THREAD_POOL_ENTITY_H_20111223150404294
// end of file
