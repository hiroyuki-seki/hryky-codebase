/**
  @file         task_distributor.h
  @brief        attaches workers to the concurrent units.
  @author       HRYKY
  @version      $Id: task_distributor.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
  @addtogroup   task
  @{
 */
#ifndef TASK_DISTRIBUTOR_H_20111120173739401
#define TASK_DISTRIBUTOR_H_20111120173739401
#include "hryky/exclusion/exclusion_counter.h"
#include "hryky/mempool/mempool_global_registry.h"
#include "hryky/without_copy.h"
#include "hryky/task/task_common.h"
#include "hryky/with_stream_out.h"
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
	/// attaches workers to the concurrent units
	class Distributor;
	typedef Distributor distributor_type;

	/// manages concurrent units.
	class Factory;
	typedef Factory factory_type;

namespace worker
{
	class Base;
}

} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief    attaches workers to the concurrent units.
  @param    WorkerT is derived class of task::worker::Base.
  @attention
  - The instance of this class shall not be released during the lifetime
    of the passed factory module.
 */
class hryky::task::Distributor :
	public WithStreamOut<Distributor>,
	public WithSwap<Distributor>,
	private WithoutCopy
{
public :
	typedef Distributor     this_type;
	typedef worker::Base    worker_type;
	typedef Factory         factory_type;

	/// default constructor
	Distributor();

	/// copy constructor.
	Distributor(this_type const & rhs);

	/// move constructor.
	Distributor(this_type && rhs);

	/// constructor with memory pool.
	explicit Distributor(mempool::Ptr const & mempool);

	/// constructor.
	Distributor(factory_type & factory, mempool::Ptr const & mempool);

	/// destructor
	~Distributor();

	/// copy assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// clears resources
	void clear();

	/**
	  attaches a worker to the concurrent unit.
	  @param worker is attached to the concurrent unit.
	  @return success or failure.
	 */
	bool attach(worker_type & worker);

	/// confirms whether some error occurred.
	bool error() const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// retrieves the factory.
	factory_type * factory();

	/// assigns a new manager that provides a concurrent unit.
	void factory(factory_type & src);

	/// retrieves the memory pool.
	mempool::Ptr mempool() const;

protected :

private :

	factory_type *  factory_;
	bool            error_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::task::Distributor::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(error);


	if (!hryky_is_null(this->factory_)) {
		out << stream::denote("factory") << *this->factory_;
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
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // TASK_DISTRIBUTOR_H_20111120173739401
/// @}
// end of file
