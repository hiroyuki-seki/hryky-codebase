/**
  @file         uri_host_entity.cpp
  @brief        retains the information about the 'host' of URI.
  @author       HRYKY
  @version      $Id: uri_host_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/uri/uri_host_entity.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
namespace host
{
namespace
{
} // namespace "anonymous"
} // namespace host
} // namespace uri
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
hryky::uri::host::Entity::Entity()
	: ipv4_()
	  , ipv6_()
	  , ipvf_()
	  , regname_()
{
}
/**
  @brief copy constructor.
 */
hryky::uri::host::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(ipv4)
	  , hryky_copy_member(ipv6)
	  , hryky_copy_member(ipvf)
	  , hryky_copy_member(regname)
{
}
/**
  @brief move constructor.
 */
hryky::uri::host::Entity::Entity(this_type && rhs)
	: hryky_move_member(ipv4)
	  , hryky_move_member(ipv6)
	  , hryky_move_member(ipvf)
	  , hryky_move_member(regname)
{
}
/**
  @brief constructor.
 */
hryky::uri::host::Entity::Entity(mempool_type const mempool)
	: ipv4_()
	  , ipv6_()
	  , ipvf_()
	  , regname_(mempool)
{
}
/**
  @brief destructor.
 */
hryky::uri::host::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::uri::host::Entity::clear()
{
	hryky::clear(this->regname_);
	hryky::clear(this->ipvf_);
	hryky::clear(this->ipv6_);
	hryky::clear(this->ipv4_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::uri::host::Entity::swap(this_type & src)
{
	hryky_swap_member(ipv4);
	hryky_swap_member(ipv6);
	hryky_swap_member(ipvf);
	hryky_swap_member(regname);
}
/**
  @brief assigns a reg-name of URI.
 */
void hryky::uri::host::Entity::regname(regname_type const & src)
{
	this->regname_ = src;
}
/**
  @brief assigns a IPv4address of URI.
 */
void hryky::uri::host::Entity::ipv4(ip::v4_type const & src)
{
	this->ipv4_ = src;
}
/**
  @brief assigns a IPv6address of URI.
 */
void hryky::uri::host::Entity::ipv6(ip::v6_type const & src)
{
	this->ipv6_ = src;
}
/**
  @brief assigns a new IP address of future version.
 */
void hryky::uri::host::Entity::ipvf(ip::vf_type const & src)
{
	this->ipvf_ = src;
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
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
namespace host
{
namespace
{
} // namespace "anonymous"
} // namespace host
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
