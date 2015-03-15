/**
  @file         thread_pool_resource.h
  @brief        holds the resource of concurrent unit.
  @author       HRYKY
  @version      $Id: thread_pool_resource.h 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
 */
#ifndef THREAD_POOL_RESOURCE_H_20111223161711345
#define THREAD_POOL_RESOURCE_H_20111223161711345
#include "hryky/definition.h"
#include "hryky/exclusion.h"
#include "hryky/intrusive_ptr.h"
#include "hryky/thread/thread_common.h"
#include "hryky/runnable/runnable_base.h"
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
	/// holds the resource of concurrent unit
	class Resource;

	class Entity;

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
  @brief holds the resource of concurrent unit.
 */
class hryky::thread::pool::Resource :
	public WithStreamOut<Resource>,
	private WithoutCopy
{
public :

	typedef Resource                    this_type;
	typedef runnable::Base<>::pointer   runnable_type;
	
	/// default constructor.
	Resource();

	/// destructor.
	~Resource();

	/**
	  starts this thread with a thread pool.

	   When this thread is paused due to no runnable object,
	  the thread pool is notified by inactivate().
	 */
	void start(pool_type & pool);

	/// confirms whether this thread started.
	bool started() const;

	/// calls for the end of this concurrent unit.
	void terminate();

	/// enregisters a new runnable object.
	void activate(runnable_type const & runnable);

	/**
	  indicates the preferred processor on which this thread will run.
	  
	  @param processor_id is the identifier of a processor or a core

	  - This function does not necessarily guarantee the execution on
	    the specified processor.
	 */
	void ideal_processor(
		processor_id_type const & processor_id);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// retrieves the next node of this instance.
	Resource * next() const;

	/// replace the next node of this instance with a new node.
	void next(Resource * const src);

protected :

private :

	typedef exclusion::Mutex                lockable_type;
	typedef exclusion::Cond                 cond_type;
	typedef exclusion::duration_type        duration_type;
	typedef exclusion::Lock<lockable_type>  lock_type;

	/// type of raw concurrent unit
#if HRYKY_USE_BOOST_EXCLUSION
	typedef boost::thread       raw_type;
#else
	typedef ::std::thread         raw_type;
#endif

	/// raw callable object invoked by raw concurrent unit
	struct RawRunnable
	{
		RawRunnable(Resource & resource)
			: resource_(&resource)
		{}

		RawRunnable(RawRunnable const & rhs)
			: hryky_copy_member(resource)
		{}

		RawRunnable & operator=(RawRunnable const & rhs)
		{
			this->resource_ = rhs.resource_;
			return *this;
		}

		void operator()() const
		{
			this->resource_->run();
		}

		Resource * resource_;
	};

	hryky_delete_this_copy_constructor(Resource);
	hryky_delete_this_copy_assign_op(Resource);
	
	/// waits the end of concurrent unit until specified duration elapses.
	bool join(duration_type const & duration);

	/// invokes a runnable function for a concurrent unit.
	void run();

	/// sets the duration to wait until the end of concurrent unit.
	void joinable_duration(duration_type const & src);

	pool_type *     pool_;
	this_type *     next_;
	raw_type        raw_;
	lockable_type   lockable_;
	cond_type       workable_;
	runnable_type   runnable_;
	duration_type   joinable_duration_;
	size_t          used_count_;
	bool            terminating_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::thread::pool::Resource::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(terminating);
	hryky_write_member(used_count);
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
}
}
#endif // THREAD_POOL_RESOURCE_H_20111223161711345
// end of file
