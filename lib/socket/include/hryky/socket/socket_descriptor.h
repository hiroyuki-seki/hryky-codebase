/**
  @file     socket_descriptor.h
  @brief    retains a socket descriptor.
  @author   HRYKY
  @version  $Id: socket_descriptor.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef SOCKET_DESCRIPTOR_H_20140224173044396
#define SOCKET_DESCRIPTOR_H_20140224173044396
#include "hryky/without_copy.h"
#include "hryky/socket/socket_common.h"
#include "hryky/socket/socket_sent.h"
#include "hryky/socket/socket_received.h"
#include "hryky/socket/socket_family.h"
#include "hryky/socket/socket_socktype.h"
#include "hryky/socket/socket_protocol.h"
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
	/// retains a socket descriptor.
	class Descriptor;

	class Address;

} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a socket descriptor.
 */
class hryky::socket::Descriptor :
	public WithStreamOut<Descriptor>,
	public WithSwap<Descriptor>,
	private WithoutCopy
{
public :

	typedef Descriptor              this_type;
	typedef raw_descriptor_type     raw_type;
	typedef Address                 address_type;
	typedef Family                  family_type;
	typedef Socktype                socktype_type;
	typedef Protocol                protocol_type;
	typedef int                     backlog_type;
	typedef Sent                    sent_type;
	typedef Received                received_type;

	/// default constructor.
	Descriptor();

	/// move constructor.
	Descriptor(this_type &&);

	/// destructor.
	~Descriptor();

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// shutdowns the mutual communication.
	void shutdown();

	/// shutdowns to read data from peer.
	void shutdown_read();

	/// shutdowns to write data to peer.
	void shutdown_write();

	/// opens a socket by an address.
	bool open(address_type const & address);

	/// opens a socket.
	bool open(
		family_type const & family,
		socktype_type const & sock_type,
		protocol_type const & protocol);

	/// connects to peer.
	bool connect(address_type const & address);

	/// names a socket.
	bool bind(address_type const & address);

	/// makes the socket as server.
	bool listen(backlog_type const backlog);

	/**
	  makes the socket as server with the backlog which
	  the platform specifies.
	 */
	bool listen();

	/// keeps this socket from blocking.
	this_type & as_nonblock();

	/// waits the incoming connection.
	this_type accept();

	/// sends data to the connected peer.
	sent_type send(void const * const buffer, size_t const size);

	/// sends data as datagram.
	sent_type sendto(
		void const * const buffer,
		size_t const size,
		address_type const & addr);

	/// receives the data from the connected peer.
	received_type recv(void * const buffer, size_t const size);

	/// receives the data without connection.
	received_type recvfrom(
		void * const buffer,
		size_t const size,
		address_type & addr);

	/// confirms whether the socket is open.
	bool opened() const;

	/// confirms whether the socket is now trying to connect.
	bool connecting() const;

	/// sends the data in a container.
	template <typename ContainerT>
	sent_type send(ContainerT const & container);

	/// sends the data in a container to the specified peer.
	template <typename ContainerT>
	sent_type sendto(
		ContainerT const & container, address_type const & addr);

	/// receives the data into a container.
	template <typename ContainerT>
	received_type recv(ContainerT & container);

	/// receives the data into a container from a connection-less peer.
	template <typename ContainerT>
	received_type recvfrom(
		ContainerT & container, address_type & addr);

protected :

private :

	static raw_type const invalid_raw = g_invalid_raw_descriptor;

	hryky_delete_this_copy_constructor(Descriptor);
	hryky_delete_this_copy_assign_op(Descriptor);

	/// closes the socket.
	void close();

	raw_type        raw_;
	family_type     family_;
	socktype_type   socktype_;
	protocol_type   protocol_;

	union
	{
		uint32_t flags_;
		struct
		{
			bool nonblock_:1;
			bool readable_:1;
			bool writable_:1;
			bool listening_:1;
			bool connecting_:1;
		} flag_;
	};

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
StreamT & hryky::socket::Descriptor::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}
/**
  @brief sends the data in a container.
 */
template <typename ContainerT>
hryky::socket::Descriptor::sent_type
hryky::socket::Descriptor::send(
	ContainerT const & container)
{
	return this->send(container.data(), container.size());
}
/**
  @brief sends the data in a container to the specified peer.
 */
template <typename ContainerT>
hryky::socket::Descriptor::sent_type
hryky::socket::Descriptor::sendto(
	ContainerT const & container, address_type const & addr)
{
	return this->sendto(container.data(), container.size(), addr);
}
/**
  @brief receives the data into a container.
 */
template <typename ContainerT>
hryky::socket::Descriptor::received_type
hryky::socket::Descriptor::recv(
	ContainerT & container)
{
	return this->recv(container.data(), container.size());
}
/**
  @brief receives the data into a container from a connection-less peer.
 */
template <typename ContainerT>
hryky::socket::Descriptor::received_type
hryky::socket::Descriptor::recvfrom(
	ContainerT & container, address_type & addr)
{
	return this->recvfrom(container.data(), container.size(), addr);
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
#endif // SOCKET_DESCRIPTOR_H_20140224173044396
// end of file
