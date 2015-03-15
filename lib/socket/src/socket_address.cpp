/**
  @file     socket_address.cpp
  @brief    retains the informaton of each node.
  @author   HRYKY
  @version  $Id: socket_address.cpp 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/socket/socket_address.h"
#include "hryky/clear.h"
#include "hryky/log/log_definition.h"
#include "hryky/is_null.h"
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
hryky::socket::Address::Address()
	: canonname_()
	  , sockaddr_()
	  , family_()
	  , socktype_()
	  , protocol_()
{
}
/**
  @brief constructs this instance with a raw addrinfo.
 */
hryky::socket::Address::Address(addrinfo const & src)
	: canonname_()
	  , sockaddr_()
	  , family_(src.ai_family)
	  , socktype_(src.ai_socktype)
	  , protocol_(src.ai_protocol)
{
	if (!hryky_is_null(src.ai_canonname)) {
		this->canonname_ = src.ai_canonname;
	}

	if (!hryky_is_null(src.ai_addr)) {
		this->sockaddr(
			reinterpret_cast<sockaddr_type::const_pointer>(
				src.ai_addr),
			reinterpret_cast<sockaddr_type::const_pointer>(
				src.ai_addr) + src.ai_addrlen);
	}
}
/**
  @brief copy constructor.
 */
hryky::socket::Address::Address(this_type const & rhs)
	: hryky_copy_member(canonname)
	  , hryky_copy_member(sockaddr)
	  , hryky_copy_member(family)
	  , hryky_copy_member(socktype)
	  , hryky_copy_member(protocol)
{
}
/**
  @brief move constructor.
 */
hryky::socket::Address::Address(this_type && rhs)
	: hryky_move_member(canonname)
	  , hryky_move_member(sockaddr)
	  , hryky_move_member(family)
	  , hryky_move_member(socktype)
	  , hryky_move_member(protocol)
{
}
/**
  @brief destructor.
 */
hryky::socket::Address::~Address()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::socket::Address::clear()
{
	hryky::clear(this->protocol_);
	hryky::clear(this->socktype_);
	hryky::clear(this->family_);
	hryky::clear(this->sockaddr_);
	hryky::clear(this->canonname_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::socket::Address::swap(this_type & src)
{
	hryky_swap_member(canonname);
	hryky_swap_member(sockaddr);
	hryky_swap_member(family);
	hryky_swap_member(socktype);
	hryky_swap_member(protocol);
}
/**
  @brief retrieves the information of socket address.
 */
hryky::socket::Address::sockaddr_type const & 
hryky::socket::Address::sockaddr() const
{
	return this->sockaddr_;
}
/**
  @brief retrieves the address family.
 */
hryky::socket::Address::family_type const & 
hryky::socket::Address::family() const
{
	return this->family_;
}
/**
  @brief retrieves the socket type.
 */
hryky::socket::Address::socktype_type const & 
hryky::socket::Address::socktype() const
{
	return this->socktype_;
}
/**
  @brief retrieves the protocol.
 */
hryky::socket::Address::protocol_type const & 
hryky::socket::Address::protocol() const
{
	return this->protocol_;
}
/**
  @brief assigns a new family.
 */
void hryky::socket::Address::family(family_type const & src)
{
	this->family_ = src;
}
/**
  @brief assigns a new socktype.
 */
void hryky::socket::Address::socktype(socktype_type const & src)
{
	this->socktype_ = src;
}
/**
  @brief assigns a new protocol.
 */
void hryky::socket::Address::protocol(protocol_type const & src)
{
	this->protocol_ = src;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
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
