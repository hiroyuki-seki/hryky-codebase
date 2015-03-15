/**
  @file     socket_protocol.cpp
  @brief    retains a protocol. e.g. TCP or UDP.
  @author   HRYKY
  @version  $Id: socket_protocol.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/socket/socket_protocol.h"
#include "hryky/clear.h"
#include "hryky/log.h"
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
hryky::LiteralString<> const
hryky::socket::Protocol::tokens[
	hryky::socket::Protocol::Kind::num] = {
	hryky_literal_string(any),
	hryky_literal_string(tcp),
	hryky_literal_string(udp),
};
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
hryky::socket::Protocol::Protocol()
	: kind_()
{
}
/**
  @brief constructs this instance with a value.
 */
hryky::socket::Protocol::Protocol(Kind::Raw const kind)
	: kind_(kind)
{
}
/**
  @brief constructs this instance with a raw protocol.
 */
hryky::socket::Protocol::Protocol(raw_type const src)
	: kind_()
{
	switch (src) {
	case 0:
		this->kind_ = Kind::any;
		break;
	case IPPROTO_TCP:
		this->kind_ = Kind::tcp;
		break;
	case IPPROTO_UDP:
		this->kind_ = Kind::udp;
		break;
	default :
		hryky_log_err(
			"unsupported protocol: " << src);
		break;
	}
}
/**
  @brief copy constructor.
 */
hryky::socket::Protocol::Protocol(this_type const & rhs)
	: hryky_copy_member(kind)
{
}
/**
  @brief move constructor.
 */
hryky::socket::Protocol::Protocol(this_type && rhs)
	: hryky_move_member(kind)
{
}
/**
  @brief destructor.
 */
hryky::socket::Protocol::~Protocol()
{
}
/**
  @brief assigns a new kind.
 */
hryky::socket::Protocol &
hryky::socket::Protocol::operator=(
	Kind::Raw const src)
{
	this->kind_ = src;
	return *this;
}
/**
  @brief releases the internal resources.
 */
void hryky::socket::Protocol::clear()
{
	hryky::clear(this->kind_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::socket::Protocol::swap(this_type & src)
{
	hryky_swap_member(kind);
}
/**
  @brief retrieves the raw value of protocol.
 */
hryky::socket::Protocol::raw_type hryky::socket::Protocol::raw() const
{
	switch (this->kind_.raw()) {
	case Kind::tcp: return IPPROTO_TCP;
	case Kind::udp: return IPPROTO_UDP;
	case Kind::any: return 0;
	default :
		hryky_log_err(
			"invalid protocol: " << this->kind_.raw());
		return 0;
	}
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
