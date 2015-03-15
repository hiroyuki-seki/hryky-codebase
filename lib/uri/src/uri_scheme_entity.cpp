/**
  @file         uri_scheme_entity.cpp
  @brief        retains the information about the 'scheme' part of URI.
  @author       HRYKY
  @version      $Id: uri_scheme_entity.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/uri/uri_scheme_entity.h"
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
namespace scheme
{
namespace
{
} // namespace "anonymous"
} // namespace scheme
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
hryky::uri::scheme::Entity::Entity()
	: kind_()
{
}
/**
  @brief constructor.
 */
hryky::uri::scheme::Entity::Entity(mempool_type const)
	: kind_()
{
}
/**
  @brief copy constructor.
 */
hryky::uri::scheme::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(kind)
{
}
/**
  @brief move constructor.
 */
hryky::uri::scheme::Entity::Entity(this_type && rhs)
	: hryky_move_member(kind)
{
}
/**
  @brief destructor.
 */
hryky::uri::scheme::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::uri::scheme::Entity::clear()
{
	hryky::clear(this->kind_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::uri::scheme::Entity::swap(this_type & src)
{
	hryky_swap_member(kind);
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
namespace scheme
{
namespace
{
} // namespace "anonymous"
} // namespace scheme
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
