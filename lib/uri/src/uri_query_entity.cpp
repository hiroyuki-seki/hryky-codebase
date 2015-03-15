/**
  @file         uri_query_entity.cpp
  @brief        retains the information about the query part of URI.
  @author       HRYKY
  @version      $Id: uri_query_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/uri/uri_query_entity.h"
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
namespace query
{
namespace
{
} // namespace "anonymous"
} // namespace query
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
hryky::uri::query::Entity::Entity()
	: octets_()
{
}
/**
  @brief constructor.
 */
hryky::uri::query::Entity::Entity(mempool_type const mempool)
	: octets_(mempool)
{
}
/**
  @brief copy constructor.
 */
hryky::uri::query::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(octets)
{
}
/**
  @brief move constructor.
 */
hryky::uri::query::Entity::Entity(this_type && rhs)
	: hryky_move_member(octets)
{
}
/**
  @brief constructor with octets.
 */
hryky::uri::query::Entity::Entity(octets_type const & octets)
	: octets_(octets)
{
}
/**
  @brief destructor.
 */
hryky::uri::query::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::uri::query::Entity::clear()
{
	hryky::clear(this->octets_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::uri::query::Entity::swap(this_type & src)
{
	hryky_swap_member(octets);
}
/**
  @brief appends an octet.
 */
bool hryky::uri::query::Entity::append(octet_type const src)
{
	return this->octets_.push_back(src);
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
namespace query
{
namespace
{
} // namespace "anonymous"
} // namespace query
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
