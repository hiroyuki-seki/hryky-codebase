/**
  @file     socket_find_address.h
  @brief    retains the preferable configuration in order to obtain an address.
  @author   HRYKY
  @version  $Id: socket_find_address.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef SOCKET_FIND_ADDRESS_H_20140224071858971
#define SOCKET_FIND_ADDRESS_H_20140224071858971
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/socket/socket_aiflags.h"
#include "hryky/socket/socket_address.h"
#include "hryky/string.h"
#include "hryky/raii/autofunc.h"
#include "hryky/is_null.h"
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
	/// retains the preferable configuration in order to obtain an address.
	class FindAddress;

} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the preferable configuration in order to obtain an address.
 */
class hryky::socket::FindAddress :
	public WithStreamOut<FindAddress>,
	public WithSwap<FindAddress>
{
public :

	typedef FindAddress this_type;
	typedef addrinfo    hints_type;
	typedef String<>    host_type;
	typedef String<>    service_type;
	typedef Aiflags     flags_type;
	typedef Family      family_type;
	typedef Socktype    socktype_type;
	typedef Protocol    protocol_type;

	/// default constructor.
	FindAddress();

	/// copy constructor.
	FindAddress(this_type const &);

	/// move constructor.
	FindAddress(this_type &&);

	/// destructor.
	~FindAddress();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// enumerates addresses conforming the specified information.
	template <typename FunctorT>
	bool operator()(FunctorT const & functor);

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// assigns a new host.
	this_type & host(host_type && src);

	/// assigns a new host by null-terminated characters.
	this_type & host(char const * const src);

	/// assigns a new service.
	this_type & service(service_type && src);

	/// assigns a new service by null-terminated characters.
	this_type & service(char const * const src);

	/// assigns new flags.
	this_type & flags(flags_type && src);

	/// assigns a new family.
	this_type & family(family_type && src);

	/// assigns the kind of the family.
	this_type & family(family_type::kind_type::raw_type const src);

	/// assigns a new socktype.
	this_type & socktype(socktype_type && src);

	/// assigns the kind of the socket type.
	this_type & socktype(socktype_type::kind_type::raw_type const src);

	/// assigns a new protocol.
	this_type & protocol(protocol_type && src);

	/// assigns the kind of the protocol.
	this_type & protocol(protocol_type::kind_type::raw_type const src);

	/// configures for the use as server.
	this_type & as_server();

	/// configures for the use as client.
	this_type & as_client();

	/// specifies the names of both host and service are numeric.
	this_type & as_numeric();

	/// enumerates addresses as IPv4.
	this_type & as_ipv4();

	/// enumerates addresses as IPv6.
	this_type & as_ipv6();

	/// enumerates addresses which are available with TCP.
	this_type & as_tcp();

	/// enumerates addresses which are available with UDP.
	this_type & as_udp();

protected :

private :
	/// configures a raw ai_hints.
	void configure(addrinfo & hints);

	host_type       host_;
	service_type    service_;
	flags_type      flags_;
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
  @brief enumerates addresses conforming the specified information.
 */
template <typename FunctorT>
bool hryky::socket::FindAddress::operator()(
	FunctorT const & functor)
{
	char const * const host =
		this->host_.empty() ? hryky_nullptr : this->host_.c_str();
	char const * const service =
		this->service_.empty() ? hryky_nullptr : this->service_.c_str();
	
	addrinfo hints;
	this->configure(hints);

	addrinfo * result = hryky_nullptr;
	
	socket::getaddrinfo_error_type const error = ::getaddrinfo(
		host, service, &hints, &result);
	if (0 != error) {
		hryky_log_err(
			"failed to getaddrinfo: "
			<< (json::writer()
				<< hryky_stream_denote(error)
				<< "description"
				<< socket::describe_getaddrinfo_error(error)
				<< "configuration" << *this
				));
		return false;
	}

	if (hryky_is_null(result)) {
		return false;
	}
	AutoFunc1<void, addrinfo *, freeaddrinfo> const free_result(result);

	size_t count = 0u;

	{
		addrinfo * addr = result;
		while (!hryky_is_null(addr)) {
			++count;
			if (functor(Address(*addr))) {
				return true;
			}
			addr = addr->ai_next;
		}
	}

	return false;
}
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::socket::FindAddress::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(host);
	hryky_write_member(service);
	hryky_write_member(flags);
	hryky_write_member(family);
	hryky_write_member(socktype);
	hryky_write_member(protocol);
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
#endif // SOCKET_FIND_ADDRESS_H_20140224071858971
// end of file
