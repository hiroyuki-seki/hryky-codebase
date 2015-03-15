/**
  @file     socket_descriptor.cpp
  @brief    retains a socket descriptor.
  @author   HRYKY
  @version  $Id: socket_descriptor.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/raii.h"
#include "hryky/socket/socket_address.h"
#include "hryky/socket/socket_descriptor.h"
#include "hryky/json/json_writer.h"
#include "hryky/log/log_definition.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace socket
{
namespace
{
	struct ReceivedSockAddr
	{
		static size_t const buffer_size = 64u;

		union
		{
			::sockaddr sockaddr;
			uint8_t buffer[buffer_size];
		};
	};
	
} // namespace "anonymous"
} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// static variable
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
hryky::socket::Descriptor::Descriptor()
	: raw_(invalid_raw)
	  , flags_()
{
}
/**
  @brief move constructor.
 */
hryky::socket::Descriptor::Descriptor(this_type && rhs)
	: hryky_move_member(raw)
	  , hryky_move_member(flags)
{
	rhs.raw_ = this_type::invalid_raw;
	hryky::clear(rhs.flags_);
}
/**
  @brief destructor.
 */
hryky::socket::Descriptor::~Descriptor()
{
	this->clear();
}
/**
  @brief releases the internal resources.
 */
void hryky::socket::Descriptor::clear()
{
	this->shutdown();
	this->close();
	hryky::clear(this->flags_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::socket::Descriptor::swap(this_type & src)
{
	hryky_swap_member(raw);
	hryky_swap_member(flags);
}
/**
  @brief shutdowns the mutual communication.
 */
void hryky::socket::Descriptor::shutdown()
{
	if (this_type::invalid_raw == this->raw_) {
		return;
	}

	if (this->flag_.readable_) {
		if (this->flag_.writable_) {
			::shutdown(this->raw_, socket::g_shut_rdwr);
			this->flag_.writable_ = false;
		}
		else {
			::shutdown(this->raw_, socket::g_shut_rd);
		}
		this->flag_.readable_ = false;
	}
	else if (this->flag_.writable_) {
		::shutdown(this->raw_, socket::g_shut_wr);
		this->flag_.writable_ = false;
	}
}
/**
  @brief shutdowns to read data from peer.
 */
void hryky::socket::Descriptor::shutdown_read()
{
	if (!this->flag_.readable_) {
		return;
	}

	::shutdown(this->raw_, socket::g_shut_rd);
	this->flag_.readable_ = false;
}
/**
  @brief shutdowns to write data to peer.
 */
void hryky::socket::Descriptor::shutdown_write()
{
	if (!this->flag_.writable_) {
		return;
	}

	::shutdown(this->raw_, socket::g_shut_wr);
	this->flag_.writable_ = false;
}
/**
  @brief opens a socket by an address.
 */
bool hryky::socket::Descriptor::open(address_type const & address)
{
	return this->open(
		address.family(),
		address.socktype(),
		address.protocol());
}
/**
  @brief opens a socket.
 */
bool hryky::socket::Descriptor::open(
	family_type const & family,
	socktype_type const & socktype,
	protocol_type const & protocol)
{
	raw_type const raw = ::socket(
		family.raw(), socktype.raw(), protocol.raw());
	if (this_type::invalid_raw == raw) {
		hryky_log_err(
			"failed to create a raw socket: "
			<< (json::writer()
				<< "ID" << socket::last_error()
				<< "error" << socket::describe_last_error()
				<< "family" << family
				<< "socktype" << socktype
				<< "protocol" << protocol
				));
		return false;
	}
	AutoFunc1<void, raw_type const, socket::close> close_raw(raw);

	if (this->flag_.nonblock_) {
		if (!socket::enable_nonblock(raw)) {
			return false;
		}
	}
	
	this->close();
	this->raw_ = raw;
	this->family_ = family;
	this->socktype_ = socktype;
	this->protocol_ = protocol;

	close_raw.disable();
	
	return true;
}
/**
  @brief connects to peer.
 */
bool hryky::socket::Descriptor::connect(address_type const & address)
{
	if (!this->opened()) {
		if (!this->open(address)) {
			hryky_log_err(
				"failed to open a raw socket: "
				<< (json::writer()
					<< hryky_stream_denote(address)));
			return false;
		}
	}

	address_type::sockaddr_type const & sockaddr = address.sockaddr();

	if (0 != ::connect(
		this->raw_,
		reinterpret_cast< ::sockaddr const *>(&sockaddr[0]),
		static_cast<int>(sockaddr.size()))) {

		if (!this->flag_.nonblock_
			|| (this->connecting()
				? !socket::already()
				: !socket::in_progress())) {
			hryky_log_err(
				"failed to connect to address: "
				<< (json::writer()
					<< "errorId" << socket::last_error()
					<< "error" << socket::describe_last_error()
					<< hryky_stream_denote(address)));
			return false;
		}
		this->flag_.connecting_ = true;
	}
	else {
		this->flag_.connecting_ = false;
		this->flag_.readable_ = true;
		this->flag_.writable_ = true;
	}

	return true;
}
/**
  @brief names a socket.
 */
bool hryky::socket::Descriptor::bind(address_type const & address)
{
	if (!this->opened()) {
		if (!this->open(address)) {
			hryky_log_err(
				"failed to open a raw socket: "
				<< (json::writer()
					<< hryky_stream_denote(address)));
			return false;
		}
	}

	address_type::sockaddr_type const & sockaddr = address.sockaddr();

	if (0 != ::bind(
		this->raw_,
		reinterpret_cast< ::sockaddr const *>(&sockaddr[0]),
		static_cast<int>(sockaddr.size()))) {
		hryky_log_err(
			"failed to bind the socket to address: "
			<< (json::writer()
				<< "errorId" << socket::last_error()
				<< "error" << socket::describe_last_error()
				<< hryky_stream_denote(address)));
		return false;
	}

	return true;
}
/**
  @brief makes the socket as server.
 */
bool hryky::socket::Descriptor::listen(backlog_type const backlog)
{
	if (!this->opened()) {
		hryky_log_err("A socket is not opened.");
		return false;
	}
	
	if (0 != ::listen(this->raw_, backlog)) {
		hryky_log_err(
			"failed to listen the socket: "
			<< (json::writer()
				<< "errorId" << socket::last_error()
				<< "error" << socket::describe_last_error()));
		return false;
	}
	this->flag_.listening_ = true;
	
	return true;
}
/**
  @brief makes the socket as server with the backlog which the platform specifies.
 */
bool hryky::socket::Descriptor::listen()
{
	return this->listen(SOMAXCONN);
}
/**
  @brief keeps this socket from blocking.
 */
hryky::socket::Descriptor &
hryky::socket::Descriptor::as_nonblock()
{
	this->flag_.nonblock_ = true;

	if (this->opened()) {
		socket::enable_nonblock(this->raw_);
	}
	
	return *this;
}
/**
  @brief waits the incoming connection.
 */
hryky::socket::Descriptor
hryky::socket::Descriptor::accept()
{
	if (!this->opened()) {
		hryky_log_err("This socket is not opned.");
		return this_type();
	}

	if (!this->flag_.listening_) {
		if (!this->listen()) {
			hryky_log_err(
				"failed to make the socket listen for connections.");
			return this_type();
		}
	}
	
	raw_type const raw =
		::accept(this->raw_, hryky_nullptr, hryky_nullptr);
	if (this_type::invalid_raw == raw) {
		if (!this->flag_.nonblock_ || !socket::in_progress()) {
			hryky_log_err(
				"failed to accept a incoming socket: "
				<< (json::writer()
					<< "errorId" << socket::last_error()
					<< "error" << socket::describe_last_error()));
		}
		return this_type();
	}

	this_type ret;
	ret.raw_ = raw;
	ret.flag_.readable_ = true;
	ret.flag_.writable_ = true;
	
	return ::std::move(ret);
}
/**
  @brief sends data to the connected peer.
 */
hryky::socket::Descriptor::sent_type
hryky::socket::Descriptor::send(
	void const * const buffer, size_t const size)
{
	if (!this->opened()) {
		hryky_log_err("This socket is not opned.");
		return sent_type();
	}

	if (!this->flag_.writable_) {
		hryky_log_err(
			"This socket can't send data through connection.");
		return sent_type();
	}

	int const flags = 0;
	int const sent_size = ::send(
		this->raw_,
		reinterpret_cast<char const *>(buffer),
		static_cast<int>(size),
		flags);
	if (-1 == sent_size) {
		if (!this->flag_.nonblock_ || !socket::in_progress()) {
			hryky_log_err(
				"failed to send data through the connection: "
				<< (json::writer()
					<< "errorId" << socket::last_error()
					<< "error" << socket::describe_last_error()
					<< "size" << size));
		}
		return sent_type();
	}
	return sent_type(static_cast<size_t>(sent_size));
}
/**
  @brief sends data as datagram.
 */
hryky::socket::Descriptor::sent_type
hryky::socket::Descriptor::sendto(
	void const * const buffer,
	size_t const size,
	address_type const & addr)
{
	if (!this->opened()) {
		hryky_log_err("This socket is not opned.");
		return sent_type();
	}

	address_type::sockaddr_type const & sockaddr = addr.sockaddr();

	int const flags = 0;
	int const sent_size = ::sendto(
		this->raw_,
		reinterpret_cast<char const *>(buffer),
		static_cast<int>(size),
		flags,
		reinterpret_cast< ::sockaddr const *>(&sockaddr[0]),
		static_cast<int>(sockaddr.size()));
	if (-1 == sent_size) {
		if (!this->flag_.nonblock_ || !socket::in_progress()) {
			hryky_log_err(
				"failed to send data: "
				<< (json::writer()
					<< "errorId" << socket::last_error()
					<< "error" << socket::describe_last_error()
					<< "size" << size
					<< "to" << addr));
		}
		return sent_type();
	}
	return sent_type(static_cast<size_t>(sent_size));
}
/**
  @brief receives the data from the connected peer.
 */
hryky::socket::Descriptor::received_type
hryky::socket::Descriptor::recv(
	void * const buffer, size_t const size)
{
	if (!this->opened()) {
		hryky_log_err("This socket is not opned.");
		return received_type();
	}

	if (!this->flag_.readable_) {
		hryky_log_err(
			"This socket can't receive data through connection.");
		return received_type();
	}

	int flags = 0;
	int const received_size = ::recv(
		this->raw_,
		reinterpret_cast<char *>(buffer),
		static_cast<int>(size),
		flags);
	if (-1 == received_size) {
		if (!this->flag_.nonblock_ || !socket::in_progress()) {
			hryky_log_err(
				"failed to send data through the connection: "
				<< (json::writer()
					<< "errorId" << socket::last_error()
					<< "error" << socket::describe_last_error()
					<< "size" << size));
		}
		return received_type();
	}
	return received_type(static_cast<size_t>(received_size));
}
/**
  @brief receives the data without connection.
 */
hryky::socket::Descriptor::received_type
hryky::socket::Descriptor::recvfrom(
	void * const buffer,
	size_t const size,
	address_type & addr)
{
	if (!this->opened()) {
		hryky_log_err("This socket is not opned.");
		return received_type();
	}

	ReceivedSockAddr sockaddr;
	int sockaddr_size =
		static_cast<int>(ReceivedSockAddr::buffer_size);

	int const flags = 0;
	int const received_size = ::recvfrom(
		this->raw_,
		reinterpret_cast<char *>(buffer),
		static_cast<int>(size),
		flags,
		&sockaddr.sockaddr,
		&sockaddr_size);
	if (-1 == received_size) {
		if (!this->flag_.nonblock_ || !socket::in_progress()) {
			hryky_log_err(
				"failed to receive data: "
				<< (json::writer()
					<< "errorId" << socket::last_error()
					<< "error" << socket::describe_last_error()
					<< "size" << size));
		}
		return received_type();
	}

	if (ReceivedSockAddr::buffer_size < sockaddr_size) {
		hryky_log_alert(
			"The size of sockaddr exceeds the expected size.");
		return received_type();
	}

	if (!addr.sockaddr(
		&sockaddr.buffer[0],
		&sockaddr.buffer[0] + sockaddr_size)) {
		hryky_log_err(
			"failed to allocated memory for sockaddr.");
		return received_type();
	}
	addr.family(this->family_);
	addr.socktype(this->socktype_);
	addr.protocol(this->protocol_);

	return received_type(static_cast<size_t>(received_size));
}
/**
  @brief confirms whether the socket is open.
 */
bool hryky::socket::Descriptor::opened() const
{
	return this_type::invalid_raw != this->raw_;
}
/**
  @brief confirms whether the socket is now trying to connect.
 */
bool hryky::socket::Descriptor::connecting() const
{
	return this->flag_.connecting_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief closes the socket.
 */
void hryky::socket::Descriptor::close()
{
	if (!this->opened()) {
		return;
	}

	socket::close(this->raw_);
	
	this->raw_ = this_type::invalid_raw;
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines functions used in this file
//------------------------------------------------------------------------------
namespace hryky
{
namespace socket
{
namespace
{
} // namespace "anonymous"
} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
