/**
  @file         uri_regname_entity.cpp
  @brief        retains the information about the 'reg-name' of URI.
  @author       HRYKY
  @version      $Id: uri_regname_entity.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/uri/uri_regname_entity.h"
#include "hryky/log.h"
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
namespace regname
{
namespace
{
} // namespace "anonymous"
} // namespace regname
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
hryky::uri::regname::Entity::Entity()
	: octets_()
{
}
/**
  @brief copy constructor.
 */
hryky::uri::regname::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(octets)
{
}
/**
  @brief move constructor.
 */
hryky::uri::regname::Entity::Entity(this_type && rhs)
	: hryky_move_member(octets)
{
}
/**
  @brief constructor.
 */
hryky::uri::regname::Entity::Entity(mempool_type const mempool)
	: octets_(mempool)
{
}
/**
  @brief constructor with octets.
 */
hryky::uri::regname::Entity::Entity(octets_type const & octets)
	: octets_(octets)
{
}
/**
  @brief destructor.
 */
hryky::uri::regname::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::uri::regname::Entity::clear()
{
	hryky::clear(this->octets_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::uri::regname::Entity::swap(this_type & src)
{
	hryky_swap_member(octets);
}
/**
  @brief appends a new octet to the end.
 */
bool hryky::uri::regname::Entity::append(octet_type const octet)
{
	return this->octets_.push_back(octet);
}
/**
  @brief appends an other regname to the end.
 */
bool hryky::uri::regname::Entity::append(this_type const & src)
{
	return this->octets_.insert(
		this->octets_.end(), src.octets_.begin(), src.octets_.end());
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
namespace regname
{
namespace
{
} // namespace "anonymous"
} // namespace regname
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
