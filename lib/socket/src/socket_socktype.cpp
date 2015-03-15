/**
  @file     socket_socktype.cpp
  @brief    retains a socket type. e.g. stream or datagram.
  @author   HRYKY
  @version  $Id: socket_socktype.cpp 345 2014-04-06 09:44:45Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/socket/socket_socktype.h"
#include "hryky/clear.h"
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
} // namespace "anonymous"
} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// static variable
//------------------------------------------------------------------------------
hryky::LiteralString<> const
hryky::socket::Socktype::tokens[
	hryky::socket::Socktype::Kind::num] = {
	hryky_literal_string(any),
	hryky_literal_string(stream),
	hryky_literal_string(dgram),
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
hryky::socket::Socktype::Socktype()
	: kind_()
{
}
/**
  @brief constructs this instance with a value.
 */
hryky::socket::Socktype::Socktype(Kind::Raw const kind)
	: kind_(kind)
{
}
/**
  @brief constructs this instance with a raw socket type.
 */
hryky::socket::Socktype::Socktype(raw_type const src)
	: kind_()
{
	switch (src) {
	case 0:
		this->kind_ = Kind::any;
		break;
	case SOCK_STREAM:
		this->kind_ = Kind::stream;
		break;
	case SOCK_DGRAM:
		this->kind_ = Kind::dgram;
		break;
	default:
		hryky_log_err(
			"unsupported socket type: " << src);
		break;
	}
}
/**
  @brief copy constructor.
 */
hryky::socket::Socktype::Socktype(this_type const & rhs)
	: hryky_copy_member(kind)
{
}
/**
  @brief move constructor.
 */
hryky::socket::Socktype::Socktype(this_type && rhs)
	: hryky_move_member(kind)
{
}
/**
  @brief destructor.
 */
hryky::socket::Socktype::~Socktype()
{
}
/**
  @brief assigns a new kind.
 */
hryky::socket::Socktype &
hryky::socket::Socktype::operator=(
	Kind::Raw const src)
{
	this->kind_ = src;
	return *this;
}
/**
  @brief releases the internal resources.
 */
void hryky::socket::Socktype::clear()
{
	hryky::clear(this->kind_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::socket::Socktype::swap(this_type & src)
{
	hryky_swap_member(kind);
}
/**
  @brief retrieves the raw value of socket type.
 */
hryky::socket::Socktype::raw_type hryky::socket::Socktype::raw() const
{
	switch (this->kind_.raw()) {
	case Kind::stream: return SOCK_STREAM;
	case Kind::dgram: return SOCK_DGRAM;
	case Kind::any: return 0;
	default:
		hryky_log_err(
			"invlaid socket type: " << this->kind_.raw());
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
