/**
  @file         uri_authority_entity.cpp
  @brief        retains the information of an authority of URI.
  @author       HRYKY
  @version      $Id: uri_authority_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/swap.h"
#include "hryky/uri/uri_authority_entity.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace
{
} // namespace "anonymous"
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
hryky::uri::authority::Entity::Entity()
	: userinfo_()
	  , host_()
	  , port_()
{
}
/**
  @brief constructor.
 */
hryky::uri::authority::Entity::Entity(mempool_type mempool)
	: userinfo_(mempool)
	  , host_(mempool)
	  , port_()
{
}
/**
  @brief copy constructor.
 */
hryky::uri::authority::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(userinfo)
	  , hryky_copy_member(host)
	  , hryky_copy_member(port)
{
}
/**
  @brief move constructor.
 */
hryky::uri::authority::Entity::Entity(this_type && rhs)
	: hryky_move_member(userinfo)
	  , hryky_move_member(host)
	  , hryky_move_member(port)
{
}
/**
  @brief destructor.
 */
hryky::uri::authority::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::uri::authority::Entity::clear()
{
	hryky::clear(this->port_);
	hryky::clear(this->host_);
	hryky::clear(this->userinfo_);
}
/**
  @brief assigns a userinfo of URI.
 */
void hryky::uri::authority::Entity::userinfo(userinfo_type const & src)
{
	this->userinfo_ = src;
}
/**
  @brief assigns a new host of URI.
 */
void hryky::uri::authority::Entity::host(host_type const & src)
{
	this->host_ = src;
}
/**
  @brief assigns a port number of URI.
 */
void hryky::uri::authority::Entity::port(port_type const & src)
{
	this->port_ = src;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::uri::authority::Entity::swap(this_type & src)
{
	hryky_swap_member(userinfo);
	hryky_swap_member(host);
	hryky_swap_member(port);
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
namespace
{
} // namespace "anonymous"
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
