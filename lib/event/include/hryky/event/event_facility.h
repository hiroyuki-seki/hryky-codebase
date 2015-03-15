/**
  @file     event_facility.h
  @brief    facilicates handling events from the system.
  @author   HRYKY
  @version  $Id: event_facility.h 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#ifndef EVENT_FACILITY_H_20140727135754248
#define EVENT_FACILITY_H_20140727135754248
#include "hryky/mempool/mempool_ptr.h"
#include "hryky/instance_buffer.h"
#include "hryky/thread/thread_pool_entity.h"
#include "hryky/exclusion/exclusion_boolean.h"
#include "hryky/runnable/runnable_value.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace clock
{
	class Elapse;
} // namespace clock
namespace event
{
	/// facilicates handling events from the system.
	class Facility;

} // namespace event
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief facilicates handling events from the system.
 */
class hryky::event::Facility
{
public :

	typedef Facility this_type;
	typedef runnable::Base<>::pointer on_quit_type;
	typedef runnable::Base<bool>::pointer on_draw_type;

	/// default constructor.
	Facility();

	/// creates an instance with mempool.
	Facility(mempool::Ptr const & mempool);

	/// destructor.
	~Facility();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// assigns the callback invoked when system quits.
	this_type & on_quit(on_quit_type const & src);

	/// assigns the callback for rendering.
	this_type & on_draw(on_draw_type const & src);

	/// assigns the callback for rendering.
	template <typename FunctorT>
	this_type & on_draw(FunctorT const & functor);

	/// starts the loop to handle events.
	bool run();

	/// starts the loop to handle events for the specified duration.
	bool run(chrono::milliseconds const & duration);

protected :

private :
	hryky_delete_copy_constructor(Facility);
	hryky_delete_copy_assign_op(Facility);

	/// handles an event.
	void poll(bool & quit);

	/// arises when system is about to quit.
	void on_quit();

	/// arises for rendering.
	bool on_draw();

	/// handles events in one loop.
	bool step(bool & quit, clock::Elapse & draw_after);

	mempool::Ptr const  mempool_;
	on_quit_type        on_quit_;
	on_draw_type        on_draw_;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace event
{
} // namespace event
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief assigns the callback for rendering.
 */
template <typename FunctorT>
hryky::event::Facility & hryky::event::Facility::on_draw(
	FunctorT const & functor)
{
	return this->on_draw(on_draw_type(
		mempool::instantiate<
			runnable::Value<FunctorT, on_draw_type::value_type> >(
				this->mempool_, functor, this->mempool_).release()));
}
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::event::Facility::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
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
namespace event
{
} // namespace event
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // EVENT_FACILITY_H_20140727135754248
// end of file
