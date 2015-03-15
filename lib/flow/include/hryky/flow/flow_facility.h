/**
  @file         flow_facility.h
  @brief        deploies workers onto the concurrent units.
  @author       HRYKY
  @version      $Id: flow_facility.h 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
 */
#ifndef FLOW_FACILITY_H_20130310175601413
#define FLOW_FACILITY_H_20130310175601413
#include "hryky/mempool/mempool_ptr.h"
#include "hryky/without_copy.h"
#include "hryky/scoped_registry.h"
#include "hryky/task/task_distributor.h"
#include "hryky/task/task_worker_observer_joinable.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace flow
{
	/// deploies workers onto the concurrent units.
	class Facility;
	typedef Facility facility_type;
	typedef ScopedRegistry<Facility> facility_registry_type;
	
} // namespace flow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief deploies workers onto the concurrent units.
 */
class hryky::flow::Facility :
	public WithStreamOut<Facility>,
	private WithoutCopy
{
public :

	typedef Facility                    this_type;
	typedef task::worker::Base          worker_type;
	typedef exclusion::duration_type    duration_type;

	/// default constructor.
	Facility();

	/// constructor with the memory pool.
	Facility(mempool::Ptr const & mempool);

	/// constructor with the factory to provide concurrent units.
	Facility(
		task::factory_type & factory,
		mempool::Ptr const & mempool);

	/// destructor.
	~Facility();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/**
	  attaches a worker onto the concurrent unit.
	 */
	bool attach(worker_type & worker);

	/**
	  waits until the all distributed worker finishes their tasks
	  or the specified duration has elapsed.
	 */
	bool join(duration_type const & duration);

	/**
	  waits until the all distributed worker finishes their tasks.
	 */
	void join();

protected :

private :

	typedef IntrusivePtr<task::worker::observer::Joinable>
		observer_type;

	hryky_delete_this_copy_constructor(Facility);
	hryky_delete_this_copy_assign_op(Facility);

	/// releases the internal resources.
	void clear();

	task::distributor_type  distributor_;
	observer_type           observer_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace flow
{
} // namespace flow
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::flow::Facility::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(distributor);
	hryky_write_member(observer);
	
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
namespace flow
{
} // namespace flow
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // FLOW_FACILITY_H_20130310175601413
// end of file
