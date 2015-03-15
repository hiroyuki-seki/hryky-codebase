/**
  @file     socket_sent.h
  @brief    retains the result of send().
  @author   HRYKY
  @version  $Id: socket_sent.h 342 2014-03-30 09:41:58Z hryky.private@gmail.com $
 */
#ifndef SOCKET_SENT_H_20140330121535177
#define SOCKET_SENT_H_20140330121535177
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
	/// retains the result of send().
	class Sent;

} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the result of send().
 */
class hryky::socket::Sent :
	public WithStreamOut<Sent>,
	public WithSwap<Sent>
{
public :

	typedef Sent this_type;

	/// default constructor.
	Sent();

	/// copy constructor.
	Sent(this_type const &);

	/// move constructor.
	Sent(this_type &&);

	/// instantiates as a valid result.
	Sent(size_t const size);

	/// destructor.
	~Sent();

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
StreamT & hryky::socket::Sent::write_to(StreamT & out) const
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
#endif // SOCKET_SENT_H_20140330121535177
// end of file
