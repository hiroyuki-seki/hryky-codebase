/**
  @file     socket_address.h
  @brief    retains the informaton of each node.
  @author   HRYKY
  @version  $Id: socket_address.h 345 2014-04-06 09:44:45Z hryky.private@gmail.com $
 */
#ifndef SOCKET_ADDRESS_H_20140223151817304
#define SOCKET_ADDRESS_H_20140223151817304
#include "hryky/socket/socket_family.h"
#include "hryky/socket/socket_protocol.h"
#include "hryky/socket/socket_socktype.h"
#include "hryky/string.h"
#include "hryky/vector.h"
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
	/// retains the informaton of each node.
	class Address;

} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the informaton of each node.
 */
class hryky::socket::Address :
	public WithStreamOut<Address>,
	public WithSwap<Address>
{
public :

	typedef Address         this_type;
	typedef String<>        canonname_type;
	typedef Vector<uint8_t> sockaddr_type;
	typedef Family          family_type;
	typedef Socktype        socktype_type;
	typedef Protocol        protocol_type;

	/// default constructor.
	Address();

	/// constructs this instance with a raw addrinfo.
	Address(addrinfo const & src);

	/// copy constructor.
	Address(this_type const &);

	/// move constructor.
	Address(this_type &&);

	/// destructor.
	~Address();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the address family.
	sockaddr_type const & sockaddr() const;

	/// retrieves the address family.
	family_type const & family() const;

	/// retrieves the socket type.
	socktype_type const & socktype() const;

	/// retrieves the protocol.
	protocol_type const & protocol() const;

	/// assigns a new family.
	void family(family_type const & src);

	/// assigns a new socktype.
	void socktype(socktype_type const & src);

	/// assigns a new protocol.
	void protocol(protocol_type const & src);

	/// assigns a new sockaddr.
	template<typename InputIteratorT>
	bool sockaddr(InputIteratorT begin, InputIteratorT end);

protected :

private :

	canonname_type  canonname_;
	sockaddr_type   sockaddr_;
	family_type     family_;
	socktype_type   socktype_;
	protocol_type   protocol_;

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
StreamT & hryky::socket::Address::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(canonname);
	hryky_write_member(sockaddr);
	hryky_write_member(family);
	hryky_write_member(socktype);
	hryky_write_member(protocol);
	return out;
}
/**
  @brief assigns a new sockaddr.
 */
template<typename InputIteratorT>
bool hryky::socket::Address::sockaddr(
	InputIteratorT begin, InputIteratorT end)
{
	return this->sockaddr_.assign(begin, end);
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
#endif // SOCKET_ADDRESS_H_20140223151817304
// end of file
