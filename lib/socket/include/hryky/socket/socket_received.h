/**
  @file     socket_received.h
  @brief    retains the result of recv().
  @author   HRYKY
  @version  $Id: socket_received.h 342 2014-03-30 09:41:58Z hryky.private@gmail.com $
 */
#ifndef SOCKET_RECEIVED_H_20140330122406183
#define SOCKET_RECEIVED_H_20140330122406183
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace socket
{
	/// retains the result of recv().
	class Received;

} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the result of recv().
 */
class hryky::socket::Received :
	public WithStreamOut<Received>,
	public WithSwap<Received>
{
public :

	typedef Received this_type;

	/// default constructor.
	Received();

	/// copy constructor.
	Received(this_type const &);

	/// move constructor.
	Received(this_type &&);

	/// instantiates as a valid result.
	Received(size_t const size);

	/// destructor.
	~Received();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// casts to a boolean value.
	operator bool() const;

	/// confirms whether the received result is FIN.
	bool shutdown() const;

	/// retrieves the size of the sent data.
	size_t size() const;

protected :

private :

	size_t size_;
	bool valid_;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace socket
{
} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::socket::Received::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(size);
	hryky_write_member(valid);
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
namespace socket
{
} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SOCKET_RECEIVED_H_20140330122406183
// end of file
