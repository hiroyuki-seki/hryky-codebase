/**
  @file         uri_userinfo_entity.cpp
  @brief        retains the information about the 'userinfo' of URI.
  @author       HRYKY
  @version      $Id: uri_userinfo_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/uri/uri_userinfo_entity.h"
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
namespace userinfo
{
namespace
{
} // namespace "anonymous"
} // namespace userinfo
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
hryky::uri::userinfo::Entity::Entity()
	: octets_()
{
}
/**
  @brief copy constructor.
 */
hryky::uri::userinfo::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(octets)
{
}
/**
  @brief move constructor.
 */
hryky::uri::userinfo::Entity::Entity(this_type && rhs)
	: hryky_move_member(octets)
{
}
/**
  @brief constructor.
 */
hryky::uri::userinfo::Entity::Entity(mempool_type const mempool)
	: octets_(mempool)
{
}
/**
  @brief constructor with octets.
 */
hryky::uri::userinfo::Entity::Entity(octets_type const & octets)
	: octets_(octets)
{
}
/**
  @brief destructor.
 */
hryky::uri::userinfo::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::uri::userinfo::Entity::clear()
{
	hryky::clear(this->octets_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::uri::userinfo::Entity::swap(this_type & src)
{
	hryky_swap_member(octets);
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
namespace userinfo
{
namespace
{
} // namespace "anonymous"
} // namespace userinfo
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
