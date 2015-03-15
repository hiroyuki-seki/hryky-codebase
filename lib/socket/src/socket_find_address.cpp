/**
  @file     socket_find_address.cpp
  @brief    retains the preferable configuration in order to obtain an address.
  @author   HRYKY
  @version  $Id: socket_find_address.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/socket/socket_find_address.h"
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
hryky::socket::FindAddress::FindAddress()
	: host_()
	  , service_()
	  , flags_()
	  , family_(Family::Kind::unspec)
	  , socktype_(Socktype::Kind::any)
	  , protocol_(Protocol::Kind::any)
{
	((this->flags_
	  |= Aiflags::Kind::map_v4_to_v6)
	 |= Aiflags::Kind::addr_config);
}
/**
  @brief copy constructor.
 */
hryky::socket::FindAddress::FindAddress(this_type const & rhs)
	: hryky_copy_member(host)
	  , hryky_copy_member(service)
	  , hryky_copy_member(flags)
	  , hryky_copy_member(family)
	  , hryky_copy_member(socktype)
	  , hryky_copy_member(protocol)
{
}
/**
  @brief move constructor.
 */
hryky::socket::FindAddress::FindAddress(this_type && rhs)
	: hryky_move_member(host)
	  , hryky_move_member(service)
	  , hryky_move_member(flags)
	  , hryky_move_member(family)
	  , hryky_move_member(socktype)
	  , hryky_move_member(protocol)
{
}
/**
  @brief destructor.
 */
hryky::socket::FindAddress::~FindAddress()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::socket::FindAddress::clear()
{
	hryky::clear(this->protocol_);
	hryky::clear(this->socktype_);
	hryky::clear(this->family_);
	hryky::clear(this->flags_);
	hryky::clear(this->service_);
	hryky::clear(this->host_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::socket::FindAddress::swap(this_type & src)
{
	hryky_swap_member(host);
	hryky_swap_member(service);
	hryky_swap_member(flags);
	hryky_swap_member(family);
	hryky_swap_member(socktype);
	hryky_swap_member(protocol);
}
/**
  @brief assigns a new host.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::host(host_type && src)
{
	this->host_ = ::std::move(src);
	return *this;
}
/**
  @brief assigns a new host by null-terminated characters.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::host(char const * const src)
{
	this->host_ = src;
	return *this;
}
/**
  @brief assigns a new service.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::service(service_type && src)
{
	this->service_ = ::std::move(src);
	return *this;
}
/**
  @brief assigns a new service by null-terminated characters.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::service(char const * const src)
{
	this->service_ = src;
	return *this;
}
/**
  @brief assigns new flags.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::flags(flags_type && src)
{
	this->flags_ = ::std::move(src);
	return *this;
}
/**
  @brief assigns a new family.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::family(family_type && src)
{
	this->family_ = ::std::move(src);
	return *this;
}
/**
  @brief assigns the kind of the family.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::family(
	family_type::kind_type::raw_type const src)
{
	this->family_ = src;
	return *this;
}
/**
  @brief assigns a new socktype.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::socktype(socktype_type && src)
{
	this->socktype_ = ::std::move(src);
	return *this;
}
/**
  @brief assigns the kind of the socket type.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::socktype(
	socktype_type::kind_type::raw_type const src)
{
	this->socktype_ = src;
	return *this;
}
/**
  @brief assigns a new protocol.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::protocol(protocol_type && src)
{
	this->protocol_ = ::std::move(src);
	return *this;
}
/**
  @brief assigns the kind of the protocol.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::protocol(
	protocol_type::kind_type::raw_type const src)
{
	this->protocol_ = src;
	return *this;
}
/**
  @brief configures for the use as server.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::as_server()
{
	this->flags_ |= Aiflags::Kind::passive;
	this->host_.clear();
	return *this;
}
/**
  @brief configures for the use as client.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::as_client()
{
	this->flags_ ^= Aiflags::Kind::passive;
	return *this;
}
/**
  @brief specifies the names of both host and service are numeric.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::as_numeric()
{
	this->flags_ |= Aiflags::Kind::numeric_host;
	this->flags_ |= Aiflags::Kind::numeric_service;
	return *this;
}
/**
  @brief enumerates addresses as IPv6.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::as_ipv6()
{
	this->family_ = Family::Kind::inet6;
	return *this;
}
/**
  @brief enumerates addresses as IPv4.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::as_ipv4()
{
	this->family_ = Family::Kind::inet;
	return *this;
}
/**
  @brief enumerates addresses which are available with TCP.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::as_tcp()
{
	this->socktype_ = Socktype::Kind::stream;
	this->protocol_ = Protocol::Kind::tcp;
	return *this;
}
/**
  @brief enumerates addresses which are available with UDP.
 */
hryky::socket::FindAddress &
hryky::socket::FindAddress::as_udp()
{
	this->socktype_ = Socktype::Kind::dgram;
	this->protocol_ = Protocol::Kind::udp;
	return *this;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief configures a raw ai_hints.
 */
void hryky::socket::FindAddress::configure(addrinfo & hints)
{
	hints.ai_flags = this->flags_.raw();
	hints.ai_family = this->family_.raw();
	hints.ai_socktype = this->socktype_.raw();
	hints.ai_protocol = this->protocol_.raw();
	hints.ai_addrlen = 0;
	hints.ai_addr = hryky_nullptr;
	hints.ai_canonname = hryky_nullptr;
	hints.ai_next = hryky_nullptr;
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
