/**
  @file     socket_family.cpp
  @brief    retains an address family.
  @author   HRYKY
  @version  $Id: socket_family.cpp 345 2014-04-06 09:44:45Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/socket/socket_family.h"
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
hryky::socket::Family::tokens[
	hryky::socket::Family::Kind::num] = {
	hryky_literal_string(unspec),
	hryky_literal_string(inet),
	hryky_literal_string(inet6),
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
hryky::socket::Family::Family()
	: kind_()
{
}
/**
  @brief constrcts this instance with a value.
 */
hryky::socket::Family::Family(Kind::Raw const kind)
	: kind_(kind)
{
}
/**
  @brief constructs this instance with a raw address family.
 */
hryky::socket::Family::Family(raw_type const src)
	: kind_()
{
	switch (src) {
	case AF_UNSPEC:
		this->kind_ = Kind::unspec;
		break;
	case AF_INET:
		this->kind_ = Kind::inet;
		break;
	case AF_INET6:
		this->kind_ = Kind::inet6;
		break;
	default :
		hryky_log_err(
			"unsupported address family: " << src);
		break;
	}
}
/**
  @brief copy constructor.
 */
hryky::socket::Family::Family(this_type const & rhs)
	: hryky_copy_member(kind)
{
}
/**
  @brief move constructor.
 */
hryky::socket::Family::Family(this_type && rhs)
	: hryky_move_member(kind)
{
}
/**
  @brief destructor.
 */
hryky::socket::Family::~Family()
{
}
/**
  @brief assigns a new value.
 */
hryky::socket::Family &
hryky::socket::Family::operator=(Kind::Raw const rhs)
{
	this->kind_ = rhs;
	return *this;
}
/**
  @brief releases the internal resources.
 */
void hryky::socket::Family::clear()
{
	hryky::clear(this->kind_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::socket::Family::swap(this_type & src)
{
	hryky_swap_member(kind);
}
/**
  @brief retrieves the raw value of address family.
 */
hryky::socket::Family::raw_type hryky::socket::Family::raw() const
{
	switch (this->kind_.raw()) {
	case Kind::inet: return AF_INET;
	case Kind::inet6: return AF_INET6;
	case Kind::unspec: return AF_UNSPEC;
	default:
		hryky_log_err(
			"invalid address family: " << this->kind_.raw());
		return AF_UNSPEC;
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
