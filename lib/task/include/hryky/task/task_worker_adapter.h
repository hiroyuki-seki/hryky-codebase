/**
  @file         task_worker_adapter.h
  @brief        intermediates the interface of hryky::task::worker::Base.
  @author       HRYKY
  @version      $Id: task_worker_adapter.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef TASK_WORKER_ADAPTER_H_20130316234226654
#define TASK_WORKER_ADAPTER_H_20130316234226654
#include "hryky/task/task_worker_base.h"
#include "hryky/adapter.h"
#include "hryky/retention/retention_reference.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ClientT
#define hryky_template_arg \
	ClientT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace task
{
namespace worker
{
	/// intermediates the interface of hryky::task::worker::Base.
	template <hryky_template_param>
	class Adapter;

} // namespace worker
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief intermediates the interface of hryky::task::worker::Base.
 */
template <hryky_template_param>
class hryky::task::worker::Adapter :
	public hryky::Adapter<Base, ClientT, retention::Reference>,
	public WithStreamOut<Adapter<hryky_template_arg> >,
	private WithoutCopy
{
public :

	typedef Adapter<hryky_template_arg> this_type;

	typedef hryky::Adapter<base, ClientT, retention::Reference>
		 base_type;

	/// constructor without a memory pool.
	explicit Adapter(ClientT & client);

	/// constructor with a memory pool.
	Adapter(ClientT & client, mempool::Ptr const & mempool);

	/// destructor.
	~Adapter();

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :

	hryky_delete_default_constructor(Adapter);
	hryky_delete_this_copy_constructor(Adapter);
	hryky_delete_this_copy_assign_op(Adapter);

	/// executes a task.
	virtual void run_impl();
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace task
{
namespace worker
{
} // namespace worker
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor with a memory pool.
 */
template <hryky_template_param>
hryky::task::worker::Adapter<hryky_template_arg>::Adapter(
	ClientT & client, mempool::Ptr const & mempool)
	: base_type(client, mempool)
{
}
/**
  @brief constructor without a memory pool.
 */
template <hryky_template_param>
hryky::task::worker::Adapter<hryky_template_arg>::Adapter(
	ClientT & client)
	: base_type(client)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::task::worker::Adapter<hryky_template_arg>::~Adapter()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::task::worker::Adapter<hryky_template_arg>::clear()
{
	this->base_type::clear();
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::task::worker::Adapter<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->base_type::write_to(out);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief executes a task.
 */
template <hryky_template_param>
void hryky::task::worker::Adapter<hryky_template_arg>::run_impl()
{
	this->get()->run();
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace task
{
namespace worker
{

} // namespace worker
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // TASK_WORKER_ADAPTER_H_20130316234226654
// end of file
