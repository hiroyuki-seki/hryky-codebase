/**
  @file     socket_aiflags.cpp
  @brief    retaints the combination of flags for getaddrinfo.
  @author   HRYKY
  @version  $Id: socket_aiflags.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/socket/socket_aiflags.h"
#include "hryky/clear.h"
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
hryky::socket::Aiflags::tokens[
	hryky::socket::Aiflags::Kind::num] = {
	hryky_literal_string(passive),
	hryky_literal_string(canonical_name),
	hryky_literal_string(numeric_host),
	hryky_literal_string(numeric_service),
	hryky_literal_string(both_v4_v6),
	hryky_literal_string(addr_config),
	hryky_literal_string(map_v4_to_v6),
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
hryky::socket::Aiflags::Aiflags()
	: flag_()
{
}
/**
  @brief constructs this instance with a raw ai_flags.
 */
hryky::socket::Aiflags::Aiflags(raw_type const src)
	: flag_()
{
	if (0 != (AI_PASSIVE & src)) {
		this->flag_.on(Kind::passive);
	}
	if (0 != (AI_CANONNAME & src)) {
		this->flag_.on(Kind::canonical_name);
	}
	if (0 != (AI_NUMERICHOST & src)) {
		this->flag_.on(Kind::numeric_host);
	}
	if (0 != (AI_NUMERICSERV & src)) {
		this->flag_.on(Kind::numeric_service);
	}
	if (0 != (AI_ALL & src)) {
		this->flag_.on(Kind::both_v4_v6);
	}
	if (0 != (AI_ADDRCONFIG & src)) {
		this->flag_.on(Kind::addr_config);
	}
	if (0 != (AI_V4MAPPED & src)) {
		this->flag_.on(Kind::map_v4_to_v6);
	}
}
/**
  @brief copy constructor.
 */
hryky::socket::Aiflags::Aiflags(this_type const & rhs)
	: hryky_copy_member(flag)
{
}
/**
  @brief move constructor.
 */
hryky::socket::Aiflags::Aiflags(this_type && rhs)
	: hryky_move_member(flag)
{
}
/**
  @brief destructor.
 */
hryky::socket::Aiflags::~Aiflags()
{
}
/**
  @brief enables a flag.
 */
hryky::socket::Aiflags &
hryky::socket::Aiflags::operator|=(Kind::Raw const kind)
{
	this->flag_.on(kind);
	return *this;
}
/**
  @brief disables a flag.
 */
hryky::socket::Aiflags & hryky::socket::Aiflags::operator^=(
	Kind::Raw const kind)
{
	this->flag_.off(kind);
	return *this;
}
/**
  @brief releases the internal resources.
 */
void hryky::socket::Aiflags::clear()
{
	hryky::clear(this->flag_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::socket::Aiflags::swap(this_type & src)
{
	hryky_swap_member(flag);
}
/**
  @brief retrieves the raw value of ai_flags.
 */
hryky::socket::Aiflags::raw_type hryky::socket::Aiflags::raw() const
{
	return (
		0
		| (this->flag_.test(Kind::passive) ? AI_PASSIVE : 0)
		| (this->flag_.test(Kind::canonical_name) ? AI_CANONNAME : 0)
		| (this->flag_.test(Kind::numeric_host) ? AI_NUMERICHOST : 0)
		| (this->flag_.test(Kind::numeric_service) ? AI_NUMERICSERV : 0)
		| (this->flag_.test(Kind::both_v4_v6) ? AI_ALL : 0)
		| (this->flag_.test(Kind::addr_config) ? AI_ADDRCONFIG : 0)
		| (this->flag_.test(Kind::map_v4_to_v6) ? AI_V4MAPPED : 0)
		);
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
