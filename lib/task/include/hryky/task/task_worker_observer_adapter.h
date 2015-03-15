/**
  @file         task_worker_observer_adapter.h
  @brief        intermediates the hryky::task::worker::Observer::Base.
  @author       HRYKY
  @version      $Id: task_worker_observer_adapter.h 332 2014-03-09 09:57:05Z hryky.private@gmail.com $
 */
#ifndef TASK_WORKER_OBSERVER_ADAPTER_H_20130310222517600
#define TASK_WORKER_OBSERVER_ADAPTER_H_20130310222517600
#include "hryky/task/task_worker_observer_base.h"
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
namespace observer
{
	/// intermediates the hryky::task::worker::Observer::Base.
	template <typename ClientT>
	class Adapter;

} // namespace observer
} // namespace worker
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief intermediates to hryky::task::worker::observer::Base.
 */
template <typename ClientT>
class hryky::task::worker::observer::Adapter :
	public Base
{
public :

	typedef Adapter<ClientT>    this_type;
	typedef Base                base_type;

	/// constructor with a client which has the implementation.
	Adapter(ClientT & client);

	/// releases the internal resources.
	void clear();

protected :

private :

	virtual void on_attach_impl(worker_type & worker) {
		this->client_.on_attach(worker);
	}

	virtual void on_detach_impl(worker_type & worker) {
		this->client_.on_detach(worker);
	}

	virtual void on_error_impl(worker_type & worker) {
		this->client_.on_error(worker);
	}

	ClientT & client_;

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
namespace observer
{
} // namespace observer
} // namespace worker
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor with a client which has the implementation.
 */
template <typename ClientT>
hryky::task::worker::observer::Adapter<ClientT>::Adapter(ClientT & client)
	: base_type()
	  , client_(client)
{
}
/**
  @brief releases the internal resources.
 */
template <typename ClientT>
void hryky::task::worker::observer::Adapter<ClientT>::clear()
{
	hryky::clear(this->client_);
	this->base_type::clear();
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
namespace worker
{
namespace observer
{
} // namespace observer
} // namespace worker
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // TASK_WORKER_OBSERVER_ADAPTER_H_20130310222517600
// end of file
